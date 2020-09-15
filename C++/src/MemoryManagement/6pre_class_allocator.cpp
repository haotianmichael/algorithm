#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;


class Screen
{
public:
    Screen (int x) : i(x) {}
    virtual ~Screen () {}
    int get() {return i;}


    //重载
    static void* operator new(size_t);
    static void operator delete(void*, size_t);
private:
    Screen* next;
    static Screen* freeStore;
    static const int screenChunk;
private:
    int i;
};

Screen* Screen::freeStore = 0;  //最开始的头结点
const int Screen::screenChunk = 24;


void *Screen::operator new(size_t size) {  //size为元素大小,一次分配24个

    Screen* p;
    if(!freeStore) {
        //linked list 是空的，申请一大块
        size_t chunk = screenChunk* size;
    
        freeStore = p = reinterpret_cast<Screen*>(new char[chunk]);


        //将这一块分割成片，当做linked list串接起来
        for(; p != &freeStore[screenChunk - 1]; ++p) {
            p->next =  p + 1; 
        }
        p->next = 0;
    }
    p = freeStore;
    freeStore = freeStore->next;
    return p;
}


void Screen::operator delete(void* p, size_t) {

    //将delete object 插回到free list前端
    (static_cast<Screen*>(p))->next = freeStore;
    freeStore = static_cast<Screen*>(p);
}

int main(void)
{


    
    return 0;
}
