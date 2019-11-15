#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 510, INF = 0x3f3f3f3f;

int g[N][N];
int dist[N];
bool st[N];
int n, m;


int prim() {
    memset(dist, 0x3f, sizeof dist);

    int res = 0;
    for(int i = 0; i < n; i ++) {
        int t = -1;
        for(int j = 1; j <= n; j ++)
            if(!st[j] && (t==-1 || dist[t] > dist[j]))  t = j;
    
        if(i && dist[t] == INF) return INF;
        if(i)  res += dist[t];


        for(int i = 1; i <= n; i ++) dist[i] = min(dist[i], g[t][i]);
        st[t] = true;
    }

    return res;
}

int 
main(void) {
    cin >> n >> m;
    memset(g, 0x3f, sizeof g);
    while(m --){
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = g[b][a] = min(g[a][b], c);
    }

    int t = prim();

    if(t == INF) cout << "impossible" << endl;
    else cout << t << endl;

    return 0;
} 
