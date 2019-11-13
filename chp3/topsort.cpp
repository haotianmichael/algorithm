#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
int n, m; const int N = 100010;
int e[N], ne[N], h[N], idx;
int q[N], d[N];


/*
    注意在图的存储过程中
    因为有节点和边两个变量  所以一定要注意数组下表是从1开始还是从0开始
    数组可以作为额外存储信息的很好的存储介质    本题中作为存储入度的介质
*/

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}

bool topsort() {
    int hh = 0, tt = -1;
    for(int i =1; i <= n; i++)   //注意初始值是1 因为h数组是从1开始算的
        if(!d[i]) q[++tt] = i;

    while(hh <= tt) {
        int t = q[hh++];
        for(int i =h[t]; i != -1; i=ne[i]) {
            int j = e[i];
            d[j] --;
            if(!d[j]) q[++tt] = j;  
        } 

    }
    return (tt == n - 1);
}

int 
main(void) {

    cin >> n >> m;
    //注意在存储过程中一定要注意 初始化为-1
    memset(h, -1, sizeof h);
    while(m --) {
        int a, b;
        cin >> a >> b;
        add(a, b); 
        d[b] ++;    
    }

    if(topsort()) {
        for(int i = 0; i < n; i++) cout << q[i] << endl;
    }else cout << "-1" << endl;

    return 0;
}
