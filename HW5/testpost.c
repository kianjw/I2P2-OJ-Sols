#include <stdio.h>

int main(){
	int n;
    while(scanf("%d", &n) != EOF){
        if(n == 1){
        	printf("1\n");
        	continue;
        }
    	int pre[10], post[10];
        for(int i = 0; i < n; ++i) scanf("%d", &pre[i]);
    	for(int i = 0; i < n; ++i) scanf("%d", &post[i]);
        int ans = 0;
        for(int i = 0; i < n-1; ++i){
        	for(int j = 1; j < n; ++j){
            	if(pre[i] == post[j] && pre[i+1] == post[j-1]){
                	ans = (ans == 0 ? 2: ans*2);
                }
            }
        }
        printf("%d\n", ans);
    }

}