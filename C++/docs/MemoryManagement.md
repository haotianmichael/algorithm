# C++内存管理

## 参考资料

#### **[vedio](https://www.bilibili.com/video/BV1Kb411B7N8?from=search&seid=2095136970590855889)**

#### **Libraries:**

* STL Allocators
* MFC CPlex+CFixedAlloc
* Boost.Pool
* Loki SmallObjAllocator
* VC malloc/free
* jemalloc
* tcmalloc

**向侯捷老师致敬！**

## 编译环境

> * `macOS Mojave/Clang 9.0.0`
> * `Ubuntu 18.04/GCC 7.5.0`
>
> 主力机器是`MAC`，必要时为了模拟`GNU`环境会使用`Ubuntu`来测试。  
>
> 如果没有特别标注`GCC`,则全部使用`Clang`编译并取得和`GNU`平台上逻辑相同的输出。需要说明的是`LLVM`和`GCC`渐行渐远，为`Clang`自行开发的`lib++`已经取代了`GCC`的标准库`libstd++`，导致不同的编译器最终的结果会有些许不同。

## index

### 1. primitives

| 分配                     | 释放                         | 类型      | 可否重载                     |
| ------------------------ | ---------------------------- | --------- | ---------------------------- |
| `malloc`                 | `free`                       | C函数     | 不可                         |
| `new`                    | `delete`                     | C++表达式 | 不可                         |
| `::operator new`         | `::operator delete`          | C++函数   | 可                           |
| `allocator<T>::allocate` | `allocator<int>::deallocate` | C++标准库 | 可自由设计并以之搭配任何容器 |

* [绪论](../src/MemoryManagement/0primitives_index.cpp)
* [new/delete探究](../src/MemoryManagement/1primitives_new_delete.cpp)
* [数组new/delete探究](../src/MemoryManagement/2primitives_array_new_delete.cpp)
* [placement_new探究](../src/MemoryManagement/3primitives_replacement_new.cpp)
* [operator_new重载](../src/MemoryManagement/4override_operator_new.cpp)
* [placement_new重载](../src/MemoryManagement/5override_placement_new.cpp)
* [class allocator_1.0对象内存池](../src/MemoryManagement/6per_class_allocator.cpp)
  * `GCC`: 重载`operator new/delete`间隔为`16Bytes`,不重载的间隔`32Bytes`
  * `Clang`: 都是`16Bytes`
* [class allocator 2.0对象内存池](../src/MemoryManagement/6per_class_allocator_advanced.cpp)
* [static allocator 3.0对象内存池](../src/MemoryManagement/7static_allocator.cpp)
* [macro static allocator 4.0对象内存池](../src/MemoryManagement/8macro_static_allocator.cpp)
* [new handler/default/delete探究](../src/MemoryManagement/9end.cpp)

 

### 2. sd::allocator

> **VC6.0**和**BorlandC5.0**这两个著名的编译器标准库内部实现中，每个容器的`std::allocater`都是通过`::operator new/delete`来完成的。而`GNU2.9 C++`中使用的版本是`std::alloc`，经过更新迭代在`GNU4.9`中改名为`__gnu_cxx::__pool_alloc`——也是本章的重点关注对象。
>
> 各个编译器标准库版本的容器举例如下:

```C++
//VC6
template<class _Ty,
class _A= allocator<_Ty>>
class vector{  
  //...
};             


//BC5
template<class T, 
	class Allocator=allocator<T>>
class vector{
  //... 
};


//GNU C++
template<class T, 
	class Alloc = alloc>
class vector{
  //...  
};            
```

* [GNU2.9-4.9对cookie的优化](../src/MemoryManagement/10pool_alloc.cpp)
  * `GCC2.9-std::allocator`: 连续申请三个`8Bytes-double`的元素，地址间隔`32Bytes`
  * `GCC4.9-__gnu_cxx::__pool_alloc`:连续申请三个`8Bytes-double`的元素，地址间隔`16Bytes`

> ` GNU2.9`中的`std::alloc`内存分配细节：
>
> * `size`容器所申请的单元大小；`chunk`分配器提供的内存单元,共16种。
>
> * 维护16条长度各异(第`n`条链表一次分配的`chunk`大小为:`8*(n + 1)Bytes`，)的自由链表，超过能分配最大的内存单元会申请`malloc`。**所有使用`malloc`使用的都会带`cookie`**。
>
> * 分配器会将申请的内存`size`按照分配单元调整到合适的边界(比如`std::alloc`是8的倍数，`malloc`也会调整)
> * 分配器一次分配40个`chunk`，其中20个使用，剩下20个留给下次分配使用，分配大小`size * 20 * 2 +ROUNDUP(memory_allocated >> 4);  ` 其中`ROUNDUP()`是对齐函数。
> * 分配的时候先去找上次分配的剩下的20个`chunk`，如果有直接使用，没有则调用`malloc`分配，如果剩下的`chunk`小于`size`，则被看成是碎片——需要重新挂到相应的链表头指针上。**这里需要注意的是，对于已经分配好的内存来说，每一个`chunk`的大小是一定的，所以就算A链表上总共有20*8Bytes,但是如果申请的`size`是16Bytes，那这个A上分配的内存是无法使用的。**
> * 由于一次性分配40个`chunk`，而每一次分配必须按照其`size`来选择链表头结点，所以有很大概率某些指针上的空闲`chunk`就会比较多。而`std::alloc`对`chunk`的选择一定是大于等于`size`的。从技术的角度，将这些空闲的`chunk`合并在一起难度非常大。
> * 分配器面向的用户是**容器**——元素一样大的集合，如果用户直接使用分配器，就必须记住分配的大小。这是因为自主分配的内存不会带`cookie`，而容器的第一个目标参数都会是参数类型，只要`sizeof`一下就可以计算出来所申请的`size`。
> * `embedded pointers`是成熟的工业级分配器都会使用的`Tips`。

* [GNU2.9的std::alloc源码实现](../src/MemoryManagement/11std::alloc.cpp)

> 如果只是为了理解内存分配，其实很多代码都没有用。

* [GNU2.9的std::alloc源码实现简易版](../src/MemoryManagement/11simplified_ver_std::alloc.cpp)







### 3. malloc/free



### 4. Loki::allocator





### 5. Other allocators

 







