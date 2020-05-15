#include <iostream>

using namespace std;
const int N = 100010;
int a[N];
int n;


void quickSort(int a[], int l, int r) {


}


int main(void)
{
    
    cin >> n;
    for(int i= 0; i < n ; i ++) cin >> a[i];
    quickSort(a, 0, n);
    for(int i = 0; i < n; ++i ) cout << a[i]; 
    return 0;
}
