#include <iostream>

/*
 
Item1: 视C++为一个语言联邦
    
    * C
    * Object-Oriented C++
    * Template C++
    * STL
 
术语: 
    声明式 &&  定义式
    初始化
    default构造函数
    copy构造函数 && copy assignment操作符 

 */

using namespace std;

/*声明式(declaration)是告诉编译器某个东西的名称和类型(type), 但略去细节*/

extern int x;  //对象声明式  这里的对象:  内置类型  &&   用户自定义类型

std::size_t numDigits(int number);  //函数声明式子

class Widge;  //类声明式

template<typename T>   //模板声明式
class GraphNode;



/*
   定义式(Definition)的任务是提供编译器一些声明式所遗漏的细节。
    * 对对象而言，定义式是编译器为此对象拨发内存的地点;
    * 对function或function template而言， 定义式提供了代码本体；
    * 对class或者template而言，定义式列出它们的成员
*/

int x;   //x的定义式   分配内存

std::size_t numDigits(int number) {   // 函数定义式

    std::size_t digitsSoFar = 1;   

    while(number /= 10) {
        ++digitsSoFar; 
    }

    return digitsSoFar;
}

class Widge{  //class的定义式
    public:
        Widge();
        ~Widge();
};

template<typename T>   //template的定义式
class GraphNode{
    public:
        GraphNode();
        ~GraphNode();

};


/*
    copy构造函数用来“以同型对象初始化自我对象” , 定义一个对象如何passed by value
    copy assignmeent 操作符用来“从另一个同型对象中拷贝其值到自我对象” 
        如果一个新对象被[定义]，则一定会有一个构造函数被调用，否则是赋值操作运算符
 */
class Widget
{
public:
    Widget ();
    Widget(const Widget& rhs);
    Widget& operator=(const Widget& rhs);
private:

};

int main(void)
{
    Widget w1;
    Widget w2(w1);  //copy构造函数
    w1 = w2; //copy assignment操作符



    return 0;
}
