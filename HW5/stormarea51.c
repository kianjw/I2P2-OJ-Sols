#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _Point{
	struct _Point *left, *right;
	int type;
	int val;
	char op_id;
}Node;
int x, y, z;
char a[101] = {};

Node *buildtree(int run) {
    if(a[run] == ' ') run++;
	
    Node *now = (Node *)malloc(sizeof(Node)); printf("%d ", run);
    if (a[run] >= '0' && a[run] <= '9') {
        now->type = 0;
        now->val = a[run] - '0';
        run++;
    } else if (a[(run)] == 'x' || a[(run)] == 'y' || a[(run)] == 'z') {
        now->type = 1;
        now->op_id = a[(run)];
        if (a[(run)] == 'x') now->val = x;
        else if (a[(run)] == 'y') now->val = y;
        else if (a[(run)] == 'z') now->val = z;
        run++;
    } else if (a[(run)] == '+' || a[(run)] == '-' || a[(run)] == '*' || a[(run)] == '/') {
        now->type = 2;
        now->op_id = a[run++];
        now->left = buildtree(run);
        now->right = buildtree(run);
    }

    return now;
}



void print(Node*head){
	if(head){
   //printf("%d", head->type);
    print(head->left);
   print(head->right);
    }
    
}
int main(){
    fgets(a, 101, stdin);	
	scanf("%d%d%d", &x, &y, &z);
	 int run = 0;
	Node* head = buildtree(run);
    //print(head);
	//traversal(head, 0);
}