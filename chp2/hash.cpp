#include <iostream>
using namespace std;
const int N = 100003;

/*常用的哈希冲突算法：拉链法  开放寻址法*/
/*做哈希的时候   数组的长度N一般取一个质数且离2的整次幂远一些(保证冲突的概率是最小的)*/ /*一般用哈希的话  仅仅使用添加和查找没有删除操作  有的话也使用flag=false的方式*/
/*时间复杂度是O(1)*/

//求得大于x的最小的质数
int
Prime(int x) {
    int i;
    for(i = x; ; i ++) {
        bool flag = true;
        for(int j = 2; j * j <= i ; j ++) 
            if(i % j == 0) {
                flag = false;
                break; 
            }

        if(flag) {
            break; 
        }
    }
    return i;
}


/*拉链法*/
//注意x和k含义不同  x是真正需要存储的值  而k是哈希表中需要存储的位置
int h[N], e[N], ne[N], idx;
void 
insert(int x) {
    int k = (x % N + N) % N; //C++中保证余数为正数
    e[idx] = x;
    ne[idx] = h[k];
    h[k] = idx;
    idx++; 
}
bool
find(int x) {
    int k = (x % N + N) % N; 
    for(int i = h[k]; i != -1; i = ne[i]) 
        if(e[i] == x)
            return true;

    return false;
}
int 
chain_main(void) {
    
    //cout << Prime(N) << endl;
    int n;
    cin >> n;
    memset(h, -1, sizeof h);
    while(n --) {
        char op[2];
        int x;
        cin >> op >> x;
        if(op[0] == 'I')  insert(x);  
        else {
            if(find(x)) puts("Yes");
            else puts("No");
        } 
    } 
    return 0;
}

/*开放寻址法*/
const int null = 0x3f3f3f3f;
const int NN = 200003;
int
search(int x) {
   int k = (x % NN + NN) % NN; 
    while(h[k] != null && h[k] != x) {   
        k++;
        if(k == NN)  k  = 0;  //循环从头开始找 但是NN是平时数组的2~3倍 所以一般不会死循环
    }
    
    return k;
}

int 
addr_main(void) {
    int n;
    scanf("%d", &n);
    memset(h, 0x3f, sizeof h); //memset 以字节  一个字4字节故需要些一个0x3f
    while(n --) {
        char op[2];
        int x;
        scanf("%s%d", op, &x); 

        int k = search(x);
        if(* op == 'I') h[k] = x;
        else {
            if(h[k] != null) puts("Yes"); 
            else puts("No");
        }
    }
    
    return 0;
}



int 
main(void) {

    addr_main();
    chain_main();

    return 0;
}
