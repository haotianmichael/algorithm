#include <iostream>
#include <algorithm>

/*
动机:
    某些情况下我们可能会”过度的使用继承来扩展对象的功能“，由于继承为类型引入的静态特质(编译时装饰)，使得这种扩展
缺乏灵活性；并且随着子类的增多(扩展功能的增多)，各种子类的组合(扩展功能的组合)会导致更多子类的膨胀。    
    
    如何使用”对象功能的扩展“能够根据需求来动态的实现？同时避免”扩展功能的增多“带来的子类膨胀问题？从而
使得任何”功能扩展变化“所导致的影响即为最低。
*/
/*******************************************结构化程序模型*/
//业务操作
class Stream{
    public:
        virtual char Read() = 0;
        virtual void Seek() = 0;
        virtual void Write() = 0;

        virtual ~Stream();
};
//文件流
class FileStream : public Stream{
    public:
        virtual char Read() {
            //读文件流
            return ' '; 
        }

        virtual void Seek() {
            //定位文件流 
        }

        virtual void Write() {
            //写文件流        
        }
};
//网络流
class NetworkStream : public Stream{
    public:
        virtual char Read() {
            //读网络流
            return ' ';
        }
        
        virtual void Seek(){
            //定位网络流
        }

        virtual void Write() {
            //写网络流
        }
};
//内存流
class MemoryStream : public Stream{
    public:
        virtual char Read() {
            //读内存流
            return ' '; 
        }

        virtual void Seek() {
            //定位内存流
        }

        virtual void Write() {
            //写内存流
        }
};
//扩展操作
class CryptoFileStream : public FileStream{
    public:
        virtual char Read() {
            
            //额外的加密操作...
            FileStream::Read();   //读文件流
            return ' '; 
        }

        virtual void Seek(){
            
           //额外的加密操作...
            FileStream::Seek();    //定位文件流
        }

        virtual void Write() {
        
            //额外的加密操作
            FileStream::Write();    //写文件流
        }
};
//扩展操作
class CryptoNetworkStream : public NetworkStream{
    public:
        virtual char Read() {
            
           //额外的网络流 
            NetworkStream::Read();  //读网络流
            return ' ';
        }

        virtual void Seek() {
        
            //额外的加密操作
            NetworkStream::Seek();   //定位网络流
        }

        virtual void Write() {
        
            //额外的加密操作
            NetworkStream::Write();    //写文件流
        }
};
//扩展操作
class CryptoMemory : public MemoryStream{
    public:
        virtual char Read() {
            
           //额外的加密操作
            MemoryStream::Read();   //读内存流
            return ' ';
        }

        virtual void Seek() {
        
            //额外的加密操作
            MemoryStream::Seek();  //定位内存流
        }

        virtual void Write() {
        
            //额外的加密操作
            MemoryStream::Write();   //写内存流
        }
};
class BufferedFileStream : public FileStream{
    //...
};
class BufferedNetworkStream : public NetworkStream{
    // ...
};
class BufferedMemoryStream : public MemoryStream{
    // ...
};
class CryptoBufferedFileStream : public FileStream{
    //...
};
class CryptoBufferedNetWorkStream : public NetworkStream{
   // ...
};
class CryptoBufferedMemoryStream : public MemoryStream{
    // ...
};
void Process_old() {

    //编译时装配
    CryptoFileStream *fs1 = new CryptoFileStream();

    BufferedFileStream *fs2 = new BufferedFileStream();

    CryptoBufferedFileStream *fs3 = new CryptoBufferedFileStream();

}
/*
定义:
    动态(组合)地给一个对象增加一些额外的职责。就增加功能而言，Decorator模式比生成子类(继承)更为灵活(消除
    重复代码&减少子类个数)
*/
/***************************************面向对象对象模型*/
class DecoratorStream : public Stream{   //Decorator  使用组合来实现多态
    protected:
        Stream* _stream;
    public:
        DecoratorStream(Stream* stm) : _stream(stm) {
        }
};
class CryptoStream : public DecoratorStream{
    public:

    CryptoStream(Stream* stm) : DecoratorStream(stm){
    }
    virtual char Read() {
        //额外的加密操作 
        _stream->Read();    //读文件流
        return ' ';
    }

    virtual void Seek() {
        //额外的加密操作
        _stream->Seek();    //定位文件流 
    }

    virtual void Write() {
        //额外的加密操作
        _stream->Write();    //写文件流 
    }
};
class BufferedStream : public DecoratorStream{
    public:
    
    BufferedStream(Stream* stm) : DecoratorStream(stm) {
    }
    virtual char Read() {
    
        //额外的缓冲操作
        _stream->Read();
        return ' ';
    }

    virtual void Seek() {

        //额外的缓冲操作
        _stream->Seek(); 
    }

    virtual void Write() {
    
        //额外的缓冲操作
        _stream->Write();
    }
};
class CrptoBufferedStream : public DecoratorStream{
    public:

    CrptoBufferedStream(CrptoBufferedStream* stm) : DecoratorStream(stm) {
    }
    virtual char Read() {
    
        //额外的加密，缓冲操作
        _stream->Read();
        return ' ';
    }

    virtual void Seek() {
    
        //额外的加密，缓冲操作
        _stream->Seek();
    }

    virtual void Write() {
    
        //额外的加密，缓冲操作
        _stream->Write();
    }
};

void Process_new() {

    //运行时装配
    FileStream* s1 = new FileStream();
    CryptoStream* s2 = new CryptoStream(s1);
    BufferedStream* s3 = new BufferedStream(s2);
    BufferedStream* s4 = new BufferedStream(s1);

}
/*
总结: 
    通过采用组合而非继承的手法，Decorator模式实现了再运行时动态扩展对象功能的能力，而且可以根据需求扩展多个
   功能。避免了使用继承带来的”灵活性差“和"多子类衍生问题"。

    Decorator类在接口上表现为is-a Component的继承关系，即Decorator类继承了Component类所具有的接口。但是在实现上
    又表现为has-aComponent的组合关系，即Decorator类有使用另外一个COmponent类。
    
    Decorator模式的目的并非解决”多子类衍生的多继承“问题，其要点在于解决”主体类在多个方向上的扩展功能“————实为”装饰“
    的含义。
*/
