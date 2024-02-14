#include <stdio.h>
#define max(x,y) ((x) > (y) ? (x) : (y))
int arr[2000006] ={};
long long int pre[2000005] ={};
long long int ans;
long long int fans;
int main(){
	int n, q, c, d;
	while(scanf("%d%d", &n,&q) != EOF){ fans = 0;
		for(int i = 1 ;i<=n;i++){
			scanf("%d", &arr[i]);
		}
		for(int i = 1; i<=n;i++){
			pre[i] = pre[i-1] + arr[i];
		}
		while(q--){ 
			int a, b;
			scanf("%d%d", &a, &b);
			if(a<=b){
				ans = pre[b] - pre[a-1];
			}
			else{
				ans = pre[n] - pre[a-1] + pre[b];
			} 
			if(ans>fans){
				fans = ans;
				c = a;
				d = b;
			}
		}
		
		printf("Max_range: (%d,%d);", c, d);
		printf(" Value: %lld\n", fans);


	}
}