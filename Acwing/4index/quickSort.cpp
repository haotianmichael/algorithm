#include <iostream>


using namespace std;
const int N = 100010;
int a[N], n;

void quickSort(int a[], int l, int r) {

    if(l >= r) return;

    int x = a[l], i =  l - 1, j = r + 1;
    while(i < j) {
        do i ++; while(a[i] < x); 
        do j --; while(a[j] > x);
        if(i < j) swap(a[i] , a[j]);
    }

    quickSort(a, l, j);
    quickSort(a, j + 1, r);
}


int main(void)
{
    cin >> n;
    for(int i = 0; i < n; i ++) cin >> a[i];  

    quickSort(a, 0, n - 1);

    for(int i = 0; i < n; i ++)cout << a[i] << ' '; 
    puts("");
    return 0;
}
