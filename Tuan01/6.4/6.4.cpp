// 6.4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define MAX_PSO 100
struct PHANSO {
	int iTuSo;
	int iMauSo;
};
int UCLN(int a, int b)
{
	a = (a > 0) ? a : -a;
	b = (b > 0) ? b : -b;
	while (a != b)
	{
		(a > b) ? a -= b : b -= a;
	}
	return a;
}
void RutGonPhanSo(PHANSO *&P)
{
	int ucln;
	ucln = UCLN(P->iMauSo, P->iTuSo);
	P->iMauSo /= ucln;
	P->iTuSo /= ucln;
}
int SoSanhPhanSo(PHANSO *P, PHANSO*Q)
{
	RutGonPhanSo(P);
	RutGonPhanSo(Q);
	if (float(P->iTuSo) / float(P->iMauSo) > float(Q->iTuSo) / float(Q->iMauSo))
	{
		printf("Phan so thu nhat lon hon phan so thu hai.\n");
		return 1;
	}
	else if (float(P->iTuSo) / float(P->iMauSo) == float(Q->iTuSo) / float(Q->iMauSo))
	{
		printf("Phan so thu hai bang phan so thu nhat.\n");
		return 0;
	}
	else
	{
		printf("Phan so thu nhat nho hon phan so thu hai.\n");
		return -1;
	}
}
int main()
{
	PHANSO a;
	PHANSO *pa = &a;
	PHANSO b;
	PHANSO *pb = &b;
	SoSanhPhanSo(pa, pb);
    return 0;
}

