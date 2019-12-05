#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_set>

using namespace std;
const int N = 110, M = 10010;
int n,m;
int s[N], f[M]; //s表示石子个数  f表示sg函数的值

//记忆化搜索
int sg(int x) {

    if(f[x] != -1) return f[x];

    unordered_set<int> S;
    for(int i = 0; i < m; i ++) {
        int sum = s[i];
        if(x >= sum)  S.insert(sg(x - sum));  //递归搜索
    }

    for(int i =0; ; i++)
        if(!S.count(i))
            return f[x] = i;
}


int 
main(void) {

    cin >> m;
    for(int i = 0; i< m; i ++) cin >> s[i];  //初始化石子数量
    memset(f, -1, sizeof f);
    cin >> n;
    int res = 0;
    while(n --) {     //直接计算每一堆石子的sg函数值
        int x;
        cin >> x;
        res ^= sg(x); 
    }

    if(res) cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}

