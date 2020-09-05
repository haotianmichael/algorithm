#include <iostream>

using namespace std;


/*
动机:
    抽象的代价：虚函数，继承
    在软件系统中，经常有这样一种特殊的类，必须保障它们在系统内中存在一个实例，才能确保它们的
    逻辑正确性，以及良好的效率。

    如何绕过常规的构建器，提供一个机制来保证一个类只有一个实例。

    这应该是类设计者的责任，而不是使用者的责任。
    和工厂模式的区别，一个为了紧耦合，一个为了性能
*/
class Singleto_old{
    private:
        Singleto_old();
        Singleto_old(const Singleto_old& );

    public:
        static Singleto_old* getInstance();
        static Singleto_old* thread_getInstance1();
        static Singleto_old* thread_getInstance2();
        static Singleto_old* m_instance;
};
Singleto_old* Singleto_old::m_instance = nullptr;
//线程非安全版本(在单线程场景下可以使用)
Singleto_old* Singleto_old::getInstance() {  
    if(m_instance == nullptr) {
        m_instance = new Singleto_old(); 
    }
    return m_instance;
}
class Lock{

};
//加锁(高并发场景下，性能消耗比较大) 
Singleto_old* Singleto_old::thread_getInstance1() {
    Lock lock;
    if(m_instance == nullptr) {
       if(m_instance == nullptr){
           m_instance = new Singleto_old();
       } 
    }
    return m_instance;
}

//双检查锁，但由于内存读写REoeder不安全(无法使用)
Singleto_old* Singleto_old::thread_getInstance2() { 
    /*
reoeder:
        逻辑顺序:
            分配内存——构造函数——赋值运算(传递地址)   
        实际CPU乱序执行：
            分配内存——赋值运算(传递地址)——构造函数
    */
    if(m_instance == nullptr) {
       Lock lock;
       if(m_instance == nullptr){
           m_instance = new Singleto_old();
       } 
    }
    return m_instance;
}

/*
定义: 
    保证一个类仅有一个实例，并提供一个该实例的全局访问点。    
*/
class Singleto_new {
    private:
        Singleto_new();
        Singleto_new(const Singleto_new& );
    public:
        Singleto_new* getInstance();
        std::atomic<Singleto_new*> m_instance;
        std::mutex m_mutex;
};
    
//线程安全版本的单例模式
Singleto_new* Singleto_new::getInstance() {
    
    Singleto_new* tmp = m_instance.load(std::memory_order_relaxed);   //获取内存fence
    std::atomic_thread_fence(std::memory_order_acquire);
    if(nullptr == tmp) {
        std::lock_guard<std::mutex>  lock(m_mutex);
        tmp = m_instance.load(std::memory_order_relaxed);
        if(nullptr == tmp) {
            tmp = new Singleto_new;
            std::atomic_thread_fence(std::memory_order_release);   //释放内存
            m_instance.store(tmp, std::memory_order_relaxed);
        }
    }
    return tmp;
}
/*
总结: 
    Singleton模式中的实例构造器可以设置为protected以允许子类派生。
        
    Singleton模式一般不要支持拷贝构造函数和Clone接口，因为这有可能导致多个对象的实例，与
    Singleton模式的设计初衷相违背。

    如何实现多线程环境下安全的Singleton?注意对双检查锁的正确实现.
*/
