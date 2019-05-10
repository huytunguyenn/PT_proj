// 7.4.cpp : Defines the entry point for the console application.
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
void SapXepDayPhanSo(DAYPHANSO &aP)
{
	for (int i = 0; i < aP.N - 1; i++)
	{
		for (int j = i + 1; j < aP.N; j++)
		{
			if ((float)aP.arrPhanSo[i].iTuSo / aP.arrPhanSo[i].iMauSo >(float)aP.arrPhanSo[j].iTuSo / aP.arrPhanSo[j].iMauSo)
			{
				PHANSO temp;
				temp = aP.arrPhanSo[i];
				aP.arrPhanSo[i] = aP.arrPhanSo[j];
				aP.arrPhanSo[j] = temp;
			}
		}
	}

}
int main()
{
    return 0;
}

