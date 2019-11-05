#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;
const int N  = 100010;
int h[N];
int size;

int ph[N]; //第k个插入的点在堆中的下标
int hp[N];  //堆里的点是第几个插入的点


void swap_heap(int a, int b) {
    swap(ph[hp[a]], ph[hp[b]]);
    swap(hp[a], hp[b]);
    swap(h[a], h[b]);
}


void down(int x){
    int u = x;
    if(x*2 <= size && h[x*2] < h[u])  u = x *2;
    if(x*2 + 1 <= size && h[x * 2 + 1] < h[u])  u = x * 2 + 1;
    if(u != x) {
        swap_heap(u, x);
        down(u);
    }

    return ;
}

void up(int x) {

    while(x/2 && h[x] < h[x / 2] ) {
        swap_heap(x, x/2);
        x /= 2; 

    }

    return ;
} 

int 
main(void) {

    int n, m = 0;
    cin >> n;
    while( n --) {
        char op[10];
        int k, x;
        cin >> op;
        if(!strcmp(op, "I")) {
            scanf("%d", &x); 
            size++;
            m ++;
            ph[m] = size,hp[size] = m;
            h[size] = x;
            up(size);
        }else if(!strcmp(op, "PM")) cout << h[1] << endl;
        else if(!strcmp(op, "DM")) {
            swap_heap(1, size);             
            size--;
            down(1); 
        }else if(!strcmp(op, "D")) {
            scanf("%d", &k);
            k = ph[k];
            swap_heap(k, size);
            size--;
            down(k);
            up(k);
        }else {
            cin >> k >> x;
            k = ph[k];
            h[k] = x;
           down(k); 
           up(k);
        }
    }
    return 0;
}
