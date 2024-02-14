#include <stdio.h>

int main(){
	int n , q;
	scanf("%d%d", &n, &q);
	int a[1000005] = {}; int pre[1000005] = {};
	for(int i = 1; i<= n ; i++){
		scanf("%d", &a[i]);
	}
	for(int i = 1 ; i<=n;i++){
		if(a[i] <= 0) a[i] = 0;
		 pre[i] = pre[i-1] + a[i];
		
	}
	while(q--){
		int l, r, m;
		scanf("%d%d%d", &l, &r, &m);
		printf("%d\n", pre[l+m-1] - pre[l-1] );
	}
}