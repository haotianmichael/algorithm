#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>
#include <stack>


using namespace std;


const int N = 100010;
const int M = 1010;
int a[N];


/*==========*/
void quickSort(int l, int r) {

    if(l >= r) return;

    int x = a[l], i = l - 1, j = r + 1;
    while(i < j) {
        do i ++; while(a[i] < x); 
        do j --; while(a[j] > x); 
        if(i < j) swap(a[i], a[j]);
    }

    quickSort(l, j);
    quickSort(j + 1, r);
}

int tmp[N];
void mergeSort(int l, int r) {
    
    if(l >= r) return;
    int mid = (l + r) >> 1;
    mergeSort(l, mid);
    mergeSort(mid + 1, r);

    int i = l, j = mid + 1, k = 0;
    while(i <= mid && j <+ r) 
        if(a[i] < a[j])   tmp[j++] = a[i++];
        else tmp[i++] = a[k++]; 
    
    while(i <= mid) tmp[k++] = a[i++];
    while(j <= mid) tmp[k++] = a[j++];


    for(int i = l, j = 0; i <= k; i ++, j ++) a[i] = tmp[j];
}

void testSort() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i ++) cin >> a[i]; 
    quickSort(0, n - 1);
    for(int i = 0; i < n; i ++) cout << a[i] << ' ';
    puts("");
}


/*==============================*/
void binary() {

    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++) cin >> a[i]; 
    int lhs = 0, rhs = n - 1;     
    while(lhs <= rhs) {
        int mid = (rhs + lhs) >> 1;  
        if(a[mid] >= m) rhs = mid;
        else  lhs = mid + 1; 
    } 

    if(lhs > rhs) {
        cout << "-1 -1" << endl; 
    }else {
        cout << lhs << " ";  
        int lsh = 0, rhs =  n - 1; 
        while(lsh <= rhs) {
            int mid = (rhs + lhs + 1) >> 1; 
            if(a[mid] <= m) lhs = mid; 
            else rhs = mid - 1;
        }
        cout << rhs << endl;
    }

    return;
}

void testBinary() {
    binary();
}


/*===============================*/
vector<int> add(vector<int> &A, vector<int> &B) {
    vector<int> C;
    int res = 0;
    for(unsigned i = 0; i < A.size() ||  i < B.size() || res; i ++) {
        if(i < A.size())  res += A[i];
        if(i < B.size())  res += B[i];
        C.push_back(res % 10); 
        res /= 10;
    }

    return C;
}

bool cmp(vector<int> &A, vector<int> &B) {
    /*
        @return true if A == B  
    */
    if(A.size() != B.size())
        return (A.size() > B.size());
    else {
        //start from top          
        for(int i = A.size(); i >= 0; i --) {
            if(A[i] != B[i]) 
                return (A[i] > B[i]);
        } 
    }

    return true;
}

vector<int> sub(vector<int> &A, vector<int> &B) {

    vector<int> C;
    int res = 0;
    for(unsigned i = 0; i < A.size(); i ++)  {
        res = A[i] + res; 
        res -= B[i]; 
        C.push_back((res + 10) % 10);
        if(res >= 0) res = 0;
        else res = -1;
    }

    while(C.size() > 1 && ! C.back()) C.pop_back();
    return C;
}

vector<int> mul(vector<int> &A, int b) {
    int res = 0;
    vector<int> C;
    for(unsigned i = 0; i < A.size(); i ++)  {
        res += A[i] * b; 
        C.push_back(res % 10);
        res /= 10;
    }

    return C;
}

vector<int> div(vector<int> &A, int b, int &r) {

    int res = 0;
    vector<int> C;
    for(int i = A.size() - 1; i >= 0; i --) {
        res = res * 10 + A[i];  
        C.push_back(res / b); 
        res %= b;
    } 
    reverse(C.begin(), C.end());
    while(C.size() > 1 && !C.back()) C.pop_back();
    if(!res) r = res;
    return C;
}

void testHigh() {
    string a, b;
    cin >> a >> b;
    vector<int> A, B;
    for(int i = a.size() - 1; i >= 0; i --)  A.push_back(a[i] - '0');
    for(int j = b.size() - 1; j >= 0; j --) B.push_back(b[j] - '0'); 

    auto C = add(A, B);
    //auto C = sub(A, B);
    //auto C = mul(A, b);
    //auto C = div(A, b, r);
    for(int k = C.size() - 1; k >= 0; k --) cout << C[k];
    puts("");
}


/*====================================*/
void preSum() {
    int s[N];  //前缀和数组
    int n;
    cin >> n;
    for(int i = 1; i <= n; i ++) cin >> a[i]; 
    for(int j = 1; j <= n; j ++)   s[j] = s[j-1] + a[j];

    int q, l, r;
    cin >> q;
    while(q --) {
        cin >> l >> r;
        cout << s[r] - s[l-1] << endl;
    }
}

void preMatrix() {
    int ma[M][M];
    int ms[M][M];    

    //求子矩阵的和
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i ++)  
        for(int j = 1; j <= m; j ++) 
            cin >> ma[i][j];
    

    //构造前缀和矩阵
    for(int i = 1; i <= n; i++)
       for(int j = 1; j <= m; j ++)  
           s[i][j] = s[]
            

}

void difference() {



}


void differenceMatrix() {

}


/*=====================================*/
void duplicate(string s) {
    
    string res = "";
    for(unsigned i = 1; i < s.size(); i ++) {
        if(s[i - 1] != s[i]) res += s[i];
    }
    cout << res << endl;
}

void word(string s) {
    
    string word = "";
    unsigned i = 0;
    while(i < s.size()) {
        unsigned j = i;
        while(j < s.size() && s[j] != ' ') {
            word += s[j++];
        }       
        cout << word << endl;
        while(s[j] == ' ') j++;
        i = j;
        word  = "";
    } 
}


/*=====================================*/
int lowbit(int ans) {
    int num = 0;
    while(ans) {
        ans -= ans & (~ans + 1);  
        num ++;
    }
    return num;
}


int main(void)
{
    
    word("haotian is a good man");
    return 0;
}

