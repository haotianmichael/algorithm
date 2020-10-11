#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

/*
 
   快速排序
   归并排序
   二分法
*/

const int N = 100010;
int a[N], n;
int tmp[N];

void quickSort(int a[], int l, int r) {

    if(l >= r) return;

    int x = a[(l + r) >> 1], i = l - 1, j = r + 1;

    while(i < j) {
        do i ++; while(a[i] < x) ;
        do j --; while(a[j] > x);
        if(i < j) swap(a[i] , a[j]); 
    }

    quickSort(a, l, j);
    quickSort(a, j + 1, r);
}

void mergeSort(int a[], int l, int r) {

    if(l >= r) return;

    int mid = (l + r) >> 1; 
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


/*
 
     给出一列数，判断其上下界
 
*/
int x;
void bSearch() {
    int lhs, rhs;
    cin >> n >> x;
    for(int i = 0; i < n; i ++) cin >> a[i]; 
    //左边界
    lhs = 0, rhs = n - 1;
    while(lhs < rhs) {
        int mid = (lhs + rhs) >> 1; 
        if(a[mid] == x) rhs = mid;
        else lhs = mid  + 1;
    }
 

    //右边界   
    if(lhs < rhs) {
        cout << "-1, -1" << endl;
    }else {
        cout << lhs << " ";
        lhs = 0, rhs = n - 1; 
        while(lhs < rhs) {
            int mid  = (lhs + rhs + 1) >> 1; 
            if(a[mid] == x) lhs = mid;
            else rhs = mid - 1;
        } 
        cout << lhs << endl;
    }

}



int mysort(void)
{
    cin >> n;
    for(int i = 0; i < n; i ++)  cin  >> a[i]; 
    //quickSort(a, 0, n - 1);
    mergeSort(a, 0, n - 1);
    for(int i = 0; i < n; i ++) cout << a[i] <<  ' '; 
    return 0;
}


int main(void)
{
    bSearch();
    return 0;
}
