#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 100010;
int a[N], n;




void mergeSort(int a[], int l, int r) {


}

int main(void)
{
    
    cin >> n;
    for(int i = 0; i < n; i ++) cin >> a[i];
    mergeSort(a, 0, n - 1);
    for(int i = 0; i < n; i ++) cout << a[i] << ' ';
    return 0;
}
