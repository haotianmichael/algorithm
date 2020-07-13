#include <iostream>

using namespace std;


template<class T>
class NamedObject
{
    public:
        NamedObject(const char* obj, T& value) : nameobject(obj), valueobject(value){}
        NamedObject(const char* obj, const T& value) : nameobject(obj), valueobject(value) {}
        NamedObject(const string &obj,const T& value) : nameobject(obj), valueobject(value) {}
    private:
        string   nameobject;
        T   valueobject;
};





template<class T>
class NamedObjecterror
{
    public:
        NamedObjecterror(const char* obj, T& value) : nameobject(obj), valueobject(value){}
        NamedObjecterror(const char* obj, const T& value) : nameobject(obj), valueobject(value) {}
        NamedObjecterror(const string &obj,const T& value) : nameobject(obj), valueobject(value) {}
    private:
        string   nameobject;
        const T   valueobject;  //内含一个const成员
};


int testNamedObject(void)
{

    int a = 4;
    NamedObject<int> no1("haotian is a good man", a);   // 注意使用const来修饰函数参数   调用第一号构造函数
    NamedObject<int> no2("haotian", 4);  //注意对   整数和字符串字面值 都会被编译器看成是const 所以调用第二号构造函数
    NamedObject<int> no3 = no1;

    return 0;
}



int testNamedObjecterror() {

    NamedObjecterror<int> no1("haotian", 5);
    NamedObjecterror<int> no2("hangtian", 5);
    //NamedObject<int> no3 = no1;
    //no1 = no2;   需要重载运算符

    return 0;
}





int main(void)
{

    return 0;
}
