// 7.5.cpp : Defines the entry point for the console application.
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
void RutGonPhanSo(PHANSO &P)
{
	int ucln;
	ucln = UCLN(P.iMauSo, P.iTuSo);
	P.iMauSo /= ucln;
	P.iTuSo /= ucln;
}
int TimPhanSo(DAYPHANSO aP, PHANSO c)
{
	RutGonPhanSo(c);
	for (int i = 0; i < aP.N; i++)
	{
		RutGonPhanSo(aP.arrPhanSo[i]);
		if (aP.arrPhanSo[i].iTuSo == c.iTuSo && aP.arrPhanSo[i].iMauSo == c.iMauSo)
		{
			return 1;
		}
	}
	return 0;// ko co else return 0 vi se pha vong for
}
int main()
{
    return 0;
}

