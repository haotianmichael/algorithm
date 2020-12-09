/*
    Some Algorithm which is fundamental to Coding. 
    Updating constantly.
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>
#include <stack>
using namespace std;

/*==========去重*/
void duplicate(string s) {

    for(unsigned i = 0; i < s.size(); i ++)  {
        if(!i || s[i] != s[i-1]) {
            cout << s[i];
        } 
    }
    puts("");
}


/*============读单词*/
void word(string s) {

   for(unsigned i = 0; i < s.size(); i ++){
        unsigned j = i;
        while(j < s.size() && s[j] != ' ') j++;   
        for(unsigned k = i; k < j; k ++) cout << s[k]; 
        puts("");
        i = j;
   }

}


/*=============翻转
    翻转句子中的单词顺序，不翻转单词中的字母顺序 
t: 输出末尾的空格
    
   int res = 0;
    while(x) {
        res += (res* 10 + x % 10);         
        x /= 10;
    }
 */
string reverse(string s){
    if(s == "") return s;
    stack<string> st;    
    for(unsigned i = 0; i < s.size(); i ++) {
        unsigned j = i;
        string tmp = "";
        while(j < s.size() && s[j] != ' ') {
            tmp += s[j++];
        }
        st.push(tmp);
        i = j; 
    } 

    string res;
    while(st.size() > 1) {
        res += st.top();
        res += " ";
        st.pop();
    }
    cout << st.top();
    return res;
}

/*==============最大不重复子序列
 
    1. 掌握用数组判断重复
    2. 理解该题的本质在于单调 
*/
void masSquence() {
    const int N = 100010; 
    int n, a[N], s[N];
    int res = 0;
    cin >> n;
    for(int i  = 0; i < n; i ++) cin >> a[i]; 
    
    for(int i = 0, j = 0; i < n;  ++i) {
        s[a[i]] ++; 
        while(s[a[i]] > 1) {
            s[a[j]] --; 
            j++; 
        } 
        res = max(res, i - j + 1); 
    } 

    cout << res << endl;
}



/*=============位运算*/
void binary() {
    //等到复习到二进制的时候再加上这块
    int x;
    while(cin >> x) {
        cout << (bitset<8>)x << endl;
    }
}
int lowbit(int x){
    return(x & (~x + 1));
}
void count() {
    int input, count = 0;
    cin >> input;
    while(input) {
        input -= lowbit(input);
        count++;
    }
    cout << count << endl;
}

int main(void)
{
    
    //count();
    //duplicate(string("babaaabbcdeeefggg"));
    //word("haotian is a good man");
    //cout << reverse("haotian is a good man.") << endl;
    binary();

    return 0;
}
