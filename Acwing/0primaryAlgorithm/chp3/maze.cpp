#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 110;
int g[N][N];
int d[N][N];
int n, m;

//用来存储坐标的队列
typedef  pair<int, int> PII;
PII q[N];
int hh , tt;
int bfs(){

    q[0] = make_pair(0, 0);
    memset(d, -1, sizeof d); 
    d[0][0] = 0;

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    while(hh <= tt) {
        auto t = q[hh ++]; 
        for(int i = 0; i < 4; i ++) {
            int x = t.first + dx[i], y = t.second + dy[i];
            if(x>=0 && x<n && y>=0 && y<m && g[x][y]==0 && d[x][y]==-1) {
                d[x][y] = d[t.first][t.second] + 1;
                q[++ tt] = make_pair(x, y);
            }
        }
    }

    return d[n-1][m-1];
}

int 
main(void) {

    cin >> n >> m;
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < m ;j++)
            cin >> g[i][j];

    cout <<  bfs() << endl;

    return 0;
}
