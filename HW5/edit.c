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
int now = 0;
int x, y, z;

Node * createList(int val, char c){
	Node*root = (Node*)malloc(sizeof(Node));
	root->val = val;
	root->c = c;
	root->left = NULL;
	root->right = NULL;
	return root;
}

Node * buildtree(){
	if(str[now] == ' ') now++;
	Node*root = NULL;
	if(str[now] == '+' || str[now] == '-' || str[now] == '*' || str[now] == '/'  ){
		root = createList(-1, str[now]);
		root->type = 0;
		now++;
		root->left = buildtree();
		root->right = buildtree();
	}	

	else if(str[now] == 'x' || str[now] == 'y' || str[now] == 'z'){
		if(str[now] == 'x') root = createList(x, str[now]);
		if(str[now] == 'y') root = createList(y, str[now]);
		if(str[now] == 'z') root = createList(z, str[now]);
        now++;
		root->type = 1;
	}
	else if(str[now] >= '0' && str[now] <= '9'){
		int num =0;
		while(str[now] >= '0' && str[now] <= '9'){
			num = 10*num + str[now] - '0';
			now++;
		}
		root = createList(num, ' ');
		root->type = 2;
	}
	return root;
}

void inorder(Node*root){
    if(root){
	inorder(root->left);
	if(root->type == 0 || root->type == 1) printf("%c", root->c);
	else if(root->type == 2) printf("%d", root->val);
	inorder(root->right);
}}

int count(Node*root){
	if(root->type == 0){
		int l = count(root->left);
		int r = count(root->right);
		if(root->c == '+') return l+r;
		if(root->c == '-') return l-r;
		if(root->c == '*') return l*r;
		if(root->c == '/') return l/r;
	}
	return root->val;
}

int main(){ 
	fgets(str, sizeof(str), stdin);
	scanf("%d%d%d", &x, &y,&z);
	Node * root = buildtree();
	inorder(root); printf("\n");
	printf("%d", count(root));


}