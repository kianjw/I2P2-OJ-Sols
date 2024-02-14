#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int solveJosephus(int n , Node* head){

      /*your code here*/
	  int len =1;
    Node *cursor = head; 
    while(cursor->next != head){
        len++;
        cursor = cursor->next;
    }
    cursor = (head);
    
  
    Node* temp = cursor;
	
    while(len>1){
		if((len%2) != 0){ 
            for(int i = 1 ; i<= len-2; i++){
                cursor = cursor->next;
            }
			temp = cursor->next->next;
			free(cursor->next);
			cursor->next = temp; 
		}
		else{
			for(int i = 1; i<= len/2 - 1;i++){
				cursor = cursor->next;
			}
			temp = cursor->next->next;
			free(cursor->next);
			cursor->next= temp; cursor = cursor->next;
		}
    len--;
    }
    return cursor->number;


}

Node* createList(int n , Node* head){
    head = (Node*)malloc(sizeof(Node));

    /*your code here*/
    head->number = n;
    head->next = head;
    for(int i = n - 1; i>0; i--){
        Node *new = (Node*)malloc(sizeof(Node));
        new->number = i;
        new->next = head->next;
        head->next = new;

    }
    return head->next;

}