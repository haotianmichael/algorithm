#include <iostream>
using namespace std;
const int N  = 100010;
int h[N];
int size;

void down(int x){

    int u = x;
    if(x*2 <= size && h[x*2] < h[u])  u = x *2;
    if(x*2 + 1 <= size && h[x * 2 + 1] < h[u])  u = x * 2 + 1;
    if(u != x) {
        swap(h[u], h[x]); 
        down(u);
    }

    return ;
}

void up(int x) {

    while(x/2 && h[x] < h[x / 2] ) {
        swap(h[x], h[x/2]); 
        x /= 2; 

    }

    return ;
} 

int 
main(void) {

    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i ++)  cin >> h[i];
    size = n;

    for(int i = size/2; i; i --) down(i);

    while(m --) {
        printf("%d ", h[1]);
        h[1] = h[size];
        size--;
        down(1);
    }



    return 0;
}
