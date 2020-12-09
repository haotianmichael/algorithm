#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 100010, M = 200010, INF = 0x3f3f3f3f; 
int n, m;
int p[N];

struct Edge{

    int a, b, w;
    bool operator < (const Edge &W) const {
        return w < W.w; 
    }
}edges[M];

int find(int x) {
    if(p[x] != x) p[x] = find(p[x]); return p[x]; }

/*
    本质是
    将所有有序边都遍历一遍，然后选择
    (遍历的边数) && (是否在构造图中  是否连通)  
*/
int kruskal() {
    sort(edges, edges + m);
    //注意并查集的初始化   
    //注意理解图中 点和边的关系  点是从1开始的
    for(int i = 1; i <= n; i ++) p[i] = i;

    int res = 0, cnt = 0;

    for(int i = 0; i < m; i ++) {

        int a = edges[i].a, b = edges[i].b, w = edges[i].w;
        a = find(a), b = find(b); 
        if(a != b) {
            p[a] = b;
            res += w;
            cnt ++; 
        }
    }
    if(cnt < n - 1) return INF;
    return res;
}


int 
main(void){

    cin >> n >> m;
    for(int i = 0; i < m; i ++) {
        int a,b,w;
        cin >> a >> b >> w; 
        edges[i].a = a;
        edges[i].b = b;
        edges[i].w = w;
    }

    int t = kruskal();
    if(t == INF) puts("impossible");
    else printf("%d\n", t);

    return 0;
}
