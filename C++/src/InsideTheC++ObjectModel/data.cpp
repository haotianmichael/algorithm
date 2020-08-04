#include <iostream>

using namespace std;

/*
    1. Data Member的绑定：
        a. 对于inline function躯体内的data member绑定操作，是在整个class声明完后才发生的-------> 因此length是double
        b. 而对于member function的argument list的绑定操作，还是会在它们第一次遭遇时候被resolve的------>因此length是int

    防御性编程解决办法：
        在遇到nested typenames的时候，总是将其放在class的起始处，避免作用域重叠
        其中nested typenames指的是除内置类型之外的嵌套类型(类类型，数据类型)
*/
typedef int length;
class Point3d
{
public:
    Point3d() {}
    Point3d(length val) : _val(val) {}   //length 被resolve 为int
    void mumble(length val) {_val = val;}   //length 被reslove 为int; _val为double
    length mumble() { return _val;}    //length 被 resolve为int;  _val为double； 但是在返回值的时候被隐式转换为int

    void my_print() { cout << _val << endl;}   //_val为double

    typedef  double length;
    length _val = 32.4;
};


static void TestPoint3d(void)
{
    /*测试a条例*/
    Point3d p(32.4);         
    cout << p.mumble() << endl;  // 输出32
    cout << sizeof(double) << endl;  //输出8
    cout << sizeof(p._val) << endl;   //输出4


    /*测试b条例*/
    Point3d ps;
    ps.my_print();   //输出32.4
    return;
}




int main(void)
{
    TestPoint3d();
    return 0;
}
