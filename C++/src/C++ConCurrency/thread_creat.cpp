#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <thread>

using namespace std;

/*
   chp1.  线程启动，结束，创建线程多种方法


   1. 演示线程运行的开始和结束 

      创建线程对象(子线程开始执行):  thread  my(_addr);  //其中_addr表示可调用对象(函数，仿函数)
      线程运行(阻塞主线程，等待子线程执行完毕):  my.join();  //main进程(主线程--->my线程---->主线程)
      线程运行(主线程和子线程各自运行,子线程相等于被运行时库(CRT)接管,守护进程): my.detach();  
      判断是否可以成功使用join()或者detach(): joinable();


   2. 其他创建线程方式

    2.1 使用仿函数作为地址创建线程
        调用两次拷贝构造函数 
        当使用detach的时候，因为主线程会提前结束，所以不能使用main函数中的地址空间(比如引用)
        但是作为参数的对象本身会被赋值到线程中


    2.2 用lamba表达式创建现场那

*/



void my_print() {

    cout << "my thread Start! " << endl;


    cout << "my thread End!" << endl;
}


class th{

    public:
        th() {}
        th(int _mem) : mem(_mem) {
            cout << this->mem << "ctor start" << endl; 
        }

        th(const th& _th) : mem(_th.mem + 1) {
            cout << this->mem << "copy ctor start" << endl; 
        }

        ~th() {
            cout << this->mem << "dtor start" << endl; 
        } 


        void operator()() {
            cout << "my thread Start!" << endl;


            cout << "my thread End!" << endl;

        }

    private:
        int mem = 0;
};


int main(void)   //主线程从main返回，整个进程执行完毕
{

    //1. 使用函数
    /*thread mythread1(my_print);*/    // 被定义之后，线程立即开始执行
    // mythread1.join();   //主线程一定最后退出
    //mythread1.detach();   //主线程可能先退出
    //cout << mythread1.joinable() << endl;



    //2. 使用仿函数
    th _th(0);
    thread mythread2(_th);  //这里不能使用临时对象
    mythread2.detach();
    //mythread2.join();



/*  //3. 使用lambda表达式*/
    //auto lamthread = [] {
        //cout << "my thread Start" << endl;    


        //cout << "my thread End" << endl;
    //};
    //thread mythread3(lamthread);
    //mythread3.join();
    //mythread3.detach();



    cout << "Main Thread End!" << endl;
    return 0;
}
