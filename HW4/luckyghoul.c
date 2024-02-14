#include <stdio.h>
int a[2000005] ={};
int n, q;

int lb(int x){
    int l = 1;
    int r = n+1;
    while(l<r){
        int mid = (l+r)/2;
        if(a[mid] >= x ) r = mid;
        else l = mid + 1;
    }
    if(a[r] == x)
    return r;
    else return -1;

}

int main(){
   
    while(scanf("%d%d", &n, &q) != EOF){
        for(int i = 1; i<=n;i++) scanf("%d", &a[i] );
        while(q--){
            int m;
            scanf("%d", &m);
            if(lb(m) > 0) { 
            printf("%d\n", lb(m));}
            else printf("Break your bridge!\n");
        }
    }
}