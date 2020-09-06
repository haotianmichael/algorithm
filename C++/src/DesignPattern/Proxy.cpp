#include <iostream>

using namespace std;

/*
动机: 
    面向对象系统中，有些对象由于某种原因（比如对象创建的开销很大，或者某些操作需要安全控制，或者
    需要进程外的访问等），直接访问会给使用者，或者系统结构带来很多麻烦。
 
    如何在不失去透明操作对象的同时来管理/控制这些对象特有的复杂性？增加一层间接层是软件开发中常见的解决办法。
*/
class ISubject{
    public:
        virtual void process();

};


class RealSubject : public ISubject{
    public:
        virtual void process() {
            //.... 
        }
};

class Client{
    ISubject* subject;
    public:
        Client() {
            subject = new RealSubject;  //由于安全，分布式等其他原因得不到new的返回值
        }
        void DoTask() {
            //...
            subject->process(); 
            //...
        }
};

/*
定义:
    为其他对象提供一种代理以控制（隔离，使用接口）对这个对象的访问。
*/
//Proxy的设计 
class SubjuctProxy : public ISubject{
    public:
        virtual void process() {
            //对RealSubject的一种间接访问 
        }

};

/*
总结: 
    “增加一层间接层”是软甲系统中对许多复杂问题的一种常见解决方法。在面向对象系统中，直接使用某些对象会带来很多
   问题，作为间接层的Proxy对象便是解决这一问题的常用手段。

    具体Proxy设计模式的实现方法，实现粒度都相差很大，有些可能对单个对象做细粒度的控制，入copy-on-write技术，
    有些可能对组件模块提供抽象代理层，在架构层次对对象做Proxy。
    
   Proxy并不一定要求保持接口完整的一致性，只要能够实现间接控制，有时候损及一些透明性是可以接受的。 
   分布式系统中大量使用Proxy设计模式
*/
