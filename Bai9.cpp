#include <stdio.h>
 
void NhapMang(int a[], int n){
    for(int i = 0; i < n; i++){
        printf("\nNhap a[%d] = ",i);
        scanf("%d", &a[i]);
    }
}
 
void XuatMang(int a[], int n){
    for(int i = 0; i < n; i++){
        printf("%5d", a[i]);
    }
}
 
void HoanDoi(int &a, int &b){
    int temp =a;
    a=b;
    b=temp;
}

void TangDan(int a[], int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            if(a[i] > a[j]){ 
                HoanDoi(a[i],a[j]);     
            }
        }
    }
}
 
void GiamDan(int a[], int n){
    int tg;
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            if(a[i] < a[j]){         
                HoanDoi(a[i],a[j]);       
            }
        }
    }
}
 
int main(){
    int a[100];
    int n;
    printf("\nNhap so luong phan tu n = ");
    do{
        scanf("%d", &n);
        if(n <= 0){
            printf("\nNhap lai n = ");
        }
    }while(n <= 0);
    
    NhapMang(a, n);
    printf("\nMang vua nhap la: ");
    XuatMang(a, n);
    
    // Xep tang dan:
    TangDan(a, n);
    printf("\nMang xep tang dan la: ");
    XuatMang(a, n);
    
    // Xep giam dan:
    GiamDan(a, n);
    printf("\nMang xep giam dan la: ");
    XuatMang(a, n);
    
}