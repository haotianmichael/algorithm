#include <iostream>
#include <cstring>
#include <algorithm>

//因为有负权边
using namespace std;
const int N = 510, M = 10010;

struct Edge {
    int a, b, c;
}edges[M];

int n, m, k;
int dist[N];
int last[N];

void bellman_ford() {

    //数组初始化
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    //不超过k条边
    for(int i = 0; i < k; i ++) {
        memcpy(last, dist, sizeof dist);
        for(int j = 0; j < m;  j ++) {
            auto e = edges[j]; 
            dist[e.b] = min(dist[e.b], last[e.a]+e.c); 
        }
    }
}

int 
main(void) {
    cin >> n >> m >> k;

    for(int i = 0; i < m; i ++) {
        int a, b, c;
        cin >> a>> b >> c;
        edges[i].a = a;
        edges[i].b = b;
        edges[i].c = c;
    }
    bellman_ford();

    if(dist[n] > 0x3f3f3f3f / 2) puts("impossible");
    else printf("%d\n", dist[n]);

    return 0;
}
