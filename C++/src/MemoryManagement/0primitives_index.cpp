#include <iostream>
#include <complex>
#include <memory>




using namespace std;


/*
    
   1. Primitives
        不同的OS和编译器有不同的实现 
        malloc/free
        new/delete
        operator new/operator delete
        std::allocator<T>/std::deallocate<T>
*/


void primitives_sample() {



    //CRT运行时函数
    void *p1 = malloc(512);
    free(p1);


    //new
    complex<int>* p2 = new complex<int>;
    delete p2;

    //::operator new(全局函数,可被重载)
    void* p3 = ::operator new(sizeof(int));   //内部调用malloc
    ::operator delete(p3);   //内部调用delete


    // allocator分配器(STL容器分配内存的方式)
    void* p4 = allocator<int>().allocate(7);
    allocator<int>().deallocate((int*)p4, 7);

    return;
}





int main(void)
{
    primitives_sample();
    return 0;
}
