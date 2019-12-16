/*
   并查集在存储的过程中可以维护一些信息 来处理问题 
   到根节点的距离dist[]:
   mod 0: 和根节点是同类
   mod 1: 可以吃根节点
   mod 2: 可以被根节点吃
*/
#include <iostream>
#include <algorithm>

using namespace std;
const int N = 50010;
int p[N], dist[N];
int n, k;

int find(int x) {
    if(x != p[x]) {
        int t = find(p[x]); 
        dist[x] += dist[p[x]];
        p[x] = t;
    }
    return p[x];
}

int main(void) {

    int n, m;
    cin >> n >> m;
    for(int  i = 1; i<= n; i++) p[i] = i;

    int res = 0;
    while (m --) {
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y);        

        if(x > n || y > n) res ++;
        else {
            int px = find(x) , py = find(y); 
            if(op == 1) {
                if (px == py && (dist[x] - dist[y]) % 3) res ++;
                else if(px != py){
                    p[px] = py;
                    dist[px] = dist[y] - dist[x];                
                }
            }else {
                if (px == py && (dist[x] - dist[y] - 1) % 3) res ++;
                else if(px != py){
                    p[px] = py;
                    dist[px] = dist[y] + 1 - dist[x];     
                } 
            }
        }
    }
    cout << res << endl;
    return 0;
}

