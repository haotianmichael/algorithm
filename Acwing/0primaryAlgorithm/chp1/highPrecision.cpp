#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> add(vector<int> &A, vector<int> &B) {

    vector<int> C;
    int t = 0;
    for(unsigned int i = 0; i < A.size() || i < B.size(); i++) {
        if(i < A.size()) t += A[i];
        if(i < B.size()) t += B[i];
        C.push_back(t % 10); 
        t /= 10;
    }
    if(t) C.push_back(t);
    return C;
}

bool cmp(vector<int> &A, vector<int> &B) {

    if(A.size() != B.size()) return (A.size() > B.size());
    for(unsigned int i = A.size() - 1; i >= 0; i--)
        if(A[i] != B[i])
            return(A[i] > B[i]);

    return true;
}

vector<int> sub(vector<int> &A, vector<int> &B) {
    vector<int> C;
    for(unsigned int i = 0, t = 0; i < A.size(); i++) {
        t = A[i] - t;
        if(i < B.size()) t -= B[i];  
        C.push_back((t + 10) % 10);
        if(t >= 0) t = 0;
        else t = 1;
    }
    while(C.size() > 1 && C.back() == 0) C.pop_back();  
    return C;
}

vector<int> mul(vector<int> &A, int b) {
    vector<int> C;
    int t = 0;
    for(unsigned int i = 0; i < A.size() || t; i++) {
        t +=  b * A[i];
        C.push_back(t % 10); 
        t /= 10;
    }

    return C;
}

vector<int> div(vector<int> &A, int b, int &r) {
        vector<int> C;
        for(int i = A.size(); i >= 0; i--) {
            r = r * 10 + A[i];
            C.push_back(r / b); 
            r %= b;
        }
        reverse(C.begin(), C.end());
        while(C.size() > 1 && C.back() == 0) C.pop_back();
        return C;
}



int main(void) {

    string a, b;
    int c;
    //cin >> a >> b;
    cin >> a >> c;
    vector<int> A, B;
    for(int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');
    for(int i = b.size() - 1;  i >= 0; i--) B.push_back(b[i] - '0');
    //auto  C = add(A, B);


    /*if(cmp(A, B)) {*/
        //auto C = sub(A, B); 
        //for(int i = C.size() - 1; i >= 0; i--) printf("%d", C[i]);
    //}else {
        //cout << "-"; 
        //auto C  = sub(B, A); 
        //for(int i = C.size() - 1; i >= 0; i--) printf("%d", C[i]);
    /*}*/

    //auto C = mul(A, c);
    int r = 0;
    auto C = div(A, c, r);
    for(int i = C.size() - 1; i >= 0; i--) printf("%d", C[i]);
    cout << endl;
    cout << r << endl;

    return 0;

}
