#include <iostream>

using namespace std;

const int N = 1e6 + 10;
int q[N];
int n, m;


int 
main(void) {


    scanf("%d%d", &n, &m);
    for(int i = 0; i < n;  i++) scanf("%d", &q[i]); 

    while(m --) {
        int x; 
        scanf("%d", &x); 
        int l = 0, r = n - 1;
        while(l < r) {
            int mid = (l + r) >> 1; 
            if(q[mid] >= x)  r = mid;
            else l = mid  +  1;
        }
        if(q[l] != x) cout << "-1 -1" << endl;
        else {
            cout << l << ' ';
            l = 0, r = n - 1;
            while(l < r) {
                int mid = (l + r + 1) >> 1;
                if(q[mid] <= x) l = mid;
                else r = mid - 1;
            } 
            cout << r << endl;
        }

    }

    return 0;
}
