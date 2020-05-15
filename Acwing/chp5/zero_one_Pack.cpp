#include <iostream>
#include <algorithm>

using  namespace std;
const int N = 1010;
int v[N], w[N];
int f[N][N];
int n, m;
int ff[N];

//滚动数组优化版本
int oneD_main(void) {

    cin >> n >> m;
    for(int i = 1; i<= n; i ++) cin >> v[i] >> w[i];

    for(int i = 1; i <= n; i ++)
        for(int j = 0; j <= m; j ++)
            ff[j] = max(ff[j], ff[j-v[i]] + w[i]);

    cout << ff[m] << endl;
    return 0;
}

//朴素版本
int 
twoD_main(void) {

    cin >> n >> m;
    for(int i = 1;i <= n; i++) cin >> v[i] >> w[i];

    for(int i = 1; i<= n; i ++)
        for(int j = 0;  j <= m; j ++){
            f[i][j] = f[i-1][j];
            if(j >= v[i]) f[i][j] = max(f[i-1][j], f[i-1][j-v[i]] + w[i]); 
        }

    cout << f[n][m] << endl;
    return 0;
}



int 
main(void) {

    oneD_main();
    twoD_main();  

    return 0;
}
