#include <iostream>

using namespace std;

/*
    Data Member的绑定：
        其绑定作用域是从类内部，因此Point3d的length类型是int         
 
 */
typedef double length;
class Point3d
{
public:
    Point3d(length val) : _val(val) {}
    void mumble(length val) {_val = val;}
    length mumble() { return _val;}


    typedef  int length;
    length _val;
};


static void TestPoint3d(void)
{
    Point3d p(32.4);         
    cout << p.mumble() << endl;  // 输出32
    cout << sizeof(double) << endl;  //输出8
    cout << sizeof(p._val) << endl;   //输出4
    return;
}




int main(void)
{
    TestPoint3d();
    return 0;
}
