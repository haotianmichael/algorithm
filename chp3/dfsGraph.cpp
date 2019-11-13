#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 100010, M = N * 2;
int e[N], ne[N], h[N], idx;
bool st[N];

void add (int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dfs(int u) {
    st[u] = false;

    for(int i = h[u]; i != -1; i=ne[i]) {
        int j = e[i];
        if(!st[i]) dfs(j); 
    }
}

int 
main(void) {

    memset(h, -1, sizeof h);

    dfs(1);    

    return 0;
}
