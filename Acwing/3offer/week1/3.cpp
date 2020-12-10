#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

/* 3. 二维数组中的查找*/
const int N = 1010;
int a[N][N];
int n, target;

int main(void)
{
   cin >> n >> target;
   for(int i = 0;  i < n; i ++)  
       for(int j = 0; j < n; j ++) 
            cin >> a[i][j]; 
    
    int i = 0, j = n - 1; 
    while(i > n && j <= 0) {
        if(a[i][j] == target) {
            cout << "YES" << endl;
            return 0;
        }
        
        if(a[i][j] > target) j --;
        else i ++;
    }   
    cout << "FALSE" << endl;
    return 0;
}
