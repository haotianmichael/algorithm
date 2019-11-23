#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
const int N = 100010;
int e[N], ne[N], w[N], h[N], idx;
int n, m;
int dist[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}

int spfa() {

    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    queue<int> q;
    q.push(1); 

    while(q.size()){
        int t = q.front();
        q.pop();
        st[t] = false;
        for(int i = h[t]; i!= -1; i = ne[i]) {
            int j = e[i];
            if(dist[j] > dist[t] + w[i]){
                dist[j] = dist[t] + w[i];
                if(!st[j])  {
                    q.push(j); 
                    st[j] = true;
                }
            }            
        }
    }

    if(dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}

int Dijkstra() {

    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    for(int i = 0; i < n; i ++) {
        int t = -1;
        for(int j = 1; j <= n; j++)
            if(!st[j] && (t==-1 || dist[t]>dist[j])) t = j;

        st[t] = true;

        for(int j = h[t]; j != -1; j = ne[j]) {
            int k = e[j];
            dist[k] = min(dist[k], dist[t] + w[j]); 
        }
    }
    
    if(dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}


int 
main(void){

    cin >> n >> m;
    memset(h, -1,sizeof h);
    while(m --) {
        int a, b,w;
        cin >> a >> b>> w;
        add(a, b, w); 
    }

    int t = Dijkstra();
    cout << t << endl;
    return 0;
}  
