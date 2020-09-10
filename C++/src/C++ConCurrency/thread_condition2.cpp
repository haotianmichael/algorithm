#include <iostream>
#include <algorithm>
#include <cstring>
#include <thread>
#include <mutex>
#include <deque>

using namespace std;
/*
    C++条件变量的生产者-消费者模型 
 
*/


class condition{

    std::deque<int> my_queue;
    std::condition_variable my_cond;
    std::mutex my_mutex;


    public:
    void producer(){   //生产者

        int cout = 10;
        while(cout > 1) {
            
            std::unique_lock<std::mutex> locker(my_mutex);
            my_queue.push_front(cout);
            locker.unlock();
            my_cond.notify_one();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            cout --;
        } 

        return;
    }

    void consumer() {
        int data = 0;
        while(data != 1) {
            std::unique_lock<std::mutex>  locker(my_mutex);
            while(my_queue.empty()) {
                my_cond.wait(locker);
            } 
            data = my_queue.back();
            my_queue.pop_back();
            locker.unlock();
            std::cout << "consumer get a value from producerL " << data << endl;
        }

    }

};


int main(void)
{

    condition cc;
    std::thread ft1(&condition::producer, &cc);
    std::thread ft2(&condition::consumer, &cc);

    ft1.join();
    ft2.join();


    return 0;
}

