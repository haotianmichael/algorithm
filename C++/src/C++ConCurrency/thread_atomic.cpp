#include <iostream>
#include <algorithm>
#include <cstring>
#include <thread>
#include <mutex>
#include <atomic>


using namespace std;


/*

   chp9. std::future其他成员函数， shared_future, atomic

   3. 原子操作std::atomic

       3.1 原子操作基本概念

        两个线程对一个变量进行操作，线程A读，另一个线程B写。
        a. 使用互斥量来确保竞态条件
        b. 使用原子操作 (在多线程中不会被打断,不可分割的程序执行片段) 
        c. 互斥量加锁一般针对代码段(多行代码)，而原子操作一般针对一个变量

       3.2 基本的std::atomic用法
           std:::atomic(类模板)用来封装某个类型的值
           比互斥量的效率会高一些
     

 */

class A_mutex {

    int mycout = 0;
    std::mutex my_mutex;

    public:

    void my_thread() {
        for(int i = 0; i < 1000000; i ++) {
            my_mutex.lock();
            mycout++;    
            my_mutex.unlock();
        }

    }

    int get_cout() {
        return this->mycout; 
    }
};


class A_atomic{

    std::atomic<int> mycout;  //封装了一个类型为int的原子对象

    public:

    A_atomic(int para) : mycout(para){
    }
    void my_thread() {
        for(int i = 0; i < 1000000; i ++) {
            mycout++;    
        }

    }

    int get_cout() {
        return this->mycout; 
    }
};

class B_atomic{

    std::atomic<bool> ifend;
    public:
    void my_thread() {
        std::chrono::milliseconds  dura(1000);
        while(ifend == false) {
            cout << "thread ID: " << std::this_thread::get_id() <<  " running... " <<endl; 
            std::this_thread::sleep_for(dura);
        } 
        cout << "thread ID: "  << std::this_thread::get_id() << " stopped " <<  endl;
    }

    void set_ifend(bool val) {
        this->ifend = val; 
    }
};

int main(void)
{

    //1. 互斥量
    //A_mutex am;
    //std::thread mytobj(&A_mutex::my_thread, &am);
    //std::thread mytobj2(&A_mutex::my_thread, &am);
    //mytobj.join();
    //mytobj2.join();
    //cout << am.get_cout() << endl;


    //2. 原子操作
    //A_atomic aa(0);
    //std::thread myobj1(&A_atomic::my_thread, &aa);
    //std::thread myobj2(&A_atomic::my_thread, &aa);
    //myobj1.join();
    //myobj2.join();
    //cout << aa.get_cout() << endl;


    //3. 原子操作
    B_atomic ba;
    std::thread myobj1(&B_atomic::my_thread, &ba);
    std::thread myobj2(&B_atomic::my_thread, &ba);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    ba.set_ifend(true);  //对原子操作的写操作，让程序自动运行结束
    myobj1.join();
    myobj2.join();
    

    cout << "Main End!" << endl;
    return 0;
}
