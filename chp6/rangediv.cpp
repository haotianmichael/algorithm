#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
const int N  = 100010;
int n;
struct Range{
    
    int l, r;
    bool operator < (const Range & W) const {
        return l < W.l; 
    }

}range[N];


int 
main(void) {

    cin >> n;
    for(int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        range[i].l = l;
        range[i].r = r;
    }

    
    sort(range, range + n);
    priority_queue<int, vector<int>, greater<int> > heap;

    for(int i = 0; i < n; i ++) {
        auto r = range[i];
        if(heap.empty() || heap.top() >= r.l) heap.push(r.r);
        else {
            heap.pop(); 
            heap.push(r.r); 
        }
    }
    cout << heap.size() << endl;

    return 0;
}
