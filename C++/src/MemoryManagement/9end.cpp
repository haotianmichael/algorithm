#include <iostream>
#include <algorithm>
#include <cstring>
#include <cassert>

using namespace std;


/*
   1. new_handler
    当operator new没有能力分配出锁申请的memory，会抛出一个std::bad_alloc的exception或者返回0
     
    编译器会在抛出异常之前，会不断调用一个可有client指定的handler:
        typedef void(*new_handler)();
        new_handler set_new_handler(new_handler p) throw();  //标准库提供的函数原型
    设计良好的new handler只有两个选择:
        让更多内存可用&&调用abort()&&exit()



    2. =default,  =delete    
        delete表示删除函数(不能生成函数实例)
        default函数的默认版本(拷贝构造，拷贝赋值，析构函数, operator new/new[], operator delete/delete[])


*/

void noMoreMemory() {
    cout << "out of memory";
    abort();
}

/*

   set_new_handler VC6简略实现
new_handler set_new_handler(new_handler new_p) {

    //cannot use stbu to register a new handler
    assert(new_p == 0);
    //remove current handler
    _set_new_handler(0);
    return 0;
}

*/
int main(void)
{
    set_new_handler(noMoreMemory);    

    //胆小……不敢试:) 
    /*
    int *p = new[10000]; 
    assert(p); 
    */


    return 0;
}
