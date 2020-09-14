#include <iostream>
#include <algorithm>
#include <cstring>
#include <exception>


using namespace std;



/*
 
    重载new()/delete()

  a. 可以重载class member operator new(), 写出很多版本，前提是每天一版本的额声明
  都必须具有独特的参数列，其中第一参数必须是size_t, 其余参数以new指定的placement 
  arguments为初值。出现于new()小括号内的便是所谓的placement arguments 
 
  b. 可以重载class member operator delete(), 但它们绝不会被delete调用。只有当new所谓
  的ctor抛出exception，才会调用这些重载版本的operator delete()。
        经验证：Clang9.0.0并不会调用operator delete
 

  c. operator new和placement new

    两个都是重载operator new()这个函数签名
    但是operator new的参数是operator new(size_t size)
    而placement new的参数是operator new(size_t size, void* ptr);

  d. new(p)就是placement new
    被称为定点new, 而功能是并不分配内存  

   
*/
class Bad{
};
class Foo{

    public:
        Foo() {
            cout << "Foo:::Foo()" << endl; 
        }

        Foo(int ) {
            cout << "Foo::Foo(int)" << endl;
            throw Bad(); 
        }

        //一般的operator new()的重载
        void* operator new(size_t size) {
            cout << "operator new(size_t)" << endl;
            return malloc(size); 
        }

        //标准库已提供的placement new()的重载
        //当ctor发出异常，下面对应的operator delete就会被调用(其作用就是释放相应的内存)
        void* operator new(size_t size, void * start) {
            cout << "operator nen(size_t, void*)" << endl;
            return start; 
        }

        void* operator new(size_t size, long extra) {
            cout << "operator new(size_t, long)" << endl;
            return malloc(size + extra); 
        }

        void* operator new(size_t size, long extra, char init) {
            cout << "operator new(size_t, long, char)" << endl;
            return malloc(size + extra); 
        }


        //相应的delete重载函数
        void operator delete(void*, size_t size) {
            cout << "operator delete(void*, size_t)" << endl;
        } 

        void operator delete(void*, void*) {
            cout << "operator delete(void*, void*)" << endl; 
        }

        void operator delete(void*, long) {
            cout << "operator delete(void*, long)" << endl; 
        }

        void operator delete(void*, long, char) {
            cout << "operator delete(void*, long, char)" << endl; 
        }

    private:
        int m_i;
};


int main(void)
{
    //Foo start;   //对应new expression
    //Foo* p1 = new Foo;  //对应operator new()+默认构造
    //Foo* p2 = new (&start)Foo;   //对应operator new(size_t, char*)+默认构造
    //Foo* p3 = new(100)Foo;  //对应operator new(size_t, long)+默认构造
    //Foo* p4 = new(100, 'a')Foo();  //对应operator new(size_t, long, char)+默认构造

    //构造函数内部抛出异常，会调相应的operator delete()
    Foo* p5 = new(100)Foo(1);  //对应operator new(size_t, long)+Foo::Foo(int)
    //Foo* p6 = new(100, 'a')Foo(1);  //对应operator new(size_t, long, char)+Foo::Foo(int)
    //Foo* p7 = new(&start)Foo(1);  //对应operator new(size_t, char*)+Foo::Foo(int)
    //Foo* p8 = new Foo(1);  //对应operator new(size_t) + Foo::Foo(int)

    //delete p1;
    //delete p2;
    //delete p3;
    //delete p4;
    delete p5;
    //delete p6;
    //delete p7;
    //delete p8;
    
    return 0;
}
