#include <stdio.h>

void Nhap(int a[], int &n){
    printf("\nNhap n=");
    scanf("%d",&n);
    for(int i = 0; i < n; i++){
        printf("\nNhap a[%d] = ",i+1);
        scanf("%d", &a[i]);
    }
}
 
void Xuli(int a[], int b[], int n){
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if ( a[j]== a[i]) b[i]++;
        }
        
    }
    
}

void Xuat(int a[], int b[], int n){
    int max = 1;
    for (int i = 0; i < n; i++)
    {
        if( b[i] > max) max = b[i];
    }
    
    for (int i = 0; i < n; i++)
    {
        if( b[i] == max)
            printf("Phan tu xuat hien nhieu nhat la %d", a[i]);
    }
    
}
int main(int argc, char const *argv[])
{
    int a[100], b[100] = {0};
    int n;
    Nhap(a,n);
    Xuli(a,b,n);
    Xuat(a,b,n);
    return 0;
}

