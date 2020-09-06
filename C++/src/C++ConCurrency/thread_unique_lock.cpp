#include <iostream>
#include <algorithm>
#include <mutex>
#include <thread>
#include <vector>


using namespace std;


/*
    chp5.  unique_lock 
 
    1. unique_lock取代lock_guard 
 
    2. unique_lock的第二个参数
        2.1 std::adopt_lock_t

        2.2 std::try_to_lock_t


        2.3 std::defer_lock_t


    3. unique_lock的成员函数
        3.1 lock()


        3.2 unlock()


        3.3 try_lock()


        3.4 release()


    4. unique_lock所有权的传递

*/

