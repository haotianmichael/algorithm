#include <iostream>

/*
动机:
    在软件系统中，有时候面临一些“一个复杂对象”的创建工作，其通常由各个部分的子对象用一定的算法构成；由于
需求的变化，这个复杂对象的各个部分经常面临这剧烈的变化，但是将他们组合在一起的算法却相对稳定。

    如何应对这种变化，如何提供一种”封装机制“来隔离出“复杂对象的各个部分”的变化。从而保持系统中的“稳定构建算法”
不随着需求改变而改变?    
*/
class House{
    public:

    void init() {

        this->BuildPart1();

        for(int i =0 ; i < 4; i ++) {
            this->BuildPart2(); 
        }
         
        bool flag = this->BuildPart3();

        if(flag) {
            this->BuildPart4(); 
        }

        this->BuildPart5();
    } 

    protected:
        virtual void BuildPart1() = 0;
        virtual void BuildPart2() = 0;
        virtual bool BuildPart3() = 0;
        virtual void BuildPart4() = 0;
        virtual void BuildPart5() = 0;
        virtual ~House() {}
};
class StoneHouse : public House{
    protected:
    virtual void BuildPart1() override{
    }

    virtual void BuildPart2() override{
    }
    
    virtual bool BuildPart3() override{
        return false;
    }

    virtual void BuildPart4()  override{
    }

    virtual void BuildPart5() override{
    }
};

int main_old() {
    
    House* pHouse = new StoneHouse();
    pHouse->init();

    return 0;
}
/*
定义: 
    讲一个复杂对象的构建与其表示相分离，使得同样的构建过程（稳定）可以创建不同的表示(变化).
*/
 //对象的表示
class House_new{};
//对象的构建
//表示和构建两者为友元关系或者指针成员，使得两者可以互相访问 
class HouseBuilder{  
    public:
        House_new* GetResult() {
            return pHouse; 
        }

        House_new* pHouse;
        virtual void BuildPart1() = 0;
        virtual void BuildPart2() = 0;
        virtual bool BuildPart3() = 0;
        virtual void BuildPart4() = 0;
        virtual void BuildPart5() = 0;
};
class StoneHouse_new : public House_new{

    protected:
        virtual void BuildPart1() {
        }

        virtual void BuildPart2() {
        }

        virtual bool BuildPart3() {

            return false;
        }

        virtual void BuildPart4() {
        }

        virtual void BuildPart5() {
        
        }
};

class StoneHouseBuilder : public HouseBuilder{

};
//稳定部分
class HouseDirector{
    public:
        HouseBuilder* pHouseBuilder;
        
        //构造函数负责构造
        HouseDirector(HouseBuilder* hb): pHouseBuilder(hb) {

        }
        House_new* Construct() {
            pHouseBuilder->BuildPart1();

            for(int i = 0; i < 4; i++) {
                pHouseBuilder->BuildPart2(); 
            }
        
            bool flag = pHouseBuilder->BuildPart3();
            if(flag) {
                pHouseBuilder->BuildPart4(); 
            }

            pHouseBuilder->BuildPart5();

            return pHouseBuilder->GetResult();
        }

};
int main_new() {

    

    return 0;
}

/*
总结: 
    Builder模式主要用于“分步骤构建一个复杂的对象”。在这其中“分步骤”是一个稳定的算法，而复杂对象的各个部分则经常变化。
        
    变化点在哪里，封装哪里——Builder模式主要在于应对“复杂对象各个部分”的平凡需求变动。其缺点在于难以应对“分步骤构建算法”的
    需求变动。

    在Builder模式中，要注意不同语言中构造器内调用虚函数的差别。
*/
