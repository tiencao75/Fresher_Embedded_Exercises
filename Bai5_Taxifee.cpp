#include <stdio.h>

void taxifee(float so_km ){
    const int NGUONG_1(1);
	const int NGUONG_2(31);
	const int GIA_1(5000);
	const int GIA_2(4000);
	const int GIA_3(6000);
    float tong;
    if (so_km <= NGUONG_1){
        printf("Tien cuoc la: %0.3f\n", tong = so_km *GIA_1);
    }
    else if (((NGUONG_1 < so_km) and (so_km < NGUONG_2)))
    {
        printf("Tien cuoc la: %0.3f\n", tong = GIA_1*NGUONG_1 + (so_km - NGUONG_1)*GIA_2);
    }
    else
    {
        printf("Tien cuoc la: %0.3f\n",tong = GIA_1*NGUONG_1 + GIA_2*(NGUONG_2 - NGUONG_1) + (so_km - NGUONG_2)*GIA_3);
    }
     
}

int main(int argc, char const *argv[])
{
taxifee(0.5);
    return 0;
}
