#include <algorithm>
#include <iostream>
#include <cstring>
#include <list>
//#include <ext/bitmap_allocator.h>
//#include <ext/malloc_allocator.h>
//#include <ext/new_allocator.h>
//#include <ext/__pool_allocator.h>
//#include <ext/mt_allocator.h>

using namespace std;

/*
   bitmap_allocator 
   部分源码:

   template<typename _Tp>
   class bitmap_allocator : private free_list{

   public:
         pointer allocate(size_type __n) {
               if(__n > this->max_size())
                   std::__throw_bad_alloc();
               if(__builtin_expect(__n == 1, true))
                   //一个元素 分配
                   return this->_M_allocate_single_object();
               else {
                   const size_type __b = __n * sizeof(value_type);
                    //一个以上直接调用malloc
                    return reinterpret_cast<pointer>(::operator new(__b));  
               }
   }


   void deallocate(pointer __p, size_type __n)throw {
           if(__builtin_expect(__p != 0, true)) {
               if(__builtin_expect(__n == 1, true))  //一个元素   释放
                   this->_M_deallocate_single_object(__p);
               else 
                   ::operator delete(__p);    //一个以上
           }
   }

};

*/

void test_list_with_special_allocatror() {

    cout << "\ttest_list_with_special_allocator" << endl;

    list<string, allocator<string>> c1;
    //list<string, __gnu_cxx::malloc_allocator<string>> c2;
    //list<string, __gnu_cxx::new_allocator<string>> c3;
    //list<string, __gnu::cxx::__pool_alloc<string>> c4;
    //list<string, __gnu::cxx::__mt_alloc<sting>> c5;
    //list<string, __gnu::cxx::_bitmap_allocator<string>> c6;


    int choice = 0;
    long value;
    cout << "select: ";
    cin >> choice;
    cout << "how many elements";
    cin >> value; 

    char buf[10];
    clock_t timeStart = clock();
    for(long i = 0; i < value; i ++) {
        try{
            snprintf(buf, 10, "%d", i);     
            switch (choice) {
                case 1:
                    c1.push_back(string(buf)); 
                    break;
                case 2:
                    c2.push_back(string(buf));
                case 3:
                    c3.push_back(string(buf));
                case 4:
                    c4.push_back(string(buf));
                case 5:
                    c5.push_back(string(buf));
                case 6:
                    c6.push_back(string(buf));
                default:
                    break; 
            } 
        }catch(exception& p) {
            cout << "" << i << " " << p.what() << endl;
            abort();
        }     
    }

    cout << "a lot of push_back(), milli-seconds";
    //test all allocators' allocate() & deallocate()

    int* p;
    allocator<int> alloc;
    //__gnu_cxx::malloc_allocator<int> alloc;
    //__gnu_cxx::new_allocator<int> alloc;
    //__gnu_cxx::__pool_alloc<int> alloc;
    //__gnu_cxx::_mt_alloc<int> alloc;
    //__gnu_cxx::_bitmap_allocator<int> alloc;
    p = alloc.allocate(1);
    alloc.deallocate(p, 1); 


    return ;
}




int main(void)
{
    test_list_with_special_allocatror();     
    return 0;
}




