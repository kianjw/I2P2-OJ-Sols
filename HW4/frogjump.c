#include <stdio.h>
#include <stdlib.h>
#define min(x,y) ((x) < (y) ? (x) : (y))
int main(){
	int n;
	scanf("%d", &n);
	int a[100005] = {};
	for(int i = 0;i<n;i++) scanf("%d", &a[i]);
	int cost[10005] = {};
	cost[1] = abs(a[1] - a[0]); 
    int t1, t2;
	int step[10005] = {};
	step[1] = 1;
	for(int i = 2; i<n;i++){
		t1 = cost[i-1] +  abs(a[i] - a[i-1]);
		t2 = cost[i-2] + abs(a[i] - a[i-2]);
		if(t1<t2) {  cost[i] = t1; 
			step[i] = step[i-1] +1;
		}
		else if(t2<t1) {   cost[i] = t2;
		step[i] = step[i-2] + 1;
		}
		else {
			step[i] = min(step[i-2]+1, step[i-1]+1);
		}
	}

	printf("%d %d\n", step[n-1], cost[n-1]);
}