#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>


using namespace std;

/*
动机；
    在软件构建过程中，由于需求的改变，某些类层次结构中常常需要增加新的行为(方法)，
    如果直接在基类中做这样的更改，将会给子类带来很繁重的变更负担，甚至破坏原有设计。

    如何在不更改类层次结构的前提下，在运行时根据需要透明地为类层次结构上的个各类
    动态添加新的操作，从而避免上述问题?
*/
class Visitor;
class Element{
    public:
        virtual void fun1() = 0;
        virtual void func2(int data) = 0;
        //virtual void func3() = 0;    如果在过程中选择加入新的函数，则违反了开闭原则
        virtual ~Element() {}
};

class ElementA : public Element{
    public:
        void fun1() override{
        }

        void func2(int data) override{
        }
};

class ElementB : public Element{
    public:
        void fun1() override{
        }

        void func2(int data) override{
        }
};

/*
定义: 
    目前不知道未来为在基类中增加多少操作 
    表示一个作用于某对象结构中的各元素的操作，使得可以在不改变(稳定)各元素的类的前提下定义(扩展)
    作用于这些元素的新操作(变化) 


    可以接着添加Visitor3....是一种扩展。
    但是Element的子类(ElementA_new等)必须是稳定的，才可以写Visitor，否则整个架构不成立(Visitor中的
    成员函数不会稳定)
*/
class ElementA_new;
class ElementB_new;
class Visitor_new{
    public:
        virtual void visitElementA(ElementA_new& element)  = 0;
        virtual void visitElementB(ElementB_new& element) = 0;
        virtual ~Visitor_new() {}
};

class Element_new {
    public:
        virtual void accept(Visitor_new& visitor) = 0;  //doule dispatch 第一次动态辨析
        virtual ~Element_new() {}
};

class ElementA_new : public Element_new{
    public:
        void accept(Visitor_new& visitor) override{
            visitor.visitElementA(*this);           //double dispatch 第二次动态辨析
        }
};

class ElementB_new : public Element_new{
    public:
        void accept(Visitor_new& visitor) override{
            visitor.visitElementB(*this);        
        }
};

class Visitor1 : public Visitor_new{
    public:
        void visitElementA(ElementA_new& element) {
            cout << "Visitor1 is processing ElementA_new" << endl; 
        }
        
        void visitElementB(ElementB_new& element) {
            cout << "Visitor1 is processing ElementB_new" << endl; 
        }

};

class Visitor2 : public Visitor_new{
    public:
        void visitElementA(ElementA_new& element) {
            cout << "Visitor2 is procesising ElementA_new" << endl;        
        }
        void visitElementB(ElementB_new& element) {
            cout << "Visitor2 is processing ElementB_new" << endl;
        }
};


int main(void)
{
    Visitor2  visitor;   //理解visitor是为ElementB_new增加的操作
    ElementB_new element;
    element.accept(visitor);    //核心调用方式  double dispatch

    ElementA_new element2;
    element2.accept(visitor);
    return 0;
}

/*
总结: 
    Visitor模式通过所谓双重分发(double dispatch)来实现在不更改(不添加新的操作-编译时)Element类层次结构的前提下，
   在运行时透明的为类层次结构上的各个类动态添加新的操作(支持变化)

    所谓双重分发即Visitor模式中间包括了两个多态分发(注意其中的多态机制)。第一个为accept方法的多态辨析；
    第二个为visitEelementX方法的多态辨析。

    Visitor模式的最大缺点在于扩展类层次结构(增添新的Element子类)，会导致Visitor类的改变。因此Visitor
    模式适用于“Element类层次结构，而其中的操作却经常面临频繁改动。”
*/
