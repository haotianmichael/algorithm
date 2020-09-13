#include <iostream>
#include <algorithm>
#include <cstring>


using namespace std;


/*
    new/delete
        a. 分配内存
        b. 调用构造函数 
 
*/



class primitives_new_delete
{
public:
    primitives_new_delete (int _a, int _b) : a(_a), b(_b){
    }

    virtual ~primitives_new_delete () {}


    //调用new的时候，编译器生成的代码
    primitives_new_delete* new_override() {
        primitives_new_delete* pc;
        try {
            void *mem = operator new(sizeof(primitives_new_delete)); 
            pc = static_cast<primitives_new_delete*>(mem);
            return pc;
        }catch(std::bad_alloc) {
        
            cout << "Bad Allocation" << endl;
        } 
        return nullptr;
    }


private:
    int a;
    int b; 
};



int main(void)
{
    
    primitives_new_delete pnd(1, 3);
    pnd.new_override();    
    return 0;
}
