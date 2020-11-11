#include <iostream>
#include <memory>

using namespace std;


/*
    chp2. 构造函数语意学 
 
Plus:
    1. dynamic_cast
        会进行运行时刻安全检查，一般引用类型转换失败报错 std::bad_cast
    2. 智能指针
        shared_ptr/unique_ptr
        初始化方式
        拷贝/赋值方式
         
*/
class A{
    public:
    A(std::string s): str(s){
    }

    std::string str;
};
class B : public A{
    public:
    B(std::string s):A(s){
    }
};
class C : public B{};
class D : public B{};
class S {
    virtual ~S(){}
};


int main(void)
{
/*    A* pa = new C;*/
    //B *pb = dynamic_cast<B*>(pa);

    //B* pb = new B;
    //S* ps = new S;
    //C *pc = dynamic_cast<C*>(ps);

/*    A *pa = new D;*/
    //A *pb = dynamic_cast<B*>(pa);

    /* 智能指针初始化方式 */
    //std::string *str1 = new string("foo");
    //std::string *str2 = new string("idiot");
    //std::unique_ptr<std::string> uS1(str1);
    //std::unique_ptr<std::string> uS2(str2);

    //std::cout << *uS1 << std::endl;
    //std::cout << *uS2 << std::endl;

    //uS1.reset(uS2.release());
    //std::cout << *uS1 << std::endl;



    /*智能指针拷贝/赋值方式*/
    A *a = new A("foo");
    B *b = new B("idiot");
    std::unique_ptr<A> ss1(a);
    std::unique_ptr<B> ss2(b);

    std::cout << ss1->str << std::endl;
    std::cout << ss2->str << std::endl;

    ss1.reset(ss2.release());  // 需要拷贝的双方一定满足传统的拷贝/赋值关系
    //ss2.reset(ss1.release());  //  操作失败
    std::cout << ss1->str << std::endl;

    return 0;
}



