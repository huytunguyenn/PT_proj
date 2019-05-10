// 6.1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define MAX_PSO 100
struct PHANSO {
	int iTuSo;
	int iMauSo;
};
void NhapPhanSo(PHANSO *P)
{
	do {
		printf("Nhap phan so:\n");
		scanf("%d %d", &P->iTuSo, &P->iMauSo);
		if (P->iMauSo == 0)
		{
			printf("Mau so khong hop le. Vui long nhap lai!\n");
		}
		else if (P->iMauSo < 0 && P->iTuSo < 0)
		{
			P->iMauSo = -P->iMauSo;
			P->iTuSo = -P->iTuSo;
		}
		else if (P->iMauSo < 0 && P->iTuSo > 0)
		{
			P->iMauSo = -P->iMauSo;
			P->iTuSo = -P->iTuSo;
		}
	} while (P->iMauSo == 0);
}
void XuatPhanSo(const PHANSO *P)
{
	printf("%d / %d\n", P->iTuSo, P->iMauSo);
}


int main()
{
	PHANSO a;
	PHANSO *pa = &a;
	NhapPhanSo(pa);
	XuatPhanSo(pa);
    return 0;
}

