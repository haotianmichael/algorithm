#include <iostream>

using namespace std;


class TextBook
{
public:

    TextBook(string name) : text(name)  {}
    char &operator[](size_t position) {
        return  text[position];
    }

    const char &operator[](size_t position) const {
        return text[position];
    }

private:    
    string text;
};




int main(void)
{
    
    TextBook a("haotian");
    cout << a[0];

    /*
        类中的const成员变量  一定要单独对待
     */
    const TextBook b("haotian is a good man");  //如果不重载常量   会报错
    cout << b[0];
    return 0;
}
