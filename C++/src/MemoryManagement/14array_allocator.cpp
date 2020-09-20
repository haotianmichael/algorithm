#include <iostream>
#include <algorithm>
#include <memory>

/*
 
    该分配器直接使用静态数组进行分配，感觉很像placement new 的手法
    测试程序并没有完成测试，缺少std::tr1库 
 
*/


//数组分配器, 从数组中直接分配
template<typename _Tp, typename _Array = std::tr1::array<_Tp, 1>>  //底部是C++数组   静态数组（不需要释放）——所以deallocate()是空的
class array_allocator : public array_allocator_base<_Tp>
{
  public:
    typedef size_t size_type;
    typedef _Tp value_type;
    typedef _Array array_type;
    
  private:
  array_type* _M_array; //指向数组的指针
  size_type _M_used;
  
  public:
    array_allocator(array_type* __array = NULL)throw() : _M_array(_array), _M_used(size_type()){}
}


using namespace std;
using namespace std::tr1;
using namespace __gnu::cxx;

int my[65535];
array_allocator<int, array<int, 65535>>
  myalloc(&my);   //初始化
  
  //分配空间   但是不会回收释放过的空间
  int* p1 = myalloc::allocate(1);
  
  int* p2 = myalloc.allocate(3);
  
  myalloc.deallocate(p1);
  myalloc.deallocate(p2);
  
  }
