#include <iostream>
#include <algorithm>
#include <cstring>
#include <thread>
#include <mutex>
#include <atomic>
#include <future>


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

    4. std::atomic深入

        4.1 一般std::atomic原子操作，针对++, --, +=, -=,&=, |=, ^=是支持的，其他运算符可能是不支持的(比如a = a + 1;)

    5. std::async参数深入    
        用来创建一个异步任务
        std::thread()如果系统资源紧张，那么可能创建线程就失败，整个程序可能奔溃。
        
        std::thread() 创建线程
        std::asnyc() 创建一个异步任务

        a. 参数std::launch::deferred(同步)
            延迟调用，不创建新线程,util get()或者wait()函数调用才执行，如果没有调用get()或wait(),则线程不会被执行

        b. 参数std::launch::async(异步)
            强制这个异步任务创建一个新线程

        c. std::launch::deferred | std::launch::async
            意味着async的行为可能是创建新线程并立即执行，也可能是没有创建新线程，延迟调用 

        d. 不带额外参数 std::async(my_thread);
            默认值应该是c的情形，即两者都有可能，将选择权交给系统            


    6. std::async 和 std::thread的区别
        a. std::thread创建线程的时候，如果系统资源紧张创建线程失败，则整个程序就会报异常崩溃
        b. std::thread创建线程的方式，线程的返回值可通过全局量得到
           std::async创建异步任务，可能创建，也可能不创建线程，并且拿到线程入口函数k的返回值

        c. 如果用std::thread创建的线程太多，则可能创建失败，奔溃
           如果用std::async，一般不会报异常奔溃，因为系统资源紧张导致无法创建新线程的时候，std::async()就
           不会创建新线程，而是后续哪个线程调用了 get()请求结果，则异步任务就运行在那个线程上。
           
        d. 如果想要std::async必须创建新线程，使用std::launch::async
            则需要承担系统资源    

        c. 经验： 一个程序中，线程数量一般不会超过100-200,时间片    


    7. std::async()不加参数的不确定性解决    
        等价于std::async(std::launch::async | std::launch::deferred)
        不能确定系统是否会创建新线程
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
            //mycout = mycout + 1;
        }

    }

    int get_cout() {
        return this->mycout; 
    }
};


int my_thread() {

    cout << "thread ID: " << std::this_thread::get_id() << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    return 1;
}


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
    //B_atomic ba;
    //std::thread myobj1(&B_atomic::my_thread, &ba);
    //std::thread myobj2(&B_atomic::my_thread, &ba);
    //std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    //ba.set_ifend(true);  //对原子操作的写操作，让程序自动运行结束
    //myobj1.join();
    //myobj2.join();
    

    //4. std::async()
    cout << "Main Start...ID: " << std::this_thread::get_id() << endl;
    //std::future<int> result = std::async(std::launch::deferred | std::launch::async, my_thread);
    //std::future<int> result = std::async(my_thread);
    //cout << result.get() << endl;


    //5. std::async()延迟调用
    //问题：std::future<int> result = std::async(my_thread);  这个异步任务是否被推迟执行(是否创建了新线程)
    std::future<int> result = std::async(my_thread);
    std::future_status status = result.wait_for(std::chrono::seconds(0));
    if(status == std::future_status::timeout) {  //使用线程启动

        cout << "NewThread---status: timeout!" << endl;
    }else if(status == std::future_status::ready) {  //使用线程启动
    
        cout << "NewThread---status: successfully returned!" << endl; 
    }else  if(status == std::future_status::deferred) {  //延迟调用,系统资源紧张了

        cout << "status: delayed!" << endl;
        cout << result.get() << endl;  //get()所在线程中调用my_thread 
    }

    cout << "Main End!" << endl;
    return 0;
}
