#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 510, M = 100010;
const int INF = 0x3f3f3f3f;
int e[M], ne[M], h[N], w[M], idx;
int dist[N];
bool st[N];
int n, m;
void add(int a, int b, int c) {
        e[idx] = b;
        ne[idx] = h[a];
        w[idx] = c;
        h[a] = idx ++;
}

int Dijkstra() {

    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    for(int i = 0; i < n;  i ++) {
        int t = -1;
        for(int j = 1; j <= n; j ++) 
            if(!st[j] && (t==-1 || dist[t] > dist[j]))  t = j;

        st[t] = true;
        for(int j = h[t]; j != -1; j =ne[j])  {
            int k =  e[j];
            dist[k] = min(dist[k], dist[t] + w[j]); 
        }
    }

    if(dist[n] == INF) return -1;
    return dist[n];
}

int 
main(void) {

    cin >> n >> m;
    memset(h, -1, sizeof h);
    while(m --) {
        int a, b, w;
        cin >> a>> b >> w;
        add(a, b, w); 
    }

    int t = Dijkstra();

    cout << t << endl;
    return 0;
}
