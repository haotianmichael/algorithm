#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;


/*
动机:
    在软件构建过程中，某些对象的状态如果改变，其行为也会随之而发生变化，比如文档处于只读状态，
    其支持的行为和读写状态支持的行为就可能完全不同。

    如何在运行时根据对象的状态来透明的更改对象的行为？而不会为对象操作和状态转化之间引入紧耦合？
*/
enum NetworkState{
    Network_Open,
    Network_Close,
    Network_Connect,
};
class NeworkProcessor{
    NetworkState state;

    public:
    void Operation1() {
        if(state == Network_Open) {   //对象的状态发生改变，其行为也会发生改变
        
            //....
           state = Network_Close;   //交换枚举量
        }else if(state == Network_Close) {
            
           //...
           state = Network_Connect; 
        }else if(state == Network_Connect) {
        
            //...
           state = Network_Open; 
        }
    
    }

    void Operation2() {
        if(state == Network_Open) {
        
            //...
            state = Network_Connect;
        }else if(state == Network_Close) {
        
            //...
           state = Network_Open; 
        } else if(state == Network_Connect) {
        
            //...
           state = Network_Close; 
        } 
    
    }


    void Operation3() {
    }
};


/*
定义:
    允许一个对象在其内部状态改变的时候改变它的行为。从而使对象看起来似乎修改了其行为。
 
*/
class NetworkState_new{
    public:
        NetworkState_new* pNext;
        virtual void Operation1() = 0;
        virtual void Operation2() = 0;
        virtual void Operation3() = 0;
        virtual ~NetworkState_new();
};

class OpenState : public NetworkState_new{
    
    static NetworkState_new* m_instance;
    public:
    
    static NetworkState_new* getInstance() {   //Singleton模式
        if(m_instance == nullptr) {
            m_instance = new OpenState(); 
        }
        return  m_instance; 
    }

    void Operation1() {
    
        //...
        pNext = CloseState::getInstance();  //交换对象    状态切换
    }

    void Operation2() {
    
        //...
        pNext = ConnectState::getInstance();
    }
    
    void Operation3() {
    
        //...
        pNext = OpenState::getInstance();
    }

    ~OpenState() {
    }
};

class CloseState : public NetworkState_new{

    static NetworkState_new* m_instance;

    public:

    static NetworkState_new* getInstance() {   //Singleton
        if(m_instance == nullptr) {
            m_instance = new OpenState(); 
        }
        return  m_instance; 
    }

    void Operation1(){
    }

    void Operation2(){
    }

    void Operation3() {
    }

    ~CloseState(){
    }
};

class ConnectState : public NetworkState_new{
    NetworkState_new* m_instance;

    public:

    NetworkState_new* getInstance(){
        if(m_instance == nullptr) {
            m_instance = new  OpenState();
        }
        return m_instance;
    }

    void Operation1() {
    } 

    void Operation2() {
    }

    void Operation3() {
    }

    ~ConnectState() {
    }
};

class NetworkProcessor_new{
    public:


    NetworkState_new* state;

    NetworkProcessor_new(NetworkState_new* New) : state(New){
    }

    void Operation1() {
        //...
        state->Operation1(); 
        state = state->pNext;   //更新状态
        //...
    }


    void Operation2() {
        //...
        state->Operation2();
        state = state->pNext;
        //...
    }


    void Operation3() {
        //...
        state->Operation3();
        state = state->pNext;
       //... 
    }
};


/*
总结: 
    State模式将所有与一个特定状态相关的行为都放入一个State的子类对象中，在对象状态切换的时候，
    切换相应的对象；但同时维持State的接口，这样实现了具体操作与状态切换之间的解耦。

    为不同的状态引入不同的对象使得状态装换变得更加明确，而且可以保证不会出现状态不一致的情况，因为
    转换是原子性的——即要么彻底转换过来，要么不转换。

    如果State对象没有实例变量，那么各个上下文可以共享同一个State对象，从而节省对象开销。
*/
