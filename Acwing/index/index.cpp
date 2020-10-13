#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>


using namespace std;

/*
    高精度
*/
vector<int> add(vector<int> &A, vector<int> &B) {

    int res = 0;
    vector<int> C;
    for(unsigned int i = 0; i < A.size() || i < B.size() || res; i ++)  {
        if(i < A.size())  res += A[i];
        if(i < B.size())  res += B[i];
        C.push_back(res % 10);
        res /= 10;
    }

    return C;
}
bool cmp(vector<int> &A, vector<int> &B) {
    if(A.size() != B.size()) {
        return (A.size() > B.size()); 
    }else {
        for(int i = A.size() - 1; i >= 0; i --){
            if(A[i] != B[i]) {
                return (A[i] > B[i]); 
            } 
        }
    }

    return true;
}
vector<int> sub(vector<int> &A, vector<int> &B) {

    int res  = 0;
    vector<int> C;
    for(unsigned int i = 0; i < A.size(); i ++)  {
        res = A[i] - res; 
        res -= B[i];
        C.push_back((res + 10) % 10);
        if(!res) res = 1;
        else res = 0;
    }
    while(C.size() > 1 && !C.back()) C.pop_back();

    return C;
}
vector<int> mul(vector<int> &A, int b) {

    int res = 0;
    vector<int> C;
    for(unsigned int i = 0; i < A.size(); i ++)  {
        res += A[i] * b; 
        C.push_back(res % 10); 
        res /= 10; 
    }
    return C;
}
vector<int> div(vector<int> &A, int b, int &r) {

    vector<int> C;
    for(int i = A.size() - 1; i >= 0; i --)  {
        r = r * 10 + A[i];
        C.push_back(r / b);
        r %= 10;
    } 
    while(C.size() > 1 && !C.back()) C.pop_back();

    return C;
}

/*
    前缀和/差分 
*/
const int N  = 100010;
const int M = 1010;
int a[M][M], b[M][M];
void preSum(){
    int a[N], s[N];
    int n;
    cin >> n;
    for(int i = 1; i <= n; i ++)cin >> a[i];

    
    //构建前缀和
    for(int i = 1; i <= n; i ++) s[i] = s[i-1] + a[i]; 
    
    int q;
    cin >> q;
    while(q --) {
        int l, r;
        cin >> l >> r;
        cout << s[r] - s[l-1] << endl;            
    }
    return;
}

void preMatrixSum() {

    int n, m;
    cin >> n >> m;
    for(int i= 1; i <= n; i ++)  
        for(int j = 1; j <=m; j ++) 
            cin >> a[i][j];


    //构造前缀和
    for(int i = 1; i <= n; i ++) 
        for(int j = 1; j <= m; j ++) 
            b[i][j] = b[i-1][j] + b[i][j-1] - b[i-1][j-1] + a[i][j];

    int q;
    cin >> q;
    while(q --) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int res = b[x2][y2] - b[x2][y1 - 1] - b[x1 - 1][y2] + b[x1 - 1][y1 - 1]; 
        cout << res << endl;
    }

    return;
}


int c[N], d[N];
void insert(int l, int r, int c) {

    d[l] += c;
    d[r + 1] -= c;
    return; 
}

void difference() {

    int n;
    cin >> n;
    for(int i = 1; i <= n; i ++)  cin >> c[i];

    //构造差分数组
    for(int i = 1; i <= n; i ++) insert(i, i, c[i]); 

    int q;
    cin >> q;
    while(q --) {
        int l, r, c;
        cin >> l >> r >> c;
        insert(l, r, c); 
    }

    //求差分数组的前缀和
    for(int i = 1; i <= n; i ++) {
        /*
            这样写是完全没有理解前缀和和差分的区别
            c是d的前缀和，d是c的差分   
        */
        //d[i] = d[i-1] + c[i]; 
        d[i] += d[i-1];
        cout << d[i];
    } 
    puts("");

    return;
}

void insertMatric(int x1, int y1, int x2, int y2, int c) {
    
    b[x1][y1] += c;
    b[x2+1][y1] -= c;
    b[x1][y2+1] -= c;
    b[x2+1][y2+1] += c;
}


void diffMatrix() {
    
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) 
        for(int j = 1; j <= m; j ++) 
            cin >> a[i][j];


    //构造差分数组
    for(int i = 1; i <= n; i ++) 
        for(int j = 1; j <= m; j ++) 
            insertMatric(i, j, i, j, a[i][j]);

    int q;
    cin >> q;
    while(q --) {
        int x1, y1, x2, y2, c;
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        insertMatric(x1, y1, x2, y2, c);
    } 

    for(int i = 1 ;i <= n; i ++)
       for(int j = 1; j <= m; j ++)  {
           b[i][j] += b[i-1][j] + b[i][j-1] - b[i-1][j-1];
           cout << b[i][j] << endl;  
       }
}


int main(void)
{
    string a, b;
    cin >> a >> b;
    vector<int> A, B;
    for(int i = a.size() - 1;i >= 0; i --) A.push_back(a[i] - '0');
    for(int i = b.size() - 1;i >= 0; i --) B.push_back(b[i] - '0');


    auto C = add(A, B);


    for(int i = C.size() - 1; i >= 0; i --) cout << C[i];
    puts("");
    return 0;
}

