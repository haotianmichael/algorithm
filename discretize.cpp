#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1e6 + 10;
typedef pair<int, int> PII;
int a[N], s[N];
int n, m;
vector<PII> add, query;
vector<int> alls;  //待离散化数组


int find(int x) {

    int l = 0, r = alls.size() - 1;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(alls[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return r + 1;
}

//去重操作  使用双指针算法  体会算法的简洁和魅力!!!
void my_unique(vector<int> &q) {
    int j = 0;
    for(unsigned int i = 0; i < q.size(); i ++) {
        if(!i || q[i] != q[i-1]) {
            q[j++] = q[i];
        }
    }
    cout << endl;

    for(int i = 0; i < j; i ++) {
        cout << q[i] << ' '; 
    }
}


int unique_main(void) {

    vector<int> q;
    q.push_back(1);
    q.push_back(2);
    q.push_back(2);
    q.push_back(3);
    q.push_back(4);
    q.push_back(5);
    q.push_back(5);
    q.push_back(6);
    q.push_back(6);

    my_unique(q);

    return 0;
}
int 
main(void) {

    cin >> n >> m;
    //各种操作
    for(int i = 0; i < n; i ++) {
        int x, c;
        cin >> x >> c;
        add.push_back(make_pair(x, c)); 
        alls.push_back(x);    
    }

    //查询
    for(int i = 0; i < m; i ++) {
        int l, r;
        cin >> l >> r;
        query.push_back(make_pair(l, r));  
        alls.push_back(l); 
        alls.push_back(r);
    }

    //去重
    sort(alls.begin(), alls.end());
    alls.erase(unique(alls.begin(), alls.end()), alls.end());

    //插入操作
    for(auto item : add) {
        int x = find(item.first);         
        a[x] += item.second;
    }

    //处理前缀和
    for(unsigned int i = 1; i <= alls.size(); i ++) s[i] = s[i-1] + a[i];
    for(auto item : query) {
        int l = find(item.first);         
        int r = find(item.second);
        int res = s[r] - s[l-1];
        cout << res << endl;
    }

    return 0;
}
