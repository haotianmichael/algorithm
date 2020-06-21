            /*寻找矩阵的极小值*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
const int N = 100010;
int res[N][N];


class Solution
{
    public:
        Solution ();
        virtual ~Solution ();

        int query(int x, int y) {
            return res[x][y];
        }


        vector<int> getMinmumValue(int n) {
            
            const int INF = 1e8;
            int l = 0, r = n - 1;
            while(l  < r){
                int mid = (l + r)  >> 1;
                int min = INF, k;
                for(int i = 0; i < n; i ++){
                    int x = this->query(i, mid); 
                    if(min > x){
                        min = x;
                        k = i;
                    }
                }

                int left = mid ? this->query(k, mid - 1) : INF;
                int right = mid + 1 < n ? this->query(k , mid + 1) : INF;

                if(left > min && right > min) return {k, mid}; 
                if(left < min) r = mid - 1;
                else l = mid  + 1;
            }
            
            int min = INF, k;
            for(int i = 0; i < n; i++) {
                int x = this->query(i, l); 
                if(min > x) {
                    min = x;
                    k = i; 
                } 
            }
            return {k, l}; 
        
        }

};
