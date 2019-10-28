#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//去重算法
void duplicate(vector<int> &q) {
    int j = 0;
    for(unsigned int i = 0;  i < q.size(); i ++) {
        if(!i || q[i] != q[i-1]) 
            q[j++] = q[i];
    }

    for(auto item : q) 
        cout << item; 

    return;
}


//按空格读单词
void printfword(string s) {

    for(unsigned int i = 0; i < s.size(); i ++) {
        unsigned int  j = i;
        while(j < i && s[j] != ' ') j ++;
        for(unsigned int k = 0; k < j; k ++) cout << s[k]; 
        cout << endl; 
    }

    return ;
}

//最长不重复子序列
void  subsequence(vector<int> &q) {

    const int N = 1e6 + 10;
    int s[N];
    int n;
    cin >> n;
    for(int i = 0; i < n; i ++) {
        int x;
        cin >> x;
        q.push_back(x); 
    }

    int res = 0;
    for(unsigned int i = 0, j = 0; i < q.size(); i ++) {
        s[q[i]]++;
        while(s[q[i]] > 1) {
            s[q[j]] --;
            j ++; 
        } 
        res = (res >= (int)(i - j + 1)) ? res : (i - j + 1); 
    }
    cout << res << endl;
    return ;
}

int 
main(void) {
    vector<int> q;
    string s;

    //cin >> q
    duplicate(q);     

    //cin >> s
    printfword(s);

    //cin >> q
    subsequence(q);

    return 0;
}
