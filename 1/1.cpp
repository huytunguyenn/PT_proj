// 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define MAX_PASS 25 
//biến toàn cục
char passAdmin[20] = { "admin" };
char passQuanLy[20] = { "quanly" };
char passChuyenVien[20] = { "chuyenvien" };


void ChangePass()
{
}
void UpadateInfo()
{
}
void CreateUser(/*DATABASE &data, USER *p*/)
{
	/*if (strcmp(it.Acc.sUsername, user.Acc.sUsername) == 0)*/

}
void Authority()
{

}
// dùng để trang trí, chạy hiệu ứng
void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void Login(int &luachon)
{
	system("cls");
	char ch, pass[MAX_PASS];
	gotoxy(10, 4); printf("Ten dang nhap: ");
	//ch = _getch();
	gotoxy(10, 5); printf("Password:\n");
	// mã hóa mật khẩu
	gotoxy(19, 5);
	int p = 0;
	do {
		pass[p] = _getch();
		if (pass[p] != '\r')
		{
			printf("*");
		}
		p++;
	} while (pass[p - 1] != '\r');
	pass[p - 1] = '\0';
	if (strcmp(pass, passAdmin) == 0)
	{
		gotoxy(15, 9); printf("Ban da dang nhap duoi quyen admin.\n");
	}
	else if (strcmp(pass, passChuyenVien) == 0)
	{
		gotoxy(15, 9); printf("Ban da dang nhap duoi quyen chuyen vien.\n");
	}
	else if (strcmp(pass, passQuanLy) == 0)
	{
		gotoxy(15, 9); printf("Ban da dang nhap duoi quyen quan ly.\n");
	}
	else
	{
		gotoxy(8, 8); printf("\aDang nhap khong thanh cong!");
		gotoxy(8, 9); printf("Quay lai menu chinh? (1 la co, 0 la khong):");
		scanf("%d", &luachon);

		if (luachon == 1)
		{
			system("cls");
			// in lại nhưng không có hiệu ứng
			char d[26] = "He Thong Quan Ly Thu Vien";
			gotoxy(10, 4);
			for (int j = 0; j < 20; j++)
			{
				printf(":");
			}
			for (int j = 0; j < 25; j++)
			{
				printf("%c", d[j]);
			}
			for (int j = 0; j < 20; j++)
			{
				printf(":");
			}
		}
		else
		{
			Login(luachon);
		}
	}
}

void menu() //đăng nhập
{
	int luachon = 0; // nếu người dùng muốn quay lại: 1=có,0=ko
	char d[26] = "He Thong Quan Ly Thu Vien";
	system("cls");
	// in chuyển động 
	gotoxy(10, 4);
	for (int j = 0; j < 20; j++)
	{
		Sleep(50);
		printf(":");
	}
	for (int j = 0; j < 25; j++)
	{
		Sleep(50);
		printf("%c", d[j]);
	}
	for (int j = 0; j < 20; j++)
	{
		Sleep(50);
		printf(":");
	}
	do {
		gotoxy(20, 7); printf("\t1.Dang nhap");
		gotoxy(20, 9); printf("\t2.Thoat chuong trinh");
		gotoxy(20, 11); printf("Lua chon cua ban:");
		switch (_getch())
		{
		case '1':
			Login(luachon);
			break;
		case '2':
		{
			system("cls");
			gotoxy(20, 11); printf("Thoat trong 3 giay nua");
			for (int j = 0; j < 60; j++)
			{
				Sleep(50);
				printf(".");
			}
			system("cls");
			exit(0);
		}
		default:
		{
			gotoxy(20, 24); printf("\aChon sai, vui long chon lai!");
			if (_getch())
				menu();
		}
		}
	} while (luachon == 1);
}

