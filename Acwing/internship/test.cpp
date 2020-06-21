#include <iostream>
#include <algorithm>
#include <cstring>


using namespace std;
const int N = 100010;
int a[N], tmp[N];
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


void mergeSort(int q[], int l, int r) {

    if(l >= r) return;


    int mid = (l + r)  >> 1;
    mergeSort(q, l, mid);
    mergeSort(q, mid + 1, r);

    int i = l, j = mid + 1, k = 0;
    while(i <= mid &&  j <= r) {
        if(q[i] < q[j])  tmp[k++] = q[i++];
        else tmp[k++] = q[j++];
    }

    while(i <= mid) tmp[k++] = q[i++];
    while(j <= r) tmp[k++] = q[j++];

    for(int i = l, j = 0; i <= r; i++, j++) a[i] = tmp[j];

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

    //quickSort(a, 0, n - 1);
    mergeSort(a, 0, n - 1);

    while(x --) {
        int res;
        cin >> res;

        if(find(a, res)) cout << "YES"  << endl;
        else cout << "NO" << endl;
    }
   
    return 0;
}
