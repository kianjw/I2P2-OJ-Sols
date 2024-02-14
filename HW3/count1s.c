#include <stdio.h>

int main(){
	int t;
	scanf("%d",&t);
	int a; int count[1000002] = {};
	for(int i = 1; i<= 1000000;i++){
		a = i;
		while(a){
			if(a % 10 == 1)count[i]++;
			a/=10;
		}
		count[i] += count[i-1];
		
	}
	while(t--){
		int a, b;
		scanf("%d%d", &a,&b);
		printf("%d\n", count[b] - count[a-1]);
	}
}