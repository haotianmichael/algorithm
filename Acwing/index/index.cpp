#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

vector<int> add(vector<int> &A, vector<int> &B) {

    int res = 0;
    vector<int> C;
    for(unsigned int i = 0; i < A.size() || i < B.size() || res; i++)   {
        if(i < A.size())  res += A[i];
        if(i < B.size())  res += B[i]; 
        C.push_back(res % 10); 
        res /= 10;
    }

    return C;
}


vector<int> sub(vector<int> &A, vector<int> &B) {

    vector<int> C;
    int res = 0;
    for(unsigned int i = 0; i < A.size(); i ++)  {
        res = A[i] - res;        
        res -= B[i];
        C.push_back((res + 10) % 10);
        if(res < 0) res = 1;
        else res = 0;
    }
    while(C.size() && !C.back()) C.pop_back(); //去掉前导零，需要留一位

    return C;
}

bool cmp(const vector<int> &A, const vector<int> &B) {

    if(A.size() != B.size()) return (A.size() > B.size());
    for(int i = A.size() - 1; i >= 0; i --) {
        if(A[i] != B[i]) {
            return (A[i] > B[i]); 
        } 
    }    
    return true; //equal
}

vector<int>  mul(vector<int> &A, int b) {

    vector<int> C;
    int res = 0;
    for(unsigned int i = 0; i < A.size() || res; i ++)  {
        if(i < A.size())  res += A[i] * b;
        C.push_back(res % 10);
        res /= 10;
    }

    return C;
}

vector<int> div(vector<int> &A, int b, int &res) {

    vector<int> C;
    for(int i = A.size() - 1; i >= 0; i --)  {
        res = res * 10 + A[i];   
        C.push_back(res / b);           
        res %= b;
    }    
    reverse(C.begin(), C.end());
    while(C.size() > 1 && !C.back()) C.pop_back();
    return C;
}

double _sqare() {
    double x;
    cin >> x;
    double lhs = -1000, rhs = 1000;
    while((rhs - lhs) > 1e-8) {
        double mid = (rhs  + lhs) / 2; 
        if(mid * mid >= x) rhs = mid;
        else lhs = mid;
    }

    cout << lhs << endl;
    return lhs;
}


int main(void)
{
    _sqare();
    return 0;
    string a, b;
    int c;
    //cin >> a >> b;
    cin >> a >> c;
    vector<int> A, B;
    for(int i = a.size() - 1; i >= 0; i --) A.push_back(a[i] - '0'); 
    //for(int i = b.size() - 1; i >= 0; i --) B.push_back(b[i] - '0');  
    //auto C = add(A, B);
    //auto C = mul(A, b);
    int res = 0;
    auto C = div(A, c, res); 
    for(unsigned int i = 0; i < C.size(); i++) cout << C[i]; 
    puts("");
    cout << "remainder is: " << res << endl;
    return 0;
    /*
        @true 
        @false  cout << "-";
    */
    if(!cmp(A, B)){
        auto C = sub(B, A);
        cout << "-"; 
        for(int i = C.size() - 1; i >= 0; i --) cout << C[i]; 
    }else {
        auto C = sub(A, B); 
        for(int i = C.size() - 1; i >= 0; i --) cout << C[i]; 
    }
    puts("");
    return 0;
}
