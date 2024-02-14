#include <stdio.h>
#define max(x,y) ((x) > (y) ? (x) : (y))
#define min(x,y) ( (x) < (y) ? (x) : (y))
long long int a[5001]  = {};
int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n, m,  k;
        int ans = 0;
        scanf("%d%d%d", &n,&m,&k);
        k = min(k, m -1);
        for(int i = 0;  i < n;i++){
            scanf("%lld",  &a[i]);
        }
        for(int i = 0; i<= k;i++){
            int atleast = 0x3f3f3f3f;
            for(int j = 0; j<= m - 1 - k;j++){
                atleast = min(max(a[i+j], a[i+j+n-m]),atleast);

            }
            ans = max(atleast, ans);
        }
        printf("%d\n", ans);

    }
}