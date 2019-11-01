#include <iostream>

using namespace std;
const int N = 100010;

/*体会算法的间接性      尽量快的熟练思路*/

/*
   单调栈
   从一个序列中找到每一个元素左边离它最近的最小值
   3 4 2 7 5 
 */
void monoticStack() {

    int stk[N];
    int hh = 0; //模拟栈第零号不存储元素  stk[++hh] = x;

    int n;
    cin >> n; 
    while(n --) {
        int x;
        cin >> x;
        while(hh && stk[hh] > x) hh--;   // 维护一个单调的栈区间 
        if(hh) cout << stk[hh] << ' ';
        else cout << "-1 "; 
        stk[++hh] = x;
    } 
    return ;
}





//单调队列
void monticQueue() {

    int q[N], a[N];
    int hh = 0, tt = -1;
    int n, k;
    cin >> n >> k;
    for(int i = 0; i <n; i ++) cin >> a[i];
    
    //求出滑动窗口的最小值
    for(int i = 0; i < n; i ++) {
        //判断队列是否已满
        if(hh<=tt && q[hh] < i - k + 1) hh ++;
        while(hh<=tt && a[q[tt]] >= a[i])  tt--;
        q[++tt] = i;
        if(i >= k - 1) cout << a[q[hh]] << ' ';
    }

    puts("");

    //求出滑动窗口中的最大值z
    hh = 0, tt = -1;
    for(int i = 0; i < n; i ++) {
        if(hh<=tt && q[hh] < i - k + 1)hh ++;
        while(hh<=tt && a[q[tt]] <= a[i]) tt--;
        q[++tt] = i;
        if(i >= k -1) cout << a[q[hh]] << ' '; 
    }



    return;
}

int 
main(void) {

//    monoticStack();

    monticQueue();
    return 0;
}

