#include <iostream>
using namespace std;

/*并查集  理解find函数的核心作用 压缩路径优化可以将复杂度降到O(1)  有时候并查集会存储一些额外的信息*/
const int N = 100010;
int p[N];


int find(int x) {
    if(x != p[x]) p[x] = find(p[x]);
    return p[x];
}




//基本的并查集
int 
test0_main(void) {

    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) p[i] = i;

    char op;
    int a, b;
    while(m --) {
        cin >> op >> a >> b;
        if(op == 'M') {
            cin >> a >> b;
            if(find(a) == find(b)) continue;
            p[find(a)] = find(b);  
        }else if(op == 'Q') {
            cin >> a >> b;
            if(find(a) == find(b)) cout << "Yes" << endl;
            else cout << "No" << endl; 
        }

    }
    return 0;
}


//存储了额外元素的并查集
int size[N];   //存放额外的集合元素个数的数组
int 
test1_main(void) {

    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i ++) {
        p[i] = i;
        size[i] = 1; 
    }

    char op[2];
    int a, b;
    cin >> op;
    while(m --) {
        if(op[0] == 'C') {
            cin >> a >> b;
            if(find(b) == find(a))  continue;
            size[find(a)] += size[find(b)];
            p[find(b)] = find(a);
        } else if(op[1] == '1') {
            cin >> a >> b;
            if(find(b) == find(a)) cout << "Yes" << endl;
            else cout << "No" << endl;

        }else if(op[1] == '2') {
            cin >> a;
            cout << size[find(a)] << endl; 
        }
    }

    return 0;
}


int 
main(void) {
    
    test0_main();
    test1_main();

    return 0;
}
