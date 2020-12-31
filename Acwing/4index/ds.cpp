#include <iostream>
#include <algorithm>


using namespace std;
/*
 
    * 单链表
    * 双链表
    * 栈
    * 队列
    * 单调栈
    * 单调队列
    * KMP
*/

//单链表
const int N = 100010;
int e[N], ne[N];
int head, idx;
void init() {
    idx = 0;
    head = -1;
}

void insert_head(int x) {
    e[idx] = x;
    ne[idx] = head;  
    head = idx;
    idx ++;
}

void insert(int k, int x) {
    e[idx] = x;
    ne[idx] = ne[k];
    ne[k] = idx++;
}

void remove(int k) {
    ne[k] = ne[ne[k]];
}

void print() {
    for(int i = head; i != -1; i = ne[i]) {
        cout << e[i] << ' '; 
    } 

}


//双链表
int r[N], l[N];
void dinit() {
    l[1] = 0;
    r[0] = 1; 
    idx = 2;
}

void dinsert(int k, int x) {
    e[idx] = x;
    r[idx] = r[k];
    l[idx] = k;
    l[r[k]] = idx;
    r[k] = idx ++; 
}


void dremove(int k) {
    l[r[k]] = l[k];
    r[l[k]] = r[k];
}

/*===================
    * TRIE树
    * 并查集
    * 堆
    * 哈希表 
 */
int son[N][N], cnt[N], tidx;
void insert(char str[]) {
    int p = 0;
    for(int i = 0; str[i] ; i ++) {
        int u = str[i] - 'a';
        if(!son[p][u]) son[p][u] = ++idx;
        p = son[p][u]; 
    } 
    cnt[p]++;

}

int query(char str[]) {
    int p  = 0;
    for(int i = 0; str[i]; i ++) {
        int u = str[i] - 'a'; 
        if(!son[p][u]) return 0;
        p = son[p][u];
    } 

    return cnt[p];
}


/*
并查集:
    1. 将两个集合合并
    2. 询问两个元素是否在一个集合中 
*/







/*
    哈希表 
    存储结构
        开放寻址法
        拉链法
    字符串哈希方式
*/
int q[N][26];













int main(void)
{
    return 0;
}
