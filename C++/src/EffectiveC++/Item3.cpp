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

/********************1.测试内置类型****************************/
static void Test_Built_in() {

    //注意char p*  和char p[]的区别:  不管是char* 还是char []作为形式参数 实参只能是char [] (见4.Test_TestBook_Char)
    char p[] = "haotian";  
    char *ps = p;   // non-const pointer,  non-const data
    const char* cps = p;    // non-const pointer, const data
    char* const pcs = p;   // const pointer,  non-const data
    const char* const pscs = p;   //const pointer, const data

    ps++;
    cps++;
    pcs[1] = 'h';
    ps = const_cast<char *>(pscs);    
    return;
}



/********************2.测试const迭代器****************************/
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


/********************3.测试const-nonconst成员函数重载****************************/

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
    const TestBook ctb(string("is  good"));

    tb[4] = 's';
    //ctb[4] = 's';

    /*测试隐式转换  explicit*/
    tb.printB(TestBook("haotian"));  //临时变量
    //printB(string("haotian"));  //隐式转换

    return;
}




/********************4.测试bitwise constness***************************/
    /*bitwise const指 const成员函数不可以更改对象内任何non-static成员变量*/
class TestBook_Char
{
    public:
        TestBook_Char (char *text) : pText(text) {}

        char &operator[] (size_t position) const{  //这里是bitwise constness声明 但是返回值却为char(可进一步修改data member)
            return pText[position];
        }

        char operator[](size_t position) {
            return pText[position]; 
        }


    private:
        char *pText;
};


static void Test_TestBook_Char() {

    char array[] = "haotian";  
    const TestBook_Char tbc(array);
    tbc[0] = 'J';  //指针的bitwise constness 性质--->  所指内容被修改

    return;
}




/********************5.测试logical constness***************************/
    /*mutable释放掉non-static成员变量的bitwise constness约束*/
class CTextBook
{
public:
    CTextBook (char *text) : pText(text) {}
    size_t length() const;

private:
    char* pText;
    mutable size_t textLength;
    mutable bool lengthIsValid;
};


std::size_t CTextBook::length() const {

    if(!lengthIsValid) {
        textLength = std::strlen(pText);  
        lengthIsValid = true;
    }

    return textLength;
}

static void Test_CTextBook() {

    char array[] = "haotian";
    const CTextBook ctb(array);
    cout << ctb.length() << endl;
    return;
}


/********************6.测试常量性转除***************************/
class TextBook
{
public:
    TextBook (char *s): pText(s) {}
    const char& operator[](std::size_t position) const{
        return pText[position];    
    }


    //casting away constness 常量性转除
    /*
        令non-const operator[]  调用 const 是一个避免代码重复的安全做法 
        期间有两次转型
     */
    char& operator[](std::size_t position) {
        return const_cast<char&>(
               static_cast<const TextBook&>
               (*this)[position]
                );
    }

private:
    char *pText;
    
};

static void Test_TextBook() {

    /*const成员函数*/
    char array[] = "haotian";
    TextBook tb(array);
    const TextBook ctb(array);

    tb[4] = 's';
    //ctb[4] = 's';

    return;
}




int main(void)
{

    Test_TestBook();
    Test_TestBook_Char();
    Test_CTextBook();
    Test_Iterator();
    Test_TextBook();

    return 0;
}

