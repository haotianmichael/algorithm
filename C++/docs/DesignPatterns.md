# 设计模式

> 每一个模式描述了一个在我们周围不断重复发生的问题，以及该问题的结局方案的核心。这样你就能一次一次的额使用该方案而不必做重复劳动。 ——`Christopher Alex`

## 目标

* 理解**松耦合**设计思想
* 掌握**面向对象设计**原则
* 掌握**重构**技法改善设计
* 掌握`GOF`(Gun Of Four)核心设计模式  

> 软件设计的目标是**复用**——抵御变化！  



## 参考资料

* [设计模式-可复用面向对象软件的基础](https://book.douban.com/subject/1052241/)

>  `可复用`是目标，`面向对象`是实现的方法，共有23种设计模式



## 8种面向对象设计原则

* 依赖倒置原则(DIP)
  * 高层模块(稳定)不应该依赖于底层模块(变化)，二者都应该依赖于抽象(稳定)
  * 抽象(稳定)不应该依赖于实现细节(变化)，实现细节应该依赖于抽象(稳定)
* 开放封闭原则(OCP)
  * 对扩展开放，对更改封闭
  * 类模块应该是可扩展的，但是不可修改

* 单一职责原则(SRP)
  * 一个类应该仅有一个引起它变化的原因
  * 变化的方向隐含着类的责任
* `Liskov`替换原则(LSP)
  * 子类必须能够替换它们的基类(IS-A)
  * 继承表达类型抽象
* 接口隔离原则(ISP)
  * 不应该强迫客户程序依赖它们不用的方法
  * 接口应该小而完备
* 优先使用对象组合，而不是类继承
  * 类继承通常为“白箱复用”，对象组合通常为“黑箱复用”
  * 继承在某种程度上破坏了封装性，子类父类耦合度高
  * 而对象组合则只要求被组合的对象具有良好定义的接口，耦合度低
* 封装变化点
  * 使用封装来创建对象之间的分界层，让设计者可以在一侧进行修改，而不会对另一侧产生不良的影响，从而实现层次间的松耦合
* 针对接口编程，而不是针对实现编程
  * 不将变量类型声明为某个特定的具体类，而是声明为某个接口
  * 客户程序无需获知对象的具体类型，只需要知道对象所具有的接口
  * 减少系统中各部分的依赖关系，从而实现“高内聚，松耦合”的类型设计方案



## 23种经典设计模式

> 重构获得模式 `Refactoring to Patterns`.    
>
> 重构关键技法：
>
> * 静态——动态
> * 早绑定——晚绑定
> * 继承——组合(类包含)
> * 编译时依赖——运行时依赖
> * 紧耦合——松耦合
>
> 现代软件设计的特征是“需求的频繁变化”。设计模式的要点是“**寻找变化点，然后在变化点处应用设计模式**，从而来更好地应对需求的变化”。**什么时候，什么地点应用设计模式比设计模式结构本身更为重要。**  
>
> **设计模式最大的作用，就是在变化和稳定之间寻找隔离点。**寻找**稳定点**和**变化点**。  
>
> 从封装变化的角度来分类设计模式:

### 组件协作

> 现代软件专业化分工之后的第一个结果是“**框架与应用程序的划分**”，“组件协作”通过**晚期绑定**，来实现框架与应用之间的**松耦合**，是二者之间协作时候常用的模式。

* [Template Method](../src/DesignPattern/TemplateMethod.cpp)
* [Strategy](../src/DesignPattern/Strategy.cpp)
* [Observer/Event](../src/DesignPattern/Observer.cpp)

### 单一职责

> 在软件组件的设计中，如果**责任划分的不清晰**，使用继承得到的结果往往是随着需求的变化，子类急剧膨胀，同样充斥着重复代码，这时候的关键是划清责任。

* [Decorator](../src/DesignPattern/Decorator.cpp)
* [Bridge](../src/DesignPattern/Bridge.cpp)

### 对象创建

> 通过”对象创建“模式绕开`new`，来避免对象创建(new)过程中所导致的**紧耦合**（依赖具体类），从而支持对象创建的稳定。它是接口抽象之后的第一步工作。

* [Factory Method](../src/DesignPattern/FactoryMethod.cpp)
* [Abstract Factory](../src/DesignPattern/AbstractFactory.cpp)
* [Prototype](../src/DesignPattern/Prototype.cpp)
* [Builder-lessUse](../src/DesignPattern/Builder.cpp)

### 对象性能

> 面向对象很好的解决了“抽象”的问题，但是必不可免的付出一定的代价。对于通常情况来讲，面向对象的成本大都可以忽略不计。但是某些情况下，面向对象所带来的的成本必须严谨对待。

* [Singleton](../src/DesignPattern/Singleton.cpp)
* [Flyweight](../src/DesignPattern/Flyweight.cpp)

### 接口隔离

> 在组件构建过程中，某些接口之间直接的依赖常常会带来很多问题，甚至根本无法实现。采用添加一层间接（稳定）接口，来隔离本来互相紧密关联的接口是一种常见的解决方案。

* [Facade](../src/DesignPattern/Facade.cpp)
* [Proxy](../src/DesignPattern/Proxy.cpp)
* [Mediator-lessUse](../src/DesignPattern/Mediator.cpp)
* [Adapter](../src/DesignPattern/Adapter.cpp)

### 状态变化

> 在组件构建过程中，某些对象的状态经常发生变化，如何应对这些变化进行有效的管理？同时又维持高层模块的稳定？“状态变化”模式为这一问题提供了一种解=决方案。

* [Memento-lessUse](../src/DesignPattern/Memento.cpp)
* [State](../src/DesignPattern/State.cpp)

### 数据结构

>常常有一些组件在内部具有特定的数据结构，如果让客户依赖这些特定的数据结构，将极大的破坏组件的复用。这时候，将这些特定的数据结构封装在内部，在外部提供统一的接口，来实现与特定数据结构无关的访问，是一种行之有效的解决方案。

* [Composite](../src/DesignPattern/Composite.cpp)
* [Iterator-lessUse](../src/DesignPattern/Iterator.cpp)
* [Chain of Resposibility-lessUse](../src/DesignPattern/ChainOfResponsibility.cpp)

### 行为变化

> 在组件的构建过程中，组件行为的变化经常导致组件本身剧烈的变化。“行为变化”模式将组件的行为和组件本身进行解耦，从而支持组件行为的变化，实现两者之间的耦合。

* [Command-lessUse](../src/DesignPattern/Command.cpp)
* [Visitor-lessUse](../src/DesignPattern/Visitor.cpp)

### 领域问题

> 在特定领域中，某些变化虽然频繁，但可以抽象为某种规则。这时候，结合特定领域，将问题抽象为语法规则，从而给出在该领域下的一般性解决方案。

* [Interpreter-lessUse](../src/DesignPattern/Interpreter.cpp)  



## 总结

* 目标：管理变化，提高复用
* 手段：分解  && 抽象
  * 关注抽象类&接口
  * 理清变化点和稳定点
  * 审视依赖关系
  * 要有`Framework`和`Application`的区隔思维
  * 良好的设计是演化的结果

* 成长之路
  * 手中无剑，心中无剑
  * 手中有剑，心中无剑
  * 手中有剑，心中有剑
  * 手中无剑，心中有剑

