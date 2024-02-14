#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct _Point{
	char type;
	char c;
	int val;
	struct _Point *left;
	struct _Point *right;
}Node;
char str[101] = {};
int now ;

Node * createList(int val, char c){
	Node*root = (Node*)malloc(sizeof(Node));
	root->val = val;
	root->c = c;
	root->left = NULL;
	root->right = NULL;
	return root;
}

Node * buildtree(){
	if(str[now] == ' ') now--;
	Node*root = NULL;
	if(str[now] == '+' || str[now] == '-'  ){
		root = createList(-1, str[now]);
		root->type = 0;
		now--;
		root->right = buildtree();
		root->left = buildtree();
		
	}	

	else if(str[now] >= '0' && str[now] <= '9'){
		int num =0;
		while(str[now] >= '0' && str[now] <= '9'){
			num = 10*num + str[now] - '0';
			now--;
		}
		int reverse = 0;
		while(num>0){
			int digit = num%10;
			reverse = 10*reverse + digit;
			num/=10;
		}
		root = createList(reverse, ' ');
		root->type = 1;
	}
	return root;
}


int count(Node*root){
	if(root->type == 0){
		//if(root->val == 0) return root->val;
		int l = count(root->left);
		int r = count(root->right);
		//printf("%d %d\n", l,r);
		if(root->c == '+') return l+r;
		if(root->c == '-') return l-r;
	}
	return root->val;
}

int main(){ 
	fgets(str, sizeof(str), stdin);
	now = strlen(str) - 2;
	Node * root = buildtree();
	printf("%d", count(root));


}