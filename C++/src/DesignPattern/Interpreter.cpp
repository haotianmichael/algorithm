#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <string>
#include <stack>




using namespace std;

/*
动机:  
    在软件构建过程中，如果某一个特定领域的问题比较复杂，类似的结构不断重复出现，如果
  使用普通的编程方式来实现将面临非常频繁的变化。

    在这种情况下，将特定领域的问题表达为某种语法规则下的句子，然后构建一个解释器来解释这样的
  句子，从而达到解决问题的目的。  
*/
class Expression{

    public:
        virtual int interpreter(map<char, int> var) = 0;
        virtual ~Expression(){}
};

//变量表达式
class VarExpression : public Expression{
    char key;
    public:
    VarExpression(const char& _key) : key(_key){
    }

    virtual int interpreter(map<char, int> var) override{
        cout << "TEST3" << endl;
        return var[key]; 
    }
};

//符号表达式
class SymbolExpression : public Expression{
    //运算符左右
    protected:
    Expression* left;
    Expression* right;
    public:
    SymbolExpression(Expression* _left, Expression* _right) 
   : left(_left), right(_right) {
    
    }

};

//加法运算
class AddExpression : public SymbolExpression{

    public:
        AddExpression(Expression* left, Expression* right)
            : SymbolExpression(left, right){
        }

        virtual int interpreter(map<char, int> var) override{
            cout << "TEST2" << endl;
            //cout << left->interpreter(var) << "+" << right->interpreter(var) << endl; 
            int result = left->interpreter(var) + right->interpreter(var); 
            //cout << "RESULT:" << result << endl;
            return result;
        }
};

//减法运算
class SubExpression : public SymbolExpression{

    public:
        SubExpression(Expression* left, Expression* right) 
            : SymbolExpression(left,right){
        }

        virtual int interpreter(map<char, int> var) override {
            cout << "TEST1" << endl;
            return left->interpreter(var) - right->interpreter(var); 
        }
};


Expression* analyse(std::string expStr) {

    stack<Expression*> expStack;
    Expression* left = nullptr;
    Expression* right = nullptr;
    //cout << expStr.size() << endl;
    for(unsigned int i = 0; i <= expStr.size(); i ++) {
        switch(expStr[i]) {
        case '+': 
            //加法运算
            //cout << expStr[i];
            left = expStack.top();
            right = new VarExpression(expStr[++i]);
            expStack.push(new AddExpression(left, right));
            break;
        case '-':
            //减法运算
            //cout << expStr[i];
            left = expStack.top();
            right = new VarExpression(expStr[++i]);
            expStack.push(new SubExpression(left, right));
            break;

        default:
            //终结表达式
            //cout << expStr[i];
            expStack.push(new VarExpression(expStr[i])); 
            //cout << expStack.top();
        } 
    
    }

    Expression* expression = expStack.top();   //
    return expression;
}

void release(Expression* expression) {
    
    //释放内存

}

int main(void)
{
    std::string expStr = "a+b";       //类似数表达式的规则
    map<char, int> var;
    var.insert(make_pair('a', 5));
    var.insert(make_pair('b', 2));
    //cout << var.size() << endl;


    /*map<char, int>::iterator iter;*/
    //for(iter = var.begin(); iter != var.end(); iter++) {
        //cout << iter->first << endl; 
    //}
    Expression* expression = analyse(expStr);

    int result = expression->interpreter(var);
    //cout << expression->left->interpreter(var);
    cout << result << endl;

    release(expression);

    return 0;
}

/*
定义: 
    给定一个语言，定义它的文法的一种表示，并定义一种解释器，这个解释器利用该表示来解释语言中句子。
*/
/*
总结：
    Interpreter模式的应用场合是Interpreter模式应用中的难点，只有满足“业务规则频繁变化，且
    类似的结构不断重复出现”，并且容易抽象为语法规则的问题才使用使用interpreter模式。 
 
    使用Interpreter模式来表示文规则，从而可以使用面向对象技巧来方便地“扩展”文法。

    Interpreter模式比较适合简单的文法表示，对于复杂的文法表示，Interpreter模式会产生比较大的
    类层次结构，需要求助于语法分析生成器这样的标准工具。
*/
