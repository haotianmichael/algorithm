#include <iostream>
#include <algorithm>
#include <cstring>
#include <mutex>
#include <thread>
#include <future>
#include <atomic>
#include <list>


using namespace std;

/*

   chp11. 线程池谈，数量谈，总结
   1. 虚假唤醒, atomic
        当队列中没有数据的时候，唤醒线程,wait()中需要有第二参数，这个参数为lambda表达式来正确判断要处理的公共数据是否存在。
        atomic: 注意原子操作支持的运算符
            load()  | store()  两个函数

   2. 线程池
       2.1 场景设想
         服务器程序——客户端: 每来一个客户端,创建一个新线程为该客户提供服务    
         网络游戏: 2万玩家,不可能都创建线程
         稳定性: 编写的线程偶尔被创建，奔溃
        
        线程池: 将一堆线程放到一起，统一管理；循环利用线程的方式叫线程池.

       2.2 实现方式
         在程序启动的时候，一次性的创建好一定数量的线程。
         在程序的执行过程中，不会再创建或者销毁(因此不会因为临时创建和销毁而消耗资源)
         出错率小，效率高，稳定性高

   3. 线程创建数量
        3.1 线程数量极限问题
            一个程序基本上2000个线程基本到头了, 在创建程序就会奔溃

        3.2 线程创建的数量建议
            a. 某些开发程序  接口提供商：创建线程数量 = CPU数量，CPU数量x2
                
            b. 一些业务(一个线程 = 一条执行通路)
            
            c. 一定的业务需求，尽量不要超过500个，能够控制在200个之内比较理想
                    线程越多，系统的效能反而会变慢

   4. 多线程总结    
        语言层面的多线程接口比系统层面的多线程更具有移植性 

*/
class Game{
    private:
    std::atomic<int> atm;
    std::mutex my_mutex;
    std::condition_variable my_cond;
    std::list<int> msg;

    public:
    //测试condition_variable条件变量
    Game() {}
    void in() {

        for(int i = 0; i < 10; i ++){
            cout << "msg in: " << i << endl; 
            
            std::unique_lock<std::mutex> my_lock(my_mutex);
            msg.push_back(i);
            //my_lock.unlock();
            my_cond.notify_one();
            //std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        }
        return;
    }


    void out() {
    
        while(true) {
            std::unique_lock<std::mutex> my_lock(my_mutex); 
            my_cond.wait(my_lock, [this]{    //lambda表达式中的判断用来处理虚假唤醒
                   if(!msg.empty()) 
                        return true;
                    else 
                        return false; 
                    });
        }
    
        cout << "msg out: " << msg.front() << endl;
        msg.pop_front();
        my_mutex.unlock(); 
    }


    //测试std::atomic
    Game(int a) : atm(a) {
        //atomic<int> a2 = a;   原子对象直接赋值不可以
        //atomic<int> a2(atm.load());  可通过原子对象的成员函数来完成赋值
        //atm.store(12);
    }


    void outAtm() {
    
        while(true) {
            cout << atm << endl;  //读Atm是原子操作，但是改行代码不是原子操作(cout本身就是一个函数)
        }
    }


    void inAtm() {
        for(int i =0 ;i  < 1000000; i++){
            atm += 1;  //原子操作 
            //atm = atm + 1; //不是原子操作
        }  
    
    }

};

int main(void)
{

    Game game(0);

    /*测试std::condition_variable*/
    //std::thread _in(&Game::in, &game);
    //std::thread _out(&Game::out, &game);
        

    /*测试std::atomic*/ 
    std::thread _in(&Game::inAtm, &game);
    std::thread _in2(&Game::inAtm, &game);
    std::thread _out(&Game::outAtm, &game);
    
    _in.join();
    _in2.join();
    _out.join();

    return 0;
}
