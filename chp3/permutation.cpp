#include <iostream>
#include <algorithm>

using namespace std;
const int N = 100010;
int path[N], n;
bool stk[N];

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
