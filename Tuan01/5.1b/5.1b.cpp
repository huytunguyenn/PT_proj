// 5.1b.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define MAX 15
#define MIN 1
#define MAX_VALUE 10000 // giá trị tối đa của 1 phần tử

// nhập mảng 1 chiều nguyên dương a
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
		if (*(a+i) <0)
		{
			printf("Vui long nhap so nguyen duong.\n");
			i--;
		}
	}
}

//đếm số phần tử tận cùng bằng 6 và chia hết cho 6
int demPhanTu6(int *a,int n)
{
	int dem = 0;
	for (int i = 0; i < n; i++)
	{
		if ((*(a + i) % 10 == 6) && (*(a + i) % 6 == 0))
			dem++;
	}
	return dem;
}

// trung bình cộng các số trong mảng
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
float trungbinhcongNguyenTo(int *a, int n)
{
	int tong = 0;
	int dem = 0;
	for (int i = 0; i < n; i++)
	{
		if (kiemtraNguyenTo(*(a + i)) == true)
		{
			tong += *(a + i);
			dem++;
		}
	}
	return (float)tong / dem;
}

// đếm số loại số nguyên tố
int demNguyenToPhanBiet(int *a, int n)
{
	int *b; // tạo mảng b = 0
	int dem = 0;
	b = (int*)malloc(sizeof(int*)*MAX_VALUE);
	b[n] = {};
	for (int i = 0; i < n; i++)
	{
		if(kiemtraNguyenTo(*(a+i))==true)
		b[*(a + i)]++;
	}
	for (int i = 0; i < n; i++)
	{
		if (b[*(a+i)]!=0)
			dem++;
	}
	return dem;
}


int main(int argc, char *argv[])
{
	int *a = NULL;
	int n;
	nhapMang(a, n);
	printf("So phan tu tan cung bang 6 va chia het cho 6: %d", demPhanTu6(a,n));
	printf("Trung binh cong cac so nguyen to trong mang la: %f ",trungbinhcongNguyenTo(a,n));
	printf("Trong mang co %d so nguyen to phan biet",demNguyenToPhanBiet(a,n));
	free(a);
	a = NULL;
    return 0;
}

