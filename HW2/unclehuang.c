#include <stdio.h>
int m;
long long int getans(long long int x, long long int y){ 
if (y==0) return 1%m;
else if( y == 1) return x;
else{ long long int ans = getans(x,y/2);
	if((y%2) == 0){
		return ((ans%m)*(ans%m))%m;
	}
	else return (((ans%m)*(ans%m)%m)*x)%m;
}
    

}

int main(){ long long int x,y;
	scanf("%lld%lld", &x, &y);
	scanf("%d", &m);
	long long int ans = getans(x%m, y);
	printf("%lld", ans);
}