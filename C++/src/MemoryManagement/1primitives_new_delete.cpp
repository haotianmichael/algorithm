#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;


/*
   1. new/delete
    new expression
        a. 分配内存(调用operator new)
        b. 调用构造函数 
    delete expression
        a. 调用析构函数
        b. 释放内存(调用operator delete)    
 
    operator new
        a. 调用malloc
    operator delete 
        a. 调用free    

*/
//重载全局operator new(如果在类中重载必须为static)
void* operator new(size_t size, const std::nothrow_t&) 
    noexcept{  //表示程序不会抛异常

    void* p;
    while((p = malloc(size))  == 0) {  //尝试分配内存,分配失败则进入loop
    
        /*
          如果内存分配失败，则调用自设定函数new_handler来释放一些内存以供loop下次分配成功  
         */
        if(new_handler(size) == 0) break;   
    }

    return (p);
}
//重载operator  delete
void operator delete(void *pc) 
    noexcept{
    
   free(pc); 
 }


//实现new&&delete
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
            void *mem = operator new(sizeof(primitives_new_delete));   //分配内存
            pc = static_cast<primitives_new_delete*>(mem);  //指针转换
            /*
                欲直接调用ctor,则使用placement new:
                new(p) primitives_new_delete(1, 2);  
            */
            //pc->primitives_new_delete::primitives_new_delete(1, 2);  //指针不可直接调用构造函数
            new(pc) primitives_new_delete(1, 2);    //直接调用构造函数(placement new)

            return pc;
        }catch(std::bad_alloc) {
        
            cout << "Bad Allocation" << endl;
        } 
        return nullptr;
    }

    //调用delete的时候，编译器生成的代码
    void delete_override(primitives_new_delete* pc) {

        pc->~primitives_new_delete(); //指针可直接调用析构函数
        operator delete(pc);   //释放内存
    }

private:
    int a;
    int b; 
};

static void Test_NEW_DELETE() {

    primitives_new_delete pnd(1, 3);
    primitives_new_delete* pc = pnd.new_override();    
    pnd.delete_override(pc);
    return;
}

/*
    2. Ctor & Dtor 直接调用

*/
class A {
    public:
        int id;
        A(int _id) : id(_id){
            cout << "ctor.this = " << this << " id = " << endl; 
        }
        ~A() {
            cout << "dtor.this = " << this << " id = " << endl; 
        }
};
static void TEST_Ctor_Dtor() {
    
    string* pstr = new string;
    cout << "str = " << *pstr << endl;
    /*
        不能直接调用构造函数
        原因： 
            typedef basic_string string  //即string的真正类型是basic_string 
    */
    //pstr->string::string("jjhou");
    
    //可以直接调用析构
    pstr->~string();


    A* pA = new A(1);  //直接调用构造函数     
    cout << " id = " << pA->id << endl;
    //pA->A::A(3);  最终证明无法直接调用构造函数
}

int main(void)
{

    // 1. 测试new/delete
    Test_NEW_DELETE();


    //2. 测试ctor/dtor
    TEST_Ctor_Dtor();

    return 0;
}
