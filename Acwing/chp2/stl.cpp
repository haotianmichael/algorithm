#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <bitset>


using namespace std;


    int 
main (void) 
{

    int n; 
    cin >> n;


    /*vector  变长数组*/
    vector<int> a(n, 3);  //初始化的时候可以赋初值
    a.size(); a.empty();  //时间复杂度是O(1)  所有容器都有
    a.clear();  //清空容器
    a.front();  //第一个元素 
    a.back();  //最后一个元素
    a.push_back(3);  //按顺序插入
    a.pop_back();  //删除掉最后一个元素
    a.begin();  //迭代器a[0]
    a.end();  //迭代器 a[a.size()]

    //遍历容器的方式  
    for(int i = 0; i < n; i ++) a.push_back(i);
    for(auto x = a.begin(); x != a.end(); x ++) cout << *x << ' ';
    puts("");
    for(unsigned int i = 0; i < a.size(); i ++) cout << a[i] << ' ';
    puts("");
    for(auto i : a) cout << i << ' ';
    puts("");

    //支持比较运算  按照字典序比较大小
    vector<int> b(4, 3), c(3, 4); 

    /*pair二元组
      first  第一关键字
      second 第二关键字 
      只是比较运算： 以first为第一关键字  second为第二关键字（字典序）
      有两种不同的属性，按照某一个属性来排序
      三种属性 
      pair<int , pair<int, int>>a;
     */
    pair<int, string> p;
    p = make_pair(3, "haotian");



    /*string  封装字符串*/
    string str = "yxc"; 
    str += "def";
    str.size();  str.length();  //作用一样
    str.empty();
    str.clear();
    //substr(x, y) 中x是开始的字符  y代表了长度   substr(x)省略了y代表从x开始的所有子串
    cout << str.substr(1, 2) << endl;
    //c_str   返回字符数组起始地址
    printf("%s\n", str.c_str());


    /*queue 队列*/
    queue<int> q;
    q.size();
    q.empty();
    q.push(8);  //向队尾插入一个元素
    q.front();  //返回队头元素
    q.back(); //返回队尾元素
    q.pop();  //弹出队头元素


    /*priority_queue  优先队列*/
    //默认是大根堆
    priority_queue<int> pq;
    pq.push(8);   //插入一个元素   
    pq.top();   //返回堆顶元素
    pq.pop();  //弹出堆顶元素
    priority_queue<int, vector<int>, greater<int>> qp;  //申明一个小根堆



    /*stack 栈*/
    stack<int> stk;
    stk.push(0); 
    stk.size();
    stk.top();  //返回栈顶元素
    stk.pop(); //弹出栈顶元素
    stk.empty();


    /*deque 双端队列*/
    //效率很低
    deque<int> dq;
    dq.clear();
    dq.size();
    dq.empty();
    dq.front();
    dq.back();
    dq.push_back(9);
    dq.push_front(9);
    dq.pop_back();
    dq.pop_back();


    /*set和map  平衡二叉树（红黑树）   基本上所有增删改查的时间复杂度是O(logn)*/
    /*set multiset*/
    //不允许插入重复的元素
    set<int> S;
    multiset<int> MS;
    S.size();
    S.empty();
    S.clear();
    S.insert(9); //插入一个数
    S.find(9);
    S.count(9);
    //参数是一个数x  删除所有x
    //参数是一个迭代器  删除这个迭代器
    S.erase(8);
    S.lower_bound(9); //返回大于等于9的最小的数的迭代器
    S.upper_bound(9); //返回大于9的最小的书的迭代器


    /*map multimap*/
    map<int, string> M;
    pair<int, string>Mp = make_pair(2, "haotian");
    M.insert(Mp);  //插入是一个pair
    M.erase(9);
    M.lower_bound(9);
    M.upper_bound(9); 
    M[2] = "is good";  //map可以将pair中的元素当做数组来使用  时间复杂度是O(logn)


    /*unordered_map  unordered_set unordered_multimap unordered_multiset*/    
    //和上面的map  set区别在于无序存储   
    //时间复杂度是O(1)
    //不支持lower_bound  upper_bound 操作



    /*bitset*/
    //支持所有位运算   ~ & | ^ << >> == != []  count()返回多少个1 any/none()返回是否至少有一个1 
    //none判断是否全为空  
    bitset<10000> BS;
    ~BS;  //取反
    BS.count();
    BS.set();  //所有位置为一
    BS.set(9, 0); //将第9位变成0
    BS.reset();  //所有为变成0
    BS.flip();   //等价于~
    BS.flip(9); //将第9位取反

    return 0;
}
