#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 510, INF = 1e9 + 7;
int f[N][N], a[N][N];
int n;


//从底部到顶部的一种优化
void down2up() {

    cin >> n ;

    for(int i = 1; i <= n; i++)
            for(int j = 1; j <= i; j ++)
                    cin >> a[i][j];

    for(int i = n- 1; i >= 1; i --)
        for(int j = 1; j <= i; j ++)
            a[i][j] = max(a[i+1][j] + a[i][j], a[i+1][j+1] + a[i][j]);

    cout << a[1][1] << endl;

}

void
up2down(void) {

    cin >> n;
    for(int i = 1; i<= n; i ++) 
        for(int j = 1; j <= i; j ++)
                cin >> a[i][j];

    for(int i = 0; i<= n; i ++)
        for(int j = 0; j <= i + 1; j ++)
            f[i][j]  = -INF;

    f[1][1] = a[1][1];
    for(int i = 2; i<=n; i ++)
        for(int j = 1; j <= i; j ++) 
            f[i][j] = max(f[i-1][j-1] + a[i][j], f[i-1][j] + a[i][j]);



    int res = -INF;
    for(int i = 1; i<= n; i ++)
        res = max(res, f[n][i]);

    cout << res << endl;
}


int 
main(void) {


    return 0;
}
