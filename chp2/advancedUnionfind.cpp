/*
   并查集在存储的过程中可以维护一些信息 来处理问题 
 */
#include <iostream>
#include <algorithm>

using namespace std;
const int N = 50010;
int p[N], dist[N];
int n, k;

int find(int x) {
    if(p[x] != x) {
        int u = find(p[x]);
        dist[x] += dist[p[x]]; 
        p[x] = u;
    }
    return p[x];
}

int main(void)
{
    cin >> n >> k;
    for(int i = 1; i <= n; ++i) p[i] = i; 

    int res = 0;
    while (k --) {

        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        if(l > n || r > n) res ++;  
        else {

            int pl = find(l), pr = find(r);
            if (op == 1) {

                if(pl == pr && (dist[l] - dist[r])%3) res ++;
                else if(pl != pr) {
                    p[pl] = pr; 
                    dist[pl] = dist[r] - dist[l];
                }
            }else {
                if(pl == pr && (dist[l] - dist[r] - 1)%3)  res ++; 
                else if(pl != pr){
                    p[pl] = pr;
                    dist[pl] = dist[r]  + 1 - dist[l];
                }
            }
        }

    }
    cout << res << endl;
    return 0;
}

