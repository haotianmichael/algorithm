#include <iostream>


/*
动机:
    在软件构建过程中，我们需要为某些对象建立一种”通知依赖关系“——一个对象(目标对象) 的状态发生改变，所有的依赖对象
    (观察者对象)都将得到通知。如果这样的依赖关系过于紧密，将使软件不能很好的抵御变化。
    使用面向对象技术，可以将这种依赖关系弱化，并形成一种稳定的依赖关系，从而实现软件体系结构的松耦合。

*/
/***************************结构化程序模型*/
class Form {

};
class TextBox {
    public:
    std::string getText() {
        return ""; 
    }
};
class FileSplitter{
    public:
        FileSplitter(std::string, int) {
             
        }
        void split() {
        
        }
};
class MainForm : public Form{

    TextBox* txtFilePath;
    TextBox* txtFileNumber;

    public:
    void Button1_Click() {
        std::string filePath = txtFilePath->getText();  
        int number = atoi(txtFileNumber->getText().c_str()); 

        FileSplitter splitter(filePath, number);
        splitter.split();
    }
};

