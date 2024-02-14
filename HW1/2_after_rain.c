#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _NODE{
	char color[10];
	struct _NODE *next;
}Node;
void show(Node **head) {
    Node *now = (*head)->next;
    while(now!=NULL) {
        printf("%s ", now->color);
        now = now->next;
    }
    puts("");
}
void insert(Node **head, char *buf, int num1){ Node*cur =*head;
	for(int i = 0; cur->next != NULL && i < num1;i++){
		cur = cur->next;
	}
	Node *newnode = (Node*)malloc(sizeof(Node));
	strcpy(newnode->color, buf);
	newnode->next = cur->next;
	cur->next = newnode;
}

void erase1( Node** head, int num1){ Node*prev = NULL; Node*cur =*head;
	if(cur->next == NULL) return;
	for(int i = 0; cur->next != NULL && i<num1; i++){
		prev = cur;
		cur =cur->next;
	}
	prev->next = cur->next;
	free(cur);

}

void erase2(Node** head, char *buf, int num1){ Node*prev = NULL; Node*cur =*head;
	while(cur != NULL){
		if(!strcmp(buf, cur->color)){
			prev->next = cur->next;
			free(cur);
			cur = prev;
		}
		prev = cur;
		cur = cur->next;
	}

}
void reverse(Node **head, int num1, int num2){ Node* startprev = NULL; Node*follow = NULL; Node*cur =*head;
	for(int i = 0; cur->next != NULL && i < num1;i++){
		startprev = cur;
		cur = cur->next;
	}
	follow = cur->next;
	
	for(int i = num1; cur->next != NULL && i<num2;i++){
		cur->next = follow->next;
		follow->next = startprev->next;
		startprev->next = follow;
		follow = cur->next; 
	}
}
int n; char buf[100]; int num1; int num2;
int main(){ 
	Node *head = (Node*)malloc(sizeof(Node));
	memset(head->color, '\0',sizeof(head->color)); head->next = NULL;
	scanf("%d", &n);
	while(n--){
		scanf("%s", buf);
		if(!strcmp(buf, "insert")){
			scanf("%s%d", buf, &num1 );
			insert(&head, buf, num1);
		}
		else if(!strcmp(buf, "erase1")){
			scanf("%s%d", buf, &num1);
			erase1(&head, num1);
		}
		else if(!strcmp(buf, "erase2")){
			scanf("%s%d", buf, &num1);
			erase2(&head, buf, num1);
		}
		else if(!strcmp(buf, "reverse")){
			scanf("%d%d", &num1, &num2);
			reverse(&head, num1, num2);
		}
		else if(!strcmp(buf, "show")){
			show(&head);
		}
		
	}
}