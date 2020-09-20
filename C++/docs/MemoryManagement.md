# C++内存管理

## 参考资料

**向侯捷老师致敬！**

**[vedio](https://www.bilibili.com/video/BV1Kb411B7N8?from=search&seid=2095136970590855889)**

#### **Libraries:**

* `STL Allocators`
* `MFC CPlex+CFixedAlloc`
* `Boost.Pool`
* `Loki SmallObjAllocator`
* `VC malloc/free`
* `jemalloc`
* `tcmalloc`
* `ptmalloc  `

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

> **VC6.0**和**BorlandC5.0**这两个著名的编译器标准库内部实现中，每个容器的`std::allocater`都是通过`::operator new/delete`来完成的——**本质就是直接调用`malloc`其他什么都没有做**。而`GNU2.9 C++`中使用的版本是`std::alloc`——使用了诸如**pool**等高级的分配逻辑，在经过更新迭代后在`GNU4.9`中改名为`__gnu_cxx::__pool_alloc`——也是本章的重点关注对象。
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

> ` GNU2.9`中的`std::alloc`内存分配流程：
>
> * `size`容器所申请的对象大小；`chunk`分配器提供的内存单元——共16种。
>* 维护16条长度各异(第`n`条链表一次分配的`chunk`大小为:`8*(n + 1)Bytes`，)的自由链表，超过能分配最大的内存单元会申请`malloc`。**所有使用`malloc`使用的都会带`cookie`**。
> * 分配器会将申请的内存`size`按照分配单元调整到合适的边界(比如`std::alloc`是8的倍数，`malloc`也会调整)
>* 拿到一个申请的`size`需要分配的对象，首先定位它在分配器上的指针端口。然后查看是否有**战备池**的内存可以用，如果有直接使用，这时候一般分配的数量是1~20个`chunk`。没有则调用`malloc`分配。第一次分配**pool**为零，则直接调用`malloc`。
> * 分配器调用`malloc`分配大小为`size * 20 * 2 +ROUNDUP(memory_allocated >> 4);  `,其中会有`20`个`chunk`是为申请的对象准备的，剩下的内存(并不会分割)作为**战备池**为以后的分配器行为做准备——这是一个很重要的概念，分配全程需要关注**战备区pool**的容量。 其中`ROUNDUP()`是对齐函数，`memory_allocated`是已经分配好的内存总量。随着内存分配操作越来越多，**memory_allocated**也是越来越大——符合计算机内存分配越来越多的增长趋势。
> * 如果**战备池**剩下的内存小于`size`，则被看成是碎片——需要重新挂到相应的链表头指针上——寻找相应的`chunk`端口。
> * 如果`malloc`系统内存分配失败，则需要在最接近`size`的已分配好的空闲`chunk`中回填`pool`，完成分配。如果向上走也无法分配成功，那系统分配才算完全失败。
> * 由于一次性分配20个`chunk`，而每一次分配必须按照其`size`来选择链表头结点，所以有很大概率某些指针上的空闲`chunk`就会比较多。而`std::alloc`对`chunk`的选择一定是大于等于`size`的。从技术的角度，将这些空闲的`chunk`合并在一起难度非常大。
> * 分配器面向的用户是**容器**——元素一样大的集合，如果用户直接使用分配器，就必须记住分配的大小。这是因为自主分配的内存不会带`cookie`，而容器的第一个目标参数都会是参数类型，只要`sizeof`一下就可以计算出来所申请的`size`。
> * `embedded pointers`是成熟的工业级分配器都会使用的`Tips`。

* [GNU2.9的std::alloc源码实现](../src/MemoryManagement/11std::alloc.cpp)

> 如果只是为了理解内存分配，其实很多代码都没有用。

* [GNU2.9的std::alloc源码实现简易版](../src/MemoryManagement/11simplified_ver_std::alloc.cpp)
* [__pool_alloc新型的分配器测试程序](../src/MemoryManagement/12alloc_test.cpp)
  
  * `GCC`： 测试样例`1000`个元素。
    * 标准分配器: 分配`1000`次，得到`24000`个字节
    * 新型分配器: 分配`16`次，得到`25224`个字节
  
  

### 3. malloc

> `Windows`下`VC6.0`中`C++`程序的流程(简化版)——伪码中的`API`都是`Windows`平台下的。**执行流程是前一个函数调用后一个函数。需要有OS-虚拟内存的基础。**
>
> * `KERNEL32! bff89f5b()...`   内核函数
>
> * `mainCRTStartup()`   由`C Runtime Library`  
>
>   ​	系统启动最初由`HeapAlloc`分配4096字节并传给指针`_crtheap`，并建立16个`Header`。接着第一个`Header`的一个指针利用`VirtualAlloc(0, 1Mb, MEM_RESERVE)`函数向操作系统直接申请了`1MB`的虚拟地址空间(并不分配内存)，另外一个指针从`_crtheap`中又分配了`sizeof(region)`大小的内存用来建立管理中心。  
>
>   ​	**总结一下，最开始进行了两种操作，一个操作是真正的向OS要了4KB的物理内存_crtheap，用来建立`region`控制中心和16个`Header`——这里用的是API是`HeapAlloc()`；而另一个操作是作为控制中心的`region`申请了`1MB`的虚拟地址空间(注意这里并没有直接分配内存)——用的API是`VirtualAlloc()`。这一切操作都是在`ioinit`函数真正申请内存之前就完成了。**
>
>   * `_heap_init()`     
>
>     [_heap_init部分代码](../src/MemoryManagement/13heap_init.cpp)
>
>     * `__sbh_heap_init()`       
>
>       [__sbh_heap_init部分代码](../src/MemoryManagement/13sbh_heap_init.cpp)
>
>   * `_ioinit()`  第一次尝试申请内存共100h
>
>     [_ioinit部分代码](../src/MemoryManagement/13ioinit.cpp)
>
>     * `_heap_alloc_dbg()`     调试模式下
>
>       [_heap_alloc_dbg部分代码](../src/MemoryManagement/13heap_alloc_dbg.cpp)
>
>     * `_heap_alloc_base()`  确定小于1024采用SBH小区块分配器
>
>       [_heap_alloc_base部分代码](../src/MemoryManagement/13heap_alloc_base.cpp)
>
>     * `_sbh_alloc_block()`   计算好总共需要分配的内存字节    130h
>
>       [_sbh_alloc_block部分代码](../src/MemoryManagement/13sbh_alloc_block.cpp)
>
>     程序第一次申请内存分配是`ioinit()`共申请了`100h`字节，加上调试器模式下结构体大小，以及两个`cookie`(上下`cookie`是为了回收的时候上下合并)：  
>
>     `0x100 + 0x24 + 4 * 2 = 0x12C ——> 0x130(aligned)——>0x131(使用最后一位标记分配)`  
>
>     **但其实只是计算，系统并没有实际开始分配内存。**
>
>     * `heap_alloc_new_region()`      第一个`Header`的指针申请`region`——由`HeapAlloc(_crtheap, sizeof(region))`分配
>
>     内存分配原理： 16个`Header`(有一个头指针为其定位)。每一个`Header`负责管理`1MB`——申请虚拟地址空间调用`Windows API——VirtualAlloc()`。每一个`Header`有两根指针——其中一根指向其管理中心——`region`。
>
>     ```c++
>     //region结构
>     typedef struct tagRegion{
>       int indGroupUse;    //整数   
>       char cntRegionSize[64];    //64个character
>        //unsigned int 32位    高位和低位合并之后——>32组数据，每组64bits   
>       BITVEC bitvGroupHi[32]; 
>       BITVEC bitvGroupLo[32];
>       //32个group  每一个group管理32KB
>       struct tagGroup grpHeadList[32];
>     }REGION,&PREGION;
>     
>     //group结构
>     typedef struct tagGroup{
>       int cntEntries;
>     	// 64对双向链表  
>       struct tagListHead ListHead[64];   
>     }GROUP, *PGROUP;
>     
>     //双向链表
>     typedef struct tagListHead{
>       struct tagEntry* pEntryNext;
>       struct tagEntry* pEntryPrev;
>     }LISTHEAD, *PLISTHEAD;
>     
>     typedef struct tagEntry{
>       int sizeFront;       //记录4080Bytes
>       struct tagEntry* pEntryNext;
>       struct tagEntry* pEntryPrev;
>     }ENTRY *PENTRY;
>     ```
>
>     * `heap_alloc_new_group()`  
>
>     `1MB`分为32个单元，每单元`32KB`的大小。然后每一个单元又分为8个`page`，每部分`4KB`——对应操作系统的`page`。而管理中心`region`一共有32个`group`,**所以每一个`group`管理8x4KB的内存资源。**
>
>      从上面的代码中可以知道:一个`group`共有64个双向指针，**这些指针所管理的内存按照16的倍数递增(即1st—16字节，2nd—32字节...64th—>=1024字节)。** 因此一个`group`实际上可以管理的大小是`16*(1 + 2 + ...+ 64) = 32KB + 512Bytes`。符合最开始的设定。
>
>     根据`ioinit`申请的内存大小`110h`，加上`debug`模块和`cookie`，再进行16字节的对齐。最后需要向每一个`page`申请`130h`字节的内存。最后还剩下`ec0h = ff0h - 130h`。那一个`page`便会被切割成为两部分——一部分是分配的`130h`内存，**这一部分需要将`130h`改为`131h`代表脱离了SBH系统的控制分离出去。** 另一部分是剩下的`ec0h`。双方的结构都是`heap_alloc_dbg::struce _CrtMemBlockHeader`并且都需要更新`cookie`。以后每一次分配都需要根据分配的`size`计算所挂的链表——如果该链表上没有区块，则向上移动直到最后一条链表上再分配。
>
>     至此，`malloc`函数的整个分配过程基本结束了。侯捷老师的PPT和课程中的讲解**非常精彩**，建议反复听直到能够自行画出内存图。
>



### 4. free

```c++
	free(p)   //将p回收到相应的链表上
```

* 落在哪个`Header`上
* 落在哪个`Group`上
* 落在哪个`free-list`上

> 整个系统的主要结构就是:`Header/Region`——`Group`——`free-list`上述各个数据结构的大小都知道，所以很容易定位`p`指针。
>
> `Group`回收: `(p - 头指针)/32K`
>
> `Header`回收: 使用头指针`__sbh_pHeaderList`从第一个`Header`开始索引判断。
>
> `free-list`回收: 将区块`size/16 - 1`然后判断回收需要挂在`group`上的哪一个链表上面。  
>
> 合并：每一个区块都有上下的`cookie`，根据`cookie`的最后一位是不是`1`判断是否可以合并。   
>
> `Defering`：当出现两个`Group`全回收(`Counter`判断)的时候，则将`Defer`指针指向第一个准备释放给OS，如果只有一个全回收的`Group`则不释放。



### 5. Loki::allocator

> `Loki Library`中的分配器。  省略...  



### 6. Other issues

> 主要介绍`GNU-C`下其他的7个分配器。
>
> 分配器负责为标准库的容器分配内存。总的来说有两种方式:直接分配(调用`malloc`)和**智能型**。
>
> 所谓**智能型**分配的方式，就是将所分配得到的内存加以缓存(Cache)——即内存池。**这种方式不仅可以适当的提升分配的速度，而且降低了`cookie`的空间浪费。** 相关的分配器比如：
>
> * `__gnu_cxx::bitmap_allocator`    重点
> * `__gnu_xx::pool_allocator`  第二讲重点——缺点是分配的内存不回收给OS
> * `__gnu_cxx::__mt_alloc `
>
> 另外还有四种分配器:
>
> * `__gnu_cxx::new_allocator`     调用`::operator new/delete`
> * `__gnu_cxx::malloc_allocator`    直接调用`malloc/free`
>
> * `__gnu_cxx::array_allocator`    [部分源代码](../src/MemoryManagement/14array_allocator.cpp)
> * `__gnu_cxx::debug_allocator`      [部分源代码](../src/MemoryManagement/14debug_allocator.cpp)

##### bitmap_allocator

> `blocks`,`super-blocks`,`bitmap`,`mini-vector`
>
> **分配**：
>
> 容器分配一个`blocks`，每个区块8个字节。加上`bitmap`以及一些区块叫`super-blocks`。假设有64个`blocks`，则需要的`bitmap`是64`bits`——两个`unsigned int`。`bitmap`每一个`bit`为1表示还未分配。`use-count`表示用掉的区块计数(整数)。`size-super-block `表示`super-block`的大小——`64 * 8(block size) +4(use-count) + 4*2(bitmap) = 524Bytes。`
>
> `__mini_vector`: 自行实现的小型结构管理`bitmap`——成倍增长
>
> * `_M_start`,  指向头结点
> * `_M_finish`,  指向尾节点的后一个结点
> * `_M_end_of_storage `
>
> `super-block`是基本单元。当启动第二个`super-block`的时候，首先**区块数量**会加倍——从64`Bytes`变成128`Bytes`。接着`bitmap`会变成4个`unsigned int`。这时候`size-super-block`为`128 * 8(block size) + 4 * 4(bitmap) + 4(use-count)= 1044bytes `。由于需要有两个控制中心——所以`__mini_vector`也需要增加，因为是类`vector`所以有时成倍增长。
>
> **释放：**
>
> 会再增加一个`__mini_vector`，最多64个`entry`，如果超过了区块就会被还给操作系统。

* [ 其他分配器测试程序](../src/MemoryManagement/14test_allocator.cpp)
  * `GCC` 





 

 






