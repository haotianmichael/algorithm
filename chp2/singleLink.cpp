#include <iostream>
/*静态链表  数组模拟单链表*/
using namespace std;
const int N = 100010;
int e[N], ne[N];
int head, idx;


void init() {
    head = -1;
    idx = 0;
}

void insert_head(int x) {
    e[idx] = x;
    ne[idx] =  head;
    head = idx;
    idx ++;
}

void  insert(int k, int x) {
    e[idx] = x;
    ne[idx] =  ne[k];
    ne[k] = idx;
    idx ++;
}

void remove(int k) {
    ne[k] = ne[ne[k]];

}


int 
main(void) {

    int M;
    cin >> M;
    while(M --) {
    
            char op;
            int x, k;
            cin >> op;
            if(op == 'I') {
                cin >> k >> x;
               insert(k - 1, x); 
            }else if(op == 'D') {
                cin >> k;
                if(!k) head = ne[head]; 
                remove(k - 1);
            }else if(op == 'H') {
                cin >>  x;
                insert_head(x);
            }
    }

    //输出
    for(int i = head; i != -1; i = ne[i]) cout << e[i] << ' ';
    cout << endl;
    return 0;

}
