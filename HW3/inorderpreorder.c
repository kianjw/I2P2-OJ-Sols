#define right ptr_to_right_node
#define left ptr_to_left_node

int search(int * inorder, int target, int start, int end){
	for(int i = start ; i<= end;i++){
		if(inorder[i] == target){
			return i;
		}
	}
    
}
int pre_idx;
Node* buildTree(int * inorder, int*preorder, int start, int end){ //start and end is inorder
	if(start > end) return NULL;    
	Node*new = (Node*)malloc(sizeof(Node)); 
	new->number = preorder[ pre_idx++];
 
	int idx = search(inorder, new->number, start, end);
	new->left = buildTree(inorder, preorder, start, idx-1);
	new->right = buildTree(inorder, preorder , idx+1, end);
	return new;
}

void showPostorder(Node*new){ pre_idx = 0;
	if(new){
		showPostorder(new->left);
		showPostorder(new->right);
		printf("%d ", new->number);
	}
    return;
}

void freeTree(Node*new){
	if(new){
		freeTree(new->left);
		freeTree(new->right);
		free(new);
	}
    return;
}