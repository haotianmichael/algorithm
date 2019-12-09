#include <iostream>
#include <algorithm>
#include <cstring>


using namespace std;
const int N = 100010;
int n;
struct Range{

    int l, r;
    bool operator < (const Range & W)const {
//        return l < W.l; 
        return r < W.r;
    }

}range[N];



int 
main(void) {
    
    cin >> n;
    for(int i = 0; i < n; i++) {
        int l, r;q
        cin >> l >> r;
        range[i].l = l;
        range[i].r = r;    
    }

    sort(range, range + n);

    int res = 0;
    int ed = -1e9;
    for(int i = 0; i < n; i ++) {
        if(range[i].l > ed) {
            res ++; 
            ed = range[i].r; 
        } 
    }
    
    cout << res << endl;
    return 0;
}
