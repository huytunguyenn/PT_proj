// 7.3.cpp : Defines the entry point for the console application.
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
void RutGonDayPhanSo(DAYPHANSO &aP)
{
	for (int i = 0; i < aP.N; i++)
	{
		RutGonPhanSo(aP.arrPhanSo[i]);
	}
}
int main()
{
    return 0;
}

