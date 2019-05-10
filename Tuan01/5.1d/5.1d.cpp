// 5.1d.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define MAX 25
#define MIN 1

// nhập mảng 1 chiều nguyên 
void nhapMang(int *&a, int &n)
{
	do {
		printf("Nhap so phan tu mang: ");
		scanf("%d", &n);
		if (!(n >= MIN && n <= MAX))
			printf("Khong hop le.\n");
	} while (!(n >= MIN && n <= MAX));
	a = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++)
	{
		printf("Nhap phan tu thu %d: ", i + 1);
		scanf("%d", a + i);
	}
}
// xuất mảng 1 chiều nguyên 
void xuatMang(int *a, int n)
{
	for (int i = 0; i < n; i++) 
	{
		printf("Phan tu thu %d: %d\n", i + 1, *(a + i));
		
	}
}
// xuất ra phần tử có trong A mà không có trong B 
void xuatPhanTuTrung(int *a, int *b, int n, int m)
{
	int i, j, dem = 0;
	for (i = 0; i<n; i++)
	{
		for (j = 0; j < m; j++)
		{
			if (*(a + i) == *(b + j))
				break;
			if (j >= m)// j=m+1??
			{
				printf("%d\n", *(a + i));
				dem++;
			}
		}
	}
	if (dem == 0)
		printf("Moi phan tu cua A deu co trong B.\n");
}
// ghép A và B thành C sao cho C không có phần tử trùng

// ghép A, B vào C
void ghepMang(int *a, int *b, int*c, int n, int m, int &k) 
{
	//đưa mảng A vào đầu mảng C
	for (int i = 0; i < n; i++)
	{
		*(c+i) = *(a+i);
		k++; 
	}
	// đưa mảng B vào tiếp 
	for (int i = 0; i < m; i++)
	{
		*(c+n+i) = *(b+i);
		k++; 
	}
}
//sắp xếp tăng C
void HoanVi(int &c, int &d)
{
	int temp = c;
	c = d;
	d = temp;
}
void sapxepTangDan(int *c, int k)
{
	int i, j;
	for (i = 0; i < k - 1; i++)
	{
		for (j = i + 1; j < k; j++)
		{
			if (*(c + i) > *(c + j))
				HoanVi(*(c + i), *(c + j));
		}
	}
}
//Nếu C[i] số bằng 1 số cạnh nó thì kéo cả dãy tiến lên từ vị trí đó, và giảm k đi 1
void ghepMangKhongTrung(int *c, int &k) 
{
	for (int i = 0; i < k; i++)
	{
		if (*(c + i) == *(c + i + 1))
		{
			for (int j = i; j < k; j++)
			{
				*(c + j) = *(c + j + 1);
				k--;
			}
		}
	}
}


int main()
{
	int *a = NULL;
	int n;
	int *b = NULL;
	int m;
	nhapMang(a,n);
	nhapMang(b,m);
	xuatPhanTuTrung(a, b, n, m);
	int *c = NULL;
	int k = 0; //kich thước C khi hợp cả A và B
	ghepMang(a, b, c, n, m, k);
	sapxepTangDan(c, k);
	ghepMangKhongTrung(c,k);
	free(a);
	a = NULL;
	free(b);
	b = NULL;
	free(c);
	c = NULL;
    return 0;
}