//void MainMenuQuanLy()
//{
//
//	system("cls");
//	int i;
//	gotoxy(20, 3);
//	printf("\xB2\xB2\xB2\xB2\xB2\xB2 HE THONG QUAN LY THU VIEN \xB2\xB2\xB2\xB2\xB2\xB2");
//	gotoxy(20, 5);
//	printf("\xB2\xB2\xB2\ 1. Dang nhap   ");
//	gotoxy(20, 7);
//	printf("\xB2\xB2\xB2\ 2. Dang xuat   ");
//	gotoxy(20, 9);
//	printf("\xB2\xB2\xB2\ 3. Thay doi mat khau");
//	gotoxy(20, 11);
//	printf("\xB2\xB2\xB2\ 4. Cap nhat thong tin ca nhan");
//	gotoxy(20, 13);
//	printf("\xB2\xB2\xB2\ 5. View Books List");
//	gotoxy(20, 15);
//	printf("\xB2\xB2\xB2\ 6. Edit Book's Record");
//	gotoxy(20, 17);
//	printf("\xB2\xB2\xB2\ 7. Close Application");
//	gotoxy(20, 19);
//	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
//	gotoxy(20, 20);
//
//	gotoxy(20, 21);
//	printf("Lua chon cua ban:");
//	switch (_getch())
//	{
//	case '1':
//		login();
//		break;
//	case '2':
//		logout();
//		break;
//	case '3':
//
//		break;
//	case '4':
//
//		break;
//	case '5':
//
//		break;
//	case '6':
//
//		break;
//	case '7':
//	{
//		system("cls");
//		gotoxy(16, 3);
//		printf("\tHe thong quan ly thu vien");
//		gotoxy(16, 7);
//		printf("\tDo an Ky Thuat Lap Trinh");
//		gotoxy(16, 9);
//		printf("\t18120254 - 18120267");
//		gotoxy(16, 11);
//		printf("\t::::::::::::::::::::::::::::");
//		gotoxy(16, 13);
//		printf("\t::::::::::::::::::::::::::::");
//		gotoxy(16, 15);
//		printf("Thoat trong 3 giay nua...........>");
//		Sleep(3000); // sleep three seconds
//		system("cls");
//		exit(0);
//	}
//	default:
//	{
//		gotoxy(10, 23);
//		printf("\aChon sai, vui long chon lai!");
//		if (_getch())
//			MainMenuQuanLy();
//	}
//	}
//}
//void MainMenuChuyenVien()
//{
//
//	system("cls");
//	int i;
//	gotoxy(20, 3);
//	printf("\xB2\xB2\xB2\xB2\xB2\xB2 HE THONG QUAN LY THU VIEN \xB2\xB2\xB2\xB2\xB2\xB2");
//	gotoxy(20, 5);
//	printf("\xB2\xB2\xB2\ 1. Dang nhap   ");
//	gotoxy(20, 7);
//	printf("\xB2\xB2\xB2\ 2. Dang xuat   ");
//	gotoxy(20, 9);
//	printf("\xB2\xB2\xB2\ 3. Thay doi mat khau");
//	gotoxy(20, 11);
//	printf("\xB2\xB2\xB2\ 4. Cap nhat thong tin ca nhan");
//	gotoxy(20, 13);
//	printf("\xB2\xB2\xB2\ 5. View Books List");
//	gotoxy(20, 15);
//	printf("\xB2\xB2\xB2\ 6. Edit Book's Record");
//	gotoxy(20, 17);
//	printf("\xB2\xB2\xB2\ 7. Close Application");
//	gotoxy(20, 19);
//	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
//	gotoxy(20, 20);
//
//	gotoxy(20, 21);
//	printf("Lua chon cua ban:");
//	switch (_getch())
//	{
//	case '1':
//		login();
//		break;
//	case '2':
//		logout();
//		break;
//	case '3':
//
//		break;
//	case '4':
//
//		break;
//	case '5':
//
//		break;
//	case '6':
//
//		break;
//	case '7':
//	{
//		system("cls");
//		gotoxy(16, 3);
//		printf("\tHe thong quan ly thu vien");
//		gotoxy(16, 7);
//		printf("\tDo an Ky Thuat Lap Trinh");
//		gotoxy(16, 9);
//		printf("\t18120254 - 18120267");
//		gotoxy(16, 11);
//		printf("\t::::::::::::::::::::::::::::");
//		gotoxy(16, 13);
//		printf("\t::::::::::::::::::::::::::::");
//		gotoxy(16, 15);
//		printf("Thoat trong 3 giay nua...........>");
//		Sleep(3000); // sleep three seconds
//		system("cls");
//		exit(0);
//	}
//	default:
//	{
//		gotoxy(10, 23);
//		printf("\aChon sai, vui long chon lai!");
//		if (_getch())
//			MainMenuChuyenVien();
//	}
//	}
//}

//void MenuAdmin()
//{
//
//	system("cls");
//	int i;
//	gotoxy(20, 3);
//	printf("\xB2\xB2\xB2\xB2\xB2\xB2 HE THONG QUAN LY THU VIEN \xB2\xB2\xB2\xB2\xB2\xB2");
//	gotoxy(20, 5);
//	printf("\xB2\xB2\xB2\ 1. Dang xuat   ");
//	gotoxy(20, 7);
//	printf("\xB2\xB2\xB2\ 2. Thay doi mat khau   ");
//	gotoxy(20, 9);
//	printf("\xB2\xB2\xB2\ 3. ");
//	gotoxy(20, 11);
//	printf("\xB2\xB2\xB2\ 4. Cap nhat thong tin ca nhan");
//	gotoxy(20, 13);
//	printf("\xB2\xB2\xB2\ 5. View Books List");
//	gotoxy(20, 15);
//	printf("\xB2\xB2\xB2\ 6. Edit Book's Record");
//	gotoxy(20, 17);
//	printf("\xB2\xB2\xB2\ 7. Thoat chuong trinh");
//	gotoxy(20, 19);
//	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
//	gotoxy(20, 20);
//
//	gotoxy(20, 21);
//	printf("Lua chon cua ban:");
//	switch (_getch())
//	{
//	case '1':
//
//		break;
//	case '2':
//
//		break;
//	case '3':
//
//		break;
//	case '4':
//
//		break;
//	case '5':
//
//		break;
//	case '6':
//
//		break;
//	case '7':
//	{
//		system("cls");
//		printf("Thoat trong 3 giay nua");
//		for (int j = 0; j < 20; j++)
//		{
//			Sleep(50);
//			printf(".");
//		}
//		Sleep(3000); // sleep three seconds
//		system("cls");
//		exit(0);
//	}
//	default:
//	{
//		gotoxy(10, 23);
//		printf("\aChon sai, vui long chon lai!");
//		if (_getch())
//			MenuAdmin();
//	}
//	}
//}


int main()
{
	//system("color F0");
	menu();
	_getch();
	return 0;
}

