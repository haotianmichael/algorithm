#include <iostream>
#include <list>

using namespace std;

/*
    chp3. Data语意学 
    一个class的data member表现了这个class在程序执行时的某种状态
    绑定
    布局
    存取
    继承
    效率
    指针 
 */

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
    更像一个历史遗留问题……在extern和嵌套式类型声明之间的非直觉绑定操作还是会发生
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
        //return 
            //mem1 < mem2   //LLVM并未重载class member pointer的<运算符 测试失败……
            //? "member 1 occurs first" 
            //: "member 2 occurs first";
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


/*
    4. Data Member的存取
        static member不管是何种继承手段，都只存在一个实例于程序的data segment中(通过对象和指针存取该类型的member结论相同)
        non-static member存放在每一个class object中，存取操作需要编译器将  class object起始地址+data member偏移量(通过对象和指针存取该类型的member可能结论不同)
            (单一类，派生自单一或多重继承串链):每一个non-static data member的偏移位置在编译期即可获取
            (继承自virtual base class): 用指针存取便无法获知偏移量，运行期(区别于virtual function机制，data member的多态形式只存在virtual base class)
        总结：对于non-static member的存取需要知道offset, 但区别于编译期和运行期的效率

*/
class Point{
    public:
        int x;
};
class Point_Derived : public virtual Point{

};

static void Test_Point() {

    Point_Derived origin;
    Point *ppd = &origin;
    origin.x = 4;  //直接使用对象便在编译期确定offset
    ppd->x = 4;  //运行期确定offset
}

/*
    5. Data Member与“继承” 
       Base 指针可以指向Base对象以及Derived对象
       Derived指针只能指向Derived对象

    总结:多态的必要条件是指针和virtual,而对于data member来说便有以下几种情况:
    a. Base指针的行为可能导致的data member多态行为
        Base *bp = base();   // virtual base class(data多态)
        Base *bp = derived();   //只能导致由virtual function引发的多态(函数多态)
    b. Derived指针的行为可能会导致的data member多态行为
        Derived *dp = derived();


   ************注意Base *bp = derived();  其实多态只存在于这种情况，将derived object对象转化为一个Base类型,而其本质就是重新确定指针的起始地址和所指的大小范围


    "单一继承无virtual function"
        每个object对象模型中只有non-static data member，所以对于其存取也就是 起始地址+其offset

    "单一继承有virtual function"
        每个object对象模型中有non-static data member+vptr，影响offset的计算
            当base class中存在virtual function的时候，复合“自然多态”
            当base class中不存在virtual function，而derived class中存在virtual function的时候，需要重新计算offset

    "多重继承"
        和多个base class的地址统一与上述类似

    “虚拟继承”
        class如果内含virtual base class，将被分为两半：“不变区域”和“共享区域”；"不变区域"从起始地址开始，而“共享区域”地址被放在vtbl中，由vptr去索引
        不像前几个其offset都是在编译期就计算好了，但这里需要指针间接导引一次所以会变慢
 
    最终其实虚拟基类最好不要有data members

*/




/* 
    6. 指向data member的指针 

        两种指针类型:
        float Pointer_toD::* 表示取nonstatic data member的地址，得到其在class中的偏移值
        float* 表示取绑定于真正的class object身上的data member的地址，得到该data member在内存中的真正地址
*/
class Pointer_toD{
    public:
        /*
            将虚函数注释掉之后，各个data member的offset为0, 4, 8
            在由vptr及其他virtual机制支持下，各个data member的offset为8, 12, 16
            说明其vptr被编译器放在了最开头
         */
        virtual ~Pointer_toD(){}

        float x, y, z;
};


static void Test_Pointer_toD() {
    
    printf("&Pointer_toD::x = %p\n", &Pointer_toD::x);
    printf("&Pointer_toD::y = %p\n", &Pointer_toD::y);
    printf("&Pointer_toD::z = %p\n", &Pointer_toD::z);


    float Pointer_toD::*p = 0;
    Pointer_toD ptd;
    cout << "the size of float Pointer::x*is: " << sizeof(p) << endl;
    cout << "the size of float is: " << sizeof(float) << endl;
    cout << "the size of Pointer_toD is: " << sizeof(ptd) << endl;
    printf("the address of ptd is %p\n", &ptd);
    printf("the address of x is: %p\n", &ptd.x);
    printf("the address of y is: %p\n", &ptd.y);
    printf("the address of z is: %p\n", &ptd.z);

    return;
}

/*
    7.data member指针多态
        在多重继承下，将第二个(或后继)base class的指针，和一个"与derived class object绑定"的member结合起来

        编译器自行修改offset来实现多态之间的转换
            
*/
struct Base1{int val1 = 0;};
struct Base2{int val2 = 0;};
struct Derived : Base1, Base2{ };

void func1(int Derived::*dmp, Derived* pd) {
    cout << "the value of dmp is: " << dmp << endl;
    pd->*dmp = 2;
}

void func2(Derived* pd) {
    int Base2::*bmp = &Base2::val2;  
    cout << "the value of bmp is: " << bmp << endl;
    func1(bmp, pd);
}

static void Test_Base() {

    Derived der;
    func2(&der);
    printf("the offset of Derived::val1 is %p\n", &Derived::val1);
    printf("the offset of Derived::val2 is %p\n", &Derived::val2);
    printf("the offset of Base1::val1 is %p\n", &Base1::val1);
    printf("the offset of Base2::val2 is %p\n", &Base2::val2);
    cout << der.Base2::val2 << endl;
    cout << der.Base1::val1 << endl;
    return;
}


int main(void)
{
    //cout << sizeof(int*) << endl;
    //Test_Virtual();
    //TestPoint3d();
    //Test_MemLayout();
    //Test_Pointer_toD();
    Test_Base();
    return 0;
}
