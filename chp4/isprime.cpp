#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

bool isPrime(int x) {
    
    if(x < 2) return false;
    for(int  i = 2; i <= x / i ; i ++) {
        if(x % i  == 0) return false; 
    }
    return true;
}


int 
main(void){

    int n, m;
    cin >> n;
    while(n --) {
        cin >> m;
        if(isPrime(m)) cout << "Yes" << endl;
       else cout << "No" << endl; 
    }

    return 0;
}

