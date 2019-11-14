#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>


/*既可以解决负权边，又可以根据代替Dijkstra解决正权边问题*/
/*不过时间复杂度可能有时候会很高*/
using namespace std;
const int N = 100010;
int dist[N];
int e[N], ne[N], h[N], w[N], idx;
bool st[N];

int n, m;

void add(int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}


int spfa() {

    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    st[1] = true;

    queue<int> q;
    q.push(1);

    while(q.size()) {
        int t = q.front();
        q.pop();
        st[t] = false;
        for(int i = h[t]; i != -1; i =ne[i]){
            int j = e[i];
            if(dist[j] > dist[t] + w[i])  {
                dist[j] = dist[t] + w[i]; 
                if(!st[j]) {
                    q.push(j); 
                    st[j] = true;
                }
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
        cin >>a >> b >> c;
        add(a, b, c);  
    } 

    if(spfa() == -1) cout << "impossible" << endl;
    else cout << dist[n] << endl;
    return 0;
}
