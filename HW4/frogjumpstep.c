#include <stdio.h>
#include <stdlib.h>
#define min(x,y) ((x) < (y) ? (x) : (y))

int main(){ int cost[100005] = {}; int step[100005] = {};
	int n;
	scanf("%d", &n);
	int a[n];
	for(int i = 0 ; i < n ; i++){
		scanf("%d", &a[i]);
	}
	cost[1] = abs(a[1] - a[0]);
	step[1] = 1;
	int t1, t2;
	for(int i = 2; i< n;i++){
		t1 = cost[i-1] + abs(a[i] - a[i-1]);
		t2 = cost[i-2] + abs(a[i] - a[i-2]);
		if(t1>t2) {cost[i] = t2;
					step[i] = step[i-2] + 1;
		}
		else if(t1<t2) {cost[i] = t1; 
					step[i] = step[i-1] + 1;
		}
		else{
			cost[i] = t1;
			step[i] = min(step[i-2]+1, step[i-1]+1);
			
		}
		
	}
	printf("%d %d\n", cost[n-1], step[n-1]);



}