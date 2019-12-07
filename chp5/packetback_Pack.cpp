#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 110;
int n, m;
int v[N][N], w[N][N], s[N];
int f[N];



int 
main(void) {

    cin >> n >> m;
    for(int i = 1; i <= n; i ++){
        cin >> s[i];
        for(int j = 0; j < s[i]; j ++) {
            cin >> v[i][j] >> w[i][j]; 
        } 
    }
        

    for(int i = 1; i <= n; i ++)
        for(int j = m; j >= 0; j --)
            for(int k = 0; k < s[i]; k ++)
                if(v[i][k] <= j)
                    f[j] = max(f[j], f[j-v[i][k]] + w[i][k]);


    return 0;
}
