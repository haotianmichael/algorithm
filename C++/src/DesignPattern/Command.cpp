#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>


using namespace std;

/*
 动机:
    在软件构建过程中，“行为请求者”与“行为实现者”通常呈现一种“紧耦合”。但在某些
    场合——比如需要对行为进行”记录，撤销/重，事务“等处理，这种无法抵御变化的紧耦合是不合适的。

    在这种情况下，如何将”行为请求者“和“行为实现者”解耦？将一组行为抽象为对象，可以实现
    二者的松耦合。

    设计模式是为了补充语言设计的不足而实现的
Command：使用接口规范来实现，但是有性能损失
仿函数: 使用函数签名实现 编译时绑定
*/
class Command{
    public:
        virtual void execute() = 0;
};

class ConCreteCommand1 : public Command{
    string arg;
    public:
    ConCreteCommand1(string a) : arg(a) {}    
    void execute() override{
        cout << "#1 process" << arg << endl; 
    }

};

class ConCreteCommand2 : public Command{
    string arg;
    public:
    ConCreteCommand2(string a) : arg(a) {}
    void execute() override{
        cout << "#2 process" << arg << endl; 
    }
};

class MmacroCommand: public Command{
    std::vector<Command*>  commands;
    public:
        void addCommand(Command* c) {
            commands.push_back(c);
        } 

        void execute() {
        
            for(auto &c : commands) {
                c->execute();
            }
        }
};


int main(void)
{
    /*
        命令和请求作为对象会有很大的松耦合  
      
    */
    ConCreteCommand1 command1("");
    ConCreteCommand2 command2("");

    MmacroCommand macro;
    macro.addCommand(&command1);
    macro.addCommand(&command2);
    macro.execute();

    return 0;
}

/*
定义: 
    讲一个请求（行为）封装成为一个对象，从而使得你可以使用不同的请求对客户进行参数化，
    对请求排队或记录请求日志，以及支持可撤销的操作。
*/
/*
总结: 

    Command模式的根本目的在于将“行为请求者”和“行为实现者”解耦，在面向对象语言中，
    常见的实现手段是“将行为抽象为对象”

    实现Command接口的具体命令对象ConcreteCommand有时候根本需要可能会保存一些额外的状态信息，
    通过使用Compoiste模式，可以将多个“命令”封装为一个“复古命令”MacroCommand

    Command模式与C++中的函数对象有些类似。但两者定义行为接口的规范有所区别：
        Command以面向对象中的“接口-实现”来定义行为接口规范，更严格，但有性能损失。
        C++函数对象以函数签名来定义行为接口规范，更灵活，性能更高;
*/
