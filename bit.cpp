#include <iostream>


using namespace std;

//返回从个位开始的第一个1
int lowbit(int x) {
    return (x & -x);
}



//x >> k & 1得到数x二进制表示下第k位是几


int 
main() {

    int ans;
    cin >> ans;
    int num = 0;
    while(ans) {
        ans -= lowbit(ans);
        num++; 
    }

//得到每一个数二进制中的1的个数
    cout << num << endl;
    return 0;
}
