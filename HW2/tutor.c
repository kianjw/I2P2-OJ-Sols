#include "function.h"
Node *createList(int n)
{
    Node *tail = (Node*)malloc(sizeof(Node));
    tail->number = n;
    tail->next = tail;
    for(int i=n-1; i>=1; --i)
    {
        Node *now = (Node*)malloc(sizeof(Node)), *tmp = tail->next;
        now->number = i;
        now->next = tmp;
        tail->next = now;
    }
    return tail->next;
}
void freeList(Node* head)
{
 
}
int list_length(Node *head)
{
    int res = 1;
    Node *now = head;
    while(now->next != head)
    {
        res++;
    	now = now->next;
    }
    return res;
}
int solveJosephus(Node** head, int k){
    Node * cur = *head; 
    Node * temp = cur;
   int len = list_length(cur);
   
    while(len>1) { 
        for(int i = 1; i <= (k-2)%len;i++){
           cur = cur->next; 

        }temp = cur->next->next;
    free(cur->next); cur->next = temp; cur = cur->next;
    len--;
    }
   return cur->number;

}


