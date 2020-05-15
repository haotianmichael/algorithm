#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 50010;
int n;

typedef pair<int, int> PII;
PII cow[N];

int main(void)
{
    cin >> n ;
    int w, s;
    for(int i = 0; i < n;  i++) {
        cin  >> w >> s;
        cow[i] = {w, s};
    } 

    sort(cow, cow + n);
    int res = -2e9;
    int sum = 0;
    for(int i = 0; i < n; i++){
        int w = cow[i].second, s = cow[i].first - w;
        res = max(res, sum - s);
        sum += w;
    }

    cout << res << endl;
    return 0;
}
