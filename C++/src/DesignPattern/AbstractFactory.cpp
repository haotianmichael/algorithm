#include <iostream>
#include <vector>
/*
 动机:
 在软件系统中，经常面临”一系列相互依赖的对象“的建构工作，同时，由于需求的变化，
 往往存在更多系列对象的创建工作。
 
 如何应对这种变化? 如何绕过常规的对象创建方法(new)，提供一种”封装机制“来避免客户程序
 和这种”多系列具体对象创建工作“的紧耦合?
 */
class SqlConnection{
public:
    std::string ConnectionString;
};
class SqlDataReader;
class SqlCommand{
public:
    std::string CommandText;
    SqlDataReader* ExecuteReader();
};
class SqlDataReader{
public:
    bool Read();
};
class EmployDAO{
    std::vector<EmployDAO> res;
public:
    std::vector<EmployDAO> GetEmpliyees() {
        SqlConnection* connection =
        new SqlConnection();
        
        connection->ConnectionString = "...";
        
        SqlCommand* command =
        new SqlCommand();
        command->CommandText = "...";
        
        SqlDataReader *reader = command->ExecuteReader();
        while(reader->Read()) {
            
        }
        
        return res;
    }
};
/*
 定义:
 提供一个接口，让该接口负责创建一系列”相关或者相互依赖的对象“，无需指定他们具体的类。
 */
//数据库访问有关的基类
class IDBConnection{
};
class IDBCommand{
};
class IDataReader{
};
//支持SQL 数据库
class SqlConnection_new : public IDBConnection{
};
class SqlCommand_new : public IDBCommand{
};
class SqlDataReader_new : public IDataReader{
};
//支持Oracle 数据库
class OracleConnection : public IDBConnection{
};
class OracleCommand : public IDBCommand{
};
class OracleDataReader : public IDataReader{
};
class IDBFactory{  //高内聚  松耦合    防止一系列相关的对象错乱搭配
public:
    virtual IDBConnection* CreatDBConnection() = 0;
    virtual IDBCommand* CreatDBCommand() = 0;
    virtual IDataReader* CreatDataReader()  = 0;
};
class SqlDBFactory : public IDBFactory{
public:
    virtual IDBCommand * CreatDBCommand() override{
        return new SqlCommand_new();
    }
    virtual IDBConnection * CreatDBConnection() override{
        return new SqlConnection_new();
    }
    virtual IDataReader * CreatDataReader() override {
        return new SqlDataReader_new();
    }
    
};
class OracleFactory : public IDBFactory{
public:
    virtual IDBCommand * CreatDBCommand() override {
        return new OracleCommand();
    }
    
    virtual IDBConnection * CreatDBConnection() override{
        return new OracleConnection();
    }
    
    virtual IDataReader * CreatDataReader() override{
        return new OracleDataReader();
    }
};
class EmployDAO_new{
    IDBFactory* dbFactory;
    std::vector<EmployDAO> res;
public:
    EmployDAO_new(IDBFactory* idb) : dbFactory(idb) {
    }
    std::vector<EmployDAO> GetEmpliyees() {
        IDBConnection* connection =
        dbFactory->CreatDBConnection();
        
        IDBCommand* command =
        dbFactory->CreatDBCommand();
        
        IDataReader* reader = dbFactory->CreatDataReader();
        
        
        return res;
    }
    
};
/*
 总结:
 如果没有应对”多系列对象构建“的需求变化，则没有必要使用AbstractFactory模式，这时候使用简单的
 工厂模式完全可以。
 
 ”系列对象“指的是在某一特定系列下的对象之间有相互依赖，或作用的关系。不同系列的对象之间不能互相依赖。
 
 AbstractFactory模式主要在于应对”新系列“的需求变动。其缺点在于难以应对“新对象”的需求变动。
 */

