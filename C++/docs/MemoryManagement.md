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

> `macOS Mojave/LLVM 9.0.0`

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
* [class allocator 2.0对象内存池](../src/MemoryManagement/6per_class_allocator_advanced.cpp)
* [static allocator 3.0对象内存池](../src/MemoryManagement/7static_allocator.cpp)
* [macro static allocator 4.0对象内存池](../src/MemoryManagement/8macro_static_allocator.cpp)
* [new handler/default/delete探究](../src/MemoryManagement/9end.cpp)

 

### 2. sd::allocator

> **VC6.0**和**BorlandC**这两个著名的编译器标准库内部实现中，每个容器的`std::allocater`都是通过`::operator new/delete`来完成的。  而`GNU C++`中使用的版本是`std::alloc`。也是本章的重点关注对象。
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







### 3. malloc/free



### 4. Loki::allocator





### 5. Other allocators

 







