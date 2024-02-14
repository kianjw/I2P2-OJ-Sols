	#include <stdio.h>
#include <string.h>
#define m 1000000007
typedef struct Node{
	long long int mat[2][2];
}node;

node initial = {{{1,1}, {1,0}}};

node mul(node l, node r){
	node res;
	 memset(res.mat, 0, sizeof(res.mat));
	 for(int i  = 0; i<2;i++){
		for(int k = 0; k <2;k++){
			for(int j = 0; j<2;j++){
				res.mat[i][k] += (l.mat[i][j] * r.mat[j][k])%m;
				res.mat[i][k] %= m;
			}
		}
	 }
return res;
}

node fpw(node initial, long long int y){
	if(y==1) return initial;
	else{
		node temp = fpw(initial, y/2);
		if((y%2)  == 0) return mul(temp, temp);
		else return mul(mul(temp,temp), initial);
	}
}

int main(){
	long long int t;
	while(scanf("%lld", &t) != EOF){
		
		if(t <= 2) printf("1\n");
		else{
			node temp = fpw(initial, t-2 );
			long long int ans = (temp.mat[0][0] + temp.mat[0][1])%m;
			printf("%lld\n", ans);

		}
	}
} 