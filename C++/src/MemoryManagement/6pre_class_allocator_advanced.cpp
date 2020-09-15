#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

/*
    类的内存分配器精简版本
        优点: next指针变成Embedded Pointer
        缺点: 内存池最终delete后并没有还给OS ,并没有调用free(不是内存泄漏)

 
 */
class Airplane
{
    public:
        Airplane (){}
        ~Airplane (){}

    private:
        //声明
        struct AirplaneRep{  
            unsigned long miles;  //8字节
            char type;  //1字节
        };
    private:
        //定义:union的巧妙之处，在于未正式分配的是时候选择其中的8个字节作为指针
        union {  //16字节 Embedded Pointer
            AirplaneRep rep;
            Airplane* next; 
        };
    public:
        unsigned long getMiles() {return rep.miles;}
        char getType() {return rep.type;}
        void set(unsigned long m, char t) {
            rep.miles = m;
            rep.type = t; 
        }
    public:
        static void* operator new(size_t size);
        static void operator delete(void* deadObj, size_t size); 
    private:
        static const int BLOCK_SIZE;
        static Airplane* headOfFreeList;
};
Airplane* Airplane::headOfFreeList;
const int Airplane::BLOCK_SIZE = 512;


//重载
void* Airplane::operator new(size_t size) {

    if(size != sizeof(Airplane)) {  //继承发生就会有问题
        return ::operator new(size);
    }

    Airplane* p = headOfFreeList;
    if(p){
        headOfFreeList = p->next;
    }else{
        Airplane* newBlock = static_cast<Airplane*>(::operator new(BLOCK_SIZE * sizeof(Airplane))); 

        for(int i = 1; i < BLOCK_SIZE - 1; i ++) 
            newBlock[i].next = &newBlock[i+1];

        newBlock[BLOCK_SIZE - 1].next = 0;
        p = newBlock;
        headOfFreeList = &newBlock[1];
    }
    return p;
}

//重载
void Airplane::operator delete(void* deadObj, size_t size) {

    if(!deadObj) return;
    if(size != sizeof(Airplane)) {  //继承情况
        ::operator delete(deadObj); 
        return;
    }

    Airplane* carcass = static_cast<Airplane*>(deadObj);
    carcass->next = headOfFreeList;
    headOfFreeList = carcass;
}

int main(void)
{
    //cout << sizeof(unsigned long)  << endl;  8Bytes
    //cout << sizeof(Airplane*) << endl;  8Bytes
    cout << sizeof(Airplane) << endl; //16字节
    size_t const N = 100;
    Airplane* p[N];

    for(size_t i = 0; i < N; i ++) {
        p[i] = new Airplane; 
    }

    p[1]->set(1000, 'A');
    p[2]->set(2000, 'B');
    p[3]->set(3000, 'C');

    for(int i = 0; i < 10; i ++) {
        cout << p[i] << endl; 
    }


    for(size_t i = 0; i < N; i ++) {
        delete p[i]; 
    }
    return 0;
}
