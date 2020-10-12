#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
const int N = 100010;
int a[N];

void bSearch() {

    int x, n;
    cin >> n >> x;
    int lhs, rhs;

        //左边界
    lhs = 0, rhs = n - 1;
    while(lhs < rhs) {
        int mid  = (lhs + rhs) >> 1; 
        if(a[mid] >= x) rhs = mid;
        else lhs = mid + 1; 
    }

    if(lhs < rhs) {
        cout << "-1, -1" << endl; 
    }else {
        //右边界
        cout << lhs << " ";
        lhs  = 0, rhs =  n - 1;
        while(lhs < rhs) {
            int mid = (lhs  + rhs + 1) >> 1; 
            if(a[mid] <= x)  lhs = mid;
            else rhs = mid - 1; 
        }
        cout << rhs << endl; 
    }


}

//高精度add
vector<int> add(vector<int> &A, vector<int> &B) {
    int res = 0;
    vector<int> C;
    unsigned int i = 0;
    for(;i < A.size() || i < B.size() || res; i ++){
        if(i < A.size())  res += A[i];
        if(i < B.size())  res += B[i];
        C.push_back(res % 10);
        res /= 10;
    }

    return C;
}

vector<int> sub(vector<int> &A, vector<int> &B) {
    int res = 0;
    vector<int> C;

    return C;
}



int main(void)
{
    string a,b;
    cin >> a >> b;
    vector<int> A, B;
    for(int i = a.size() - 1; i >= 0; i --)   A.push_back(a[i] - '0');
    for(int i = b.size() - 1; i >= 0; i --)   B.push_back(b[i] - '0'); 
    //auto C = add(A, B);
    auto C = sub(A, B);
    for(int i = C.size() - 1; i >= 0; i --) cout << C[i];  
    puts("");
    return 0;
}
