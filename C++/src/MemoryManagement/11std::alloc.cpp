#include <algorithm>
#include <iostream>



using namespace std;

#define __THROW_BAD_ALLOC \
    cerr << "out of memory";\
    exit(1);

/*******************************************
    第一级分配器:
        从GNU4.9放弃使用,实际意义不是很大 
        第二级失败，第一级模拟new_handler
*******************************************/
template<int inst>
class __malloc_alloc_template{
    private:
        
        static void* oom_malloc(size_t);
        static void* oom_realloc(void*, size_t);
        //指向new_handler
        static void (*__malloc_alloc_oom_handler)();
    public:
        static void* allocate(size_t size) {
            
            void* result = malloc(size);   //直接调用malloc()
            if(0 == result) result = oom_malloc(size);
            return result;
        }

        static void deallocate(void* p, size_t) {

            free(p);  //直接调用free()
        }

        static void* reallocate(void* p, size_t, size_t new_size) {

            void* result = realloc(p, new_size);   //直接使用realloc()
            if(0 == result) result = oom_realloc(p, new_size);
            return result; 
        }

        /*
            等同于typedef void (*H)() static H set_malloc_handler(H f);其中H是一个函数指针
            标准库提供的函数签名是
                typedef void(*new_handler)()
                    new_handler set_new_handler(new_handler p) throw();
         
        */
        static void (*set_malloc_handler(void (*f)())) () {
        
            //类似C++的set_new_handler
            void (*old)() = __malloc_alloc_oom_handler; //记录原new-handler
            __malloc_alloc_oom_handler = f;  //将f记住以便日后可调用
            return (old); //将原先的handler传回
        }
} ;

