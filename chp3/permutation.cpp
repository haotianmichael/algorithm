#include <iostream>
#include <algorithm>

using namespace std;
const int N = 100010;
int path[N], n;
bool stk[N];

//注意其中变量u和i是最重要的理解DFS的方式，path[u]只是存储方式，i的变化才是重点
void dfs(int u) {
    if(u == n) {
        for(int i = 0; i < n; i ++) cout << path[i] << ' ';      
        puts(""); 
        return ;
    }

    for(int i = 1; i <= n; i ++) {
        if(!stk[i]) {
            path[u] = i;
            stk[i] = true;    
            dfs(u + 1); 
            stk[i] = false;
        }
    }
}

int 
main(void) {

    cin >> n;
    dfs(0);
    return 0;
}
