#include <iostream>
#include <algorithm>
#include <cstring>
#include <new>

using namespace std;



/*
    placement new (调用operator new)
        允许我们将对象建构在已经allocated的memory上
        没有所谓的placement delete，因为placement new根本不分配内存！
        不会在分配内存(定点内存)
         

 
*/

class Complex{
    int a, b;
    public:
    Complex() {}
    Complex(int _a, int _b) : a(_a), b(_b){
    }
    ~Complex() {}
};

//重载operator new(本质上就是placement new)
void* operator new(size_t size, char *buf) {
    return buf;
}


class primitives_relpacement_new {
    Complex* pc;
    public:
        
        //调用placement new  的编译器生成的代码  
        void new_override(char *buf) {
            try {
                 void *mem = operator new(sizeof(Complex), buf);   //重载
                 pc = static_cast<Complex*>(mem);
                 //pc->Complex::Complex(1,2); //构造函数
            
            }catch(std::bad_alloc) {
                cout << "Bad Allocation" << endl;     
            }
        }
};

//演示
static void sample(){
    
    char *buf = new char[sizeof(Complex)*3];
    Complex* pc = new(buf) Complex(1,2);

    delete [] buf;
    return;
}

int main(void)
{
    
    return 0;
}
