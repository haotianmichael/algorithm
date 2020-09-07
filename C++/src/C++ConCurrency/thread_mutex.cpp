#include <iostream>
#include <algorithm>
#include <thread>
#include <vector>
#include <list>
#include <mutex>

using namespace std;


/*
    chp4. 互斥量概念，死锁 

    1. 互斥量mutex的基本概念
        一个类对象，一把锁; 多个线程尝试用lock()成员函数来加锁
        只有一个线程可以锁定成功，成功的标志是lock()返回,如果没有成功会阻塞


    2. 互斥量的用法
        2.1 lock() unlock()
            lock,操作临界区，unlock

        2.2  std::lock_guard()类模板
            只能匹配unlock, 不可以搭配unlock使用
            std::lock_guard<std::mutext> m(my_mutex);
            原理: 在其构造函数中执行lock(), 在其析构函数中执行unlock();
            不足: 析构函数的作用域外才可以解锁，所以不是很难灵活.可以用大括号{}来灵活控制
            作用域生命周期

    3. 死锁
        3.1  死锁演示
                必要条件是至少两把锁: Lock_a, Lock_b
                两个线程： thread_a, thread_b
            线程thread_a执行的时候，这个线程先锁Lock_a成功，然后去锁Lock_b
            出现上下文切换，thread_b开始执行，先锁Lock_b成功，然后去锁Lock_a
            死锁发生。

        3.2  死锁的解决办法
            保证两个互斥量上锁的顺序一样，便不会死锁

        3.3  std::lock()函数模板
            一次至少锁住两个或者两个以上的互斥量
            不存在因为在多个线程中因为加锁顺序问题而导致的死锁问题。
            ***最后需要手动使用unlock解锁

        3.4  std::lock_guard的std::adopt_lock参数
        std::adopt_lock_t 一个结构体对象
            解决了std::lock()需要手动解锁的问题
            std::lock_guard(my_mutex_a, std::adopt_lock_t);        
            std::lock_guard(my_mutex_a, std::adopt_lock_t);        
 
*/

class Game{
    public:
        void inMsgRecQueue() {
            for(int i = 0; i < 10; i ++) {
                //std::lock_guard<std::mutex> myguard(my_mutex);
                //std::lock(my_mutex_a, my_mutex_b);
                my_mutex_a.lock();   //加锁
                //....
                my_mutex_b.lock();
                cout << "inMsgRecQueue Start-----Insert Msg:" << i << endl; 
                MsgRecQueue.push_back(i);
                my_mutex_b.unlock();
                my_mutex_a.unlock();
            } 
            return;
        }

        bool outMsgLULProc() {
        
            //std::lock_guard<std::mutex>  myguard(my_mutex);
            //std::lock(my_mutex_a, my_mutex_b);
           my_mutex_b.lock();
           my_mutex_a.lock();
           if(!MsgRecQueue.empty()) {
                
                cout << "OutMsgRecQueue Start-----Pop Msg:"  << MsgRecQueue.front() << endl;
                MsgRecQueue.pop_front();
                //数据处理
                my_mutex_a.unlock();  //一定要注意是在返回值之前解锁
                my_mutex_b.unlock();
                return true;    
           }else{
                 my_mutex_a.unlock();
                 my_mutex_b.unlock();
                 return false; 
           }
        }

        void outMsgRecQueue() {
            for(int i = 0; i < 10; i ++) {
               bool result = outMsgLULProc();
               if(!result){
                    cout << "Queue Empty Now!" << endl; 
               }
            }
            return;    
        }
    private:
        list<int> MsgRecQueue;   //共享数据
        std::mutex my_mutex_a;   //互斥量
        std::mutex my_mutex_b;
};



int main(void)
{
    Game mygame;
    thread in(&Game::inMsgRecQueue, &mygame); 
    thread out(&Game::outMsgRecQueue, &mygame);

    in.join();
    out.join();

    cout << "MainThread End!" << endl;

    return 0;
}
