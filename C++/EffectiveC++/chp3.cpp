#include <iostream>

class investment
{
public:
    investment ();
    virtual ~investment ();
    investment* createInvestment();
    void f();
private:
    
};


void investment::f() {

     //使用对象 管理资源
    std::auto_ptr<investment> pInv(createInvestment());  // 无法同时指向同一个元素
    std::shared_ptr<investment> pSinv(createInvestment());  //引用计数


    investment * m = pInv.get();

}
