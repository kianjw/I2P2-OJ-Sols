#include <stdio.h>
int main(){
	int t;
	while(scanf("%d", &t) != EOF){
		int a[10] = {};
		int b[10] = {};
		int count = 0;
		for(int i = 0 ; i<t;i++) scanf("%d", &a[i]);
		for(int i = 0; i<t;i++) scanf("%d", &b[i]);
		for(int i = 0;i<t-1;i++){
			for(int j = 1; j<t;j++){
				if(a[i] == b[j]){
					if(a[i+1] == b[j-1])
					count  = (count== 0 ? 2 : count*2);
				}
			}
		}
        if(count ==0) printf("1\n");
		else printf("%d\n", count);
	}
}