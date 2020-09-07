#include <iostream>
#include <algorithm>
#include <cstring>
#include <list>

using namespace std;



/*
动机: 
   在软件某些情况下，客户代码过多地依赖于对象容器复杂的内部实现结构，对象容器内部实现结构(而非
   抽象接口)的变化将引起客户代码的频繁变化，带来了代码的维护性，扩展性等弊端。

   如何将“客户代码与复杂的对象容器结构”解耦？让对象容器自己来实现自身的复杂结构，从而使得
  客户代码就像处理简单对象一样来处理复杂的对象容器？ 
*/
class Component{
    public:
        virtual void Process() = 0;
        virtual ~Component();
};

class Composite : public Component{
    string name;
    list<Component*> elements;

    public:
    Composite(const string s) : name(s){}
    void add(Component* element) {
        elements.push_back(element); 
    }

    void remove(Component* element) {
        elements.remove(element); 
    }

    void process() {
    
    
    }



};

/*
定义: 
    将对象组合成树形结构以表示“部分-整体”的层次结构。
    Composite模式使得用户对单个对象和组合对象的使用具有一致性。

*/



/*
总结: 
 

 
*/
