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
        virtual void process() = 0;
        virtual ~Component();
};
//树节点
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
        
       //1. process current node

       //2. process leaf node 

        for(auto &e : elements){
            e->process(); //多态调用
        } 
    }
};
//叶子节点
class Leaf : public Component{
    string name;
    public:
    Leaf(string s) : name(s){} 

    void process() {
        //process current node 
    }
};

static void Invoke(Component& c) {
    c.process();  //多态调用
} 

int main(void)
{
    Composite root("root");     
    Composite treeNode1("treeNode1");
    Composite treeNode2("treeNode2");
    Composite treeNode3("treeNode3");
    Composite treeNode4("treeNode4");
    Leaf leat1("left1");
    Leaf leat2("left2");


    root.add(&treeNode1);
    treeNode1.add(&treeNode2);
    treeNode2.add(&leat1);


    root.add(&treeNode3);
    treeNode3.add(&treeNode4);
    treeNode4.add(&leat2);

    Invoke(root);

    return 0;
}
/*
定义: 
    将对象组合成树形结构以表示“部分-整体”的层次结构。
    Composite模式使得用户对单个对象和组合对象的使用具有一致性。

*/



/*
总结: 
   Composite模式采用树形结构来实现普遍存在的对象容器，从而将“一对多”的关系转换为“一对一”的关系
   使得客户代码可以一致的（复用）处理对象和对象容器，无需关心处理的是单个对象，还是组合的对象容器。 

   将“客户代码与复杂的对象容器结构”解耦是Composite的核心思想，解耦之后，客户代码将与纯粹的抽象接口
   ——而非对象容器的内部实现结构——发生依赖，从而更能“应对变化”。
 
   Composite模式在具体实现中，可以让父对象中的子对象反向追溯；如果父对象有频繁的额遍历需求，可使用缓存
   技巧来改善效率。
*/
