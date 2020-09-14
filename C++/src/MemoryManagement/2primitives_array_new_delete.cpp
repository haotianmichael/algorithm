#include <iostream>
#include <algorithm>
#include <cstring>


using namespace std;

/*
 
    1. new object[]/delete[] object(本质调用malloc/delete)
 
        malloc/free分配细节：
          除了分配给定的内存之外，还会有cookie——用来记录分配数组的长度
          查看cookie中的长度，然后调用适当的析构函数

         所谓内存泄漏:
            对于一个new object[]，需要有相应的delete[] object
            本质上cookie记录了free本身需要释放的内存大小，正的泄露发生在调用的析构函数次数上:
                如果object是带指针的member,则意味着析构函数是nontrival，反之则是trival的 
            而析构函数的调用次数，则会影响指针指向的内存部分的泄露    
        

*/
class Complex{

    public:
        int id;
        Complex(int _id) : id(_id) {
            cout << "default ctor is. " << this << " id = " << id << endl;
        }
        Complex() : id(0) {
        }
    
        ~Complex() {
            cout << "dtor is. " << this << " id = " << id << endl; 
        }
};


static void sample() {

    /*
        唤起3次ctor
        无法藉由参数给予初值  
    */
    Complex* pca = new Complex[3];

    //唤起3次dtor
    delete  []pca; 
}


static void TEST_ARRAY_NEW_DELETE(int size) {

    Complex* buf = new Complex[size];  //必须有默认构造函数
    Complex* tmp = buf;
    cout << "buf = " << buf << " tmp = " << tmp << endl;
    for(int i = 0 ; i < size; i ++) {
        new (tmp++)Complex(i);  //replacemennt new
    }
    cout << "buf = " << buf << "tmp = " << tmp << endl;
    delete []buf;   //次序逆反
}

int main(void)
{
    TEST_ARRAY_NEW_DELETE(3);
    
    return 0;
}

