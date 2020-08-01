#include <iostream>
#include <string>
#include <vector>

/*

Item3:  尽可能使用const

常量：
    修饰class外部的global,namespace作用域中的常量及static变量
    修饰class内部的static及nonstatic 的data members
    修饰指针
    修饰迭代器

函数：
    参数，返回值，函数自身(this)
    运算符重载 可返回常量值(避免 (a*b) = c;)

对象：
    const对象以函数参数的形式传递


*/

using namespace std;

/********************1.测试const迭代器****************************/
static void Test_Iterator() {

    /*const迭代器*/
    std::vector<int> vec;
    const std::vector<int>::iterator iter = vec.begin();    //T* const
    *iter = 3;
    //iter++;

    std::vector<int>::const_iterator citer = vec.begin();   //const T*
    //*citer = 4;
    citer++;

    return;
}


/********************2.测试const-nonconst成员函数重载****************************/

class TestBook
{
    public:
        explicit TestBook (string _text) : text(_text) {}

        char &operator[](size_t num) {
            return text[num];
        }

        const char &operator[](size_t num) const {  //  const 修饰this   返回data member--->  const char
            return text[num];
        }
        inline void printB(TestBook tb) {

            cout << tb.get() << endl;

        }


        const string& get() {
            return text; 
        }
    private:
        string text;    
};


static void Test_TestBook() {

    /*const成员函数*/
    TestBook tb("haotian");
    const TestBook ctb(string("is a good man"));

    tb[4] = 's';
    //ctb[4] = 's';

    /*测试隐式转换  explicit*/
    tb.printB(TestBook("haotian"));  //临时变量
    //printB(string("haotian"));  //隐式转换

    return;
}




/********************3.测试bitwise const && logical const***************************/
class TestBook_Char
{
    public:
        TestBook_Char (char *text) : pText(text) {}

        char &operator[] (size_t position) const{  //这里是bitwise const声明 但是返回值却为char(可进一步修改data member)
            return pText[position];
        }

        char operator[](size_t position) {
            return pText[position]; 
        }


    private:
        char *pText;
};


static void Test_TestBook_Char() {

    char array[] = "haotian";  //对于char* 的声明用法
    const TestBook_Char tbc(array);
    tbc[0] = 'J';  //指针的bitwise const 性质--->  所指内容被修改

    return;
}




int main(void)
{

    Test_TestBook();
    Test_TestBook_Char();
    Test_Iterator();

    return 0;
}

