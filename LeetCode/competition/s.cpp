//
// Created by Administrator on 2020/7/8 0008.
//

#include <clocale>
#include <cstdlib>

class Solution {
public:

     struct ListNode {
             int val;
             ListNode *next;
             ListNode(int x) : val(x), next(NULL) {}
         };

    static ListNode* removeElements(ListNode* head, int val) {
        if(head == nullptr) return nullptr;
        ListNode *p = head;
        if(head->val == val){
            p = head;
            head = head->next;
            free(p);
            removeElements(head,val);
        }else{
            removeElements(head->next,val);
        }
        return p;
    }

};

int main() {
    Solution::ListNode *a(0);
    Solution::ListNode *b(1);
    Solution::ListNode *c(2);
    Solution::ListNode *d(3);
    Solution::ListNode *e(4);

    Solution::removeElements(nullptr,0);
}