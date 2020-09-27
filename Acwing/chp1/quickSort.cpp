#include <iostream>
#include <algorithm>


using namespace std;

const int N = 1e6 + 10;
int n;
int q[N];

void quickSort(int q[], int l, int r) {

    if(l >= r)return;
    int x = q[l], i = l - 1, j = r + 1;
    while(i < j) {
        //!!!不能再q[i] <= x上加上等于号   (仔细思考边界问题如 1 2 3 4 5/ 5 4 3 2 1)
        do i++; while(q[i]<x); 
        do j--; while(q[j]>x); 
        if(i<j) swap(q[i], q[j]); 
    
    }
    quickSort(q, l, j);
    quickSort(q, j + 1, r);
}


int 
main(void) {

    scanf("%d", &n); 
    for(int i = 0; i < n; i++)  scanf("%d", &q[i]);
    
    quickSort(q, 0, n - 1);

    for(int j = 0; j < n; j++) printf("%d ", q[j]);

    return 0;

}
