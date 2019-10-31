#include <iostream>

using namespace std;
const int N  = 100010;
int q[N], tt = -1, hh;
int stk[N],shh;

void myfront(int x) {
       q[++tt] = x; 
}

int  mypop() {
    if(hh > tt) return -1;
    return (q[hh++]);

}

//空返回真
bool empty() {
    return (hh > tt);
} 



int 
queue_main(void) {

    myfront(1);
    myfront(2);
    myfront(3);
    myfront(4);
    myfront(5);

    while(!empty()) {
        cout << mypop() << endl; 
    }

    return 0;

}

void my_spush(int x) {
    stk[++shh] = x;

}

//空返回真
bool my_sempty() {
    return (shh <= 0);
}


int my_spop() {
    if(shh <= 0) return -1;
    return (stk[shh--]);
}


int 
main(void) {
    my_spush(1);
    my_spush(2);
    my_spush(3);
    my_spush(4);
    my_spush(5);
    my_spush(6);

    while(!my_sempty()) {
        cout << my_spop() << endl; 
    }

    return 0;
}
