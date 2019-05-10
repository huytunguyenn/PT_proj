// 5.1c.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define MAX 1000
#define MIN 1
#define MAX_VALUE 10000 // giá trị tối đa của 1 phần tử

void nhapMang(int *&a, int &n)
{
	do {
		printf("Nhap so phan tu mang: ");
		scanf("%d", &n);
		if (!(n >= MIN && n <= MAX))
			printf("Khong hop le.\n");
	} while (!(n >= MIN && n <= MAX));
	a = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) {
		printf("Nhap phan tu thu %d: ", i + 1);
		scanf("%d", a + i);
	}
}
// tìm số phần tử cho mảng b
bool kiemtraNguyenTo(int b)
{
	if (b < 2)
		return false;
	for (int i = 2; i <= sqrt((float)b); i++)
	{
		if (b%i == 0)
			return false;
	}
	return true;
}
int SoPhanTuMang(int *a,int n,int *b)
{
	int m = 0;
	for (int i = 0; i < n; i++) 
	{
		if (kiemtraNguyenTo(*(a + i)) == true)
			m++;
	}
	return m;
}
// chuyển phần tử không là số nguyên tố sang b
void chuyenASangB(int *a,int *b,int n)
{
	int j = 0;
	for (int i = 0; i < n; i++)
	{
		if (kiemtraNguyenTo(*(a + i)) == false)
		{
			*(b + j) = *(a + i);
			j++;
		}
	}
}
//sắp xếp giảm B
void HoanVi(int &c, int &d)
{
	int temp = c;
	c = d;
	d = temp;
}
void sapxepGiamDan(int *b, int m)
{
	int i, j;
	for (i = 0; i < m - 1; i++)
	{
		for (j = i + 1; j < m; j++)
		{
			if (*(b + i) < *(b + j))
				HoanVi(*(b + i), *(b + j));
		}
	}
}
//xoá số nguyên tố trong A
void xoaPhanTu(int *a, int &n, int k)
{
	if ((k < 0) || (k >= n))
		return;
	for (int i = k; i < n - 1; i++)
	{
		*a = *(a + 1);
	}
	--n;
}
void xoaPhanTuNguyenTo(int *a,int n)
{
	for (int i = 0; i < n; i++)
	{
		if (kiemtraNguyenTo(*(a + i)) == true)
		{
			xoaPhanTu(a, n, i);
		}
	}
}


int main()
{
	int *a = NULL;
	int *b = NULL; // cho mảng a,b
	int n;
	nhapMang(a, n);
	int m=SoPhanTuMang(a,n,b);	// m là số phần tử của b cũng là số số không nguyên tố trong A
	chuyenASangB(a, b, n);
	sapxepGiamDan(b, m);
	xoaPhanTuNguyenTo(a, n);
	free(a);
	a = NULL;
	free(b);
	b = NULL;
    return 0;
}

