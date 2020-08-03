#include <iostream>
/*
 
Item47:   Traits 机制 

    通过实现advance函数: 将相应的迭代器(这里Traits必须保证内置类型入指针和迭代器都有效)移动某个给定的距离
    
    在编译期利用overloading 技术 确定迭代器的类型

    这里的迭代器和iterator_traits都是用户自定义   正式版本STL使用std::
*/



//定义用户 五种迭代器    
struct input_iterator_tag {};  //输入迭代器
struct output_iterator_tag {};   // 输出迭代器
struct forward_iterator_tag: public input_iterator_tag { };  //前向迭代器
struct bidirectional_iterator_tag : public forward_iterator_tag {};   //双向迭代器
struct random_access_iterator_tag : public bidirectional_iterator_tag {}; // 随机迭代器



//定义用户iterator_traits  
template<typename  IterT>
struct iterator_traits{
    typedef typename  IterT::iterator_category iterator_category;
};
//特化 指针类型
template<typename  IterT>
struct iterator_traits<IterT*> {

    typedef  random_access_iterator_tag iterator_category;
};



//overloading  函数

template<typename  IterT, typename DistT> //用于重载random_access_iterator_tag
void _advance(IterT& iter, DistT d, 
        random_access_iterator_tag) {   
    iter += d;
}

template<typename IterT, typename  DistT> //用于重载bidirectional_iterator_tag
void _advance(IterT& iter, DistT d, 
        bidirectional_iterator_tag) {
    if(d >= 0)  {  while(d--) ++iter;}
    else { while(d++) --iter;}
}

template<typename  IterT, typename  DistT> //用于重载input_iterator_tag
void _advance(IterT& iter, DistT d, 
        input_iterator_tag) {  
    if(d < 0){
        throw std::out_of_range("Negative distance"); 
    }
    while(d--) ++iter;
}



//最终实现的advance
template<typename IterT, typename  DistT>
void advance(IterT& iter, DistT d) {

    _advance(iter, d,
            typename iterator_traits<IterT>::iterator_category());

}


