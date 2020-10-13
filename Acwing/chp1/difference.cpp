#include <iostream>
using namespace std;

/*
 *  前缀和和差分是一对逆运算 
 *  理解两者的联系和区别
*/
const int N = 1e6 + 10;
int a[N], b[N];
int c[N][N], s[N][N];

//线性前缀和
int preSum() {

    int n, m;
    cin >> n >> m;
    int q[N], sum[N];
    for(int i = 1; i <= n; i ++) cin >> q[i];
    for(int i = 1; i <= n; i ++) sum[i] = sum[i-1] + q[i];
    
    while(m --) {
        int l, r;
        cin >> l >> r;
        cout << sum[r] -  sum[l - 1] << endl; 
    }
    return 0;
}


//矩阵前缀和
int preSumMatrix() {

    int a[N][N], b[N][N];
    int n, m, q;
    cin >> n >> m >> q;
    for(int i = 1; i <= n; i ++) 
        for(int j = 1; j <= m; j ++)
            cin >> a[i][j];

    //求前缀和
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++)
            b[i][j] = b[i-1][j] + b[i][j-1] - b[i-1][j-1] + a[i][j];

    while(q --) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int res = b[x2][y2] - b[x2][y1 - 1] - b[x1 - 1][y2] + b[x1 - 1][y1 - 1];   
        cout << res << endl; 
    } 

    return 0;
}


void insert_OneD(int l, int r, int c) {
    b[l] += c;
    b[r + 1] -= c;
    return ;
}

//一维差分数组
int 
testOneD_main(void) {

    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = 1; i <= n; i++) insert_OneD(i, i, a[i]);

    while(m --) {
        int l, r, c;
        scanf("%d%d%d", &l, &r, &c); 
        insert_OneD(l, r, c);
    }

    for(int i = 1; i <= n; i ++) b[i] += b[i-1];
    for(int i = 1; i <= n; i ++) printf("%d ", b[i]);

    cout << endl;
    return 0;
}


void insert_Matrix(int x1, int y1, int x2, int y2, int c) {

    s[x1][y1] += c;
    s[x2 + 1][y1] -= c;
    s[x1][y2 + 1] -= c;
    s[x2 + 1][y2 + 1] += c;    
    return ;
}


//二维差分数组
int 
Matrix_main(void) {

    int n, m, q;
    scanf("%d%d%d", &n, &m, &q); 
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++)
            scanf("%d", &c[i][j]);

    //求差分数组
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++)
            insert_Matrix(i, j, i, j, c[i][j]);

    while(q --) {

        int x1, y1, x2, y2, c;
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &c);
        insert_Matrix(x1, y1, x2, y2, c); 
    }

    
    //这里是利用s来存储前缀和数组  而不是直接求该数组的前缀和数组 注意区别
    // b[i] += b[i+1] 
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++)
            s[i][j] += s[i-1][j] + s[i][j-1] - s[i-1][j-1];  

    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++) printf("%d", s[i][j]);
        cout << endl;
    }
    return 0;
}
