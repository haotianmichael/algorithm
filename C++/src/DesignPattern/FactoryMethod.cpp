#include <iostream>

/*
动机:
    在软件系统中，经常面临着创建对象的工作；由于需求的变化，需要创建的对象的具体类型经常变化。

    如何应对这种变化？如何绕过常规的对象创建方法(new)，提供一种”封装机制“来避免客户程序和这种
”具体对象创建工作“的紧耦合？    
*/
class Form{};
class ProgressBar{};
class TextBox{};
class ISplitter{
    public:
        virtual void split() = 0;
        virtual ~ISplitter() {}
};
class BinarySplitter : public ISplitter{
    public:
    virtual void split() {
    }
};
class TxtSplitter : public ISplitter{
    public:
        virtual void split() {
        }
};
class PictureSplitter : public ISplitter{
    public:
        virtual void split() {
        }
};
class VideoSplitter : public ISplitter{
    public:
        virtual void split() {
        }
};
class MainForm_old : public Form{
    public:
        void Button1_Click() {
            
            ISplitter* splitter = new BinarySplitter();  //违背了面向接口的编程
            splitter->split();
        }
};
/*
定义:
    定义一个用于创建对象的接口，让子类决定实例化哪个类，FactoryMethod使得一个类的实例化延迟(
    目的：解耦，手段：虚函数)到子类。
*/
class SplitterFactory{
    public:
    virtual ISplitter* CreatSplitter() = 0;
    virtual ~SplitterFactory() {}
};
class TxtSplitterFactory : public SplitterFactory {
    public:
        virtual ISplitter * CreatSplitter() override{
            return new TxtSplitter(); 
        }
};
class BinarySplitterFactory : public SplitterFactory{
    public: 
        virtual ISplitter * CreatSplitter() override{
            return new BinarySplitter(); 
        }
};
class PictureSplitterFactory : public SplitterFactory {
    public:
        virtual ISplitter * CreatSplitter() override{
            return new PictureSplitter(); 
        }
};
class VideoSplitterFactory : public SplitterFactory{
    public:
        virtual ISplitter * CreatSplitter() override{
            return new VideoSplitter(); 
        }
};
class MainForm_new : public Form{
    SplitterFactory* factory;   //工厂基类
    public:
        MainForm_new(SplitterFactory* fac) : factory(fac) {
        }
        void Butto1_Click(){
            ISplitter* splitter =  factory->CreatSplitter();
            splitter->split();
        }
};
/*
总结: 
    用于隔离类对象的使用者和具体类型之间的耦合关系。面对一个经常变化的具体类型，紧耦合关系(new)会
    导致软件的脆弱。

    FactoryMethod模式通过面向对象的方式，将所要创建的具体对象工作延迟到子类，从而实现一种扩展(而非
    更改)的策略，较好的解决了这种紧耦合关系。

    FM解决了”单个对象“的需求变化。缺点在于要求创建方法/参数相同。
*/
