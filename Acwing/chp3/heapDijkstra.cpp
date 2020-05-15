#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
const int N = 100010;
int e[N], ne[N], h[N], w[N], idx;
int dist[N];
bool st[N];
int n, m;
typedef pair<int, int> PII;




void add(int a, int b ,int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}


int dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, 1});

    while(heap.size()){
        auto t = heap.top();
        heap.pop(); 
        int ver = t.second, distance = t.first;

        for(int i = h[ver]; i != -1; i = ne[i]) {
            int j = e[i];
            if(dist[j] > distance + w[i]) {
                dist[j] = distance + w[i];
                heap.push({dist[j], j});        
            } 
        }
    } 

    if(dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}


int 
main(void) {

    cin >> n >> m;
    memset(h, -1, sizeof h);
    while(m --) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c); 
    }

    cout << dijkstra() << endl;
    return 0;
}
