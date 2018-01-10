#include <stdio.h>

#define MAX_NUM 80

void quicksort(int* a, int p,int q)
{
    int i = p;
    int j = q;
    int temp = a[p];
    
    while(i < j)
    {
        // 越过不小于基准值的数据 
        while( a[j] >= temp && j > i ) j--;
        
        if( j > i )
        {
            a[i] = a[j];
            i++;
            
            // 越过小于基准值的数据 
            while(a[i] <= temp && i < j )  i++;
            if( i < j )
            {
                a[j] = a[i];
                j--;
            }
        }        
    }
    a[i] = temp; 
    
    for(int k = p; k <= q;k++)
    {
        if( k == i ) 
        {
            printf("(%d) ",a[k]);
            continue;
        }
        printf("%d ",a[k]);
    } 
    printf("\n");
    
    if( p < (i-1)) quicksort(a,p,i-1);
    if((j+1) < q ) quicksort(a,j+1,q);    
}

int main(int argc, char* argv[])
{
    int a[MAX_NUM];
    int n;    

    printf("Input total numbers: ");
    scanf("%d",&n);

    if( n > MAX_NUM ) n = MAX_NUM;
    
    for(int i = 0; i < n;i++)
    {
        scanf("%d",&a[i]);
    }
    
    printf("Divide sequence:\n");
    quicksort(a,0,n-1);
    
    printf("The sorted result:\n");
    for(int i = 0; i < n;i++)
    {
        printf("%d ",a[i]);
    } 
    printf("\n");
    
    return 0;
}