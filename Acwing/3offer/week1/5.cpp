#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

/* 5. 从尾到头打印链表*/
const int  N = 100010;
int e[N], ne[N];
int head = -1, idx = 0;

void insert_head(int x) {
    e[idx] = x;
    ne[idx] = head;
    head = idx++;
}

void insert(int k,  int x) {
    e[idx] = x;
    ne[idx] = ne[k];
    ne[k] = idx;
    idx ++;
}

void remove(int k) {
    ne[k] = ne[ne[k]];
}


void print(){
    for(int i  = head; i != -1; i = ne[i])  cout << e[i] << ' ';   
    puts("");
}

void reversePrint() {
    std::vector<int> res;
    for(int i = head; i != -1; i = ne[i]) res.push_back(i);
    reverse(res.begin(), res.end()); 
    for(auto e : res) cout << e << ' ';
    puts("");
}

int main(void)
{
    insert_head(0);
    for(int i = 0; i <= 9; i++) 
        insert(i, i+1);

    print();
    reversePrint();
    return 0;
}
