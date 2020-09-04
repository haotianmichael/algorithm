#include <iostream>

/*
动机:
    在软件构建过程中，某些对象使用的算法可能多种多样，经常改变，如果将这些算法都编码到对象中，
    将会使对象变得异常复杂；而且有时候支持不使用的算法也是一个性能负担。

    如何在运行时根据需要透明地更改对象的算法？将算法与对象本身解耦，从而避免上述问题？
*/
/***************************结构化程序模型
        不要静态的看软件的设计 

*/
enum TaxBase{
    CN_Tax,
    US_Tax,
    DE_Tax,
    FR_tax     //更改———— 违背开放封闭原则
};
class SalesOrder_old{
    TaxBase tax;
    public:
        double CalculateTax() {
        
            if(tax == CN_Tax) {
            
            }else if(tax == US_Tax) {
            
            }else if(tax == DE_Tax) {
            
            }else if(tax == FR_tax) {   //更改   违背开放封闭原则
            
            }
            return -1;
        }
        
};


/*
定义: 
    定义一系列算法，把它们一个个封装起来，并且使它们可互相替换(变化)。
    该模式使得算法可独立于使用它的客户程序(稳定)而变化(扩展，子类化)
*/
/**************************面向对象程序模型
 
 
 
*/
class Context{


};
class TaxStrategy{
    public:
        virtual double calclate(const Context& context) = 0;
        virtual ~TaxStrategy() {}

};

class CNTax : public TaxStrategy{
    public:
        virtual double calclate(const Context& context) {
            //重写 
            return 0;
        }
};

class USTax : public TaxStrategy{
    public:
        virtual double calclate(const Context& context) {
            //重写        
            return 0;
        }
};

class DETax : public TaxStrategy{
    public:
        virtual double calclate(const Context& context) {
            //重写
            return 0;        
        }
};

//扩展-遵循了开放封闭原则
class FRTax : public TaxStrategy{
    public:
        virtual double calclate(const Context& context) {
            //重写
            return 0; 
        }
};


class SalesOrder_new {
    private:
        TaxStrategy* strategy;
    public:
        /*
            后续的工厂模式的构造函数
            返回堆对象
            SalesOrder_new(SrategyFactory* startegyfactory) {
                this->startegy = strategyfactor->CreateStartegy(); 
            } 
        */
        SalesOrder_new() {
        
        }

        ~SalesOrder_new() {}

        double CalculateTax() {
     
              Context context;   
              double val = strategy->calclate(context);    //多态调用
              return val;
         } 

};
/*
总结:
    Strategy及其子类为组件提供了一系列可重用的算法，从而可以使得类型     
    在运行时方便的根据需要在各个算法之间进行切换.

    提供了用条件判断语句以外的另一种选择，消除条件判断语句，就是在解耦合。
    含有许多条件判断语句的代码通常都需要Strategy模式
    
*/
