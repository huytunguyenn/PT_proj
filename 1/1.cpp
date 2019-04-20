// 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//prototype
void menu();
void gotoxy(int x, int y);
void MenuAdmin();
void Login(int &luachon);
void RePassAdmin();


void RePassAdmin()
{
	// lấy lại username
	char userAdmin[MAX_USERNAME];
	FILE *fAcc = fopen("Admin.txt", "rt"); 
	rewind(fAcc);
	fscanf(fAcc, "%s", userAdmin);
	fclose(fAcc);
	// ghi lại toàn bộ file Admin
	FILE *fAcc2 = fopen("Admin.txt", "wt");
	char newPass[MAX_PASS];
	printf("Mat khau moi: ");
	scanf("%s", &newPass);
	rewind(fAcc);
	fprintf(fAcc, userAdmin);
	fprintf(fAcc, "\n");
	fprintf(fAcc, newPass);
	fclose(fAcc);
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
void MenuAdmin()
{
	int luachon;
	system("cls");
	gotoxy(20, 3);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2 HE THONG QUAN LY THU VIEN - ADMIN \xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(20, 5);
	printf("\xB2\xB2\t 1. Dang xuat");
	gotoxy(20, 7);
	printf("\xB2\xB2\t 2. Thay doi mat khau");
	gotoxy(20, 9);
	printf("\xB2\xB2\t 3. Cap nhat thong tin ca nhan");
	gotoxy(20, 11);
	printf("\xB2\xB2\t 4. Tao tai khoan moi");
	gotoxy(20, 13);
	printf("\xB2\xB2\t 5. Phan quyen (quan ly hoac nhan vien)");
	gotoxy(20, 15);
	printf("\xB2\xB2\t 6. Quan ly doc gia");
	gotoxy(20, 17);
	printf("\xB2\xB2\t 7. Quan ly sach");
	gotoxy(20, 19);
	printf("\xB2\xB2\t 8. Lap phieu muon sach");
	gotoxy(20, 21);
	printf("\xB2\xB2\t 9. Lap phieu tra sach");
	gotoxy(20, 23);
	printf("\xB2\xB2\t 10. Thong ke");
	gotoxy(20, 25);
	printf("\xB2\xB2\t 11. Thoat chuong trinh");
	gotoxy(20, 27);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");


	gotoxy(20, 29);
	printf("Lua chon cua ban:");
	scanf("%d", &luachon);
	switch (luachon)
	{
	case 1:
		menu();
		break;
	case 2:
		RePassAdmin();
		MenuAdmin();
		break;
	case 3:

		break;
	case 4:
		
		break;
	case 5:

		break;
	case 6:

		break;
	case 7:

		break;
	case 8:

		break;
	case 9:

		break;
	case 10:

		break;
	case 11:
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
		gotoxy(20, 31);
		printf("\aChon sai, vui long chon lai!");
		if (_getch())
			MenuAdmin();
	}
	}
}
void Login(int &luachon)
{
	char userAdmin[MAX_USERNAME];
	char passAdmin[MAX_PASS];
	FILE *fAcc = fopen("Admin.txt", "rt"); // Admin.txt lưu trữ username và pass của admin
	if (fAcc == NULL)
	{
		fAcc = fopen("Admin.txt", "wt"); // tập tin sẽ được tạo nếu chưa có
		if (fAcc == NULL)
		{
			printf("Khong mo duoc tap tin"); system("pause");
		}
	}
	rewind(fAcc);
	fscanf(fAcc, "%s", userAdmin);
	fseek(fAcc, strlen(userAdmin), SEEK_SET);
	fscanf(fAcc, "%s", passAdmin);
	fclose(fAcc);
	system("cls");
	char pass[MAX_PASS];
	char username[MAX_USERNAME];
	gotoxy(20, 4); printf("Username: ");
	scanf("%s", &username);
	gotoxy(20, 6); printf("Password: ");
	// mã hóa mật khẩu
	gotoxy(29, 6);
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
	if (strcmp(username, userAdmin) == 0 && strcmp(pass, passAdmin) == 0)
	{
		gotoxy(20, 9); printf("Ban da dang nhap duoi quyen Admin.\n");
		_getch();
		MenuAdmin();
	}
	/*else if ()
	{
		gotoxy(15, 9); printf("Ban da dang nhap duoi quyen chuyen vien.\n");
	}
	else if ()
	{
		gotoxy(15, 9); printf("Ban da dang nhap duoi quyen quan ly.\n");
	}*/
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
//menu đăng nhập
void menu() 
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


int main()
{
	system("color F0");
	menu();
	_getch();
	return 0;
}

