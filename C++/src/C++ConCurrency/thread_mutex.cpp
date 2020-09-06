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
            先lock,操作临界区，unlock

        2.2  std::lock_guard()类模板


    3. 死锁
        3.1  死锁演示


        3.2  死锁的解决办法


        3.3  std::lock()函数模板


        3.4  std::lock_guard的std::adopt_lock参数
 
*/

class Game{
    public:
        void inMsgRecQueue() {
            for(int i = 0; i < 10; i ++) {
                my_mutex.lock();
                cout << "inMsgRecQueue Start-----Insert Msg:" << i << endl; 
                MsgRecQueue.push_back(i);
                my_mutex.unlock();
            } 
            return;
        }


        void outMsgRecQueue() {
            for(int i = 0; i < 10; i ++) {
                if(!MsgRecQueue.empty()) {
                      int command = MsgRecQueue.front();   
                      cout << "OutMsgRecQueue Start-----Pop Msg:"  << command << endl;
                      MsgRecQueue.pop_front(); 
                }else {
                      cout << "Queue Empty Now!" << endl; 
                }
            }
            return;    
        }
    private:
        list<int> MsgRecQueue;   //共享数据
        std::mutex my_mutex;   //互斥量
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
