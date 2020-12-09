#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 100010;
int e[N],ne[N], h[N], idx;
int q[N], d[N];
int n, m;

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}

int bfs() {

    int hh = 0, tt = 0;
    q[0] = 1;   // 因为是从第一个点
    memset(d, -1, sizeof d);
    d[1] = 0; //从第一个点

    while(hh <= tt) {
        int t = q[hh++];
        for(int i=h[t]; i != -1; i=ne[i]) {
            int j = e[i];
            if(d[j] == -1) {
                d[j] = d[t] + 1;
                q[++tt] = j;  
            } 
        }   
    }
    return d[n];
}

int 
main(void) {

    cin >> n >> m;
    memset(h, -1, sizeof h);

    while(m --) {
        int a, b;
        cin >> a >> b;
        add(a, b); 
    }

    cout << bfs() << endl;
    return 0;
}
