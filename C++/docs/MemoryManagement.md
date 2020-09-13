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

* [4种primitives](../src/MemoryManagement/primitives_index.cpp)

* [new/delete](../src/MemoryManagement/pritimitives_new_delete.cpp)



 

### 2. malloc/free





### 3. sd::allocator





### 4. Other allocators

 



### 5. Loki::allocator





