#include <iostream>
#include <algorithm>
#include <cstring>
#include <thread>
#include <mutex>
#include <future>
#include <vector>


using namespace std;

/*

    chp8. async, future, packaged_task, promise
 
    这些函数需要区别到底是在主线程中调用的，还是在新创建的线程中调用的
    1. std::async, std::future创建后台任务并返回值
        希望线程返回一个结果：
            a. std::async(para1) 函数模板——启动一个异步任务(自动创建一个线程并开始执行对应的线程入口函数),然后返回一个std::future对象(对象里面就含有
            线程所返回的结果,可以通过调用std::future对象的成员函数get()来获取(get()函数会因为线程的执行情况而适当阻塞,不能调用多次))
            b. std::future 类模板,提供一种访问异步操作结果的机制(即这个结果没有办法马上得到，
            但是在将来线程执行完毕的时候就可以拿到结果)
            c. get()函数的语义是移动语义,因此不能重复调用

        通过向std::async()传递一个参数，该参数类型是std::launch类型(枚举类型)实现某种功能
            a. std::launch::deferred; 表示线程入口函数被延迟到std::futrue的wait()或者get()函数调用时才执行
            (如果不调用get()和wait()，整个线程甚至不会被创建)(如果调用了get()或者wait()，整个线程入口函数会在主线程中执行，并不创建新的线程) 
            b. std::launch::async;(后续会有深入讲解，这部分将的不对)


    2. std::packaged_task(类模板)
            a. 模板参数是各种可调用对象，通过std::packaged_task可以将各种可调用对象包装起来方便将来作为线程入口函数

            b. std::packaged_task包装起来的可调用对象可以直接调用，从这个角度来讲，std::packaged_task本身也是一个可调用对象


    3. std::promise (类模板)
        能够在某个线程中给它赋值,然后可以在其他线程中将这个值取出来使用
        
         


    4. 总结

*/

int my_thread() {

    cout << "my_thread() Start---ID: " << std::this_thread::get_id() <<  endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    cout << "my_thread() End---ID: " << std::this_thread::get_id() <<  endl;
    return 5;
}


int my_thread2(int para) {

    cout << "my_thread's para is " << para << endl;
    cout << "my_thread2() Start---ID: " << std::this_thread::get_id() << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    cout << "my_thread2() End---ID: " << std::this_thread::get_id() << endl;
    return 4;
}

void my_thread3(std::promise<int> &tmp, int calc){

    //线程的复杂运算  耗时5秒，得到结果result
    cout << "Computing Thread Starting---ID: "  << std::this_thread::get_id() << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    int result = --calc;  


    tmp.set_value(result);   //结果保存在tmp对象中
    return;
}

void my_thread4(std::future<int> &tmp) {

    cout << "Result Thread Start---ID: "  << std::this_thread::get_id() << endl;
    auto result = tmp.get();
    cout << "result = " << result << endl;
    return;
}

class A {
    public:
        int fun(int mypara) {
        
            cout <<   "fun-thread's para is:" << mypara << endl;
            cout << "fun-thread Start---ID: " << std::this_thread::get_id() << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            cout << "fun-thread End---ID: " << std::this_thread::get_id() << endl;
            return 5;
        }
};


int main(void)
{

    //1. std::async(para1) 使用线程入口函数
    cout << "Main Start---ID: " << std::this_thread::get_id() << endl;
    //std::future<int> result = std::async(my_thread);   //创建一个线程并开始执行
    //cout <<  "Result is: " << result.get() << endl;   //只有当线程执行完毕，get()才可以拿到结果
    //result.wait();  //等待线程返回，本身并不返回结果


    //2.1 std::async(para1) 使用类的成员函数作为入口函数
    //A a;
    //std::future<int> result = std::async(&A::fun, &a, 12);  //对象引用保证线程中是同一个对象
    /*当std::async(para1)函数最后不加上result.get()函数的时候，线程还是会持续等待到其执行完毕*/ 

    //2.2 使用std::launch::deferred参数的时候，不会创建新的线程，线程入口函数都会在主线程中执行
    //std::future<int> result = std::async(std::launch::deferred, &A::fun, &a, 13);
    //cout << result.get() << endl;;

    //2.3 使用std::launch::async参数；强制创建新线程
    //std::future<int> result = std::async(std::launch::async, &A::fun, &a, 13);
    //cout << result.get() << endl;;


    //3.1 std::packaged_task  将函数mythread2通过std::packaged_task包装起来
    //std::packaged_task<int(int)> mypt(my_thread2);
    //std::thread tl(std::ref(mypt), 10); 
    //tl.join();
    //std::future<int> result = mypt.get_future();    //std::future对象里包含有线程入口函数的返回值
    //cout << result.get() << endl;

    //3.2 std::packaged_task 使用lambda表达式直接调用(并没有启动线程)
/*    std::packaged_task<int(int)> mypt2([](int mypar){*/
            
            //cout << "Mypt2's para is: "  << mypar<< endl;
            //cout << "Mypt2 Start---ID: " << std::this_thread::get_id()  << endl; 
            //std::this_thread::sleep_for(std::chrono::milliseconds(5000)); 
            //cout << "Mypt2 End---ID: " << std::this_thread::get_id()  << endl;
            //return 3;
            //});
    /*mypt2(10);*/
    //std::future<int> result = mypt2.get_future();
    //cout << result.get() << endl;


    //3.3使用容器包装
/*    vector<std::packaged_task<int(int)>> task;*/
    //task.push_back(std::move(mypt2));  //移动
    //auto iter = task.begin();
    //mypt2 = std::move(*iter); //移动
    //task.erase(iter);  //删除第一个元素，迭代已经失效了，所以后续代码不可以再使用iter
    //mypt2(100);
    //std::future<int> result = mypt2.get_future();
    //cout << result.get() << endl;


    //4. std::promise
    //通过promise保存一个值，在将来通过将一个future绑定到一个promise上来得到这个值
    std::promise<int> prom;   //保存的值类型为int
    std::thread t4(my_thread3, std::ref(prom), 13);
    t4.join();
    std::future<int> result = prom.get_future();   //std::promise::get_future
    std::thread t5(my_thread4, std::ref(result));
    t5.join();


    cout << "Main END!" << endl;
    return 0;
}
