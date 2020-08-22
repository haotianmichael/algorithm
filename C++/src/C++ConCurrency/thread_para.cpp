#include <iostream>
#include <algorithm> 
#include <thread>


using namespace std;
/*
       chp2. 线程传参详解，detach注意事项，成员函数做线程函数

       1. 传递临时对象作为线程参数
           个人觉得这个问题出现的必要是因为使用引用传参可以提高效率(减少copy ctor的调用次数)，而应用本身和线程detach的内存模型又是矛盾的，所以才会产生这么多的解决办法

myprint1: 函数参数传递引用和指针的不确定性，所以将引用改为传值，将char指针改为const string &            
myprint2: 函数参数使用类对象的话，使用引用可以减少copy ctor的调用次数，实参的选择很关键：
            a. 不能直接在main中构造一个对象，因为会被释放掉
            b. 所以只能采取临时对象，但是需要禁止隐式构造，因为不能确保其执行点在main结束之前~
            c. 综上所述，只有使用显式临时对象
    

       2. 临时对象
           获取线程id : std::this_thread::get_id()
           通过myprint3可以发现
                a. 使用隐式转换时，构造发生在子线程
                b. 使用显式转换时，构造发生在主线程

                    addr                thread-id
        ctor/dtor   0x7ffee2446688      0x11565d5c0
        copy/dtor   0x7ffee24465c8      0x11565d5c0
        copy        0x7f99a3402670      0x11565d5c0(拷贝构造发生在主线程)
        dtor        0x7f99a3402670      0x700001ef8000(析构发生在子线程)

                c. 如果函数参数使用传值而不是引用，会多一次copy ctor和dctr



        3. 使用智能指针作为线程参数
            使用std::move()传递参数



        4. 使用成员函数指针做线程函数
            需要传递成员函数地址作为参数    


*/


void myprint1(const int i, const string &pmybuf) {   //并不是引用,指针(查看地址不同)   实际是值传递 实际得看具体thread构造函数的实现
    //std::ref
    cout <<  i << endl;
    //printf("i address is %p\n", &i);
    printf("pmybuf address is %p\n", &pmybuf);
    cout << pmybuf << endl;
    return ;
}


class A
{
public:
    A (int a) : m_i(a) {
        cout << "ctor start" << this << endl; 
    }

    A(const A& a) : m_i(a.m_i) {
        cout << "copy ctor start" << this << endl; 
    }

    ~A() {
        cout << "dtor start" << this << endl;
    }

private:
    int m_i;
    
};
void myprint2(const int &i, const A &pmybuf) {  //这里面临的问题是对象实参如果发生构造函数是否会提前于main线程结束之前

    printf("address of buf is %p\n", &pmybuf);

}



class A_advanced
{
public:
    A_advanced (int a) : m_i(a) {
        cout << "ctor start at: " << this << 
            "------thread id: " << std::this_thread::get_id() << endl; 
    }

    A_advanced(const A_advanced& a) : m_i(a.m_i) {
        cout << "copy ctor start at: " << this << 
            "------thread id: " << std::this_thread::get_id() << endl; 
    }

    ~A_advanced() {
        cout << "dtor start at: " << this << 
            "------thread id: " << std::this_thread::get_id() << endl;
    }

private:
    int m_i;
    
};
void myprint3(const A_advanced &mybuf) {
    

    cout << "son thread start at:" <<  &mybuf << 
        "------son thread id: " << std::this_thread::get_id() << endl;

}


void myprint4(unique_ptr<int> pzn) {
    
    cout << "son thread start at: " << &pzn << endl; 

}



class A_funP
{
public:

    A_funP(int a) : _num(a) {
        cout << "ctor start at: " << this << 
            "------thread id: " << std::this_thread::get_id() << endl; 
    }

    A_funP(const A_funP& a) : _num(a._num) {
        cout << "copy ctor start at: " << this << 
            "------thread id: " << std::this_thread::get_id() << endl; 
    }

    ~A_funP() {
        cout << "dtor start at: " << this << 
            "------thread id: " << std::this_thread::get_id() << endl;
    }
    void thread_word(int num) {
        cout << "thread start at:" <<  this << 
        "------son thread id: " << std::this_thread::get_id() << endl;
        _num = num; 
    }


    void operator()(int num) {
    
        cout << "thread() start at:" <<  this << 
        "------son thread id: " << std::this_thread::get_id() << endl;
        _num = num; 
    
    }
private:
    int _num;
};




int main(void)
{
    // 1. 使用简单类型
    //int myvar = 1;
    //int &myvary = myvar;
    //char mybuf[] = "this is a test";


    //printf("myvar address is %p\n", &myvar);
    //printf("mybuf address is %p\n", &mybuf);

    //thread mytobj(myprint1, myvar, mybuf);
    //mytobj.join();
    //mytobj.detach();





    // 2. 使用类
    //int mysecond = 12;
    //A a(mysecond);  这个对象会导致内存非法引用
    //thread mytobj2(myprint2, myvar, mysecond);  这里不能保证隐式转换的执行点
    //thread mytobj2(myprint2, myvar, A(mysecond));  //使用临时对象
    //mytobj2.join();
    //mytobj2.detach();




    // 3.使用线程id证明临时对象的构造点
    //cout << "Main thread is:"  << std::this_thread::get_id() << endl;
    //int mvar = 1;
    //thread mytobj3(myprint3, mvar); 
    //thread mytobj3(myprint3, A_advanced(mvar)); //事实上这里会发生一次拷贝构造
    //thread mytobj3(myprint3, std::ref(A_advanced(mvar)));   //使用std::ref可以将参数引用传递到线程地址空间
    //mytobj3.join();


    // 4. 智能指针
    //unique_ptr<int>  upt(new int(100));       
    //thread myobj4(myprint4, std::move(upt));
    //myobj4.join();


    // 5. 使用成员函数作为线程函数
    A_funP ap(10);
    //thread myobj5(&A_funP::thread_word, ap, 15);
    //thread myobj5(&A_funP::thread_word, std::ref(ap), 10);  //std::ref直接使用引用(考虑join。不能使用detach)
    //thread myobj5(&A_funP::thread_word, &ap, 10); //直接使用引用
    thread myobj5(ap, 10);   //使用仿函数
    myobj5.join();



    cout << "Main End" << endl;
    return 0;
}
