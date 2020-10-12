#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

const int N = 100010;
int a[N], n;
int tmp[N];


/*
    排序算法 
*/
void mergeSort(int l, int r) {
    if(l >= r) return;
    int mid = (l + r) >> 1;

    mergeSort(l, mid);
    mergeSort(mid + 1, r);

    int i = l, j = mid + 1;
    int k = 0;
    while(i <= mid && j <= r) {
        if(a[i] < a[j]) tmp[k++] = a[i++];
        else tmp[k++] = a[j++];
    }
    while(i <= mid) tmp[k++] = a[i++];
    while(j <= r) tmp[k++] = a[j++];

    for(int i = l, j = 0; i <= r; i ++, j ++)  a[i] = tmp[j];

}
void quickSort(int l, int r) {

    if(l >= r) return;

    int x = a[l], i = l - 1, j = r + 1;
    while(i < j) {
        do i++;while(a[i] < x); 
        do j--;while(a[j] > x);
        if(i < j) swap(a[i], a[j]); 
    }

    quickSort(l,  j);
    quickSort(j + 1, r);
}
void mysort() {

    cin >> n;
    for(int i = 0; i < n; i ++) cin >> a[i];
    //quickSort(0, n - 1);
    mergeSort(0, n - 1);
    for(int i = 0; i < n; i ++) cout << a[i] <<  ' ';
}

void bSearch() {

    int n, x;
    cin >> n >> x;

    for(int i = 0; i < n; i ++) cin >> a[i]; 
    int l = 0, r =  n - 1;
    while(l < r){
        int mid = (l + r) >> 1; 
        if(a[mid] >= x) r = mid; 
        else l = mid + 1;
    }

    if(l < r) {
        cout << "-1, -1" << endl; 
    }else {
        cout << l << " ";  
        l = 0, r = n - 1;
        while(l < r) {
            int mid = (l + r + 1) >> 1; 
            if(a[mid] <= x) l = mid;
            else r = mid - 1;
        } 
        cout << l << endl;
    }

    return;

}
void b2() {

    double x;
    cin >> x;
    double mid;
    double l = -1000, r = 1000;
    while((r - l) >= 1e-8) {
        mid = (l + r) / 2; 
        if(mid * mid >= x) l = mid;
        else r = mid;
    }
    printf("%lf.6", mid);

}


vector<int> add(vector<int> &A, vector<int> &B) {

    int res = 0;
    vector<int> C;
    for(unsigned int i = 0; i < A.size() || i < B.size() || res; i ++)  {
        if(i < A.size()) res += A[i];
        if(i < B.size()) res += B[i];
        C.push_back(res % 10);
        res /= 10;
    }

    return C;
}



int main(void)
{
    //mysort();
    //bSearch();
    //b2();

    string a, b;
    cin >> a >> b;
    vector<int> A, B;
    for(int i = a.size()  - 1; i >= 0; i --) A.push_back(a[i] - '0'); 
    for(int i = b.size() - 1; i >= 0; i --)  B.push_back(b[i]  - '0');


    auto C = add(A, B);
    for(int i = C.size() - 1; i >= 0; i --) cout << C[i];
    puts("");
    
    return 0;
}
