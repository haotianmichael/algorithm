#include <iostream>

/*
动机：
    由于某些类型的固有的实现逻辑，使得它们具有两个变化的维度，乃至多个维度的变化。

    如何应对这种”多维度“的变化？如何利用面向对象技术来使得类型可以轻松的沿着两个乃至多个方向变化，而不
    引入额外的复杂度？
*/
/***********************************************结构化程序模型*/
class Image{ };
class Message{
    public:
        virtual void Login(std::string name, std::string password) = 0;
        virtual void SendMessage(std::string message) = 0;
        virtual void SendPicture(Image image) = 0;

        virtual void PlaySound() = 0;
        virtual void DrawShapge() = 0;
        virtual void Write() = 0;
        virtual void Connect() = 0;

        virtual ~Message(){}
};
//平台实现
class PCMessageBase : public Message{
    public:
        virtual void PlaySound() {
        }

        virtual void DrawShapge() {
        }

        virtual void Write() {
        }

        virtual void Connect() {
        }
};
class MobileMessageBase : public Message{
    public:
        virtual void PlaySound() {
        }

        virtual void DrawShapge() {
        }

        virtual void Write() {
        
        }

        virtual void Connect() {
        
        }
};
//业务抽象
class PCMessageBaseLite : public PCMessageBase{
    public:
        virtual void Login(std::string name, std::string password) {
            PCMessageBase::Connect(); 
            //........
        }

        virtual void SendMessage(std::string message) {
            PCMessageBase::Write(); 
            //.........
        }

        virtual void SendPicture(Image image) {
            PCMessageBase::DrawShapge();
            //......... 
        }
};
class PCMessagePerfect : public PCMessageBase{
    public:
        virtual void Login(std::string name, std::string password) {
            PCMessageBase::PlaySound();
            //************
            PCMessageBase::Connect();
            //************ 
        }

        virtual void SendMessage(std::string message) {
            PCMessageBase::PlaySound();
           //***************
            PCMessageBase::Write(); 
        }

        virtual void SendPicture(Image image) {
            PCMessageBase::PlaySound();
            //**************
            PCMessageBase::DrawShapge();
        }
};
//Mobile业务抽象类似
class MobileMessagePerfect : public MobileMessageBase{
    public:
        virtual void Login(std::string name, std::string password) {
            MobileMessageBase::PlaySound();
            //***************
            MobileMessageBase::Connect();
        }

        virtual void SendMessage(std::string message){
             MobileMessageBase::PlaySound();
           //*****************
             MobileMessageBase::Write(); 
        }

        virtual void SendPicture(Image image) {
            MobileMessageBase::PlaySound();
          //********************
            MobileMessageBase::DrawShapge();  
        }

};
class MobileMessageLite : public MobileMessageBase{
    public:
        virtual void Login(std::string name, std::string password) {
            //***************
            MobileMessageBase::Connect();
        }

        virtual void SendMessage(std::string message){
           //*****************
             MobileMessageBase::Write(); 
        }

        virtual void SendPicture(Image image) {
          //********************
            MobileMessageBase::DrawShapge();  
        }

};
void Process_old() {

    //编译时装配
    Message *m = 
        new MobileMessagePerfect();

}
/*
定义：
    将抽象部分(业务功能)与实现部分(平台实现)分离，使它们都可以独立地变化。 
*/
/************************************************面向对象程序模型*/
class MessageImp;
class Message_new{
    protected:
    MessageImp* messagerimp;   //统一
    public:
        virtual void Login(std::string name, std::string password) = 0;
        virtual void SendMessage(std::string message) = 0;
        virtual void SendPicture(Image image) = 0;
        virtual ~Message_new(){}
};
class MessageImp{
    public:
        virtual void PlaySound() = 0;
        virtual void DrawShapge() = 0;
        virtual void Write() = 0;
        virtual void Connect() = 0;

        virtual ~MessageImp(){}
};
class PCMessageImp : public MessageImp{
    public:
        virtual void PlaySound() {
        }

        virtual void DrawShapge() {
        }

        virtual void Write() {
        }

        virtual void Connect() {
        }
};
class MobileMessageImp : public MessageImp{
    public:
        virtual void PlaySound() {
        }

        virtual void DrawShapge() {
        }

        virtual void Write() {
        
        }

        virtual void Connect() {
        
        }
};
class MessageLite : public Message_new{
    public:
        virtual void Login(std::string name, std::string password) {
            //***************
            messagerimp->Connect();
        }

        virtual void SendMessage(std::string message){
           //*****************
             messagerimp->Write(); 
        }

        virtual void SendPicture(Image image) {
          //********************
            messagerimp->DrawShapge();  
        }

};
class MessagePerfect : public Message_new{
    public:
        virtual void Login(std::string name, std::string password) {
            messagerimp->PlaySound();
            //***************
            messagerimp->Connect();
        }

        virtual void SendMessage(std::string message){
             messagerimp->PlaySound();
           //*****************
             messagerimp->Write(); 
        }

        virtual void SendPicture(Image image) {
            messagerimp->PlaySound();
          //********************
            messagerimp->DrawShapge();  
        }

};
void Process_new() {
    //运行时装配
    MessageImp* imp = new PCMessageImp();
    Message* m = new MessageLite(imp);
}
/*
    Bridge模式使用”对象间的组合关系“解耦了抽象和实现之之间固有的绑定关系，使得抽象和实现之间可以沿着各自的维度
来变化，所谓抽象和实现沿着各自维度的变化，即”子类化“它们。
    Bridge模式有时候类似于多继承方案，但是多继承方案往往违背单一职责原则(即一个类只有一个变化的原因)，复用性比较差。
Bridge模式是比多继承更好的解决方法。
    Beidege模式的应用一般在”两个非常强的变化维度“，有时候一个类也有多余两个的变化维度，这时候可以使用Bridge的扩展模式。
*/
