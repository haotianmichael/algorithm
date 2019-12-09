#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 100010;
struct Range{
    
    int l , r;
    bool operator < (const Range & W) const {
        return r < W.r; 
    }
}range[N];





int 
main(void)
{
    int n;
    cin >> n;
    for(int i= 0; i<n; ++i) {
       int a, b;
        cin >> a >> b;
        range[i].l = a;
        range[i].r = b;
    }        

    sort(range, range + n);

    int  res = 0;
    int ed = -1e9;
   for(int i = 0; i < n; i++){
        if (range[i].l > ed) {
            res ++;
            ed = range[i].r;
        }
   } 


   cout << res << endl;

    return 0;
}
