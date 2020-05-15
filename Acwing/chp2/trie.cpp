#include <iostream>
using namespace std;
const int N = 100010;
int son[N][26], cnt[N], idx;

void insert(char str[]){
    int p = 0;
    for(int i = 1;str[i] ; i ++) {
        int u = str[i] - 'a';
        if(!son[p][u])  son[p][u] = ++idx;
        p = son[p][u];
    }

    cnt[p] ++;
}


int find(char str[]) {
    int p = 0;
    for(int i =0; str[i]; i++) {
        int u  = str[i] - 'a';
        if(!son[p][u])  return 0;
        p = son[p][u];
    }

    return cnt[p];
} 



int 
main(void) {

    int n;
    cin >> n;
    char str[N];
    cin >> str;


    while(n --) {
        char op;
        cin >> op >> str;
        if(op == 'I') {
            insert(str);
        }else if(op == 'Q') {
            cout << find(str) << endl;
        }    

    }

    return 0;
}
