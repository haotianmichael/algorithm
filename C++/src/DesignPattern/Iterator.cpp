#include <iostream>
#include <algorithm>
#include <cstring>
#include <iterator>


using namespace std;

/*
动机: 
   有些过时
   在软件构建过程中，集合对象内部结构常常变化各异。但对于这些集合对象，我们希望在不暴露其内部结构
   的同时，可以让外部客户代码透明的访问其中包含的元素；同时这种“透明遍历”也为“同一种算法在多种
   集合对象上进行操作”提供了可能。

   使用面向对象技术将这种遍历机制抽象为“迭代器对象”为“应对变化中的集合对象”提供了一种优雅的方式。 

   模板:编译时多态
   虚函数:运行时多态
   面向对象的迭代器模式已经过时(性能损耗严重) ，使用泛型编程中的迭代器思想
*/
template<typename  T>
class Iterator{
    public:
        virtual void first() = 0;
        virtual void next() = 0;
        virtual bool isDone() = 0;
        virtual T& current() = 0;
};

template<typename  T>
class MyCollection{
    public:
        Iterator<T> GetIterator() {
            //... 
        }

};

template<typename T>
class CollectionIterator : public Iterator<T> {
        MyCollection<T> mc;
    public:
        CollectionIterator(const MyCollection<T>& c) : mc(c) {}
        virtual void first() {
        }
        virtual void next(){
        } 
        virtual bool isDone() const {
        }
        virtual T& current() {
        }
};


void MyAlgorithm() {

    MyCollection<int> mc;
    Iterator<int> iter = mc.GetIterator();

    for(iter.first(); !iter.isDone(); iter.next()) {
        cout << iter.current() << endl; 
    }
}
/*
定义: 
    提供一种方式顺序访问一个聚合对象中的各个元素，而又不暴露(稳定)该对象的内部表示。
*/



/*
总结: 
    迭代抽象: 访问一个聚合对象的内容而无需暴露它的内部表示

    迭代多态：为遍历不同的集合结构提供一个统一个接口，从而支持同样的算法在不同的集合结构上进行操作。

    迭代器的健壮性考虑: 遍历的同时更改迭代器所在的集合结构，会导致问题。
*/
