// 7.1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define MAX_PSO 100
struct PHANSO {
	int iTuSo;
	int iMauSo;
};
struct DAYPHANSO {
	PHANSO arrPhanSo[MAX_PSO]; //mang luu day phan so
	int N;                     // so luong phan so trong mang
};
void NhapPhanSo(PHANSO &P, int i)
{
	do {
		printf("Nhap phan so thu %d:\n", i);
		scanf("%d %d", &P.iTuSo, &P.iMauSo);
		if (P.iMauSo == 0)
		{
			printf("Mau so khong hop le. Vui long nhap lai!\n");
		}
		else if (P.iMauSo < 0 && P.iTuSo < 0)
		{
			P.iMauSo = -P.iMauSo;
			P.iTuSo = -P.iTuSo;
		}
		else if (P.iMauSo < 0 && P.iTuSo > 0)
		{
			P.iMauSo = -P.iMauSo;
			P.iTuSo = -P.iTuSo;
		}
	} while (P.iMauSo == 0);
}
void XuatPhanSo(const PHANSO P)
{
	printf("%d / %d\n", P.iTuSo, P.iMauSo);
}

void NhapDayPhanSo(DAYPHANSO &aP)
{
	printf("Nhap so luong phan so trong day: ");
	scanf("%d", &aP.N);
	for (int i = 0; i < aP.N; i++)
	{
		NhapPhanSo(aP.arrPhanSo[i], i + 1); // khong dung aP->arrPhanSo[i]) duoc???
	}
}
		
void XuatDayPhanSo(const DAYPHANSO aP)
{
	for (int i = 0; i < aP.N; i++)
	{
		XuatPhanSo(aP.arrPhanSo[i]);
	}
}
int main()
{
    return 0;
}

