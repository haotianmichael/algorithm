#include <iostream>
#include <algorithm>
#include <cstring>


using namespace std;

const int N = 10010;
int a[N], n;
int tmp[N];

void quickSort(int a[], int l, int r) {

    if(l >=r ) return;

    int x = a[l], i = l - 1, j = r + 1;


    while(i < j) {
        do i++; while(a[i] < x); 
        do j--; while(a[j] > x);
        if(i < j) swap(a[i] , a[j]);
    }
    quickSort(a, l, j);
    quickSort(a, j + 1, r);

}

void mergeSort(int a[], int l, int r) {

    if(l >= r) return;

    int mid = ( l + r) >> 1;
    mergeSort(a, l, mid);
    mergeSort(a, mid + 1, r);
    int i = l, j = mid + 1;

   int k = 0;
    while(i <= mid && j <= r) {
        if(a[i] < a[j])  tmp[k++] = a[i++];
        else tmp[k++] = a[j++];
    }


    while(i <= mid) tmp[k++] = a[i++];
    while(j <= r) tmp[k++] = a[j++];

    for(int i = l, j = 0; i <= r; i ++, j ++) a[i] = tmp[j];
}

int main(void)
{
    cin >> n;
    for(int i =0 ;i < n; i ++) cin >> a[i]; 
    //quickSort(a, 0, n - 1);
    mergeSort(a, 0, n - 1);

    for(int i =0 ; i < n; i ++) cout << a[i] << ' '; 
    return 0;
}
