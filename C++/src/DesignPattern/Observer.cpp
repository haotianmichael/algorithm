#include <iostream>
#include <vector>
#include <algorithm>


/*
动机:
    在软件构建过程中，我们需要为某些对象建立一种”通知依赖关系“————一个对象(目标对象)的状态发生改变
    (观察者对象)都将得到通知。如果这样的依赖关系过于紧密，将使软件不能很好的抵御变化。
    使用面向对象技术，可以将这种依赖关系弱化，并能形成一定的依赖关系，从而实现软件体系结构的松耦合。

*/
/******************************结构化程序模型*/
class Form_old{};

class TextBox_old{
    public:
        std::string getText() {
            return "";
        }
};  
//添加进度条需求
class ProgressBar_old{ 
    public:
        void setValue(int num) {
            num = 0; 
        }
};
//文件分割器
class FileSplitter{
    std::string m_filePath;
    int m_fileNumber;

    //违反依赖倒置原则(编译时依赖) 是一个实现细节
    /*为什么不直接在FileSplitter中提供呢，没有参数传递是不是就没有这个问题了*/
    ProgressBar_old* progressBar;  


    public:
        FileSplitter(std::string filepath, int filenumber, ProgressBar_old* pro) : 
            m_filePath(filepath), m_fileNumber(filenumber), progressBar(pro) {
            
            }


        void split() {
            //1. 读取大文件



            //2. 分批次向小文件中写入
            for(int i = 0; i < m_fileNumber; ++ i) {
                if(!progressBar)
                    progressBar->setValue((i + 1) / m_fileNumber); 
            }
        
        }
};
//界面
class MainForm : public Form_old{

    TextBox_old* txtFilePath;
    TextBox_old* txtFileNumber;

    ProgressBar_old* pro;

    public:
    void Butto1_Click() {
        
        std::string filePath = txtFilePath->getText();
        int number = atoi(txtFileNumber->getText().c_str()); 
    
        FileSplitter splitter(filePath, number, pro);

        splitter.split();
    }
};

/*
定义:
    定义对象间的一对多(变化)的依赖关系，以便当一个对象(Subject)的状态发生改变的时候，
    所有依赖于它的对象都得到通知并且自动更新

*/
/*****************************面向对象程序模型-单一通知形式*/
class Form_new{};
class TextBox_new{
    public:
        std::string getText() {
            return "";        
        }

};
class ProgressBar_new{
    public:
        void setValue(int num) {
            num = 0; 
        }
};
class IProgress{   //抽象基类
    public:
        virtual void DoProgress(float value) = 0;
        virtual ~IProgress() {}
};
//文件分割器
class FileSplitter_new{
    std::string m_filePath;
    int m_fileNumber;

    IProgress* progress;   //抽象的通知机制
    public:
        FileSplitter_new(std::string& filepath, int filenumber, IProgress* pro) :
            m_filePath(filepath), m_fileNumber(filenumber), progress(pro){
        
        }

        void split() {
            
            //1. 读取文件


            //2. 分批次向小文件中写入
            for(int i = 0; i < m_fileNumber; i ++) {
                float value = (i + 1) / m_fileNumber;
                    onProgress(value); 
            }
        
        }

    protected:
        void onProgress(float value) {
            if(!progress) {
                progress->DoProgress(value);
            } 
        }
};
//界面
class MainForm_new : public Form_new, public IProgress {  //C++推荐的多继承模型：多个接口继承

    TextBox_new* txtFilePath;
    TextBox_new* txtFileNumber;

    ProgressBar_old* pro;   
    public:
    void Button1_Click() {
    
        std::string filepath = txtFilePath->getText();
        int number = atoi(txtFileNumber->getText().c_str());
    
        FileSplitter_new splitter(filepath, number, this);

        splitter.split();
    }    

    //重构
    virtual void DoProgress(float value) {
        pro->setValue(value); 
    }
};
/*
总结:
    使用面向对象的抽象，Observer模式使得可独立的改变目标与观察者，从而使得二者之间的依赖关系
达致松耦合。
    目标发送通知的时候，无需指定观察者，通知(可以携带通知信息作为参数)会自动传播。
    观察者自己决定是否需要订阅通知，目标对象对此一无所知。
 
*/
/*********************************************面向对象程序模型——多通知形式*/
class ConsoleNotifier : public IProgress {    //多通知
    public:
        virtual void DoProgress(float value) {
            std::cout << "."  << value << std::endl;  
        }
};
class FileSplitter_multi{

    std::string m_filePath;
    int m_fileNumber;

    //抽象通知机制，支持多个观察者
    std::vector<IProgress*>  m_iprogressVec;

    public:
    FileSplitter_multi(std::string& path, int num) :
        m_filePath(path), m_fileNumber(num){ 
    }


    void addProgress(IProgress* ip) {
        m_iprogressVec.push_back(ip); 
    }

    void removeProgress(IProgress* ip) {
        std::vector<IProgress*>::iterator res  = m_iprogressVec.begin();
        while(res != m_iprogressVec.end()) {
            if(*res == ip) {
                break; 
            } 
        }
        m_iprogressVec.erase(res);  //删除元素
    }

    void split() {
        
        //1. 读取大文件



        //2. 分批次向小文件中写入
        for(int i = 0; i < m_fileNumber; i ++) {
            float value = (i + 1) / m_fileNumber;
            OnProgress(value);        
        }
    }


    protected:
    virtual void OnProgress(float value) {
        if(!m_iprogressVec.empty())
            return;

        std::vector<IProgress*>::iterator itor = m_iprogressVec.begin();
        while(itor != m_iprogressVec.end()) {
            (*itor)->DoProgress(value);
            itor++;
        }
    }
};
//界面
class MainForm_multi : public Form_new, public IProgress{
    TextBox_new* txtFilePath;
    TextBox_new* txtFileNumber;

    ProgressBar_old* pro;   
    ConsoleNotifier* cn;
    public:
    void Button1_Click() {
    
        std::string filepath = txtFilePath->getText();
        int number = atoi(txtFileNumber->getText().c_str());
    
        FileSplitter_multi splitter(filepath, number);   //多通知机制

        splitter.addProgress(this);  //订阅通知
        splitter.addProgress(cn);

        splitter.split();
    }    

    //重构
    virtual void DoProgress(float value) {
        pro->setValue(value); 
    }

};
