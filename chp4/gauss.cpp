#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std; const int N = 110;
const double eps = 1e-6;
double a[N][N];
int n;

/*
    高斯消元法 
*/
int gauss() {

    int r, c;
    for(r = 0, c = 0; c < n; c ++) {
        //c列  最大值
        int t = r;
        for(int i = r; i < n + 1; i ++) 
            if(fabs(a[i][c]) > fabs(a[t][c]))  t = i;

        if(fabs(a[t][c]) < eps) continue;

        //换到第一行 列是n + 1列！！
        for(int i = c; i < n + 1; i++) swap(a[r][i], a[t][i]);
        //第一个值赋值1
        for(int i = n; i >= c; i --) a[r][i] /= a[r][c];

        //清零
        for(int i = r + 1;  i < n; i ++)
            if(fabs(a[i][c]) > eps)
                for(int j = n; j >= c; j --) 
                    a[i][j] -= a[r][j] * a[i][c];
        r ++; 
    }

    if(r < n) {
        for(int i = r; i < n; i ++) 
            if(fabs(a[i][n])) return 2;
        return 1;
    }

    for(int i = n - 1; i >= 0; i --)
        for(int j = i + 1; j < n; j ++)
            a[i][n] -= a[j][n] * a[i][j];

    return 0;
}


int 
main(void) {

    cin >> n;
    for(int i = 0; i < n; i++) 
        for(int j = 0; j <  n + 1; j ++)
            cin >> a[i][j];

    int t = gauss();

    if(t == 0) {
        for(int i = 0;  i < n; i ++) printf("%.2lf\n", a[i][n]); 
    }else if(t == 1) cout << "Infinite group solutions" << endl;
    else cout << "No solution" << endl;

    return 0;
}
