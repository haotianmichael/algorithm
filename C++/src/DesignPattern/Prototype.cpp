#include <iostream>

/*
动机:
    在软件系统中，经常面临着“某些结构复杂的对象”的创建工作；由于需求的变化，这些对象经常面临着剧烈
的变化，但是它们却拥有比较稳定一致的接口。

    如何应对这些变化？如何向“客户程序（使用这些对象的程序）”隔离出“这些易变对象”，从而使用“依赖这些易变对象”
的客户程序不随着需求改变而改变?    
 
*/

/***Same Code as FactoryMethod**/

/*
定义: 
    使用原型实例指定创建对象的种类，然后通过拷贝(深拷贝)这些原型来创建新的对象。 
*/
class ISplitter{
    public:
        virtual void split() = 0;
        virtual ISplitter* clone() = 0;
        virtual ~ISplitter(){}
};
class BinarySplitter : public ISplitter{
    public:
        ~BinarySplitter() {
        }
        BinarySplitter(const BinarySplitter& bs) {
        }
        virtual ISplitter* clone() {
            return new BinarySplitter(*this);
        }
};
class TxtSplitter : public ISplitter{
    public:
    TxtSplitter(const TxtSplitter& ts) {
    }
    virtual ISplitter* clone() {
        return new TxtSplitter(*this);
    }
};
class PictureSplitter : public ISplitter{
    public:
        PictureSplitter(const PictureSplitter& ps) {
        
        }
        virtual ISplitter * clone() override{
            return new PictureSplitter(*this);
        }
};
class MainForm{
    ISplitter* prototype;  //原型对象

    MainForm(ISplitter* prototype) {
        this->prototype = prototype; 
    }

    void Button(){
        ISplitter* splitter = prototype->clone();  //克隆原型
        splitter->split();
    }

};

/*
总结: 
    Prototype模式同样用于隔离类对象的使用者和具体类型(易变类)之间的耦合关系，它同样要求这些“易变类”
拥有“稳定的接口”。

    Prototype模式对于“如何创建易变的实体对象”采用“原型克隆”的方法来做，它使得我们可以非常灵活地动态创建
“某些稳定接口”的新对象——所需工作紧紧是注册一个新类的对象（即原型），然后在任何需要的地方Clone。    
 
    Clone方法可以利用某些框架中的序列化来实现浅拷贝.
*/
