#include <iostream>
#include <algorithm>
#include <cstring>


using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};



//迭代版本
ListNode *reverseListN(ListNode *head) {
        ListNode *prev = NULL, *cur = head;
        while(cur) {
            auto next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;  
        }

        return prev;
}



//递归版本
ListNode *reverseListR(ListNode *head) {

    if(!head || !head->next) return head;

    auto tail = reverseListR(head->next);
    head->next->next = head;
    head->next = nullptr;
    
    return tail;
}


int main(void)
{
    

    return 0;
}
