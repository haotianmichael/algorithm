#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

/*时间复杂度 是O(n)*/
const int N = 10010, M = 100010;
int n, m;
char p[N], s[M];
int ne[N];


int 
main(void) {

    cin >>  n >> (p + 1) >> m >> (s + 1);
    //求next过程
    for(int i = 2, j = 0; i <= n; i ++) {
        while(j && p[i] != p[j+1])  j = ne[j];
        if(p[i] == p[j+1])  j ++;
        ne[i] = j;
    }


    //匹配过程
    for(int  i = 1,j = 0; i <= m; i ++) {
        while(j && s[i]!=p[j+1])  j = ne[j];   
        if(s[i] == p[j+1]) j ++;
        if(j == n){
            //匹配成功 
            cout << i - n<< endl;
            j = ne[j];
        } 
    }    

    return 0;
}
