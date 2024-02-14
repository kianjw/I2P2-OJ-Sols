#define next ptr_to_next_node
#define prev ptr_to_prev_node

void insert( Node**cursor, char intype){
	Node* cur = *cursor;
	Node*new = (Node*)malloc(sizeof(Node));
	new->next = cur->next;
	new->prev = cur;
	cur->next->prev = new;
	cur->next = new;
	new->character = intype;
}

void deletion(Node**cursor){
	Node*cur = *cursor;
	if(cur->next == head) return;
	Node*temp = cur->next;
	temp->next->prev = cur;
	cur->next = temp->next;
	free(temp);
}

void backspace(Node**cursor){
	if((*cursor) == head) return;
	(*cursor) = (*cursor)->prev; Node* cur= (*cursor) ;
	deletion(&cur);

}

void go_left(Node**cursor, int num){
	while(num--){
		(*cursor) = (*cursor)->prev;
	}
}

void go_right(Node**cursor, int num){
	while(num--){
		(*cursor) = (*cursor)->next;
	}
}

void go_home(Node**cursor){
	(*cursor) = head;
}
void go_end(Node**cursor){
	(*cursor) = head->prev;
}