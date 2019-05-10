// 7.2.cpp : Defines the entry point for the console application.
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
PHANSO Tong(PHANSO a, PHANSO b)
{
	PHANSO tong;
	tong.iTuSo = a.iTuSo*b.iMauSo + b.iTuSo*a.iMauSo;
	tong.iMauSo = a.iMauSo*b.iMauSo;
	RutGonPhanSo(tong);
	return tong;
}
void TongDayPhanSo(DAYPHANSO aP)
{
	PHANSO tong;
	tong.iTuSo = aP.arrPhanSo[0].iTuSo;
	tong.iMauSo = aP.arrPhanSo[0].iMauSo;
	for (int i = 1; i < aP.N; i++)
	{
		tong = Tong(tong, aP.arrPhanSo[i]);
	}
	printf("%d / %d\n", tong.iTuSo, tong.iMauSo);
}
int main()
{
    return 0;
}

