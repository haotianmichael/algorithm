#include <iostream>
#include <cstring>
#include <algorithm>

//可以尝试使用邻接表 来实现以下朴素版本的Dijkstra
using namespace std;
const int N = 510;
int n, m;
int g[N][N];   //邻接矩阵
int dist[N];   //最短距离
bool st[N];   //是否已经被收录



//注意理解Dijkstra算法的精髓：若路径是按照递增的顺序生成的，那真正的最短路一定只经过S中的顶点
int dijkstra() {

    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;


    for(int i = 0; i < n; i ++) {
        int t = -1;
        //未收录（！st[i]）定点中距离最小的定点
        for(int j = 1;  j <= n; j ++) 
            if(!st[j] && (t==-1 || dist[j]<dist[t]))   t = j;
    
        st[t] = true;    //至少被处理n次
    
        for(int j = 1; j <= n; j ++)    //用找到的最小值 更新周边的所有定点
            dist[j] = min(dist[j], dist[t] + g[t][j]);    //邻接矩阵中g[t][j]已经表示从t指向j的边，所以没有的便是无穷大   所以就是按照临边
    }
    
    if(dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}



int 
main(void) {

    scanf("%d%d", &n, &m);
    memset(g, 0x3f, sizeof g);
    
    while(m --) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c); 
        g[a][b] = min(g[a][b], c); 
    }

    
    int t = dijkstra();

    cout << t << endl;

    return 0;
}
