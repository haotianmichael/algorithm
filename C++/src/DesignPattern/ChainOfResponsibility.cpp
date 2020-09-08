#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>


using namespace std;

/*
   有些过时
   动机: 

   在软件构建过程中，一个请求可能会被多个对象处理，但是每个请求在运行时只能有一个接受者。
   如果显式指定，将必不可少的带来请求者与接受者的紧耦合。

   如何使请求的发送者不需要指定具体的接受者？让请求的接受者自己在运行时决定来处理请求，从而使两者解耦。
 */
enum reqType{
    REQ_HANDLER1,
    REQ_HANDLER2,
    REQ_HANDLER3
};
class Reqest{

    string descritption;
    reqType reqT;
    public:
    Reqest(const string& desc, reqType _req) : descritption(desc), reqT(_req) {
    }
    reqType getReqType() const{
        return reqT;
    }
    std::string getDescription() const{
        return descritption; 
    }
};


class ChainHandler{

    ChainHandler* nextChain;
    void sendRequestToNextHandler(const Reqest& req) {
        if(!nextChain) {
            nextChain->handle(req); 
        }
    }

    protected:
    virtual bool canHandRequest(const Reqest& req) = 0;
    virtual void processRequest(const Reqest& req)  = 0;
    virtual ~ChainHandler() {}

    public:
    ChainHandler() {nextChain = nullptr;}  //初始化
    void setNextChain(ChainHandler* next) { nextChain = next; }

    void handle(const Reqest& req) {
        
        if(canHandRequest(req)) {
            processRequest(req);
        }else {
            sendRequestToNextHandler(req);
        } 
    }

};


class Handler1 : public ChainHandler{
    public:
        virtual ~Handler1() {}

    protected:
        virtual bool canHandRequest(const Reqest& req) {
            return req.getReqType() == reqType::REQ_HANDLER1;    
            //return false;
        }

        virtual void processRequest(const Reqest& req) {
            cout << "Handler1 is handling request: " << req.getDescription() << endl;
        }

};

class Handler2 : public ChainHandler{
public:
    virtual ~Handler2 ();

protected:
    virtual void processRequest(const Reqest& req) {
        cout << "Handler2 is handlingn request" << req.getReqType() << endl;  
    }

    virtual bool canHandRequest(const Reqest& req) {
        return req.getReqType() == reqType::REQ_HANDLER2;  
        //return false;
    }
};


class Handler3 : public ChainHandler
{
public:
    virtual ~Handler3 ();

protected:
    virtual void processRequest(const Reqest& req) {
        cout << "Handler3 is handling request: " << req.getDescription() << endl;
    }

    virtual bool canHandRequest(const Reqest& req) {
        return req.getReqType() == reqType::REQ_HANDLER3; 
    }
};

int main(void)
{
    Handler1 h1;
    Handler2 h2;
    Handler3 h3;
    h1.setNextChain(&h2);    
    h2.setNextChain(&h3);

    Reqest req("process task...", reqType::REQ_HANDLER3);
    h1.handle(req);
    return 0;
}

/*
定义:   
   使多个对象都有机会处理请求，从而避免请求的发送者和接受者之间的耦合关系。
   将这些对象连成一条链，并沿着这条链传递请求，直到有一个对象处理它为止。
*/


/*
 总结:
    Chain Of Resposibility模式的应用场合在于“一个请求可能有多个接受者，但是最终真正的接受者只有一个”
    这时候请求发送者与接受者的耦合有可能出现“变化脆弱”的症状，职责链的目的就是将二者解耦，从而更好
    的应对变化。


    应用了该模式后，对象的职责分派将更具有灵活性。我们可以在运行时动态添加/修改请求的处理职责。

    如果请求传递到职责链的末尾任然得不到处理，应该有一个合理的缺省机制。这也是每一个接受对象的责任，
    而不是发出请求的对象的责任。
*/
