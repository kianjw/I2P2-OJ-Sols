#include <stdio.h>
#include <stdlib.h>
typedef struct _point{
	int number;
	struct _point *right;
	struct _point *left;
}Node;

int search(int * inorder, int start, int end, int target){
	for(int i = start; i<=end;i++){
		if(inorder[i] == target) return i;
	}
}

Node*build(int * inorder, int *postorder, int start, int end, int * run){
	if(start > end) return NULL;
	Node* new = (Node*)malloc(sizeof(Node));
	new->number = postorder[(*run)--];
	int idx = search(inorder, start, end , new->number);
	new->right = build(inorder, postorder, idx+1, end, run);
	new->left = build(inorder, postorder, start, idx-1, run);
	return new;
}

Node * buildtree(int * inorder, int *postorder, int start, int end){
	int run = end;
	return build(inorder, postorder, start, end, &run);
}

void showpre(Node*root){
	if(root){
		printf("%d ", root->number);
		showpre(root->left);
		showpre(root->right);
	}
	return;
}

void freetree(Node*root){
	if(root){
		freetree(root->left);
		freetree(root->right);
        free(root);
	}
	return;
}


int main(){
	int n; int count = 0;
	while(scanf("%d", &n) != EOF){ count++;
		int inorder[200000] ={};
		int postorder[200000] = {};
		for(int i = 0; i<n;i++) scanf("%d", &inorder[i]);
		for(int i = 0;i<n;i++) scanf("%d", &postorder[i]);
		Node * root = buildtree(inorder, postorder, 0, n -1);
		printf("testcase%d: ", count);
		showpre(root);
		printf("\n");
                                  freetree(root);
	}
}