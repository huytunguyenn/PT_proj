// 5.2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define MAX_VALUE 10000
void capphatMang2Chieu(int **&a, int m, int n)
{
	a = new int*[m];	// a là con trỏ cấp 2->quản lý con trỏ câp 1
	for (int i = 0; i < m; i++)
	{
		*(a + i) = new int[n]; // thêm dấu * là giảm 1 cấp cho con trỏ
	}
}
void thuhoiMang2Chieu(int **&a, int m)
{
	for (int i = 0; i < m; i++)
	{
		delete[] a[i];	//thu hồi các cột của dòng
	}
	delete[] a;		//thu hồi tất cả các dòng
	a = NULL;
}
void nhapMang(int **a, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("Nhap phan tu [%d][%d]: ", i, j);
			scanf("%d", *(a + i) + j);
		}
	}
}
void xuatMang(int **a, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("[%d][%d] = %d\t", i, j, *(*(a + i) + j)); // a[i][j]
		}
		printf("\n");
	}
}
// tính tổng dương 
int tinhTongDuong(int **a, int m, int n)
{
	int tong = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (*(*(a + i) + j) >= 0)
				tong += *(*(a + i) + j);
		}
	}
	return tong;
}
// đếm số lượng số nguyên tố
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
int demSNT(int **a, int m, int n)
{
	int dem = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (kiemtraNguyenTo(*(*(a + i) + j)) == true)
				dem++;
		}
	}
	return dem;
}
// tìm số lớn nhất trên biên ma trận
int timMaxTrenBien(int **a, int m, int n)
{
	int max = a[0][0];
	for (int j = 0; j < n; j++)
	{
		if (a[0][j] >= max)
			max = a[0][j];
	}
	for (int j = 0; j < n; j++)
	{
		if (a[m - 1][j] >= max)
			max = a[m - 1][j];
	}
	for (int i = 0; i < m; i++)
	{
		if (a[i][0] >= max)
			max = a[i][0];
	}
	for (int i = 0; i < m; i++)
	{
		if (a[i][n - 1] >= max)
			max = a[i][n - 1];
	}
	return max;
}
// tìm số dương nhỏ nhất trong ma trận
int timMinDuong(int **a, int m, int n)
{
	int min;
	// tìm số dương đầu tiên
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] > 0)
			{
				min = a[i][j];
				break;
			}
		}
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] > 0 && a[i][j] <= min)
				min = a[i][j];
		}
	}
	return min;
}
// liệt kê dòng chứa giá trị âm trong ma trận
void lietkeDongAm(int **a, int m, int n)
{
	bool check = false;
	printf("Cac dong chua gia tri am:\n");
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] < 0)
			{
				printf("Dong %d.\n", i + 1);
				check = true;
				break;
			}
		}
	}
	if (check == false)
		printf("Khong co dong nao chua gia tri am.\n");
}
//liệt kê dòng chứa toàn bộ số chẵn
void lietkeDongToanChan(int **a, int m, int n)
{
	bool check = false;
	bool temp = true;
	printf("Cac dong chua toan bo so chan:\n");
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] % 2 != 0)
			{
				temp = false;
				break;
			}
		}
		if (temp == true)
		{
			printf("Dong %d\n", i + 1);
			check = true;
		}
	}
	if (check == false)
		printf("Khong co dong nao toan bo chan.\n");
}
// đếm phần tử yên ngựa
 //ìm min cột j
int timMinCot(int **a, int j, int m)
{
	int min = a[0][j];
	for (int i = 0; i < m; i++)
	{
		if (a[i][j] <= min)
			min = a[m][i];
	}
	return min;
}
// tìm max dòng i
int timMaxDong(int **a, int i, int n)
{
	int max = a[i][0];
	for (int j = 0; j < n; j++)
		if (a[i][j] >= max)
			max = a[i][j];
	return max;
}
void timYenNgua(int **a, int m, int n)
{
	bool check = false;
	int dem = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] == timMinCot(a, j, m) && a[i][j] == timMaxDong(a, i, n)) //tìm cột check dòng, tìm dòng check cột
			{
				dem++;
				check = true;
			}
		}
	}
	if (check == true)
		printf("Tong so diem yen ngua: %d\n", dem);
	else
		printf("Khong co diem yen ngua.\n");
}

//đếm phần tử hoàng hậu
// tìm max cột j
int timMaxCot(int **a, int j, int m)
{
	int max = a[0][j];
	for (int i = 0; i < m; i++)
	{
		if (a[i][j] >= max)
			max = a[m][i];
	}
	return max;
}
//tìm max đường chéo chính
int timMaxDCTrai(int **a, int i, int j, int m, int n)
{
	return 1;
}
// tìm max đường chéo phụ
int timMaxDCPhai(int **a, int i, int j, int m, int n)
{
	return 1;
}
void timHoangHau(int **a, int m, int n)
{
	bool check = false;
	int dem = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] == timMaxCot(a, j, m) && a[i][j] == timMaxDong(a, i, n) && a[i][j] == timMaxDCTrai(a, i, j, m, n) && a[i][j] == timMaxDCPhai(a, i, j, m, n))
			{
				dem++;
				check = true;
			}
		}
	}
	if (check == true)
		printf("Tong so diem hoang hau: %d\n", dem);
	else
		printf("Khong co diem hoang hau.\n");
}
//tính tổng các phần tử cực trị
int tongCucTri(int **a, int m, int n)
{
	int tong = 0;
	for (int i = 1; i < m - 1; i++)
	{
		for (int j = 1; j < n - 1; j++)
		{
			if (((a[i][j] > a[i + 1][j + 1]) && (a[i][j] > a[i - 1][j - 1])) || ((a[i][j] < a[i + 1][j + 1]) && (a[i][j] < a[i - 1][j - 1])))
				tong += a[i][j];
		}
	}
	return tong;
}
//tìm chữ số xuất hiện nhiều nhất trong ma trận
void timSoXuatHienNhieuNhat(int **a, int m, int n)
{
	int *b; // tạo mảng b = 0
	b = new int[MAX_VALUE];
	b[n] = {};
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; i < n; i++)
		{
			b[a[i][j]]++;
		}
	}
	// tìm max trong mảng b
	int max = b[0];
	for (int i = 0; i < MAX_VALUE - 1; i++)
	{
		if (b[i] >= max)
			max = i;
	}
	printf("So xuat hien nhieu nhat: %d", max);
}
// sắp xếp biên ma trận tăng dần theo chiều kim đồng hồ
//

int main()
{
	int **a = NULL;
	int m, n;
	do {
		printf("Nhap so dong, so cot:\n");
		scanf("%d%d", &m, &n);
		if (n < 0 || m < 0)
			printf("Nhap lai.\n");
	} while (n < 0 || m < 0);
	capphatMang2Chieu(a, m, n);
	nhapMang(a, m, n);
	xuatMang(a, m, n);
	printf("Tong cac phan tu duong trong ma tran: %d\n", tinhTongDuong(a, m, n));
	printf("So so nguyen to trong ma tran: %d\n", demSNT(a, m, n));
	printf("So lon nhat tren bien ma tran: %d\n", timMaxTrenBien(a, m, n));
	printf("So duong nho nhat trong ma tran: %d\n", timMinDuong(a, m, n));
	lietkeDongAm(a, m, n);
	lietkeDongToanChan(a, m, n);
	timYenNgua(a, m, n);
	printf("Tong cac phan tu cuc tri trong ma tran: %d\n", tongCucTri(a, m, n));
	timSoXuatHienNhieuNhat(a,m,n);
	thuhoiMang2Chieu(a, m);
	return 0;
}

