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

        notify_one()一次只能通知一个线程
   2. notify_all()  
        一次可以通知多个线程     


 */
class Game{

    std::mutex my_mutex_a;
    std::condition_variable my_cond;
    std::list<int>  order;

    public:

    void inMsgQueue() {
        for(int i = 0; i < 10; i++) {
            cout << "inMsgQueue Start------Insert Msg: "  << i<< endl;

            std::unique_lock<std::mutex> ulock(my_mutex_a);
            order.push_back(i);         
            ulock.unlock();
            std::chrono::milliseconds dura(2000);
            std::this_thread::sleep_for(dura);
            //my_cond.notify_one();  //尝试将wait线程唤醒
            my_cond.notify_all();   //尝试唤醒多个线程
            
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

                wait(para1, para2)被激活后，继续不断尝试重新获取互斥量锁，如果获取不到，则wait还是会继续尝试直到
                拿到互斥锁,如果获取到了
                a. 如果是wait(para1, para2)且para2为false, 则wait又对互斥量解锁并堵塞(等待唤醒)
                b. 如果wait(para1, para2)且para2为true，则wait(para1, para2)返回，流程继续执行(此时互斥锁还是wait手里)
                c. 如果wait(para1)则wait(para1)返回，流程继续执行，

            */
            my_cond.wait(my_lock, [this]{   //lambda表达式就是一个可调用对象(函数)
                    if(!order.empty())  
                        return true;
                    return false;
                    });     //条件变量和互斥量配合使用
        } 

        //流程执行到这里，可以保证队列中至少有一条数据，以及线程拥有互斥锁
        cout << "outMsgQueue Start------Pop Msg: "  << order.front() << endl;
        order.pop_front();
        my_mutex_a.unlock();   //可以提前解锁让另一个线程执行
    }

};

int main(void)
{

    Game g;
    std::thread out(&Game::outMsgQueue, &g); 
    std::thread out2(&Game::outMsgQueue, &g); 
    std::thread in(&Game::inMsgQueue, &g); 
    std::thread in2(&Game::inMsgQueue, &g); 

    out.join();
    out2.join();
    in.join();
    in2.join();
    return 0;
}
