#include <iostream>

using namespace std;



/*
   chp4.  Function语意学  
        member function分为non-static static virtual三种函数
        Member各种调用方式
        Virtual Member Function
        函数效能
        指向Member Function的指针
        Inline Function 

 */

/*
   1. non-static 被内化成为non-member的形式
        Point3d  Point3d::magnitude()----------->Point3d  Point3d::magnitude(Point3d *const this);
 */


/*
   2. static member function 
    其特性就是取消this指针，因此有以下特性：
        不能够直接存取其class中的nonstatic class
        不能够被声明为const, volatile或virtual
        不需要经过class object调用
*/


/*
   3. virtual-member-function 

*/

class Point3d{


    public:
        float magnitude() const {
            return res;
        }


        Point3d normalize()const {
            float mag = magnitude();
            Point3d normal;


            normal._x = _x/mag;
            normal._y = _y/mag;
            normal._z = _z/mag;

            return normal; 

        }

    protected:
        float res;
        float _x;
        float _y;
        float _z;
};




static void Test_Point3d() {
    Point3d obj;
    Point3d *ptr = &obj;

    ptr->normalize();



}


