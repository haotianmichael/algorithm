#include <iostream>
#include <algorithm>
#include <cstring>


using namespace std;



/*
   debug_allocator 
    

 */
//该分配器并不自己分配内存，仅仅是对申请的内存做一些处理(增)然后调用其他的分配进行分配
/*
template<typaname _Alloc>
class debug_allocator{
    private:
        size_type _M_extra;
        _Alloc _M_allocator;  //自己包裹起来的分配器

        size_type _S_extra() {  //计算extra(bytes)相当于几个元素
            const size_t __obj_size = sizeof(value_type);
            return(sizeof(size_type) + __obj_size - 1) / obj_size;
        }

    public:
        debug_allocator(const _Alloc& __a) : _M_allocator(__a), _M_extra(_S_extra){}


        pointer allocate(size_type __n) {
            Pointer _res = _M_allocate(n + _M_extra);
            size_type* __ps = reinterpret_cast<size_type*>(__res);
            *__ps = __n;
            return __res + _M_extra;
        }

        void deallocate(pointer __p, size_type _n) {
            ...
        }

}

*/ 
int main(void)
{

    return 0;
}
