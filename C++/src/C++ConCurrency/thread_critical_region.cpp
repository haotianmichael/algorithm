#include <iostream>
#include <algorithm>
#include <cstring>
#include <thread>
#include <mutex>
#include <list>


using namespace std;
/*
    chp10. windows临界区， 其他各种mutex互斥量
    1. Windows临界区
        几乎等价std::mutex 

    2. 多次进入临界区试验
        在同一个线程中，std::mutex不允许调用两次lock()(加锁)
        windows临界区概念是可以允许多调用几次

    3. 自动析构技术
        std::lock_guard(std::mutex)自动释放锁/同样不允许掉用两次

    4. recursive_mutex递归的独占互斥量
        std::mutex 独占互斥量  
        如果需要使用该互斥量，请首先考虑代码是否有优化空间(减少消耗)
        std::recursive_mutex 递归的独占互斥量(允许同一个线程，同一个互斥量多次被.lock())
        it's said 递归次数有限制

    5. 带超时的互斥量std::timed_mutex和std::recursive_timed_mutex
        std::mutex 拿不到锁，就会一直阻塞
        std::timed_mutex 带超时功能的递归独占互斥量(拿不到锁，卡一定的时间会自动继续执行而不会一直阻塞)        
        
        std::timed_mutex两个接口: 
try_lock_for: 等待一段时间，如果拿到锁就继续执行。(参数是一段时间)
try_lock_until: 在未来的时间点未到之前，如果拿到锁就继续执行。如果时间到了没拿到锁，也继续执行。 (参数是一个时间点)
std::recursive_timed_mutex: 允许同一个线程多次获取这个互斥量

*/

class Game{

    public:

        void inMsgRecQueue() {
        
            for(int i = 0; i < 10; i ++) {

                std::chrono::milliseconds timeout(100);
                if(my_time_mutex.try_lock_until(std::chrono::steady_clock::now() + timeout)){  //从现在开始等待100毫秒开始拿锁
                //if(my_time_mutex.try_lock_for(timeout)){  //等待100毫秒来尝试获取锁
                    //成功拿到锁
                    cout << "inMsgRecQueue Start---Insert Msg: " << i << endl;
                    my_time_mutex.unlock();
                }else {
                    //没有拿到锁
                    cout << "Can't get Lock. Waiting...." << endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
                //std::lock_guard<std::recursive_mutex> lock_guard(my_re_mutex);
                //std::lock_guard<std::mutex> lock_guard(my_mutex_a);
                //my_mutex_a.lock();
                //cout << "inMsgRecQueue Start---Insert Msg: " << i << endl;
                //MsgRecQueue.push_back(i); 
                //my_mutex_a.unlock();
            }
            return;
        }


        bool outMsgProc() {
        
            //std::lock_guard<std::recursive_mutex> lock_guard(my_re_mutex);
            //std::this_thread::sleep_for(std::chrono::minutes(10));
            std::lock_guard<std::mutex> lock_guard(my_mutex_a);
            //my_mutex_a.lock();
            if(!MsgRecQueue.empty()) {

                cout << "outMsgRecQueue Start---Pop Msg: " << MsgRecQueue.front() << endl;
                MsgRecQueue.pop_front();
                //my_mutex_a.unlock();
                return true;
            }else {
                //my_mutex_a.unlock();
                return false; 
            }
        }


        void outMsgRecQueue() {
            for(int i =0 ; i < 10; i ++) {
                //std::lock_guard<std::mutex> lock_guard(my_mutex_a);
                //std::lock_guard<std::recursive_mutex> lock_guard(my_re_mutex);
                bool result = outMsgProc(); 
                if(!result) {
                    cout << "Queue Empty Now!" << endl;
                } 
            }
            return;
        }



    private:
        list<int> MsgRecQueue;
        std::mutex my_mutex_a;
        std::recursive_mutex my_re_mutex; 
        std::timed_mutex my_time_mutex;
};

int main(void)
{

    Game game;
    std::thread out(&Game::outMsgRecQueue, &game);
    std::thread in(&Game::inMsgRecQueue, &game);

    in.join();
    out.join();

    cout << "MainThread End!" << endl;
    return 0;
}
