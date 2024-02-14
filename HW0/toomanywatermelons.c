#include <stdio.h>
int main(){
	int n; 
	scanf("%d", &n);
	int a[200001];
	int b[200001];
	int pos[200001];
	for(int i = 1; i<=n;i++){
		scanf("%d", &a[i]);
	}
	for(int i = 1; i<=n;i++){
		scanf("%d", &b[i]);		
	}
	for(int i = 1;i<=n;i++){
		pos[a[i]] = i;
	} int now = 0;
	for(int i = 1; i<=n;i++){ 
		if(now > pos[b[i]]){
			printf("0 ");
		}
		else{
			printf("%d ", pos[b[i]] - now); now = pos[b[i]];
		}


	}
}