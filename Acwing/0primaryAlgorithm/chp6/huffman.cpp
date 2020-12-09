#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
const int N  = 10010;


int main(void)
{
    int n;
    cin >> n;
    priority_queue<int,vector<int>, greater<int> > heap;

    while(n --) {
        int x;
        cin >> x;
        heap.push(x); 
    }
    
    int res = 0;
    while (heap.size() > 1) {
        int a = heap.top(); heap.pop();
        int b = heap.top(); heap.pop();
        res += a  + b; 
        heap.push(a + b);
    }

    cout << res << endl;
    return 0;
}
