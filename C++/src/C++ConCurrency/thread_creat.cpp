#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <thread>

using namespace std;

/*
   1. 演示线程运行的开始和结束 

      创建线程对象(子线程开始执行):  thread  my(_addr);  //其中_addr表示可调用对象(函数，仿函数)
      线程运行(阻塞主线程，等待子线程执行完毕):  my.join();  //main进程(主线程--->my线程---->主线程)
      线程运行(主线程和子线程各自运行,子线程相等于被运行时库(CRT)接管,守护进程): my.detach();  
      判断是否可以成功使用join()或者detach(): joinable();


   2. 其他创建线程方式



 */


void my_print() {

    cout << "my thread Start! " << endl;


    cout << "my thread End!" << endl;
}


class th{

    public:
        void operator()() {
            cout << "my thread Start!" << endl;


            cout << "my thread End!" << endl;

        }

};


int main(void)   //主线程从main返回，整个进程执行完毕
{

    /*     thread mythread1(my_print);*/
    //mythread1.detach();
    //cout << mythread1.joinable() << endl;



    th _th;
    thread my(_th);  //这里不能使用临时对象
    my.join();




    cout << "Main Thread End!" << endl;
    return 0;
}
