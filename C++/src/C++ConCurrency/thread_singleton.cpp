#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <algorithm>
#include <cstring>


using namespace std;


/*
 
    chp6. singleton模式共享数据分析，解决,call_noce

    1. 设计模式概述
        不能为了用设计模式而用设计模式(先有开发需求，再有理论总结)

    2. 单例设计模式
        单例: 整个项目中，某些特殊的类，属于该类的对象只能创建一个。

    3. 单例设计模式共享数据问题分析，解决

        多线程情况下的单例设计模式，可能会因为m_instance成员变量的竞态而出错
        执行if(m_instance == nullptr)之后，如果有线程切换，则导致m_instance被实例两次。

        3.1 直接加锁
            每一次取单例对象，都需要加锁,造成性能损失
            std::unique_lock<std::mutex> my_lock(std::mutex my_mutex);

        3.2 双重检查
           if(m_instance != nullptr) 表示m_instance已经被new
           if(m_instance == nullptr) 不表示m_instance不一定没被new 
           提高效率：在进入条件之后同一时间时只有一个线程拿到锁。
            
           注意: 在使用双重锁定的时候，需要给m_instance加上voltaile
           原因: 必须保证在对m_instance修改之后将其值立刻写进主存(Main Memory)中，而不是暂时寄存在
        寄存器或者高速缓存中，即需要保证求值对其他线程可见。 

    4. std::call_once()
        功能: 能够保证函数a只会被调用一次。具备解决单例模式下的1次调用        
        需要和std::once_flag配合使用(函数调用成功后，会标记std::once_flag为已调用)


*/
std::mutex resource_mutex;
std::once_flag flag;
class MyCAS{   //单例类
    private:
        MyCAS(){}
        MyCAS(const MyCAS&){}

    private:
        volatile static MyCAS* m_instance;

    public:
        volatile static MyCAS* getInstance1() {
            if(m_instance == nullptr) {   //双重锁定
                std::unique_lock<std::mutex> myunlock(resource_mutex);  //自动加锁
                if(m_instance == nullptr) {
                   m_instance = new MyCAS(); 
                   static GC  gc;   //利用静态成员变量生命周期来析构内存
                 } 
            }
            return m_instance;
        }

        volatile static MyCAS* getInstance2() {
         
            std::call_once(flag, CreatOnce);   //只允许调用一次函数。具备互斥量的作用
            std::chrono::milliseconds dura(20000);
            std::this_thread::sleep_for(dura);


            return m_instance;
        }

        void func() {
            cout << "Test:" << endl; 
        }

        static void CreatOnce() {
            m_instance = new MyCAS();
            cout << "getMyCAS Over" << endl;
            static GC gc; 
        }

    public:
        class GC{   
            public:
                ~GC() {
                    if(!MyCAS::m_instance) {
                        delete MyCAS::m_instance; 
                        MyCAS::m_instance = nullptr;
                    } 
                }        
        };
};
volatile MyCAS* MyCAS::m_instance = nullptr;  //对静态成员赋初值

static void test_singleton1(void)
{
    volatile MyCAS* pa = MyCAS::getInstance1();
    volatile MyCAS* pb = MyCAS::getInstance1();
    printf("Address of pa is %p\n", pa);
    printf("Address of pb is %p\n", pb);

}



//线程安全的单例模式
void mythread() {
    cout << "Thread Start: " << endl;
    volatile MyCAS* pa = MyCAS::getInstance2();

}


int test_singleton2(void)
{
    
    std::thread tobj1(mythread);
    std::thread tobj2(mythread);
    tobj1.join();
    tobj2.join();

    cout << "Main Thread End!" << endl;
    return 0;
}


int main(void)
{
    test_singleton1();

    test_singleton2();
    return 0;
}
