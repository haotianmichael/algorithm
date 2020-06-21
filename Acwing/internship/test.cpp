#include <iostream>
#include <algorithm>
#include <cstring>


using namespace std;
const int N = 100010;
int a[N];
int n, x;


void quickSort(int q[], int l, int r) {

    if(l >= r) return;

    int x = q[l], i = l - 1, j = r + 1;
    while(i < j){
        do i ++; while(a[i] < x); 
        do j --; while(a[j] > x);
        if(i < j) swap(a[i], a[j]);
    }

    quickSort(q, l, j);
    quickSort(a, j + 1, r);
}


bool find(int *q, int res) {

    int size = 0;
    while(q[size++]) ;

    int l = 0, r =  size - 1;
    while(l < r) {
        int mid = (l + r) >> 1; 
        if(q[mid] >= res)  r = mid;
        else l = mid + 1;
    } 

    if(a[l] != res) return false;
    else return true;

}


int main(void)
{
    cin >> n >> x;
    for(int i = 0; i < n; i++) cin >> a[i];

    quickSort(a, 0, n - 1);

    while(x --) {
        int res;
        cin >> res;

        if(find(a, res)) cout << "YES"  << endl;
        else cout << "NO" << endl;
    }
   
    return 0;
}
