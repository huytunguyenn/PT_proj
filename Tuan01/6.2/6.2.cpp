// 6.2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define MAX_PSO 100
struct PHANSO {
	int iTuSo;
	int iMauSo;
};
PHANSO *Tong(PHANSO *a, PHANSO *b)
{
	PHANSO *tong;
	tong->iTuSo = a->iTuSo*b->iMauSo + b->iTuSo*a->iMauSo;
	tong->iMauSo = a->iMauSo*b->iMauSo;
	return tong;
	
}
void Hieu(PHANSO *a, PHANSO *b)
{
	PHANSO *hieu;
	hieu->iTuSo = a->iTuSo*b->iMauSo - b->iTuSo*a->iMauSo;
	hieu->iMauSo = a->iMauSo*b->iMauSo;
	printf("Hieu hai phan so:\n%d / %d\n", hieu->iTuSo, hieu->iMauSo);
}
void Tich(PHANSO *a, PHANSO *b)
{
	PHANSO *tich;
	tich->iTuSo = a->iTuSo*b->iTuSo;
	tich->iMauSo = a->iMauSo*b->iMauSo;
	printf("Tich hai phan so:\n%d / %d\n", tich->iTuSo, tich->iMauSo);
}
void Thuong(PHANSO *a, PHANSO *b)
{
	PHANSO *thuong;
	thuong->iTuSo = a->iTuSo*b->iMauSo;
	thuong->iMauSo = a->iMauSo*b->iTuSo;
	printf("Thuong hai phan so:\n%d / %d\n", thuong->iTuSo, thuong->iMauSo);
}

int main()
{
	PHANSO a;
	PHANSO *pa = &a;
	PHANSO b;
	PHANSO *pb = &b;
	PHANSO *tong = Tong(pa, pb);
	printf("Tong hai phan so:\n%d / %d\n", tong->iTuSo, tong->iMauSo);
	Hieu(pa, pb);
	Tich(pa, pb);
	Thuong(pa, pb);
    return 0;
}

