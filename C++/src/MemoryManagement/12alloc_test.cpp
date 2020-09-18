#include <iostream>
#include <algorithm>
#include <list>
#include <cstring>
//#include <ext/pool_allocator.h>



/*
    GNU4.9下 __pool_alloc测试 
*/
static long long coutNew = 0;
static long long timesNew = 0;

void *myAlloc(size_t size) {
    return malloc(size);
}

void myFree(void* ptr) {
    return free(ptr);
}

void* operator new(size_t size) {
    coutNew += size;
    ++timesNew;
    return myAlloc(size);
}

void* operator new[](size_t size){
    return myAlloc(size);
}

void operator delete(void* ptr, size_t) {
    myFree(ptr);
}

void operator delete[](void* ptr, size_t) {
    myFree(ptr);
}
    


/*
    使用标准的分配器——使用::operator new/delete (malloc/free) 
*/
void TEST_OPERATOR_NEW() {
    coutNew = 0;
    timesNew = 0;
    std::list<double> lst;

    for(int i =0 ; i < 1000;  ++i){
        lst.push_back(i); 
    }

    std::cout << "::contNew = " << ::coutNew << std::endl;
    std::cout << "::timesNew = " << ::timesNew << std::endl;

    return;
}

/*
    使用新型分配器__gnun_cxx::__pool_alloc 
*/
template<typename  T>
        using listPool = std::list<T, __gnu_cxx::__pool_alloc<T>>;
void TEST_ALLOC() {

    coutNew = 0;
    timesNew = 0;
    listPool<double> lst;
    for(int i = 0; i < 1000; i ++) {
        lst.push_back(i); 
    }
    
    std::cout << "::countNew = " << ::coutNew << std::endl;
    std::cout << "::timeNew = " << ::timesNew << std::endl;
    return;
}

int main(void)
{
    
    //TEST_OPERATOR_NEW();
    TEST_ALLOC();

    return 0;
}
