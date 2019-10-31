#include <iostream>

/*双链表  静态数组模拟   体会使用数组元素模拟双链表两个左右端点的方式*/
using namespace std;

const int N = 10010;
int l[N], r[N], e[N];
int idx;

void init() {
    l[1] = 0;
    r[0] = 1;
    idx = 2;
}


void insert(int k, int x) {

    e[idx] = x;
    r[idx] = r[k];
    l[idx] = k;
    l[r[k]] = idx;
    r[k] = idx;
    idx++;
}

void remove(int k) {

    l[r[k]] = l[k];
    r[l[k]] = r[k];

}


int 
main (void) {

    int M;
    cin >> M;
    init();
    while(M --) {
        string op;
        int x, k;
        cin >> op;
        if(op == "L") {
            cin >> x;
            insert(0, x);    
        }else if(op == "R") {
            cin >> x;
            insert(l[1], x); 
        }else if(op == "IL") {
            cin >> k >> x;
            insert(l[k] + 1, x);
        }else if(op == "IR") {
            cin >> k >> x;
            insert(k + 1, x); 
        }else if(op == "D") {
            cin >> k;
            remove(k + 1); 

        }
    }
    for(int i = r[0]; i != 1; i = r[i]) cout <<  e[i] << ' ';
    cout << endl;
    return 0;

}
