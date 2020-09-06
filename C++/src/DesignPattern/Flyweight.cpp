#include <iostream>
#include <map> 

using namespace std;

/*
动机: 
    在软件系统中，采用纯粹对象方案的问题在于大量细粒度的对象会很快充斥在系统中，从而
    带来很高的运行代价——主要指的是内存需求方面的代价。

    如何在避免大量细粒度对象问题的同时，让外部客户程序任然能够头命名你的适用面向对象的方式来
    进行操作。
*/



/*
定义: 
    运用共享技术有效的支持大量细粒度的对象。
    比如:字符串相关技术，线程池技术
*/
class Font{
    private:
        //unique object key
        string key;

        //object state
        //....

    public:
        Font(const string &key) {
        //... 
        }
};

class FontFactory{
    private:
        map<string, Font*> fontPool;

    public:        
        Font* GetFont(const string& key) {
            map<string, Font*>::iterator item = fontPool.find(key); 
            if(item != fontPool.end()) {   //和单例模式很相像
                return fontPool[key]; 
            } 
            else {
                
               Font* font = new Font(key); 
                fontPool[key] = font; 
                return font; 
            }
        }

        void clear() {
            //....
        }
};

/*
 总结:
    面向对象很好的解决了抽象性的问题，但是作为一个运行在机器中的程序实体，我们需要考虑对象的
    代价问题。Flyweight主要解决面向对象的代价问题，一般不触及面向对象的抽象问题。

    Flyweight采用对象共享的做法来降低系统中对象的个数，从而降低细粒度对象给系统带来的内存压力。
    在具体实现上，要注意对象状态的处理。

    对象的数量太大而导致对象内存开销加大——什么样的数量才算大？这需要自习根据具体应用情况进行评估，而不能凭空臆断。
*/
