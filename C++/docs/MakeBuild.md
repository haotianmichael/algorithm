# Gnu-Makefile

## 参考资料

* [陈皓-Makefile](https://seisman.github.io/how-to-write-makefile/overview.html)  



## 1. `Makefile`介绍

### 显式规则

> `Makefile`描述了整个工程的**编译规则**，本质其实是**文件依赖性**。

```makefile
target...: prerequisites:...
	command
	...
	...
```

* `target`: 目标文件
* `prerequisites`: 生成`target`所依赖的文件
* `command`: 该`target`要执行的命令

> 对于`target`文件，`prerequisites` 中如果有一个以上的文件比`target`要新的话(通过对比文件的修改时间)，`command`所定义的命令会被执行。**第一个`target`会被看成是`makefile`的最终目标。**
>
> 对于太长的命令，可以使用反斜杠`\`作为换行符。

### 变量&&隐晦规则

```makefile
obj = main.o kbd.o command.o  
edit : $(obj)
	cc -o edit $(obj)
	
main.o : defs.h
kdb.o : defs.h command.h
command.o : defs.h command.h
```

> 这里的变量可以简化书写的规则。  **Makefile变量其实就是C/C++中宏。**
>
> 另外，`make`的**隐晦规则**表示看到一个`.o`文件，便会自动的将`.c`文件加载依赖关系中。并且`cc -c *.c`也会被推导出来。  

 ### 引用其他`Makefile`

```makefile
include foo.Makefile *.mk $(bar)
```

> `make`命令开始时，会找到`include`所指出的其他`Makefile`。路径:
>
> * 当前路径
> * `-I "path"`路径
> * `/usr/local/bin `或者`/usr/include`等系统路径

```makefile
-include  <filename>  # 找不到文件也不会退出，继续执行
```

### `make`流程

* 读入所有的`Makefile`
* 读入被`include`的其他`Makefile`
* 初始化文件中的变量
* 推导隐晦规则，并分析所有规则
* 为所有的目标文件创建依赖关系链
* 根据依赖关系，决定哪些目标要重新生成
* 执行生成命令



## 2.  书写规则

### 规则

>包含两个部分，一个是**依赖关系**，一个是**生成目标的方法**。
>
>```makefile
>foo.o: foo.c defs.h   #  依赖关系
>	cc -c -g foo.c	  # 生成目标的方法
>```

### 通配符

> `make`支持三种通配符:`*`,`?`,`~`.  而`\*`,`\?`,`\~`表示相应的真实符号。
>
> * 应用于规则
>
> ```makefile
> clean: 
> 	cat main.c
> 	rm -f *.o
> ```
>
> * 应用于变量1
>
> ```makefile
> objects = *.o
> ```
>
> `objects`的值就是`*.o`
>
> * 应用于变量2
>
> ```makefile
> objects = $(wildcard *.o)
> ```
>
> `objects`的值就是所有`.o`文件名的集合

### 文件搜索

> 对于工程中一些不同目录下的文件，`make`寻找依赖关系的时候，可以自行加上路径。**当前目录永远都是最高优先搜索的地方**。
>
> ```makefile
> VPATH = src:../headers
> ```
>
> `VPATH`加上了`src`和`../headers`，`make`首先会在当前目录下寻找依赖文件，如果找不到则切换到指定的目录下寻找。
>
> ```makefile
> vpath <pattern> <directories>   # 为符合模式<pattern>的文件指定搜索目录<directorise>
> vpath <pattern>       # 清除符合模式<pattern>的文件的搜索目录
> vpath    # 清除所有已被设置好了的文件搜索目录
> 
> vpath %.h   ../headers
> ```
>
> **注意**: <pattern>需要包含`%`字符——匹配零活若干字符。

### 伪目标

> `make`中的`target`只有两种:
>
> * **目标文件**——指的就是通过编译生成的可执行文件/中间文件
> * **伪目标**
>
> 由于**伪目标**不是文件，只是一个标签。所以`make`无法生成它的依赖关系和决定它是否要执行。只有显式的指明这个”目标“才能让其生效。
>
> ```makefile
> .PHONY : clean
> clean : 
> 	rm *.o temp
> ```
>
> **伪目标同样可以作为默认目标。正式目标文件可以作为依赖。**
>
> ```makefile
> all: prog1 prog2 prog3
> .PHONY : all  # 声明了伪目标
> prog1 : prog1.o utils.o
> 	cc -o prog1 prog1.o utils.o
> ...
> ```
>
> > 主要用于写`Makefile`一口气生成若干个可执行文件的情况。
>
> * 因为是**默认目标**(第一个目标)，所以一定会执行
> * 因为伪目标不能生成文件,所以不会生成`all`文件，但是依赖文件会被执行
>
> **伪目标同样可以成为依赖。**
>
> ```makefile
> .PHONY : cleanall cleanobj cleandiff
> cleanall : cleanobj cleandiff
> 	rm program
> cleanobj : 
> 	rm *.o
> cleandiff : 
> 	rm *.diff
> ```
>
> 不同层次的清楚方式。

### 多目标&&静态模式

> `Makefile`中的规则可以不止一个，当具有多个目标的时候。可以使用静态模式来减少脚本量。
>
> ```makefile
> obj = foo.o bar.o   
> 
> all : $(objects)    #  all为伪目标
> $(objects) : %.o : %.c
> 	$(CC) -c $(CFLAGS) $< -o $@
> ```
>
> * `$<`  第一个依赖文件
> * `$@`  目标集
>
> 模板：
>
> ```makefile
> <targets ...> : <target-pattern> : <prere-pattern...>
> 	<commands>
> 	...
> ```

### 自动生成依赖性

> 编译器`-M`选项会自动找寻源文件中包含的头文件，并生成一个依赖关系。



## 3. 书写命令

### 显示命令

> `make`经常会将将要执行的**命令**输出到屏幕上。
>
> * 当使用`@`在一条命令开头会使其不被输出。
>
> ```makefile
> @echo "compiling xxx module"
> ```
>
> * `make  -n`只是显示命令但是不会执行，用于调试
> * `make -s/--silent/--quiet`  全面禁止命令输出

### 命令执行

> 在执行命令的时候，如果需要第二条命令是在前一条的基础上运行，就应该将其写在一行并用分号分割。
>
> ```Makefile
> exec1:
> 	cd /home/hao
> 	pwd
> 	
> exec2:
> 	cd /home/hao; pwd
> ```
>
> 第二条会输出`home/hao`；

### 命令出错

> * `-`: 在命令前加上，则该认为不管处不出错该命令都是成功的
> * `make  -i`:  忽略所有的错误

###嵌套执行`make`

> 使用根目录下的`Makefile`控制子目录下的所有`Makefile`。
>
> ```
> subsystem:
> 	cd sub && $(MAKE)
> ```
>
> * `make -w `  会输出递归执行命令的进出目录细节
>
> 如果嵌套执行，总控`Makefile`中的变量会传递到下级的`Makefile`中(**如果你显式的声明**)：
>
> ```makefile
> export <variable ...>;
> ```
>
> 但是其中的`SHELL`,`MAKEFLAGS`变量一定会传递到下一层。

### 定义命令包

> 如果`Makefile`中出现一些相同命令序列，那么我们可以为这些相同的命令序列定义一个变量。
>
> ```makefile
> define run-yacc
> yacc $(firstword $^)
> mv y.tab.c $@
> endef
> ```



## 4. 变量

### 变量定义

> `Makefile`中有两种方式用变量定义变量的值。
>
> * `=`
>   * 变量可以用后面定义的变量来定义
> * `=:`  
>   * 只能使用前面已经定义好的变量
>
> * `?=` 
>   * `Foo ?= bar`      如果`Foo`以前被定义过，那变量`Foo`的值就是`bar`,如果先前未被定义过，那该语句什么也不做

### 环境变量

> `make`执行的时候系统环境变量即被载入到`Makefile`文件中，如果`Makefile`文件中已经定义了这个变量，则系统变量会被覆盖。
>
> * `make -e `  则系统环境变量会覆盖`Makefile`中定义的变量



## 5. 使用条件判断

```makefile
libs_for_gcc = -lgnu
normal_libs =

foo: $(objects)
ifeq	($(CC), gcc)
	$(CC) -o foo $(objects) $(libs_for_gcc)
else 
	$(CC) -o foo $(objects) $(normal_libs)
endif
```

> 条件关键有四个。
>
> * `ifeq`
>
>   * 比较两个参数是否相同
>
>   ```
>   ifeq (<arg1>, <arg2>)
>   ifeq '<arg1>' '<arg2>'
>   ifeq "<arg1>" "<arg2>"
>   ifeq "<arg1>" '<arg2>'
>   ifeq '<arg1>' "<arg2>"
>   ```
>
> * `ifneq`
>
>   * 比较两个参数是否不同
>
> * `ifdef <variable-name>`
>
>   * 如果变量的值非空，则表达式为真
>
> * `ifndef`
>
>   * 如果变量的值为空，则表达式为真



## 6. 函数

```makefile
$(<function> <arguments>)
${<function> <arguments>}
```

> 在`Makefile`中可以使用函数来处理变量。

* `$(subset <form>, <to>, <text>)`
  * 将`<text>`中的`<form>`字符串替换成为`<to>`
  * 返回函数被替换后的字符串
* `$(patsubst <pattern>, <replacement>, <text>)`
  * 
* `strip`
* `findstirng`
* `filter`
* `filter-oute`
* `sort`
* `word`
* `wordlist`
* `words`
* `firstword`
* `dir`
* `notdir`
* `suffix`
* `basename`
* `addsubffix`
* `addprefix`
* `join`
* `foreach`
* `if`
* `call`
* `origin`
* `shell`
* `make`

### `make`退出码

* `0` 成功执行
* `1` 出现错误
* `2`   使用了`-q`选项，使得一些目标不需要更

### 伪目标

> `all`, `clean`,`install`,`print`,`tar`,`dist`,`TAGS`,`check`/`test`



## 7.隐含规则

### `make`中默认的关键字

#### 关于命令的变量

* `AB` : 函数库打包程序`ar`
* `AS`: 汇编语言编译程序`as`
* `CC`：C语言编译器程序`cc`
* `CXX`: C++语言编译器程序`g++`
* `CO`: 从RCS文件中扩展文件程序`co`
* `CPP`: C程序的预处理器(输出是标准输出设备)
* `GET`: 从SCCS文件中扩展文件的程序`get`
* `LEX`: Lex方法分析器程序(针对C)`lex`
* `YACC`: Yacc文法分析器`yacc`
* `RM`:  删除文件命令

#### 关于参数的变量(如果没有默认值，则为空)

* `ARFLAGS`: 函数库打包程序AR命令的参数,默认值为`rv`
* `ASFLAGS`:  汇编语言编译器参数,默认值为`.s/.S`
* `CFLAGS`: C编译器参数
* `CXXFLAGS`: C++ 编译器参数
* `CPPFLAGS`:  C预处理器参数
* `LDFLAGS`: 链接器参数
* `LFLAGS`: Lex文法分析器参数
* `YFLAGS`: Yacc文法分析器参数

### 模式规则

> 在模式规则中，目标的定义需要有`%`字符。`%`的意思是表示一个或多个任意字符。在依赖目标中同样可以使用`%`,只是依赖目标中的`%`的取值，取决于其目标。**模式规则中的`%`发生在运行时。**
>
> ```makefile
> %.o : %.c
> 	<command....>
> ```
>
> 一旦依赖目标中的模式被确定，则`make`会去匹配当前目录下所有的文件名，一旦找到就会执行命令。。

### 自动化变量

> 将模式中所定义的一系列的文件自动的挨个取出，直至所有符合模式的文件都取完了。共7个。
>
> * `$@`: 表示规则中的目标文件集。在模式规则中，如果有多个目标，那么`$@`就是匹配于目标中模式定义的集合
> * `$%`: 仅当目标是函数库文件中，表示规则中的目标成员名。
> * `$<`: 依赖目标中的第一个目标名字。如果依赖目标是以模式`%`定义的，那么`$<`就是符合模式的一系列的文件集。注意是一个一个取出来的。
> * `$?`: 所有比目标新的依赖目标的集合。以空格分隔。如果只是对更新过的依赖文件进行操作，则这个很有用。
> * `$^`: 所有依赖目标的集合。以空格分隔。如果在依赖目标中有多个重复的，那么这个变量会去除重复的依赖目标，也保留一份。
> * `$+`: 和`$^`很像，只是不去除重复的依赖目标。
> * `$*`: 这个变量表示目标模式中`%`及其之前的部分。
>
> 其中`$@`,`$<`,`$%`,`$*`在扩展的时候只会有一个文件，而另外三个的值是一个文件列表。其次这7个变量还可以取得文件的目录名或是在当前目录下符合模式的文件名，只需要搭配上`D`和`F`字样。

















































