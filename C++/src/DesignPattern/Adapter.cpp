#include <iostream>


using namespace std;


/*
动机:
    在软件系统中，由于应用环境的变化，常常需要将“一些现存的对象”放在新的环境中应用，但是新环境要求的
   接口是这些现存对象所不满足的。

    如何应对这种“迁移的变化”？如何既能利用现有对象的良好实现，同时又能满足新的应用环境所要求的接口？ 
 */
//目标接口(新接口)
class ITarget{
    public:
        virtual void process() = 0;
};

//遗留接口(老接口)
class IAdaptee{
    public:
        virtual void foo(int data) =0;
        virtual int bar() = 0;
};
class OldClass : public IAdaptee{
    public:
        virtual void foo(int data) {
        }

        virtual int bar() {

            return 0;
        }
};

//对象适配器
class Adapter_obj : public ITarget{   //继承
    protected:
        IAdaptee* pAdaptee;   //组合

    public:
        Adapter_obj(IAdaptee *ia) : pAdaptee(ia){
        }
        virtual void process() {
            int val = pAdaptee->bar(); 
            pAdaptee->foo(val);
        }

};


//类适配器(不推荐)
class Adapter_class : public ITarget, protected IAdaptee{
    


};

int main(void)
{
    IAdaptee* pAdaptee = new OldClass();

    ITarget* pTarget = new Adapter_obj(pAdaptee);
    pTarget->process();

    return 0;
}
/*
定义: 
    将一个类的接口转化成客户希望的另一个接口。Adapter模式使得原本由于接口不兼容而不能一起
   工作的那些类可以一起工作。 
*/


/*
总结: 
    Adapter模式主要应用于”希望复用一些现存的类，但是接口又与复用环境要求不一致的情况。“在遗留代码复用，
    类库迁移等方面非常有用。

    GoF 23 定义了两种Adapter模式的实现结构；对象适配器和类适配器。但类适配器采用”多继承“的实现方式，一般
    不推荐使用。对象适配器采用”对象组合“的方式，更符合松耦合精神。

    Adapter模式可以实现的非常灵活，不必拘泥于GoF23顶你故意的两种结构。例如：完全可以将Adapter模式中的”现存
    对象“作为新的接口方法参数，来达到适配的目的。
*/
