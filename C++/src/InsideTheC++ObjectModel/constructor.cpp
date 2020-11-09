#include <iostream>

using namespace std;


/*
    chp2. 构造函数语意学 
 
 
*/
class A{
    virtual void fun(){
        ;
    }
};
class B : public A{};
class C : public B{};
class D : public B{};
class S {
    virtual ~S(){}
};


int main(void)
{
/*    A* pa = new C;*/
    //B *pb = dynamic_cast<B*>(pa);

    B* pb = new B;
    S* ps = new S;
    C *pc = dynamic_cast<C*>(ps);

/*    A *pa = new D;*/
    //A *pb = dynamic_cast<B*>(pa);

    return 0;
}



