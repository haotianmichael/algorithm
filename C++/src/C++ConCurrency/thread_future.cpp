#include <iostream>
#include <algorithm>
#include <cstring>
#include <thread>
#include <mutex>
#include <future>

using namespace std;

/*
 
    chp9. std::future其他成员函数, shared_future，atomic

    1. std::future其他成员函数
        std::future_status的三种状态
            ready
            timeout
            deferred


    3. 原子操作std::atmoic

        3.1 原子操作概念引出范例


        3.2 基本的std::atomic用法范例
 
*/

int mythread() {

    cout << "mythread() Start---ID: " <<  std::this_thread::get_id() << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    cout << "mythread End---ID: " << std::this_thread::get_id() << endl;
    return 5;
}



int main(void)
{
    
    cout << "Main Start---ID: " << std::this_thread::get_id() << endl;
    std::future<int> result = std::async(std::launch::deferred, mythread);
    //cout << result.get() << endl;

    //枚举类型
    //wait_for 等待一定的时间
    //std::future_status status = result.wait_for(std::chrono::seconds(1));
    std::future_status status = result.wait_for(std::chrono::seconds(6));
    if(status == std::future_status::timeout) {   //表示线程还没有执行完毕
        cout << "status: timeout!" << endl; 
    }else if(status == std::future_status::ready){   //表示成功返回
        cout << "status: successfully returned" << endl;    
        cout << result.get() << endl; 
    }else if(status == std::future_status::deferred) {    //如果async的第一个参数被设置为std::launch::defered，则成立
        cout << "status: delayed!" << endl; 
        //cout << result.get() << endl;  //入口函数会在主线程中执行
    }

    cout <<  "Main End!" << endl;
    return 0;
}
