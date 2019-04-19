// 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//biến toàn cục
char password[10] = { "userpass" };

void Login()
{
	// vũ viết hàm
}
void Logout()
{
	// vũ viết hàm
}
void ChangePass()
{
	// vũ viết hàm
}
void UpadateInfo()
{
	// tú viết hàm
}
void CreateUser(/*DATABASE &data, USER *p*/)
{
	// tú viết hàm
	/*if (strcmp(it.Acc.sUsername, user.Acc.sUsername) == 0)*/

}
void gotoxy(int x, int y) // dùng để trang trí, chạy hiệu ứng
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}
void mainmenu()
{
	gotoxy(20, 7);
	printf("\t1. Dang nhap");
	gotoxy(20, 9);
	printf("\t2. Dang xuat");
	gotoxy(20, 11);
	printf("\t3. Thay doi mat khau");
	gotoxy(20, 13);
	printf("\t4. Cap nhat thong tin ca nhan");
	gotoxy(20, 15);
	printf("\t5. Tao nguoi dung");
	gotoxy(20, 17);
	printf("\t6. Phan quyen nguoi dung (danh cho quan ly, nhan vien)");
	gotoxy(20, 19);
	printf("\t7. Thoat chuong trinh");

	gotoxy(20, 22);
	printf("Lua chon cua ban:");
	switch (_getch())
	{
	case '1':
		Login();
		break;
	case '2':
		Logout();
		break;
	case '3':
		ChangePass();
		break;
	case '4':
		UpadateInfo();
		break;
	case '5':
		CreateUser();
		break;
	case '6':

		break;
	case '7':
	{
		system("cls");
		gotoxy(20, 11);
		printf("Thoat trong 3 giay nua");
		for (int j = 0; j < 60; j++)
		{
			Sleep(50);
			printf(".");
		}
		//Sleep(3000); // ngủ 3 giây
		system("cls");
		exit(0);
	}
	default:
	{
		gotoxy(20, 24);
		printf("\aChon sai, vui long chon lai!");
		if (_getch())
			mainmenu();
	}
	}
}
void MainMenuAdmin()
{

	system("cls");
	int i;
	gotoxy(20, 3);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2 HE THONG QUAN LY THU VIEN \xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(20, 5);
	printf("\xB2\xB2\xB2\ 1. Dang xuat   ");
	gotoxy(20, 7);
	printf("\xB2\xB2\xB2\ 2. Thay doi mat khau   ");
	gotoxy(20, 9);
	printf("\xB2\xB2\xB2\ 3. ");
	gotoxy(20, 11);
	printf("\xB2\xB2\xB2\ 4. Cap nhat thong tin ca nhan");
	gotoxy(20, 13);
	printf("\xB2\xB2\xB2\ 5. View Books List");
	gotoxy(20, 15);
	printf("\xB2\xB2\xB2\ 6. Edit Book's Record");
	gotoxy(20, 17);
	printf("\xB2\xB2\xB2\ 7. Thoat chuong trinh");
	gotoxy(20, 19);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(20, 20);

	gotoxy(20, 21);
	printf("Lua chon cua ban:");
	switch (_getch())
	{
	case '1':
	
		break;
	case '2':
	
		break;
	case '3':

		break;
	case '4':

		break;
	case '5':

		break;
	case '6':

		break;
	case '7':
	{
		system("cls");
		printf("Thoat trong 3 giay nua");
		for (int j = 0; j < 20; j++)
		{
			Sleep(50);
			printf(".");
		}
		Sleep(3000); // sleep three seconds
		system("cls");
		exit(0);
	}
	default:
	{
		gotoxy(10, 23);
		printf("\aChon sai, vui long chon lai!");
		if (_getch())
			MainMenuAdmin();
	}
	}
}
void Password(void) //để đăng nhập
{
	system("cls");
	char d[26] = "He Thong Quan Ly Thu Vien";
	char ch, pass[10];
	int i = 0;
	gotoxy(10, 4);

	// in chuyển động 
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
	
	
	mainmenu();

	/*while (ch != 13)
	{
		ch = _getch();

		if (ch != 13 && ch != 8) {
			_putch('*');
			pass[i] = ch;
			i++;
		}
	}
	pass[i] = '\0';
	if (strcmp(pass, password) == 0)
	{

		gotoxy(15, 9);
		printf("Ban da dang nhap bang quyen admin!");
		gotoxy(17, 10);
		printf("\n\xB2\xB2\xB2\xB2\Press any key to countinue...");
		_getch();
		MainMenuAdmin();
	}
	else
	{
		gotoxy(15, 16);
		printf("\aMat khau khong chinh xac!");
		_getch();
		Password();
	}*/
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




int main()
{
	system("color F0");
	Password();
	_getch();
    return 0;
}

