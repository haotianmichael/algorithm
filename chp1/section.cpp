#include <iostream>
#include <algorithm>
#include <vector>

/*区间合并*/
using namespace std;
typedef pair<int, int> PII;
vector<PII> segs;


void merge(vector<PII> &q) {

    vector<PII> res;
    sort(q.begin(), q.end());

    int st = 2e9, ed = 2e9;  //添加哨兵  这个方式和快排的l - 1 && r + 1本质是一样的，很经典的算法
    for(auto seg : segs) {
    
        if(ed < seg.first) {
            if(st != 2e9) res.push_back({st, ed});              
            st = seg.first, ed = seg.second;
        }else {
            ed = max(seg.second, ed); 
        }
    }
    if(st != 2e9) res.push_back({st, ed});

    segs = res;
}




int 
main (void) {

    int n;
    cin >> n;
    for(int i = 0; i < n; i ++) {
        int l, r;
        cin >> l >> r;
        segs.push_back(make_pair(l, r));
    }
    merge(segs);
    cout << segs.size() << endl;
    return 0;
}
