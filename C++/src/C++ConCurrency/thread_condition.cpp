#include <iostream>
#include <algorithm>
#include <cstring>
#include <thread>
#include <mutex>
#include <list>

using namespace std;

/*

   chp7. condition_variable, wait, notify_one, notify_all

   1. 条件变量std::condition_variable, wait(), notify_one()
        线程A:  等待一个条件满足
        线程B:  专门往消息队列中传递数据(满足条件之后(触发)通知线程A)
    thread_unique.cpp老式的写法中，使用while或者轮训的方式来检测order队列中是否为空(见outMsgQueue()函数)，其实是非常消耗性能的~  
    为了避免不断询问，而换成当队列空的时候通知线程去取，效果肯定会更好一些。

        条件变量std::condition_variable是一个和条件相关的类, 等待一个条件达成。这个类需要和互斥量配合工作。
    需要生成这个类的对象。   

   2. notify_all()  



 */
class Game{

    std::mutex my_mutex_a;
    std::condition_variable my_cond;
    std::list<int>  order;

    public:

    void inMsgQueue() {
        for(int i = 0; i < 10; i++) {

            std::unique_lock<std::mutex> ulock(my_mutex_a);
            cout << "inMsgQueue Start------Insert Msg: "  << i<< endl;
            order.push_back(i);         
            my_cond.notify_one();  //尝试将wait线程唤醒
            
        }
    }

    void outMsgQueue() {

        while(true) {
            
            std::unique_lock<std::mutex>  my_lock(my_mutex_a);

            /*
                wait(para1, para2)函数  
                如果para2返回值为true,wait就返回。如果para2返回值是false，那么wait()将解锁互斥量，并堵塞到本行，直到其他某个
            线程调用notify_one()成员函数为止。

                wait(para)函数
                相当于para2参数为false——堵塞直到notify_one()被调用 

                wait()被激活后，继续不断尝试重新获取互斥量锁，如果获取不到，则还是wait还是会继续尝试直到
                拿到互斥锁,如果获取到了，wait()就继续执行

            */
            my_cond.wait(my_lock, [this]{   //lambda表达式就是一个可调用对象(函数)
                    if(!order.empty())  
                        return true;
                    else
                        return false;
                    
                    });     //条件变量和互斥量配合使用
        } 
    }

};

int main(void)
{

    Game g;
    std::thread out(&Game::outMsgQueue, &g); 
    std::thread in(&Game::inMsgQueue, &g); 

    in.join();
    out.join();
    return 0;
}
