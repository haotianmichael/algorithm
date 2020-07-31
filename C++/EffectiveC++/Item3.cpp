#include <iostream>
#include <string>

/*
 
Item3:  尽可能使用const

    

 
 
 */

using namespace std;



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

    const string& get() {
        return text; 
    }
private:
    string text;    
};

inline void printB(TestBook tb) {
    
    cout << tb.get() << endl;

}

int main(void)
{
    
    TestBook tb("haotian");
    const TestBook ctb(string("is a good man"));

    tb[4] = 's';
    //ctb[4] = 's';


    printB(TestBook("haotian"));  //临时变量
    //printB(string("haotian"));  //隐式转换

    return 0;
}

