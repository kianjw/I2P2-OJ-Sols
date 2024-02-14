#include <stdio.h>
typedef struct _Point{
	int l, r;
}Point;
Point a[100005] = {};
int main(){
	int n, k;
	scanf("%d%d", &n, &k);
	
	for(int i = 0; i < n;i++) scanf("%d", &a[i].l);
	for(int i = 0 ; i< n;i++) scanf("%d", &a[i].r);
	
}