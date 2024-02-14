#include <stdio.h>
#include <string.h>
int k;
char input[21]; 
char to_print[21];
int length;
void recursive(int pos){
	if(pos == k){
		printf("%s\n", to_print);
		return;
	}
	for(int i = 0; i<length;i++){
		to_print[pos] = input[i];
		recursive(pos+1);
	}
}


int main(){
	scanf("%s", input);
	scanf("%d", &k);
	length = strlen(input);
	recursive(0);	
}