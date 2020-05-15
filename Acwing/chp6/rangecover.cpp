#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 100010;
int n;
struct Range{
    
    int l, r;
    bool operator < (const Range & W) const {
        return l < W.l; 
    }
}range[N];



int 
main(void)  {


    int st, ed;
    cin >> st >> ed;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int l , r;
        cin >> l >> r;
        range[i] = {l, r};
    }


    sort(range, range + n);
    int res = 0;
    bool success = false;

    for(int i = 0; i < n; i++) {
        int j = i, r = -2e9;
        while(j < n && range[j].l <= st) {
            r = max(r, range[j].r); 
            j ++;
        } 


        if(r < st) {
            res = -1;
            break; 
        }
        res ++;
       if(r >= ed) {
           success = true;
           break;
        }
    
       st = r;
       j = j - 1;
    }


    if(!success) res = -1;
    cout << res << endl;
    return 0;
}

