#include <iostream>
#include <algorithm>
#include <cstring>


using namespace std;


/*
   重载全局operator new/delete 
 */
void* myAlloc(size_t size) {
    return malloc(size);
}

void myFree(void* ptr) {
    return free(ptr);
}

void* operator new(size_t size) {
    cout << "global new()" << endl;
    return myAlloc(size);
}

void* operator new[](size_t size) {
    cout << "global new[]()" << endl;
    return myAlloc(size);
}

void operator delete(void* ptr) noexcept{
    cout << "global delete()" << endl;
    return myFree(ptr);
}

void operator delete[](void* ptr) noexcept{
    cout << "global delete[]()" << endl;
    myFree(ptr);
}

/*
   重载类内operator new/delete
 */
class Foo{
    public:
        int _id;
        long _data;
        string _str;
    public:
        Foo() : _id(0) {
            cout << "default ctor. this = " << this << "id = " << _id << endl; 
        }

        Foo(int i) : _id(i) {
            cout << "ctor.this = " << this << "id = " << _id << endl; 
        }
        ~Foo() {
            cout << "dtor.this = " << this << " id = " << _id << endl; 
        }

        //这里需要静态函数, 无法通过对象调用该函数
        static void *operator new(size_t size){
            Foo *p = (Foo*) malloc(size); 
            cout << "Foo new()" << endl;
            return p;
        }
        static void operator delete(void* pdead, size_t) {
            cout << "Foo delete()" << endl; 
            free(pdead);
        }

        static void* operator new[](size_t size){
            Foo* p = (Foo*)malloc(size); 
            cout << "Foo new()" << endl;
            return p;
        }
            
        void operator delete[] (void * pdead, size_t) {
            cout << "Foo delete()" << endl;
            free(pdead); 
        }
};



void TEST_LOCAL_OPERATOR_NEW(void)
{
    
    cout << "sizeof(Foo) is: " << sizeof(Foo) << endl;;
    Foo* p = ::new Foo(7);  //全局作用域
    ::delete p;

    Foo* pArray  = ::new Foo[5];
    ::delete [] pArray;

    return ;
}

void TEST_GLOBAL_OPERATOR_NEW(void) {

    
    cout << "sizeof(Foo) is: " << sizeof(Foo) << endl;;
    Foo* p = new Foo(7);  //局部作用域
    delete p;

    Foo* pArray  = new Foo[5];
    delete [] pArray;

    return ;
}

int main(void)
{
    int op;
    cout << "op 1 ——> LOCAL, op 2 ——> GLOBAL;" << endl;
    cin >> op;
    if(op) {
        TEST_LOCAL_OPERATOR_NEW() ;
    }else {
        TEST_GLOBAL_OPERATOR_NEW();
    }
    return 0;
}
