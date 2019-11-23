#include <iostream>
#include <algorithm>
#include <cstring> 

using namespace std;
const int N = 100010, M = 2 * N;
int n, m;
int h[N], e[M], ne[M], idx; //因为是无向图，点数相同，边数加倍
int color[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}


//具有深搜的性质。理解bool st数组和color的转换方式
bool dfs(int u, int c) {
    color[u] = c;
    for(int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if(!color[j]){
               if(!dfs(j, 3 - c)) return false; 
        }else if(color[j] == c) return false; 
    }
    return true;
}

int 
main(void) {

    cin >> n >> m;
    memset(h, -1, sizeof h);
    
    //建图
    while(m --) {
        int a, b;
        cin >> a >> b; 
        add(a, b), add(b, a); 
    }

    bool flag = true;
    for(int i = 1; i <= n; i ++)
        if(!color[i]) {
            if(!dfs(i, 1)) {
                flag = false;
                break; 
            } 
        }


    if(flag) puts("Yes");
    else puts("No");

    return 0;
}
