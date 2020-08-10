#include<iostream>

using namespace std;


/*  chp1. 对象模型初探*/
/*
    1. 对象模型的内存大小 
        a. 其nonstatic data member的总和大小
        b. 任何由于alignmeent的需求而填补的空间
        c. 为了支持virtual机制而由内部产生的任何额外负担(overhead)
 
*/



/*

   2. 面向对象模型初探(继承，多态) 
        a. 多态的必要条件是指针和引用
        b. 多态经过一个共同的接口影响类型的封装，该接口就是virtual函数机制 其本质就是根据运行期object的真正类型来解析哪一个函数实例被调用
        c. 指针的类型解释了其所指对象的大小及内容
        d. 指针的类型只能够决定其本身调用的接口和access level, 而对象多态化的实例则取决于对象本身所存取的vptr中 
        e. 继承对象之间的直接赋值只会造成slided
 */

class Library_mateials
{
    public:
        virtual void  check() {
            cout << "Library_mateials" << endl;
        }

};

class Book : public Library_mateials
{
    public:
        virtual void check() {
            cout << "Book" << endl; 
        }

};
static void Test_Polymorphism()
{
    Book book;
    Library_mateials thing1 = book;
    thing1.check();   //输出Library_mateial

    Library_mateials &thing2 = book;
    thing2.check();  //输出Book

    return;
}



int main(void)
{
    
    Test_Polymorphism();
    return 0;
}
