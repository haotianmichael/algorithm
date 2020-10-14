#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//去重算法
void duplicate(vector<int> &q) {
    for(unsigned int i = 0;  i < q.size(); i ++) {
        if(!i || q[i] != q[i-1]) 
            cout << q[i];
    }
    puts("");

    return;
}


//按空格读单词
void printfword(string s) {

    for(unsigned int i = 0; i < s.size(); i ++) {
        unsigned int  j = i;
        while(j < s.size() && s[j] != ' ') j ++;
        for(unsigned int k = 0; k < j; k ++) cout << s[k]; 
        cout << endl; 
        i = j;
    }

    return ;
}

//注意思路的培养
void subsequenceII() {

    const int N = 100010;
    int a[N], s[N];
    int n;
    cin >> n;
    for(int i = 0; i< n; i ++) cin >> a[i];

    int res = 0;
    for(int i = 0, j = 0; i  < n; ++ i){
        s[a[i]] ++;
        while (s[a[i]] > 1) {
            s[a[j]] --;
            j ++; 
        }        
        res = max(res, i - j + 1);
    }  
    cout << res << endl;
    return;
}


//最长不重复子序列
void  subsequence(vector<int> &q) {

    const int N = 1e6 + 10;
    int s[N];
    /*int n;*/
    //cin >> n;
    //for(int i = 0; i < n; i ++) {
        //int x;
        //cin >> x;
        //q.push_back(x); 
    //}

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
    //duplicate(q);     

    //cin >> s
    //printfword(s);

    q.push_back(1);
    q.push_back(2);
    q.push_back(3);
    q.push_back(3);
    q.push_back(4);
    q.push_back(5);
    q.push_back(6);
    subsequence(q);

    return 0;
}