template<int inst>
void (* __malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;

template<int inst>
void* __malloc_alloc_template<inst>::oom_malloc(size_t size) {
        
    void (*my_malloc_handler)();
    void* result;


    for(; ;) {   //不断尝试释放，分配，在释放，在分配...

        my_malloc_handler = __malloc_alloc_oom_handler; 
        if(0 == my_malloc_handler) {__THROW_BAD_ALLOC;} 
        (*my_malloc_handler) ();  //呼叫handler, 企图释放memory
        result = malloc(size);   //再次尝试分配memory
        if(result) return result;
    }
}

template<int inst>
void* __malloc_alloc_template<inst>::oom_realloc(void* p, size_t size) {

    void (*my_malloc_handler)();
    void* result;

    for(; ; ) {  
         
        my_malloc_handler = __malloc_alloc_oom_handler;    
        if(0 == my_malloc_handler) {__THROW_BAD_ALLOC;} 
        (*my_malloc_handler)();  //呼叫handler, 企图释放memory
        result = realloc(p, size);  //再次尝试分配memory
        if(result) return result;
    }
}
typedef __malloc_alloc_template<0> malloc_alloc;

//将分配单位由bytes转换成为元素个数
template<class T, class Alloc>
    class simple_alloc{

    public:
        static  T* allocate(size_t size) {   //一次分配size个Tobject
            return 0 == size ? 0 : (T*)Alloc::allocate(size * sizeof(T)); 
        }

        static T* allocate(void) {   //一次分配一个T对象
            return static_cast<T*> (Alloc::allocate(sizeof(T)));
        }


        static void deallocate(T* p, size_t size) {   //一次释放size个Tobject
            if(0 != size) Alloc::deallocate(p); 
        }

        static void deallocate(T* p) {   //一次释放一个Tobject
            Alloc::deallocate(p);
        }
};

/*
template<class T, class Alloc = alloc>
class vector{
    protected:
        typedef simple_alloc<T, Alloc> data_allocator;

        result = data_allocator::allocate();

        data_allocator::deallocate(result);
};
*/



/******************************
    第二级分配器 
*******************************/

//enum {__ALLGN = 8};   //上调边界
//enum {__MAX_BYTES = 128};   //分配chunk的上限
//enum {__NFREELISTS = __MAX_BYTES / __ALLGN};  //链表的条数
static const int __ALLGN = 8;
static const int __MAX_BYTES = 8;
static const int __NFREELISTS = __MAX_BYTES / __ALLGN;

template<bool threads, int inst>
class __default_alloc_template{
    private:
        static size_t ROUND_UP(size_t bytes) {  //向上取整8
            return (bytes + __ALLGN - 1) & ~(__ALLGN - 1); 
        }

    private:
        union obj{
            union obj* free_list_link; 
        };  //改用struct亦可

    private:
        static obj* volatile free_list[__NFREELISTS];
        static size_t FREELIST_INDEX(size_t bytes) {   //根据size选择指针
            return ((bytes + __ALLGN - 1) / __ALLGN - 1); 
        }

        //Returns an object size n, andn optionally adds to size n free list.
        static void *refill(size_t size);  //填充free list并返回一个区块的(其实就是第一个)起始地址

        //Allocate a chunk for nobjs of size "size". nobjs may be reduced
        //if it is inconvenient to allocate the requestd number.
        static char* chunk_alloc(size_t size, int &nobjs);

        //Chunk allocationn state  战备池
        static char* start_free;  //指向pool的头
        static char* end_free;  //指向pool的尾
        static size_t heap_size;   //分配累积量

    public:
        static void* allocate(size_t size) {
            obj* volatile *my_free_list;        
            obj* result;

            if(size > (size_t)__MAX_BYTES)   //大于128改用第一级
                return (malloc_alloc::allocate(size));
        
            my_free_list = free_list + FREELIST_INDEX(size);  //定位
            result = *my_free_list;
            if(result == 0) {   //list为空  第一次或者如果备战池都用光了，则result = nullptr
                void* t = refill(ROUND_UP(size));   //充值
                return t;
            }
            
            //list内已有可用区块
            *my_free_list = result->free_list_link; 
            
            return (result);
        }


        /*
            如果P并非当初从alloc取得，仍可并入alloc不是很好，如果p所指大小不是8个倍数则更不好 
            释放器并没有将收回的内存还给操作系统,但不算内存泄漏
        */
        static void deallocate(void* p, size_t size) {
            obj* q = (obj*)p;        
            obj* volatile* my_free_list;

           if(size >static_cast<size_t>(__MAX_BYTES))  {
               malloc_alloc::deallocate(p, size);   //大于128 改用第一级分配器
               return;
           }
           my_free_list = free_list + FREELIST_INDEX(size);  //定位
           q->free_list_link = *my_free_list;
           *my_free_list = q;
        }


        static void* reallocate(void* p, size_t old_size, size_t new_sz);

};
/*
    Returns an object of size n, and optionally adds to size n free list.
    We assume that n is properly aligned. we hold the allocation lock. 
*/
template<bool threads, int inst>
void* __default_alloc_template<threads, inst>::refill(size_t size) { //size已调整为8的倍数

    int nobjs = 20;  //预设取20个区块(不一定)
    char *chunk  = chunk_alloc(size, nobjs);   //获取一大块内存  不一定是20个，如果战备池为零，则重新分配20个chunk,而如果备战池里有内存资源则可能直接分配少于20个chunk
    obj* volatile* my_free_list;
    obj* result;
    obj* current_obj;
    obj* next_obj;

    if(1 == nobjs) return (chunk);  //还有分配了一个的话，直接交给客户

    //以下开始将所有chunk区块挂上free-list
    my_free_list = free_list + FREELIST_INDEX(size);  
    //在chunk内建立一个自由链表
    /*
        所谓切割就是将指针所指转型为Obj 
    */
    result = (obj*)chunk;
    *my_free_list = next_obj = (obj*)(chunk + size);
    for(int i = 1; ; i ++) {  
        current_obj = next_obj;
        next_obj = (obj*)((char*)next_obj + size); 
        if(nobjs -1 == i) {  //最后一个
            current_obj->free_list_link = 0;     
            break;
        }else {
            current_obj->free_list_link = next_obj; 
        }
    }
    
    return result;
}

/*
    We allocate memory in large chunks inn order to avoid fragmenting the malloc
   heap too much, We assume that size is properly aligned.
    We hold the allocation lock. 
*/
template<bool threads, int inst>
char* __default_alloc_template<threads, inst>::chunk_alloc(size_t size, int& nobjs) {

    char* result;
    size_t total_bytes = size * nobjs;
    size_t bytees_left = end_free - start_free;
    
    if(bytees_left >= total_bytes) {  //pool空间足以满足需求

        result = start_free;
        start_free += total_bytes;
        return(result); 
    }else if(bytees_left >= size) {  //pool空间只满足一块以上
        
        nobjs = bytees_left / size;   //改变需求个数
        total_bytes  = size * nobjs;  //改变需求总量   pass-by-value会改变参数
        result = start_free;
        start_free += total_bytes;
        return (result); 
    }else {   //pool空间不足以满足一块需求  碎片&&0

        //打算从system free-store上去这么多来充值
        size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
        //处理碎片(将其挂到相应的chunk指针端口)
        if(bytes_to_get > 0) {
            obj* volatile *my_free_list =   //重新定位碎片的指针
               free_list + FREELIST_INDEX(bytees_left); 
            ((obj*)start_free)->free_list_link = *my_free_list;
            *my_free_list = (obj*)start_free; 
        }

        //从system free-store中取
        start_free = (char*)malloc(bytes_to_get); 
        if(0 == start_free) {  //如果当前的chunk分配失败，则向上继续找相邻的chunk继续分配
            obj* volatile *my_free_list, *p;
            for(int i = size; i <= __MAX_BYTES; i += __ALLGN) {
                my_free_list = free_list + FREELIST_INDEX(i); 
                p = *my_free_list;
                if(0 != p) {  //该free-list有可用区块
                    *my_free_list = p->free_list_link; 
                    start_free  = (char*)p;
                    end_free = start_free + i; 
                    return (chunk_alloc(size, nobjs));   //结果再试一次
                }
            }
            end_free = 0;
            start_free = (char*)malloc_alloc::allocate(bytes_to_get); 
        }

        //至此，表示已经从system free-store成功取得很多memory
        heap_size += bytes_to_get;
        end_free = start_free + bytes_to_get;
        return (chunk_alloc(size, nobjs));   //战备池有内存了，所以递归重新处理分配逻辑
    }
}

//静态定义(分配内存)
template<bool threads, int inst>
char* __default_alloc_template<threads, inst>::start_free = 0;


template<bool threads, int inst>
char* __default_alloc_template<threads, inst>::end_free = 0;

template<bool threads, int inst>
size_t __default_alloc_template<threads, inst>::heap_size = 0;


template<bool threads, int inst>
__default_alloc_template<threads, inst>::obj* volatile
__default_alloc_template<threads, inst>::free_list[__NFREELISTS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


//std::alloc为第二级分配器
typedef  __default_alloc_template<false, 0> alloc;


int main(void)
{
    
    return 0;
}
