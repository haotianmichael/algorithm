#include <iostream>
#include <vector>
#include <thread>
#include <list>


using namespace std;
/*
    chp3. 创建多个线程，数据共享问题分析 
 
    1. 创建和等待多个线程

        多个线程执行顺序是乱的，跟操作系统内部对线程的运行调度机制有关
        将线程放进容器中进行管理

    2. 数据共享问题分析
        2.1  只读的数据
            不需要加锁，操作无异常

        2.2  有读有写
            处理: 读写不能同时进行

        2.3  其他

    3. 共享数据的保护 
        简化网络游戏服务器。两个自己创建的线程:
                一个线程收集玩家命令(用数字代表)，并把命令数据写到一个队列中。
                一个线程从这个队列中取出玩家发出的命令,解析执行动作。
 
        解决办法: 互斥量        
*/
void myprint(int num) {

    cout << "Thread Start, No." << num << endl;


    
    cout << "Thread End, No." << num << endl;
}


class A{
    public:

        //将收到的消息(玩家命令)，收到一个队列中
        void inMsgRecQueue(){
            for(int j = 0; j < 10; ++j) {
                cout << "inMsgRecQueue Start, insert Msg: "  << j << endl; 
                msgRecvQueue.push_back(j); 
            } 
        } 

        //将数据从消息队列中取出
        void outMsgRecQueue() {
            for(int i =0 ; i < 10; i ++) {
                if(!msgRecvQueue.empty()) {

                    //消息不为空
                    int command = msgRecvQueue.front(); 
                    cout << "outMsgRecQueue Start, pop  Msg: "  << command << endl; 
                    msgRecvQueue.pop_front();
                } else {
                    //消息为空 
                    cout << "Queue Empty Now!" << endl;
                }
            }
            cout << "OUTQueue End" << endl; 
        }

    private:
        std::list<int> msgRecvQueue;   //命令队列
};

int main(void)
{
    
    //1. 创建和等待多个线程
            
    //vector<std::thread> threads;

    //创建10个线程，线程入口函数统一使用myprint
    //for(int i = 0; i < 10; i ++) {
        //threads.push_back(thread(myprint, i)); 
    //}

    //for(auto iter = threads.begin(); iter != threads.end(); iter++) {
        //iter->join(); 
    //}


    //2. 数据共享问题
    A myobj;
    std::thread myOutMsgObj(&A::outMsgRecQueue, &myobj);
    std::thread myInMsgObj(&A::inMsgRecQueue, &myobj);
    myInMsgObj.join();
    myOutMsgObj.join();
    cout << "Main Thread End" << endl;


    return 0;
}
