#include <iostream>
#include <list>

using namespace std;



/*
   1. 虚拟继承的对象模型 
       C++ Standard并不规定virtual functions和virtual base class的实现细节，不同的编译器有不同的实现模型

 */

class X{};
class Y : public virtual X {};
class Z : public virtual X {};
class A : public Y, public Z {};

static void Test_Virtual(){
    cout << "X:" << sizeof(X) << endl;   // 输出1
    cout << "Y:" << sizeof(Y) << endl;  //输出8
    cout << "Z:" << sizeof(Z) << endl;  //输出8
    cout << "A:" << sizeof(A) << endl;  // 输出16
}


/*
   2. Data Member的绑定
    a. 对于inline function躯体内的data member绑定操作，是在整个class声明完后才发生的-------> 因此length是double
    b. 而对于member function的argument list的绑定操作，还是会在它们第一次遭遇时候被resolve的------>因此length是int

   防御性编程解决办法：
   在遇到nested typenames的时候，总是将其放在class的起始处，避免作用域重叠
   其中nested typenames指的是嵌套类型(类类型，数据类型)
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


/*
   3. Data Member的布局

 */
template<class class_type, 
    class data_type1,
    class data_type2>
    const char *access_order(
            data_type1 class_type::*mem1,
            data_type2 class_type::*mem2) {

        assert(mem1 != mem2);
        return 
            mem1 < mem2 
            ? "member 1 occurs first" 
            : "member 2 occurs first";
    }
class layout{

    layout(float _x, float _y, float _z) : x(_x) , y(_y), z(_z) {}
    public:
    int x;
    static list<layout*> *freelist;
    int y;
    static const int chunkSize = 240;
    int  z;

};


static void Test_MemLayout() {

    access_order(&layout::x, &layout::z); 
}






int main(void)
{
    cout << sizeof(int*) << endl;
    //Test_Virtual();
    //TestPoint3d();
    Test_MemLayout();
    return 0;
}
