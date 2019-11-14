#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const int N = 100010;
int e[N], ne[N], h[N], w[N], idx;
int dist[N], cnt[N];
int n, m;
bool st[N];


void add(int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}



bool spfa() {

    queue<int> q;
    for(int i = 1; i <= n; i ++) {
        st[i] = true;
        q.push(i); 
    }

    while(q.size()) {
        int t = q.front();
        q.pop();
        st[t] = false;

        for(int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if(dist[j] > dist[t]+w[i]) {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1; 
                if(cnt[j] >= n) return true;
                if(!st[j]) {
                    st[j] = true;
                    q.push(j);
                } 
            } 
        } 
    }
    return false;
}


int 
main(void) {

    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m --) {
        int a, b, c;
        cin >>a >> b >> c;
        add(a, b, c); 
    }
    if(spfa()) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}
