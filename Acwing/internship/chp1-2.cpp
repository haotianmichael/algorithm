#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;


//数组快排
const int N = 100010;
int a[N];
int n;
void quickSort(int q[], int l, int r){

    if(l >= r) return;

    int x = q[l], i = l - 1, j = r + 1;

    while(i < j) {
        do i ++; while(q[i] < x); 
        do j --; while(q[j] > x);
        if(i < j) swap(a[i], a[j]);
    }

    quickSort(q, l, j);
    quickSort(q, j + 1, r);
}
void arrayTest() {
    cin >> n;
    for(int i = 0; i < n; i ++) cin >> a[i];
    quickSort(a, 0, n - 1);
    for(int i = 0; i < n; i ++) cout << a[i] << ' ';
    return ;
}

/*链式快排*/
struct  ListNode{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    Solution ();
    virtual ~Solution ();
    
    ListNode* get_tail(ListNode *head) {
        while(head->next) head = head->next;
        return head; 
    }

    ListNode* quickSort(ListNode *head) {

        if(!head || !head->next) return head;

        auto left = new ListNode(-1), mid  = new ListNode(-1), right = new ListNode(-1); 
        auto ltail = left, mtail = mid, rtail = right;
        int val = head->val;
        for(auto p = head; p; p = p->next){
            if(p->val < val)  ltail = ltail->next = p;
            else if(p->val == val) mtail = mtail->next = p;
            else rtail = rtail->next = p;
        }

        ltail->next = mtail->next = rtail->next = NULL;

        left->next = quickSort(left->next);
        right->next = quickSort(right->next);
    
        //拼接
        get_tail(left)->next = mid->next;
        get_tail(left)->next = right->next;
        return left->next;
    }


};


int main(void)
{
    arrayTest();    
    return 0;
}
