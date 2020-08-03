#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <thread>

using namespace std;

/*
    演示线程运行的开始和结束 
    *    main进程---->主线程 
    *    主线程(main) + thread(初始函数) 



*/


void my_print() {

    cout << "my thread Start! " << endl;




    cout << "my thread End!" << endl;
}



int main(void)
{
    
    std::thread mythread(my_print);
    mythread.join();


    cout << "I love China!" << endl;
    return 0;
}
