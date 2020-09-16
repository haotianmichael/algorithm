#include <algorithm>
#include <iostream>
//#include <ext/pool_allocator.h>


using namespace std;

/*
    测试对比GNU2.9和GNU4.9平台对cookie的优化情况:
    GNU2.9: 未优化
    GNU4.9: 优化
*/
template<typename  Alloc>
void cookie_test(Alloc alloc, size_t size) {
    typename  Alloc::value_type* p1, *p2, *p3;
    p1 = alloc.allocate(size);
    p2 = alloc.allocate(size);
    p3 = alloc.allocate(size);

    cout << "p1 = " << p1 << '\t';
    cout << "p2 = " << p2 << '\t';
    cout << "p3 = " << p3 << '\t';

    alloc.deallocate(p1, sizeof(typename  Alloc::value_type));
    alloc.deallocate(p2, sizeof(typename  Alloc::value_type));
    alloc.deallocate(p3, sizeof(typename  Alloc::value_type));
}

int main(void)
{
    //GNU 4.9
    //cout << sizeof(__gnu_cxx::__pool_alloc(int)) << endl;
    //cookie_test(__gnu_cxx::__pool_alloc<double>(), 1);


    //GNU2.9
    cout << sizeof(std::allocator<int>) << endl;
    cookie_test(std::allocator<double>(), 1);

    return 0;
}
