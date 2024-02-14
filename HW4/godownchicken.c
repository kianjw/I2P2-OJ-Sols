#include <stdio.h>
#define m 1000000007
typedef struct _point{
	int l, r;
}Point;
int n, q;
Point ans[1000005] = {};

long long int getans(int y){
	if(y==1) return 2;
	else{
		if(y%2==0) return (getans(y/2)*getans(y/2))%m;
		else return ((getans(y/2)*getans(y/2))%m*2)%m;
	}
}

int cmp( const void*a, const void*b){
	Point *aa = (Point*)a;
	Point *bb = (Point*)b;
	return (*aa).r - (*bb).r;
}

int lb(int x){
	int l = 0;
	int r= n;
	while(l<r){
		int mid = (l+r)/2;
		if(ans[mid].r >=x) r = mid;
		else l = mid+1;
	}
	if(ans[r].r == x) return r;
	else return -1;
}

int main(){
while(scanf("%d%d", &n, &q) != EOF){
	int num;
	for(int i = 0 ; i<n;i++){
		scanf("%d(/`A`)/ ~I__I", &num);
		if(num % 2 == 0) ans[i].r = getans(num/2);
		else ans[i].r = 0;
	}
	for(int i = 0;i<n;i++) ans[i].l = i+1;
	qsort(ans, n, sizeof(ans[0]), cmp);

while(q--){
	int x;
	scanf("%d", &x);
	int idx = lb(x);
	if(idx>=0) printf("%d\n", ans[idx].l);
	else printf("Go Down Chicken 404\n");
}
}
}