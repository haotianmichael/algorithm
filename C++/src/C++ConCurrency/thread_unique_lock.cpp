#include <iostream>
#include <algorithm>
#include <mutex>
#include <thread>
#include <vector>
#include <list>


using namespace std;


/*
    chp5.  unique_lock 
 
    1. unique_lock取代lock_guard 
        类模板()
            对mutex互斥量加锁/解锁管理,效率比lock_guard差一些
 
    2. unique_lock的第二个参数
        2.1 std::adopt_lock(必须提前lock)
            std::unique_lock<std::mutex>  ulock(my_mutex, std::adopt_lock); 
            表示这个互斥量已经被Lock过(前提是:必须使用Lock将该互斥量锁住)         
            该参数说明调用方线程已经拥有了该互斥的所有权，所以Lock_unique不会再构造函数中主动对该互斥量加锁

        2.2 std::try_to_lock(不能提前lock)
            std::unique_lock<std::mutex>  ulock(my_mutex, std::try_to_lock);
            尝试用mutex的lock去锁定mutex，但是如果没有锁定成功，也会立即返回而不会阻塞。(前提是:自己
            不能提前lock)
            if(myulock.owns_lock()) {}   //检查是否拿到锁

        2.3 std::defer_lock(不能提前lock)
            std::unique_lock<std::mutex> ulock(my_mutex_a, std::defer_lock);
            初始化了一个没有加锁的mutex，可以配合unique_lock的成员函数

    3. unique_lock的成员函数
        unique_lock绑定mutex,并管理该mutex
        3.1 lock()
           加锁，不需要担心手动解锁问题

        3.2 unlock()
           灵活控制解锁的时间(unique_lock和lock_guard一样在生命期内构造和释放) 

        3.3 try_lock()
            尝试给互斥量加锁，如果拿不到锁返回false，拿到了返回true(不阻塞)

        3.4 release()
            返回所管理的mutex对象指针，并释放所有权(即unique_lock和mutex无关系)           
            严格区分release和unlock的区别：
            std::unique_lock初始化操作是将unique锁和Mutex互斥量绑定在一起，而lock，unlock只是其中的操作，
            release相当于将两个对象分开，因此release之后一定要自行管理mutex互斥量(解锁)
            std::unique_lock<std::mutex> mytex(my_mutex_a);
            std::mutex *sp = mytex.release();
            sp.unlock();

    4. unique_lock所有权的传递
            std::unique_lock<std::mutex> sg(my_mutex);
            sg拥有my_mutex的所有权
            sg对象可以将my_mutex的所有权可以转移给sgg，但是不能复制
            std::unique_lock<std::mutex>  ssg(std::move(sg));  //所有权转移，和unique_ptr独占类型智能指针类似

            在函数中return一个局部unique_lock变量，发生移动构造函数(和unique_ptr类似)
*/

class Game_new{

    private:
    std::mutex my_mutex_a;
    std::mutex my_mutex_b;
    std::list<int> order;

    public:
    void inMsgRecQueue() {
        for(int i =0; i < 10; i ++) {

            //my_mutex_a.lock();
            //std::unique_lock<std::mutex> myulock(my_mutex_a, std::adopt_lock);
            /*
            std::unique_lock<std::mutex> myulock(my_mutex_a, std::try_to_lock);
            if(myulock.owns_lock()) {  //尝试拿到锁
                cout << "inMsgRecQueue Start----Insert Msg: " << i << endl;       
                order.push_back(i); 
            }else {
                cout << "inMsgRecQueue Failed to Lock" << endl;
            }
            */

            std::unique_lock<std::mutex> ulock(my_mutex_a, std::defer_lock);  //没有加锁的mutex
            if(ulock.try_lock()) {
            
                 cout << "inMsgRecQueue Start----Insert Msg: " << i << endl;       
                 order.push_back(i); 
            }else {
                cout << "inMsgRecQueue Failed to Lock" << endl;
            }
           //my_mutex_a.unlock();
        }
    }


    bool  _outMsgRecQueue() {
        
        //my_mutex_a.lock(); 
        std::unique_lock<std::mutex> myulock(my_mutex_a);
        //std::unique_lock<std::mutex> myulock(my_mutex_a, std::adopt_lock);
        //std::unique_lock<std::mutex> myulock(my_mutex_a, std::try_to_lock);

        std::chrono::milliseconds dura(20);
        std::this_thread::sleep_for(dura);   //睡眠20秒

        if(!order.empty()) {
            
            cout << "outMsgRecQueue Start-----Pop Msg: " << order.front() << endl; 
            order.pop_front();
            //my_mutex_a.unlock();
            return true;
        }else {
            //my_mutex_a.unlock();
            return false;
        }
    }

    void outMsgRecQueue() {
    
        for(int i =0 ; i < 10; i ++) {

            bool result = _outMsgRecQueue(); 
            if(!result) {
                cout<< "Queue Empty Now!" << endl; 
            }
        }
        return; 
    }

};



int main(void)
{
    
    Game_new ga;
    thread out(&Game_new::outMsgRecQueue, &ga);
    thread in(&Game_new::inMsgRecQueue, &ga);

    in.join();
    out.join();

    cout << "MainThread End!" << endl;
    return 0;
}
