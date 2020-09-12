#include <iostream>
#include <algorithm>
#include <cstring>
#include <thread>
#include <mutex>
#include <future>


using namespace std;



/*
 
    chp9. std::future其他成员函数，shared_future, atomic

    2. std::shared_future(类模板)
        std::future.get()  是将future的数据转移给了result
        std::shared_future.get() 是将数据拷贝给了result
*/


int my_thread1(int para) {
    
    cout << "my_thread1() Start---ID: " << std::this_thread::get_id() << endl;
    cout << "my_thread1's para is: " << para << endl;;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    cout << "my_thread1 End---ID: " << std::this_thread::get_id() << endl;
    return 8;
}


void my_thread2(std::future<int> &tmp) {
    cout << "my_thread2 Start---ID: " << std::this_thread::get_id() << endl;
    cout << tmp.get() << endl;
    //cout << tmp.get() << endl;  移动语义
    cout << "my_thread2 End---ID: " << std::this_thread::get_id() << endl;
}

void my_thread3(std::shared_future<int> &tmp) {
    
    cout << "my_thread3 Start---ID: " << std::this_thread::get_id() << endl;
    cout << tmp.get() << endl;
    cout << "my_thread3 End---ID: " << std::this_thread::get_id() << endl;
}


void my_thread4(std::shared_future<int> &tmp) {
    
    cout << "my_thread4 Start---ID: " << std::this_thread::get_id() << endl;
    cout << tmp.get() << endl;
    cout << "my_thread4 End---ID: " << std::this_thread::get_id() << endl;
}



int main(void)
{
    cout << "Main Start---ID: " << std::this_thread::get_id() << endl;
    
    std::packaged_task<int(int)> mypt(my_thread1);
    std::thread t1(std::ref(mypt), 10);
    t1.join();

    //1. 使用std::future的移动语义，get()函数只能调用一次
    //std::future<int>  result = mypt.get_future();
    //std::thread  t2(my_thread2, std::ref(result));
    //t2.join();


    //2. 使用std::shared_future的拷贝语义，get()函数可以调用多次
    //std::shared_future<int>  shared_result1(std::move(result));  //通过std::future得到shared_future，需要转成右值
    //std::shared_future<int>  shared_result2(result.share());  //执行完毕之后shared_result种有值，而result里空了
    //auto val = result.valid();  查看result是否有效值
    std::shared_future<int> shared_result1(mypt.get_future());  //直接得到shared_future
    std::thread t3(my_thread3, std::ref(shared_result1));
    std::thread t4(my_thread4, std::ref(shared_result1));
    t3.join();
    t4.join();

    cout << "Main End!" << endl;
    return 0;
}
