// 5.1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define MAX 10000
#define MIN 1


// nhập mảng 1 chiều a
void nhapMang(int *&a, int &n)
{
	do {
		printf("Nhap so phan tu mang: ");
		scanf("%d", &n);
		if (!(n >= MIN && n <= MAX))
			printf("Khong hop le.\n");
	} while (!(n >= MIN && n <= MAX));
	a = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++){
		printf("Nhap phan tu thu %d: ", i + 1);
		scanf("%d", a + i);
	}
}


// tìm trong mảng a các ước số của X
void xuatMangUocSo(int *a, int n, int &x, int &dem)
{
	printf("Nhap so X: ");
	scanf("%d", &x);
	printf("Uoc so cua X:\n");
	for (int i = 0; i < n; i++) {
		if (x % *(a + i) == 0)
		{
			printf("Phan tu thu %d: %d\n", i + 1, *(a + i));
			dem++;
		}
	}
}


// dồn phần tử về cuối mảng và sắp xếp các phần tử còn lại

// xoá phần tử tại vị trí k
void xoaPhanTuK(int *a, int &n, int k)
{
	if ((k < 0) || (k >= n))
		return;
	for (int i = k; i < n - 1; i++)
	{
		*a = *(a + 1);
	}
	--n;
}
void donUocSo(int *a,int n,int x, int dem)
{
	// thêm dem phần tử nguyên tố
	a = (int*)realloc(a, n-1+dem);
	int j = n - 1;
	for (int i = 0; i < n; i++) {
		if (x % *(a + i) == 0)
		{
			*(a + j) = *(a + i); 
			j++; // dời về cuối mảng
			xoaPhanTuK(a, n, i);
		}
	}
}
// sắp xếp tăng dần 
void HoanVi(int &c, int &d)
{
	int temp = c;
	c = d;
	d = temp;
}
void sapxepTangDan(int *a, int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (*(a + i) > *(a + j))
				HoanVi(*(a + i), *(a + j));
		}
	}
}

int main(int argc, char *argv[])
{
	int *a = NULL, n;
	int x, dem=0;// dem là số ước số X trong mảng
	nhapMang(a, n);
	xuatMangUocSo(a, n, x,dem);
	donUocSo(a, n, x, dem);
	sapxepTangDan(a, n);
	free(a);
	a = NULL;
	return 0;
}

