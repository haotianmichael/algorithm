#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

/*
    为类写内存分配器,目的在于
    a. 提高分配速度
    b. 降低空间浪费率
    通过Screen和Screen_new两个类来测试重载operator new对cookie的影响

    结论: Clang两个版本都不带cookie,大小和间隔都是16
          GCC 分配区别明显

    注意: 在写程序的时候，一定要注意virtual机制带来的内存浪费

    优点: 内存池，减少malloc调用次数
    缺点: 引入next指针,没有调用free
*/
class Screen{
    public:
        Screen(long x) : i(x){}
        ~Screen() {}
        int get() {return i;}

    private:
        Screen* next;
        static Screen* freeStore;
        static const int screenChunk;
    private:
        long i;
};
class Screen_override
{
public:
    Screen_override (int x) : i(x) {}
    ~Screen_override () {}
    int get() {return i;}

    //重载
    static void* operator new(size_t);
    static void operator delete(void*, size_t);
private:
    Screen_override* next;
    static Screen_override* freeStore;
    static const int screenChunk;
private:
    int i;
};
Screen_override* Screen_override::freeStore = 0;  //最开始的头结点
const int Screen_override::screenChunk = 5;

/*
    @operator new
    逻辑是当freeStore空的时候分配24个
    当freeStore不空的时候，从Chunk中取next
*/
void *Screen_override::operator new(size_t size) {  //size为元素大小,一次分配24个

    Screen_override* p;
    if(!freeStore) {
        //linked list 是空的，申请一大块
        size_t chunk = screenChunk* size;
        freeStore = p = reinterpret_cast<Screen_override*>(new char[chunk]);

        //将这一块分割成片，当做linked list串接起来
        for(; p != &freeStore[screenChunk - 1]; ++p) {
            p->next =  p + 1; 
        }
        p->next = 0;
    }
    p = freeStore;
    freeStore = freeStore->next;
    return p;
}


/*
   将deleted object 插回到free list前端
*/
void Screen_override::operator delete(void* p, size_t) {

    (static_cast<Screen_override*>(p))->next = freeStore;
    freeStore = static_cast<Screen_override*>(p);
}


//测试不重载operator new，分配内存带cookie
void TEST_WITH_COOKIE(){
    
    cout << endl << "TEST_WITH_COOKIE" << endl;
    //16字节，4(int) +8(Screen*) +4(Alignment) ; static 成员变量并不算在对象中
    cout << "size of Screen: " << sizeof(Screen)  << endl;

    int const N = 100;
    Screen* p[N];
    for(int i = 0; i < N; i ++) {
        p[i] = new Screen(i); 
    }

    for(int i =0 ; i < 10; i ++) {
        cout << p[i] << endl; 
    }

    for(int i = 0;i < N; i ++){
        delete p[i]; 
    }
    return;
}


//重载operator new, 分配内存不带cookie
void TEST_NO_COOKIE(void)
{

    cout << endl << "TEST_NO_COOKIE...." << endl;
    //16字节
    cout  << "size of Screen_override: " << sizeof(Screen_override) << endl;

    int  const N = 100;
    Screen_override* p[N];

    for(int i =0 ; i < N; i ++) {
        p[i] = new Screen_override(i); 
    }


    for(int i =0 ; i < 10; i ++) {
        cout << p[i] << endl;    
    }
    
    for(int i =0 ; i < N; i ++) {
        delete p[i]; 
    }
    return;
}


int main(void)
{
    
    //cout << sizeof(int) << endl;
    //cout << sizeof(Screen*) << endl;
    TEST_WITH_COOKIE();

    TEST_NO_COOKIE();
    return 0;
}
