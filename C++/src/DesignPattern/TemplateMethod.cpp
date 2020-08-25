#include <iostream>


/*
动机:
    对于某一项任务，常常有稳定的整体操作结构，但是各个子步骤却有很多改变的需求
    如何确定稳定操作的前提下，来灵活应对各个子步骤的变化或者晚期实现的需求？ 
 
*/
/*******************************结构化程序模型
 
    Library_old 开发人员：开发具体步骤
    Application_old 开发人员：开发步骤，记忆程序主流程
    Application_old 调用 Library_old (早绑定)

 */
class Library_old{
    public:
        void Step1() {
        
        }

        void Step3() {
        
        }

        void Step5() {
        
        }
};

class Application_old{
    public:
        bool Step2() {
            return false; 
        }
 

        void Step4() {
        
        }
};


int main_old() {
    
    Library_old lib;
    Application_old app;

    lib.Step1();

    if(app.Step2()){
        lib.Step3(); 
    }

    for(int i = 0; i < 4; i ++) {
        app.Step4(); 
    }
    return 0;
}



/*
定义:
    定义一个操作中的算法的骨架(稳定)，而将一些步骤延迟(变化)到子类中。Template Method设计模式
    使得子类可以不改变(复用)一个算法的结构即可重定义(override 重写)该算法的某些特定步骤    
 
*/
/*******************************面向对象程序模型
    
    Library_new 开发人员: 开发具体步骤，及程序主流程
    Application_new 开发人员：开发具体步骤
    Library_new 调用 Application_new (晚绑定)


*/
class Library_new{
    public:
    /*大部分设计模式的特点：稳定中有变化*/
    //稳定   template method
    void Run() {
            
        Step1();

        if(Step2()) {   //支持变化==> 虚函数的多态调用
            Step3(); 
        }       
    
        for(int i = 0; i < 4; i ++) {
            Step4();   //支持变化==> 虚函数的多态调用
        }

        Step5();
    }


    virtual ~Library_new() {}

    protected:

    void Step1() {  //稳定
    }

    void Step3() {    //稳定
    }

    void Step5() {   //稳定
    }

    virtual bool Step2()  = 0;   //变化
    virtual void Step4() = 0;   //变化
};
class Application_new : public Library_new{
    protected:
        virtual bool Step2() {
            //子类重写实现
            return false; 
        }

        virtual void Step4() {
            //子类重写实现
        }

};
int main_new() {

    Library_new* pLib = new Application_new();  //多态指针

    pLib->Run();
    
    delete pLib;


    return 0;
}

/*
总结: 
   Template Method是一种非常基础的设计模式，它用最简洁的机制(虚函数的多态性)为很多
   应用框架提供了灵活的扩展点，是代码复用方法的基本实现结构。

    在具体实现方面，被TM设计模式调用的虚方法可以具有实现，也可以没有任何实现(抽象方法，
    纯虚方法)，但一般推荐设置为protected方法(主要是因为这种方法一般不作为接口，而是作为流程
    中的某一个实现步骤)
*/
