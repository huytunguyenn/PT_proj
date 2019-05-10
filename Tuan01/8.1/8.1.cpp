// 8.1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define PI 3.14
#define MAX_HTRON 1000
struct HinhTron {
	double dX;  // tam X
	double dR;  // ban kinh R
};
struct MANGHINHTRON{
	HinhTron arrHinhTron[MAX_HTRON]; 
	int N;                     
};
void Nhap(HinhTron &P)
{
	printf("Nhap diem tam va ban kinh: ");
	scanf("%lf %lf", &P.dX, &P.dR);
}
void Xuat(const HinhTron P)
{
	printf("%lf, %lf", P.dX, P.dR);
}

void Tinh(HinhTron P)
{
	double chuvi = 2 * PI*P.dR;

	double dientich = PI*P.dR*P.dR;

	printf("Chu vi hinh tron la: %f\n", chuvi);

	printf("Dien tich hinh tron la: %f", dientich);
}
void NhapDayHinhTron(MANGHINHTRON &aP)
{
	printf("Nhap so luong phan so trong day: ");
	scanf("%d", &aP.N);
	for (int i = 0; i < aP.N; i++)
	{
		Nhap(aP.arrHinhTron[i]);
	}
}
void XuatDayPhanSo(const MANGHINHTRON aP)
{
	for (int i = 0; i < aP.N; i++)
	{
		Xuat(aP.arrHinhTron[i]);
	}
}
int main()
{
    return 0;
}

