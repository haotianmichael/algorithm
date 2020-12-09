#include <iostream>
#include <cstring>
#include <vector>


using namespace std;
const int n = 100010;


//截取v[l]~v[r]
int get(vector<int> num, int l, int r) {
    int res = 0;
    for(int i = l; i >= r; i --) res = res*10 + num[i]; 
    return res;
}

int power10(int x) {
    int res = 1;
    while(x --) res *= 10;
    return res;
}



//从1~n中判断x出现的次数
int counts(int n, int x) {

    if(!n)   return 0;
    std::vector<int> v;
    while (n) {
        v.push_back(n % 10);
        n /= 10;
    }   

    n = v.size();
    int res = 0;
    for(int i = n - 1 - !x;  i >= 0; i--){   //从最高位开始枚举

        //第一种情况
        if(i < n - 1)  {  
            res +=  get(v, n - 1, i + 1) * power10(i);
            if(!x)  res -= power10(i);          //特殊情况x = 0
        }       

        //第二种情况
        if (v[i] == x) {
            res += get(v, i - 1, 0) + 1;
        } else if(v[i] > x){
            res += power10(i);            
        }  
    } 
    return res;
}


int main(void)
{
    
    int a,b;
    while (cin >> a >> b, a || b) {
        if(a > b) swap(a, b);
        for(int i = 0; i <= 9; i ++) 
            cout << counts(b, i) - counts(a - 1, i) << ' ';
        puts(""); 
    }
    return 0;
}
