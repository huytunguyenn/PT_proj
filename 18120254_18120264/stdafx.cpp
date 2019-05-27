#include "stdafx.h"
// di chuyển đến vị trí (x,y)
void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}
// kiểm tra ngày hợp lệ
int CheckDate(DATES BirthDate)
{
	int MaxDay; // ngày trong tháng
	if (BirthDate.Year <= LIMIT_YEAR || BirthDate.Year > THIS_YEAR || BirthDate.Month < 0 || BirthDate.Month > 12 || BirthDate.Day < 0 || BirthDate.Day > 31)
	{
		return 1;
	}
	else
	{
		switch (BirthDate.Month)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			MaxDay = 31;
			break;
		case 2:
			if (BirthDate.Year % 4 == 0 && BirthDate.Year % 100 != 0)
				MaxDay = 29;
			else
				MaxDay = 28;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			MaxDay = 30;
			break;
		}
		if (BirthDate.Day <= MaxDay)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
}
// xuất thông tin 1 tài khoản
void OutputInfo(ACCOUNT login)
{
	printf("\n\t\tUsername: %s", login.Username);
	printf("\n\n\t\tHo va Ten: %s", login.FullName);
	printf("\n\t\tCMND: %s", login.CMND);
	printf("\n\t\tDia chi: %s", login.Address);
	if (login.Genre == 1)
		printf("\n\t\tGioi tinh: Nam\n");
	else
		printf("\n\t\tGioi tinh: Nu\n");
	printf("\n\t\tNgay Sinh: %d/%d/%d     ", login.BirthDate.Day, login.BirthDate.Month, login.BirthDate.Year);
}
// thay đổi mật khẩu
void RePass(ACCOUNT &login)
{
	ACCOUNT checkpass;
	do {
		// nhập pass mới
		gotoxy(20, 6); printf("Password moi: ");
		// mã hóa mật khẩu
		gotoxy(34, 6);
		int p = 0;
		do {
			login.Password[p] = _getch();
			if (login.Password[p] != '\r')
			{
				printf("*");
			}
			p++;
		} while (login.Password[p - 1] != '\r');
		login.Password[p - 1] = '\0';
		// nhập lại pass
		gotoxy(20, 8); printf("Nhap lai password: ");
		// mã hóa mật khẩu
		gotoxy(39, 8);
		p = 0;
		do {
			checkpass.Password[p] = _getch();
			if (checkpass.Password[p] != '\r')
			{
				printf("*");
			}
			p++;
		} while (checkpass.Password[p - 1] != '\r');
		checkpass.Password[p - 1] = '\0';
		if (strcmp(login.Password, checkpass.Password) != 0)
		{
			gotoxy(20, 10); printf("Khong trung khop. Vui long nhap lai.  ");
			gotoxy(30, 6); printf("                               ");
			gotoxy(39, 8); printf("                               ");
		}
	} while (strcmp(login.Password, checkpass.Password) != 0);
	FILE *fAcc = fopen("Account.bin", "rb+");
	if (fAcc == NULL)
	{
		printf("Khong mo duoc file");
	}
	rewind(fAcc);
	ACCOUNT temp;
	while (fread(&temp, sizeof(ACCOUNT), 1, fAcc))
	{
		if (strcmp(login.Username, temp.Username) == 0)
		{
			// đi đến vị trí info để ghi
			fseek(fAcc, ftell(fAcc) - sizeof(ACCOUNT), 0);
			fwrite(&login, sizeof(ACCOUNT), 1, fAcc);
			fclose(fAcc); // quan trọng: không được để ngoài vòng if
			gotoxy(20, 10); printf("Cap nhat password thanh cong.  ");
		}
	}
}
// cập nhật thông tin cá nhân 
void UpdateInfo(ACCOUNT &login)
{
	gotoxy(10, 4); printf("::::::::::::::::::::Cap nhat thong tin ca nhan::::::::::::::::::::");
	FILE *fAcc = fopen("Account.bin", "rb+");
	if (fAcc == NULL)
	{
		printf("Khong mo duoc file");
	}
	rewind(fAcc);
	ACCOUNT temp;
	while (fread(&temp, sizeof(ACCOUNT), 1, fAcc))
	{
		if (strcmp(login.Username, temp.Username) == 0)
		{
			// nhập info mới
			while (getchar() != '\n');
			flushall();
			gotoxy(20, 6); printf("Username moi: ");
			fgets(login.Username, sizeof(login.Username), stdin);
			strtok(login.Username, "\n"); // loại bỏ \n do fgets tự thêm
			gotoxy(20, 8); printf("Ho Va Ten moi: ");
			fgets(login.FullName, sizeof(login.FullName), stdin);
			gotoxy(20, 10); printf("CMND moi: ");
			fgets(login.CMND, sizeof(login.CMND), stdin);
			gotoxy(20, 12); printf("Dia chi moi: ");
			fgets(login.Address, sizeof(login.Address), stdin);
			do {
				gotoxy(20, 14); printf("Gioi tinh moi (1 la Nam, 2 la Nu): ");
				scanf("%d", &login.Genre);
				if (login.Genre != 1 || login.Genre != 2)
				{
					gotoxy(20, 16); printf("Vui long chi nhap so 1 hoac 2!");
				}
			} while (login.Genre != 1 && login.Genre != 2);
			int check = 0;
			do {
				gotoxy(20, 16); printf("                              ");
				gotoxy(20, 16); printf("Ngay sinh moi: ");
				scanf("%d", &login.BirthDate.Day);
				gotoxy(20, 18); printf("Thang sinh moi: ");
				scanf("%d", &login.BirthDate.Month);
				gotoxy(20, 20); printf("Nam sinh moi: ");
				scanf("%d", &login.BirthDate.Year);
				check = CheckDate(login.BirthDate);
				if (check != 0)
				{
					gotoxy(20, 22); printf("Ngay thang khong hop le. Vui long nhap lai\n");
				}
			} while (check != 0);
			// đi đến vị trí để ghi info
			fseek(fAcc, ftell(fAcc) - sizeof(ACCOUNT), 0);
			fwrite(&login, sizeof(ACCOUNT), 1, fAcc);
			fclose(fAcc); // quan trọng: ko dc bỏ ngoài vòng if
		}
	}
}
// nhập thông tin 1 tài khoản
void InputInfo(ACCOUNT &acc)
{
	while (getchar() != '\n');
	flushall();
	gotoxy(20, 6); printf("Username: ");
	fgets(acc.Username, sizeof(acc.Username), stdin);
	strtok(acc.Username, "\n"); // loại bỏ \n do fgets tự thêm
	ACCOUNT checkpass;
	do {
		// nhập pass 
		gotoxy(20, 8); printf("Password: ");
		// mã hóa mật khẩu
		gotoxy(30, 8);
		int p = 0;
		do {
			acc.Password[p] = _getch();
			if (acc.Password[p] != '\r')
			{
				printf("*");
			}
			p++;
		} while (acc.Password[p - 1] != '\r');
		acc.Password[p - 1] = '\0';
		// nhập lại pass
		gotoxy(20, 10); printf("Nhap lai password: ");
		// mã hóa mật khẩu
		gotoxy(39, 10);
		p = 0;
		do {
			checkpass.Password[p] = _getch();
			if (checkpass.Password[p] != '\r')
			{
				printf("*");
			}
			p++;
		} while (checkpass.Password[p - 1] != '\r');
		checkpass.Password[p - 1] = '\0';
		if (strcmp(acc.Password, checkpass.Password) != 0)
		{
			gotoxy(20, 12); printf("Khong trung khop. Vui long nhap lai.  ");
			gotoxy(30, 8); printf("                               ");
			gotoxy(39, 10); printf("                               ");
		}
	} while (strcmp(acc.Password, checkpass.Password) != 0);
	gotoxy(20, 12); printf("                                      ");
	gotoxy(20, 12); printf("Ho Va Ten: ");
	fgets(acc.FullName, sizeof(acc.FullName), stdin);
	gotoxy(20, 14); printf("CMND: ");
	fgets(acc.CMND, sizeof(acc.CMND), stdin);
	gotoxy(20, 16); printf("Dia chi: ");
	fgets(acc.Address, sizeof(acc.Address), stdin);
	do {
		gotoxy(20, 18); printf("Gioi tinh (1 la Nam, 2 la Nu): ");
		scanf("%d", &acc.Genre);
		if (acc.Genre != 1 || acc.Genre != 2)
		{
			gotoxy(20, 20); printf("Vui long chi nhap so 1 hoac 2!");
		}
	} while (acc.Genre != 1 && acc.Genre != 2);
	int check = 0;
	do {
		gotoxy(20, 20); printf("                              ");
		gotoxy(20, 20); printf("Ngay sinh: ");
		scanf("%d", &acc.BirthDate.Day);
		gotoxy(20, 22); printf("Thang sinh: ");
		scanf("%d", &acc.BirthDate.Month);
		gotoxy(20, 24); printf("Nam sinh: ");
		scanf("%d", &acc.BirthDate.Year);
		check = CheckDate(acc.BirthDate);
		if (check != 0)
		{
			gotoxy(20, 26); printf("Ngay thang khong hop le. Vui long nhap lai\n");
		}
	} while (check != 0);
}
//kiểm tra username tài khoản đã tồn tại, return true nếu có tồn tại
bool ExistAcc(FILE *f, ACCOUNT acc)
{
	rewind(f);
	ACCOUNT temp;
	while (fread(&temp, sizeof(ACCOUNT), 1, f))
	{
		if (strcmp(temp.Username, acc.Username) == 0)
			return true;
	}
	return false;
}
// thêm tài khoản
void CreateAcc()
{
	FILE *fAcc = fopen("Account.bin", "ab+");
	if (fAcc == NULL)
	{
		printf("Khong mo duoc file");
	}
	ACCOUNT acc;
	int choice;
	do {
		gotoxy(20, 6); printf("Chon loai tai khoan");
		gotoxy(23, 8); printf("1. Chuyen Vien");
		gotoxy(23, 10); printf("2. Quan Ly");
		gotoxy(20, 12); printf("Lua chon cua ban: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
		{
			bool check = false;
			do {
				system("cls");
				gotoxy(10, 4); printf("::::::::::::::::::::Tao tai khoan Chuyen Vien::::::::::::::::::::");
				InputInfo(acc);
				acc.Permission = 2;
				acc.Status = 2; // blocked
				if (ExistAcc(fAcc, acc) == false)
				{
					check = true;
					fseek(fAcc, 0, SEEK_END);
					fwrite(&acc, sizeof(ACCOUNT), 1, fAcc);
					fclose(fAcc);
					gotoxy(16, 26); printf("Them tai khoan thanh cong.    ");
				}
				else
				{
					gotoxy(16, 26); printf("Username tai khoan da ton tai.");
					int choice;
					do {
						gotoxy(16, 28); printf("Thoat ra menu?");
						gotoxy(20, 30); printf("1. Co");
						gotoxy(20, 32); printf("2. Khong, nhap lai.");
						gotoxy(16, 34); printf("Lua chon cua ban: ");
						scanf("%d", &choice);
						if (choice != 1 && choice != 2)
						{
							gotoxy(16, 36); printf("Vui long chi nhap 1 hoac 2");
						}
					} while (choice != 1 && choice != 2);
					if (choice == 1)
					{
						fclose(fAcc);
						break;
					}
					system("cls");
				}
			} while (check == false);
			system("pause");
			break;
		}
		case 2:
		{
			bool check = false;
			do {
				system("cls");
				gotoxy(10, 4); printf("::::::::::::::::::::Tao tai khoan Quan Ly::::::::::::::::::::");
				InputInfo(acc);
				acc.Permission = 3;
				acc.Status = 2; // blocked
				if (ExistAcc(fAcc, acc) == false)
				{
					check = true;
					fseek(fAcc, 0, SEEK_END);
					fwrite(&acc, sizeof(ACCOUNT), 1, fAcc);
					fclose(fAcc);
					gotoxy(16, 26); printf("Them tai khoan thanh cong.    ");
				}
				else
				{
					gotoxy(16, 26); printf("Username tai khoan da ton tai.");
					int choice;
					do {
						gotoxy(16, 28); printf("Thoat ra menu?");
						gotoxy(20, 30); printf("1. Co");
						gotoxy(20, 32); printf("2. Khong, nhap lai.");
						gotoxy(16, 34); printf("Lua chon cua ban: ");
						scanf("%d", &choice);
						if (choice != 1 && choice != 2)
						{
							gotoxy(16, 36); printf("Vui long chi nhap 1 hoac 2");
						}
					} while (choice != 1 && choice != 2);
					if (choice == 1)
					{
						fclose(fAcc);
						break;
					}
					system("cls");
				}
			} while (check == false);
			system("pause");
			break;
		}
		default:
		{
			gotoxy(20, 14); printf("\aLua chon khong hop le. Vui long chon lai!      ");
			system("pause");
		}
		}
	} while (choice != 1 && choice != 2);
}
// kiểm tra tài khoản đăng nhập  
void CheckLogin(FILE *f, char username[MAX_PASS], char pass[MAX_USERNAME], ACCOUNT &login, int &checkacc)
{
	// checkacc = 1: admin, 2: chuyên viên, 3: quản lý, 4: chưa activate
	rewind(f);
	ACCOUNT temp;
	while (fread(&temp, sizeof(ACCOUNT), 1, f))
	{
		if (strcmp(username, temp.Username) == 0 && strcmp(pass, temp.Password) == 0 && temp.Permission == 1)
		{
			checkacc = temp.Permission;
			login = temp;
		}
		else if (strcmp(username, temp.Username) == 0 && strcmp(pass, temp.Password) == 0 && temp.Permission == 2)
		{
			if (temp.Status == 1)
			{
				checkacc = temp.Permission;
				login = temp;
			}
			else
			{
				checkacc = 4;
			}
		}
		else if (strcmp(username, temp.Username) == 0 && strcmp(pass, temp.Password) == 0 && temp.Permission == 3)
		{
			if (temp.Status == 1)
			{
				checkacc = temp.Permission;
				login = temp;
			}
			else
			{
				checkacc = 4;
			}
		}
	}
}
//menu đăng nhập
void menu()
{
	int luachon = 2; // nếu người dùng muốn quay lại: 1 = có, 2 = ko
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
			gotoxy(20, 13); printf("\aLua chon khong hop le. Vui long chon lai!     ");
			if (_getch())
			{
				menu();
			}
		}
		}
	} while (luachon == 1);
}
// đăng nhập
void Login(int &luachon)
{
	system("cls");
	// chứa thông tin tài khoản đang login
	ACCOUNT login;
	// user nhập info
	char pass[MAX_PASS];
	char username[MAX_USERNAME];
	gotoxy(20, 4); printf("Username: ");
	scanf("%s", &username);
	gotoxy(20, 6); printf("Password: ");
	// mã hóa mật khẩu
	gotoxy(30, 6);
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
	// mở file tài khoản
	FILE *fAcc = fopen("Account.bin", "rb");
	if (fAcc == NULL)
	{
		printf("Khong mo duoc tap tin");
	}
	// kiểm tra quyền
	int checkacc;
	CheckLogin(fAcc, username, pass, login, checkacc);
	fclose(fAcc);
	if (checkacc == 1)
	{
		gotoxy(20, 9); printf("Ban da dang nhap duoi quyen Admin.\n");
		_getch();
		MenuAdmin(login);
	}
	else if (checkacc == 2)
	{
		gotoxy(20, 9); printf("Ban da dang nhap duoi quyen Chuyen Vien.\n");
		_getch();
		MenuChuyenVien(login);
	}
	else if (checkacc == 3)
	{
		gotoxy(20, 9); printf("Ban da dang nhap duoi quyen Quan Ly.\n");
		_getch();
		MenuQuanLy(login);
	}
	else if (checkacc == 4)
	{
		gotoxy(20, 9); printf("Tai khoan dang bi khoa!  ");
		system("pause"); system("cls");
		gotoxy(20, 9); printf("Lua chon hanh dong.");
		gotoxy(27, 11); printf("1. Quay lai menu chinh");
		gotoxy(27, 13); printf("2. Dang nhap lai");
		gotoxy(20, 15); printf("Lua chon cua ban: ");
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
	else
	{
		gotoxy(20, 8); printf("\aDang nhap khong thanh cong!  ");
		system("pause"); system("cls");
		gotoxy(20, 9); printf("Quay lai menu chinh?");
		gotoxy(27, 11); printf("1. Co");
		gotoxy(27, 13); printf("2. Khong. Dang nhap lai");
		gotoxy(20, 15); printf("Lua chon cua ban: ");
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
// phân quyền tài khoản
void PhanQuyen()
{
	FILE *f = fopen("Account.bin", "rb+");
	if (f == NULL)
	{
		printf("Khong mo duoc file");
	}
	rewind(f);
	gotoxy(10, 4); printf("::::::::::::::::::::Phan quyen Tai khoan::::::::::::::::::::");
	char usertemp[MAX_USERNAME];
	gotoxy(20, 6); printf("Nhap username: ");
	scanf("%s", &usertemp);
	ACCOUNT temp;
	while (fread(&temp, sizeof(ACCOUNT), 1, f))
	{
		if (strcmp(usertemp, temp.Username) == 0)
		{
			do {
				gotoxy(20, 8); printf("Loai tai khoan");
				gotoxy(23, 10); printf("2. Chuyen Vien");
				gotoxy(23, 12); printf("3. Quan Ly");
				gotoxy(20, 14); printf("Lua chon cua ban: ");
				scanf("%d", &temp.Permission);
				if (temp.Permission != 2 && temp.Permission != 3)
				{
					gotoxy(20, 16); printf("Vui long chi nhap 2 hoac 3");
				}
			} while (temp.Permission != 2 && temp.Permission != 3);
			do {
				gotoxy(20, 16); printf("Tinh trang tai khoan      ");
				gotoxy(23, 18); printf("1. Kich hoat");
				gotoxy(23, 20); printf("2. Khoa");
				gotoxy(20, 22); printf("Lua chon cua ban: ");
				scanf("%d", &temp.Status);
				gotoxy(20, 24); printf("                          ");
				if (temp.Status != 1 && temp.Status != 2)
				{
					gotoxy(20, 24); printf("Vui long chi nhap 1 hoac 2");
				}
			} while (temp.Status != 1 && temp.Status != 2);
			fseek(f, ftell(f) - sizeof(ACCOUNT), 0);
			fwrite(&temp, sizeof(ACCOUNT), 1, f);
			fclose(f); // quan trọng: không được để ngoài vòng if
			return;
		}
	}
	fclose(f);
	gotoxy(20, 8); printf("Khong tim thay tai khoan   ");
}
// xem tài khoản
void ViewAcc()
{
	system("cls");
	gotoxy(1, 1);
	printf("::::::::::::::::::::::::::::::: Thong tin Tai Khoan :::::::::::::::::::::::::::::::::");
	gotoxy(2, 5);
	printf("USERNAME     PASSWORD     QUYEN             TINH TRANG");
	FILE *fAcc = fopen("Account.bin", "rb");
	if (fAcc == NULL)
	{
		printf("Khong mo duoc file");
	}
	rewind(fAcc);
	int j = 7;
	ACCOUNT temp;
	while (fread(&temp, sizeof(ACCOUNT), 1, fAcc) == 1)
	{
		gotoxy(2, j); printf("%s", temp.Username);
		gotoxy(15, j); printf("%s", temp.Password);
		if (temp.Permission == 1)
		{
			gotoxy(28, j); printf("Admin");
		}
		else if (temp.Permission == 2)
		{
			gotoxy(28, j); printf("Chuyen Vien");
		}
		else if (temp.Permission == 3)
		{
			gotoxy(28, j); printf("Quan Ly");
		}
		if (temp.Status == 1)
		{
			gotoxy(46, j); printf("Dang kich hoat");
		}
		else if (temp.Status == 2)
		{
			gotoxy(46, j); printf("Dang khoa");
		}
		j++;
	}
	fseek(fAcc, 0, SEEK_END);
	long size = ftell(fAcc);
	int tong = size / sizeof(ACCOUNT);
	gotoxy(2, j + 4); printf("So tai khoan: %d             ", tong);
	fclose(fAcc);
}

// nhập thông tin 1 cuốn sách
void InputBook(BOOK &book)
{
	while (getchar() != '\n');
	flushall();
	gotoxy(20, 6); printf("ISBN: ");
	fgets(book.ISBN, sizeof(book.ISBN), stdin);
	gotoxy(20, 8); printf("Ten sach: ");
	fgets(book.Name, sizeof(book.Name), stdin);
	gotoxy(20, 10); printf("Tac gia: ");
	fgets(book.Author, sizeof(book.Author), stdin);
	gotoxy(20, 12); printf("Nha xuat ban: ");
	fgets(book.Publisher, sizeof(book.Publisher), stdin);
	gotoxy(20, 14); printf("The loai: ");
	fgets(book.Categories, sizeof(book.Categories), stdin);
	gotoxy(20, 16); printf("Gia (VND): ");
	scanf("%d", &book.Price);
	gotoxy(20, 18); printf("So luong: ");
	scanf("%d", &book.Quantity);
	gotoxy(20, 20); printf("So sach chua duoc tra (nhap 0 neu day la sach moi): ");
	scanf("%d", &book.Borrow);
	int check = 0;
	do {
		gotoxy(20, 22); printf("Ngay xuat ban: ");
		scanf("%d", &book.Issued.Day);
		gotoxy(20, 24); printf("Thang xuat ban: ");
		scanf("%d", &book.Issued.Month);
		gotoxy(20, 26); printf("Nam xuat ban: ");
		scanf("%d", &book.Issued.Year);
		check = CheckDate(book.Issued);
		if (check != 0)
		{
			gotoxy(20, 28); printf("Ngay thang khong hop le. Vui long nhap lai\n");
		}
	} while (check != 0);
}
// kiểm tra ISBN sách đã tồn tại chưa, return true nếu có tồn tại
bool ExistBook(FILE *f, BOOK book)
{
	rewind(f);
	BOOK temp;
	while (fread(&temp, sizeof(BOOK), 1, f))
	{
		if (strcmp(temp.ISBN, book.ISBN) == 0)
			return true;
	}
	return false;
}
// thêm sách
void AddBook()
{
	BOOK book;
	int choice;
	bool check = false;
	do {
		FILE *fBook = fopen("Book.bin", "ab+");
		if (fBook == NULL)
		{
			printf("Khong mo duoc file");
		}
		system("cls");
		gotoxy(10, 4); printf(":::::::::::::::::::::: Them Sach ::::::::::::::::::::::");
		InputBook(book);
		if (ExistBook(fBook, book) == false)
		{
			check = true;
			fseek(fBook, 0, SEEK_END);
			fwrite(&book, sizeof(BOOK), 1, fBook);
			gotoxy(16, 28); printf("Them sach thanh cong.    ");
			fclose(fBook);
		}
		else
		{
			system("cls");
			gotoxy(10, 4); printf(":::::::::::::::::::::: Them Sach ::::::::::::::::::::::");
			gotoxy(16, 10); printf("Sach da ton tai.");
			int choice;
			do {
				gotoxy(16, 12); printf("Thoat ra menu?");
				gotoxy(20, 14); printf("1. Co");
				gotoxy(20, 16); printf("2. Khong, nhap lai.");
				gotoxy(16, 18); printf("Lua chon cua ban: ");
				scanf("%d", &choice);
				if (choice != 1 && choice != 2)
				{
					gotoxy(16, 20); printf("Vui long chi nhap 1 hoac 2");
				}
			} while (choice != 1 && choice != 2);
			if (choice == 1)
			{
				fclose(fBook);
				break;
			}
			system("cls");
		}
	} while (check == false);
}
// xem sách
void ViewBook()
{
	system("cls");
	gotoxy(1, 1);
	printf("::::::::::::::::::::::::::::::: Danh sach Sach :::::::::::::::::::::::::::::::::");
	gotoxy(2, 5);                                               
	printf("ISBN       TEN SACH                 TEN TAC GIA         NHA XUAT BAN       NAM    THE LOAI      DON GIA(VND)     SO LUONG");
	FILE *fBook = fopen("Book.bin", "rb");
	if (fBook == NULL)
	{
		printf("Khong mo duoc file");
	}
	rewind(fBook);
	int j = 7;
	int tong = 0;
	int tongreal = 0;
	BOOK temp;
	while (fread(&temp, sizeof(BOOK), 1, fBook))
	{
		gotoxy(2, j); printf("%s", temp.ISBN);
		gotoxy(13, j); printf("%s", temp.Name);
		gotoxy(37, j); printf("%s", temp.Author);
		gotoxy(56, j); printf("NXB %s", temp.Publisher);
		gotoxy(78, j); printf("%d", temp.Issued.Year);
		gotoxy(85, j); printf("%s", temp.Categories);
		gotoxy(99, j); printf("%d", temp.Price);
		gotoxy(116, j); printf("%d          ", temp.Quantity - temp.Borrow);
		j++;
		tong = tong + temp.Quantity;
		tongreal = tongreal + temp.Quantity - temp.Borrow;
	}
	gotoxy(2, j + 4); printf("So luong sach nhap ve: %d cuon             ", tong);
	gotoxy(2, j + 6); printf("So luong sach hien tai: %d cuon             ", tongreal);
	fclose(fBook);
}
// Chỉnh sửa thông tin 1 quyển sách // BUG
void UpdateBook()
{
	while (getchar() != '\n');
	flushall();
	char ISBNtemp[MAX_PASS];
	gotoxy(10, 4); printf("::::::::::::::::::::Cap nhat thong tin sach::::::::::::::::::::");
	gotoxy(20, 6); printf("Nhap ISBN: ");
	fgets(ISBNtemp, sizeof(ISBNtemp), stdin);
	FILE *fBook = fopen("Book.bin", "rb+");
	if (fBook == NULL)
	{
		printf("Khong mo duoc file");
	}
	rewind(fBook);
	BOOK temp;
	while (fread(&temp, sizeof(BOOK), 1, fBook))
	{
		if (strcmp(ISBNtemp, temp.ISBN) == 0)
		{
			// nhập info mới
			BOOK book;
			//while (getchar() != '\n');
			//flushall();
			gotoxy(20, 8); printf("ISBN moi: ");
			fgets(book.ISBN, sizeof(book.ISBN), stdin);
			gotoxy(20, 10); printf("Ten sach moi: ");
			fgets(book.Name, sizeof(book.Name), stdin);
			gotoxy(20, 12); printf("Tac gia moi: ");
			fgets(book.Author, sizeof(book.Author), stdin);
			gotoxy(20, 14); printf("Nha xuat ban moi: ");
			fgets(book.Publisher, sizeof(book.Publisher), stdin);
			gotoxy(20, 16); printf("The loai moi: ");
			fgets(book.Categories, sizeof(book.Categories), stdin);
			gotoxy(20, 18); printf("Gia moi (VND): ");
			scanf("%d", &book.Price);
			gotoxy(20, 20); printf("So luong moi: ");
			scanf("%d", &book.Quantity);
			book.Borrow = 0;
			int check = 0;
			do {
				gotoxy(20, 22); printf("Ngay xuat ban moi: ");
				scanf("%d", &book.Issued.Day);
				gotoxy(20, 24); printf("Thang xuat ban moi: ");
				scanf("%d", &book.Issued.Month);
				gotoxy(20, 26); printf("Nam xuat ban moi: ");
				scanf("%d", &book.Issued.Year);
				check = CheckDate(book.Issued);
				if (check != 0)
				{
					gotoxy(20, 28); printf("Ngay thang khong hop le. Vui long nhap lai\n");
				}
			} while (check != 0);
			// đi đến vị trí info để ghi
			fseek(fBook, ftell(fBook) - sizeof(BOOK), 0);
			fwrite(&book, sizeof(BOOK), 1, fBook);
			gotoxy(20, 28); printf("Cap nhat sach thanh cong            \n");
		}
		else
		{
			gotoxy(20, 8); printf("Khong tim thay sach            ");
		}
	}
	fclose(fBook);
}
// xuất thông tin 1 quyển sách
void OutputBook(BOOK book)
{
	gotoxy(20, 8); printf("-----------------------------------------------");
	gotoxy(20, 10); printf("Ten sach: %s", book.Name);
	gotoxy(20, 12); printf("Tac gia: %s", book.Author);
	gotoxy(20, 14); printf("Nha xuat ban: %s", book.Publisher);
	gotoxy(20, 16); printf("The loai: %s", book.Categories);
	gotoxy(20, 18); printf("Gia (VND): %d", book.Price);
	gotoxy(20, 20); printf("So luong: %d\n", book.Quantity - book.Borrow);
	gotoxy(20, 22); printf("Ngay xuat ban: %d/%d/%d      ", book.Issued.Day, book.Issued.Month, book.Issued.Year);
}
//Tìm kiếm sách theo ISBN
void SearchBookISBN()
{
	while (getchar() != '\n');
	flushall();
	char ISBNtemp[MAX_PASS];
	gotoxy(10, 4); printf("::::::::::::::::::::Tim kiem Sach theo ISBN::::::::::::::::::::");
	gotoxy(20, 6); printf("Nhap ISBN: ");
	fgets(ISBNtemp, sizeof(ISBNtemp), stdin);
	FILE *fBook = fopen("Book.bin", "rb");
	if (fBook == NULL)
	{
		printf("Khong mo duoc file");
	}
	rewind(fBook);
	BOOK temp;
	bool check = false; // để in ra ko tìm thấy sách
	while (fread(&temp, sizeof(BOOK), 1, fBook))
	{
		if (strcmp(ISBNtemp, temp.ISBN) == 0)
		{
			// in ra info
			OutputBook(temp);
			check = true;
		}
	}
	fclose(fBook);
	if (check == false)
	{
		gotoxy(20, 8); printf("Khong tim thay sach      ");
	}
}
//Tìm kiếm sách theo tên sách
void SearchBookName()
{
	while (getchar() != '\n');
	flushall();
	char Nametemp[MAX_NAME];
	gotoxy(10, 4); printf("::::::::::::::::::::Tim kiem Sach theo Ten::::::::::::::::::::");
	gotoxy(20, 6); printf("Nhap ten: ");
	fgets(Nametemp, sizeof(Nametemp), stdin);
	FILE *fBook = fopen("Book.bin", "rb");
	if (fBook == NULL)
	{
		printf("Khong mo duoc file");
	}
	rewind(fBook);
	BOOK temp;
	bool check = false; // để in ra ko tìm thấy sách
	while (fread(&temp, sizeof(BOOK), 1, fBook))
	{
		if (strcmp(Nametemp, temp.Name) == 0)
		{
			// in ra info
			OutputBook(temp);
			check = true;
		}
	}
	fclose(fBook);
	if (check == false)
	{
		gotoxy(20, 8); printf("Khong tim thay sach      ");
	}
}
//Xóa thông tin sách theo ISBN
void DeleteBook()
{
	while (getchar() != '\n');
	flushall();
	char ISBNtemp[MAX_PASS];
	gotoxy(10, 4); printf("::::::::::::::::::::::Xoa Sach::::::::::::::::::::::");
	gotoxy(20, 6); printf("Nhap ISBN: ");
	fgets(ISBNtemp, sizeof(ISBNtemp), stdin);
	FILE *fBook = fopen("Book.bin", "rb");
	if (fBook == NULL)
	{
		printf("Khong mo duoc file");
	}
	rewind(fBook);
	BOOK temp;
	bool check = false; // để ko cần phải remove + rename lúc đang đọc (mâu thuẫn)
	while (fread(&temp, sizeof(BOOK), 1, fBook))
	{
		if (strcmp(ISBNtemp, temp.ISBN) == 0)
		{
			check = true;
			FILE* ft = fopen("Temp.bin", "wb+");  // tạo Temp.bin để ghi sách k bị delete
			rewind(fBook);
			while (fread(&temp, sizeof(BOOK), 1, fBook))
			{
				if (strcmp(temp.ISBN, ISBNtemp) != 0)
				{
					fseek(ft, 0, SEEK_CUR);
					fwrite(&temp, sizeof(BOOK), 1, ft); // ghi hết sách vào Temp.bin trừ sách muốn delete
				}
			}
			fclose(ft);
			gotoxy(20, 8); printf("Xoa sach thanh cong     ");
		}
	}
	fclose(fBook);
	if (check == true)
	{
		remove("Book.bin");
		rename("Temp.bin", "Book.bin"); // xóa Book.bin cũ, đổi Temp.bin thành Book.bin mới
	}
	else if (check == false)
	{
		gotoxy(20, 8); printf("Khong tim thay sach      ");
	}
}
// menu quản lý sách
void MenuSach(ACCOUNT login)
{
	int luachon;
	do {
		system("cls");
		gotoxy(20, 3); printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 QUAN LY SACH \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(20, 4); printf("\xB2"); gotoxy(66, 4); printf("\xB2");
		gotoxy(20, 5); printf("\xB2"); gotoxy(66, 5); printf("\xB2");
		gotoxy(20, 6); printf("\xB2"); gotoxy(66, 6); printf("\xB2");
		gotoxy(20, 7); printf("\xB2"); gotoxy(66, 7); printf("\xB2");
		gotoxy(20, 8); printf("\xB2"); gotoxy(66, 8); printf("\xB2");
		gotoxy(20, 9); printf("\xB2"); gotoxy(66, 9); printf("\xB2");
		gotoxy(20, 10); printf("\xB2"); gotoxy(66, 10); printf("\xB2");
		gotoxy(20, 11); printf("\xB2"); gotoxy(66, 11); printf("\xB2");
		gotoxy(20, 12); printf("\xB2"); gotoxy(66, 12); printf("\xB2");
		gotoxy(20, 13); printf("\xB2"); gotoxy(66, 13); printf("\xB2");
		gotoxy(20, 14); printf("\xB2"); gotoxy(66, 14); printf("\xB2");
		gotoxy(20, 15); printf("\xB2"); gotoxy(66, 15); printf("\xB2");
		gotoxy(20, 16); printf("\xB2"); gotoxy(66, 16); printf("\xB2");
		gotoxy(20, 17); printf("\xB2"); gotoxy(66, 17); printf("\xB2");
		gotoxy(20, 18); printf("\xB2"); gotoxy(66, 18); printf("\xB2");
		gotoxy(20, 19); printf("\xB2"); gotoxy(66, 19); printf("\xB2");
		gotoxy(20, 20); printf("\xB2"); gotoxy(66, 20); printf("\xB2");
		gotoxy(20, 21); printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(21, 5); printf("\t 1. Danh sach sach trong thu vien");
		gotoxy(21, 7); printf("\t 2. Them sach");
		gotoxy(21, 9); printf("\t 3. Cap nhat thong tin sach");
		gotoxy(21, 11); printf("\t 4. Xoa sach");
		gotoxy(21, 13); printf("\t 5. Tim sach theo ISBN");
		gotoxy(21, 15); printf("\t 6. Tim sach theo ten sach");
		gotoxy(21, 17); printf("\t 7. Quay ve menu chinh");
		gotoxy(21, 19); printf("\t 8. Thoat chuong trinh");
		gotoxy(20, 23); printf("Lua chon cua ban:");
		scanf("%d", &luachon);
		switch (luachon)
		{
		case 1:
		{
			if (login.Permission == 1 || login.Permission == 3)
			{
				system("cls");
				ViewBook();
			}
			else
			{
				gotoxy(20, 27); printf("Ban khong co quyen su dung chuc nang nay            ");
			}
			system("pause");
			break;
		}
		case 2:
		{
			if (login.Permission == 1 || login.Permission == 3)
			{
				system("cls");
				AddBook();
			}
			else
			{
				gotoxy(20, 27); printf("Ban khong co quyen su dung chuc nang nay            ");
			}
			system("pause");
			break;
		}
		case 3:
		{
			if (login.Permission == 1 || login.Permission == 3)
			{
				system("cls");
				UpdateBook();
			}
			else
			{
				gotoxy(20, 27); printf("Ban khong co quyen su dung chuc nang nay            ");
			}
			system("pause");
			break;
		}
		case 4:
		{
			if (login.Permission == 1 || login.Permission == 3)
			{
				system("cls");
				DeleteBook();
			}
			else
			{
				gotoxy(20, 27); printf("Ban khong co quyen su dung chuc nang nay            ");
			}
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			SearchBookISBN();
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			SearchBookName();
			system("pause");
			break;
		}
		case 7:
		{
			if (login.Permission == 1)
			{
				MenuAdmin(login);
			}
			else if (login.Permission == 2)
			{
				MenuChuyenVien(login);
			}
			else if (login.Permission == 3)
			{
				MenuQuanLy(login);
			}
			break;
		}
		case 8:
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
			gotoxy(20, 25); printf("\aLua chon khong hop le. Vui long chon lai!      ");
			system("pause");
		}
		}
	} while (luachon != 8);
}

// thêm độc giả
void InputReader(READER &reader)
{
	while (getchar() != '\n');
	flushall();
	gotoxy(20, 6); printf("Ma doc gia: ");
	fgets(reader.ID, sizeof(reader.ID), stdin);
	gotoxy(20, 8); printf("Ho va ten: ");
	fgets(reader.FullName, sizeof(reader.FullName), stdin);
	gotoxy(20, 10); printf("CMND: ");
	fgets(reader.CMND, sizeof(reader.CMND), stdin);
	do {
		gotoxy(20, 12); printf("Gioi tinh (1 la Nam, 2 la Nu): ");
		scanf("%d", &reader.Genre);
		if (reader.Genre != 1 || reader.Genre != 2)
		{
			gotoxy(20, 14); printf("Vui long chi nhap so 1 hoac 2!");
		}
	} while (reader.Genre != 1 && reader.Genre != 2);
	while (getchar() != '\n');
	flushall();
	gotoxy(20, 14); printf("                              ");
	gotoxy(20, 14); printf("Email: ");
	fgets(reader.Email, sizeof(reader.Email), stdin);
	gotoxy(20, 16); printf("Dia chi: ");
	fgets(reader.Address, sizeof(reader.Address), stdin);
	int check = 0;
	do {
		gotoxy(20, 18); printf("Ngay sinh: ");
		scanf("%d", &reader.BirthDate.Day);
		gotoxy(20, 20); printf("Thang sinh: ");
		scanf("%d", &reader.BirthDate.Month);
		gotoxy(20, 22); printf("Nam sinh: ");
		scanf("%d", &reader.BirthDate.Year);
		check = CheckDate(reader.BirthDate);
		if (check != 0)
		{
			gotoxy(20, 24); printf("Ngay thang khong hop le. Vui long nhap lai\n");
		}
	} while (check != 0);
	gotoxy(20, 24); printf("                                            ");
	check = 0;
	do {
		gotoxy(20, 24); printf("Ngay lap the: ");
		scanf("%d", &reader.BornCard.Day);
		gotoxy(20, 26); printf("Thang lap the: ");
		scanf("%d", &reader.BornCard.Month);
		gotoxy(20, 28); printf("Nam lap the: ");
		scanf("%d", &reader.BornCard.Year);
		check = CheckDate(reader.BornCard);
		if (check != 0)
		{
			gotoxy(20, 30); printf("Ngay thang khong hop le. Vui long nhap lai\n");
		}
	} while (check != 0);
	reader.EndCard.Day = reader.BornCard.Day;
	reader.EndCard.Month = reader.BornCard.Month;
	reader.EndCard.Year = reader.BornCard.Year + 4;
}
bool ExistReader(FILE *f, READER reader)
{
	rewind(f);
	READER temp;
	while (fread(&temp, sizeof(READER), 1, f))
	{
		if (strcmp(temp.ID, reader.ID) == 0)
			return true;
	}
	return false;
}
void AddReader()
{
	READER reader;
	int choice;
	bool check = false;
	do {
		FILE *fReader = fopen("Reader.bin", "ab+");
		if (fReader == NULL)
		{
			printf("Khong mo duoc file");
		}
		system("cls");
		gotoxy(10, 4); printf(":::::::::::::::::::::: Them Doc Gia ::::::::::::::::::::::");
		InputReader(reader);
		if (ExistReader(fReader, reader) == false)
		{
			check = true;
			fseek(fReader, 0, SEEK_END);
			fwrite(&reader, sizeof(READER), 1, fReader);
			gotoxy(16, 30); printf("Them doc gia thanh cong.    ");
			fclose(fReader);
		}
		else
		{
			fclose(fReader);
			system("cls");
			gotoxy(10, 4); printf(":::::::::::::::::::::: Them Doc Gia ::::::::::::::::::::::");
			gotoxy(16, 10); printf("Doc gia da ton tai.");
			int choice;
			do {
				gotoxy(16, 12); printf("Thoat ra menu?");
				gotoxy(20, 14); printf("1. Co");
				gotoxy(20, 16); printf("2. Khong, nhap lai.");
				gotoxy(16, 18); printf("Lua chon cua ban: ");
				scanf("%d", &choice);
				if (choice != 1 && choice != 2)
				{
					gotoxy(16, 20); printf("Vui long chi nhap 1 hoac 2");
				}
			} while (choice != 1 && choice != 2);
			if (choice == 1)
				break;
			system("cls");
		}
	} while (check == false);
}
// xem độc giả
void ViewReader()
{
	system("cls");
	gotoxy(1, 1);
	printf("::::::::::::::::::::::::::::::: Danh sach Doc Gia :::::::::::::::::::::::::::::::::");
	gotoxy(2, 5);
	printf("ID       HO VA TEN            CMND       PHAI EMAIL                   DIA CHI                           NGAY SINH  HET HAN");
	FILE *fReader = fopen("Reader.bin", "rb");
	if (fReader == NULL)
	{
		printf("Khong mo duoc file");
	}
	rewind(fReader);
	int j = 7;
	int tong = 0;
	READER temp;
	while (fread(&temp, sizeof(READER), 1, fReader))
	{
		gotoxy(2, j); printf("%s", temp.ID);
		gotoxy(11, j); printf("%s", temp.FullName);
		gotoxy(32, j); printf("%s", temp.CMND);
		if (temp.Genre == 1)
		{
			gotoxy(43, j); printf("Nam");
		}
		else if (temp.Genre == 2)
		{
			gotoxy(43, j); printf("Nu");
		}
		gotoxy(48, j); printf("%s", temp.Email);
		gotoxy(72, j); printf("%s", temp.Address);
		gotoxy(106, j); printf("%d/%d/%d", temp.BirthDate.Day, temp.BirthDate.Month, temp.BirthDate.Year);
		gotoxy(117, j); printf("%d/%d/%d         ", temp.EndCard.Day, temp.EndCard.Month, temp.EndCard.Year);
		j++;
		tong++;
	}
	gotoxy(2, j + 4); printf("So luong doc gia: %d nguoi             ", tong);
	fclose(fReader);
}
// Chỉnh sửa thông tin 1 độc giả
void UpdateReader()
{
	while (getchar() != '\n');
	flushall();
	char IDtemp[MAX_PASS];
	gotoxy(10, 4); printf("::::::::::::::::::::Cap nhat thong tin Doc Gia::::::::::::::::::::");
	gotoxy(20, 6); printf("Nhap ID: ");
	fgets(IDtemp, sizeof(IDtemp), stdin);
	FILE *fReader = fopen("Reader.bin", "rb+");
	if (fReader == NULL)
	{
		printf("Khong mo duoc file");
	}
	rewind(fReader);
	READER temp;
	while (fread(&temp, sizeof(READER), 1, fReader))
	{
		if (strcmp(IDtemp, temp.ID) == 0)
		{
			// nhập info mới
			READER reader;
			//while (getchar() != '\n');
			//flushall();
			gotoxy(20, 8); printf("Ma doc gia moi: ");
			fgets(reader.ID, sizeof(reader.ID), stdin);
			gotoxy(20, 10); printf("Ho va ten moi: ");
			fgets(reader.FullName, sizeof(reader.FullName), stdin);
			gotoxy(20, 12); printf("CMND moi: ");
			fgets(reader.CMND, sizeof(reader.CMND), stdin);
			do {
				gotoxy(20, 14); printf("Gioi tinh moi (1 la Nam, 2 la Nu): ");
				scanf("%d", &reader.Genre);
				if (reader.Genre != 1 || reader.Genre != 2)
				{
					gotoxy(20, 16); printf("Vui long chi nhap so 1 hoac 2!");
				}
			} while (reader.Genre != 1 && reader.Genre != 2);
			while (getchar() != '\n');
			flushall();
			gotoxy(20, 16); printf("                              ");
			gotoxy(20, 16); printf("Email moi: ");
			fgets(reader.Email, sizeof(reader.Email), stdin);
			gotoxy(20, 18); printf("Dia chi moi: ");
			fgets(reader.Address, sizeof(reader.Address), stdin);
			int check = 0;
			do {
				gotoxy(20, 20); printf("Ngay sinh moi: ");
				scanf("%d", &reader.BirthDate.Day);
				gotoxy(20, 22); printf("Thang sinh moi: ");
				scanf("%d", &reader.BirthDate.Month);
				gotoxy(20, 24); printf("Nam sinh moi: ");
				scanf("%d", &reader.BirthDate.Year);
				check = CheckDate(reader.BirthDate);
				if (check != 0)
				{
					gotoxy(20, 26); printf("Ngay thang khong hop le. Vui long nhap lai\n");
				}
			} while (check != 0);
			gotoxy(20, 26); printf("                                            ");
			check = 0;
			do {
				gotoxy(20, 26); printf("Ngay lap moi: ");
				scanf("%d", &reader.BornCard.Day);
				gotoxy(20, 28); printf("Thang lap moi: ");
				scanf("%d", &reader.BornCard.Month);
				gotoxy(20, 30); printf("Nam lap moi: ");
				scanf("%d", &reader.BornCard.Year);
				check = CheckDate(reader.BornCard);
				if (check != 0)
				{
					gotoxy(20, 32); printf("Ngay thang khong hop le. Vui long nhap lai\n");
				}
			} while (check != 0);
			reader.EndCard.Day = reader.BornCard.Day;
			reader.EndCard.Month = reader.BornCard.Month;
			reader.EndCard.Year = reader.BornCard.Year + 4;
			// đi đến vị trí info để ghi
			fseek(fReader, ftell(fReader) - sizeof(READER), 0);
			fwrite(&reader, sizeof(READER), 1, fReader);
			gotoxy(20, 32); printf("Cap nhat doc gia thanh cong            \n");
		}
		else
		{
			gotoxy(20, 8); printf("Khong tim thay doc gia            ");
		}
	}
	fclose(fReader);
}
// xuất thông tin 1 độc giả
void OutputReader(READER reader)
{
	gotoxy(20, 8); printf("-----------------------------------------------");
	gotoxy(20, 10); printf("Ho va ten: %s", reader.FullName);
	gotoxy(20, 12); printf("CMND: %s", reader.CMND);
	if (reader.Genre == 1)
	{
		gotoxy(20, 14); printf("Gioi tinh: Nam");
	}
	else if (reader.Genre == 2)
	{
		gotoxy(20, 14); printf("Gioi tinh: Nu");
	}
	gotoxy(20, 16); printf("Email: %s", reader.Email);
	gotoxy(20, 18); printf("Dia chi: %s", reader.Address);
	gotoxy(20, 20); printf("Ngay sinh: %d/%d/%d", reader.BirthDate.Day, reader.BirthDate.Month, reader.BirthDate.Year);
	gotoxy(20, 22); printf("Ngay lap the: %d/%d/%d", reader.BornCard.Day, reader.BornCard.Month, reader.BornCard.Year);
	gotoxy(20, 24); printf("Ngay het han the: %d/%d/%d                 ", reader.EndCard.Day, reader.EndCard.Month, reader.EndCard.Year);
}
//Tìm kiếm độc giả theo CMND
void SearchReaderCMND()
{
	while (getchar() != '\n');
	flushall();
	char CMNDtemp[MAX_PASS];
	gotoxy(10, 4); printf(":::::::::::::::::::Tim kiem Doc Gia theo CMND:::::::::::::::::::");
	gotoxy(20, 6); printf("Nhap CMND: ");
	fgets(CMNDtemp, sizeof(CMNDtemp), stdin);
	FILE *fReader = fopen("Reader.bin", "rb");
	if (fReader == NULL)
	{
		printf("Khong mo duoc file");
	}
	rewind(fReader);
	READER temp;
	bool check = false; // để in ra ko tìm thấy sách
	while (fread(&temp, sizeof(READER), 1, fReader))
	{
		if (strcmp(CMNDtemp, temp.CMND) == 0)
		{
			// in ra info
			OutputReader(temp);
			check = true;
		}
	}
	fclose(fReader);
	if (check == false)
	{
		gotoxy(20, 8); printf("Khong tim thay doc gia       ");
	}
}
//Tìm kiếm độc giả theo họ tên
void SearchReaderName()
{
	while (getchar() != '\n');
	flushall();
	char FullNametemp[MAX_NAME];
	gotoxy(10, 4); printf("::::::::::::::::::::Tim kiem Doc Gia theo Ten::::::::::::::::::::");
	gotoxy(20, 6); printf("Nhap ten: ");
	fgets(FullNametemp, sizeof(FullNametemp), stdin);
	FILE *fReader = fopen("Reader.bin", "rb");
	if (fReader == NULL)
	{
		printf("Khong mo duoc file");
	}
	rewind(fReader);
	READER temp;
	bool check = false; // để in ra nếu ko tìm thấy độc giả
	while (fread(&temp, sizeof(READER), 1, fReader))
	{
		if (strcmp(FullNametemp, temp.FullName) == 0)
		{
			// in ra info
			OutputReader(temp);
			check = true;
		}
	}
	fclose(fReader);
	if (check == false)
	{
		fclose(fReader);
		gotoxy(20, 8); printf("Khong tim thay doc gia       ");
	}
}
//Xóa thông tin độc giả theo ID
void DeleteReader()
{
	while (getchar() != '\n');
	flushall();
	char IDtemp[MAX_PASS];
	gotoxy(10, 4); printf("::::::::::::::::::::::Xoa Doc Gia::::::::::::::::::::::");
	gotoxy(20, 6); printf("Nhap ID: ");
	fgets(IDtemp, sizeof(IDtemp), stdin);
	FILE *fReader = fopen("Reader.bin", "rb");
	if (fReader == NULL)
	{
		printf("Khong mo duoc file");
	}
	rewind(fReader);
	READER temp;
	bool check = false; // để ko cần phải remove + rename lúc đang đọc (mâu thuẫn)
	while (fread(&temp, sizeof(READER), 1, fReader))
	{
		if (strcmp(IDtemp, temp.ID) == 0)
		{
			check = true;
			FILE* ft = fopen("Temp.bin", "wb+");  // tạo temp.bin để ghi độc giả k bị delete
			rewind(fReader);
			while (fread(&temp, sizeof(READER), 1, fReader) == 1)
			{
				if (strcmp(temp.ID, IDtemp) != 0)
				{
					fseek(ft, 0, SEEK_CUR);
					fwrite(&temp, sizeof(READER), 1, ft); // ghi hết sách vào temp.bin trừ độc giả muốn delete
				}
			}
			fclose(ft);
			gotoxy(20, 8); printf("Xoa doc gia thanh cong     ");
		}
	}
	fclose(fReader);
	if (check == true)
	{
		remove("Reader.bin");
		rename("Temp.bin", "Reader.bin"); // xóa Reader.bin cũ, đổi temp.bin thành Reader.bin mới
	}
	else if (check == false)
	{
		gotoxy(20, 8); printf("Khong tim thay doc gia      ");
	}
}
// menu quản lý độc giả
void MenuDocGia(ACCOUNT login)
{
	int luachon;
	do {
		system("cls");
		gotoxy(20, 3); printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 QUAN LY DOC GIA \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(20, 4); printf("\xB2"); gotoxy(66, 4); printf("\xB2");
		gotoxy(20, 5); printf("\xB2"); gotoxy(66, 5); printf("\xB2");
		gotoxy(20, 6); printf("\xB2"); gotoxy(66, 6); printf("\xB2");
		gotoxy(20, 7); printf("\xB2"); gotoxy(66, 7); printf("\xB2");
		gotoxy(20, 8); printf("\xB2"); gotoxy(66, 8); printf("\xB2");
		gotoxy(20, 9); printf("\xB2"); gotoxy(66, 9); printf("\xB2");
		gotoxy(20, 10); printf("\xB2"); gotoxy(66, 10); printf("\xB2");
		gotoxy(20, 11); printf("\xB2"); gotoxy(66, 11); printf("\xB2");
		gotoxy(20, 12); printf("\xB2"); gotoxy(66, 12); printf("\xB2");
		gotoxy(20, 13); printf("\xB2"); gotoxy(66, 13); printf("\xB2");
		gotoxy(20, 14); printf("\xB2"); gotoxy(66, 14); printf("\xB2");
		gotoxy(20, 15); printf("\xB2"); gotoxy(66, 15); printf("\xB2");
		gotoxy(20, 16); printf("\xB2"); gotoxy(66, 16); printf("\xB2");
		gotoxy(20, 17); printf("\xB2"); gotoxy(66, 17); printf("\xB2");
		gotoxy(20, 18); printf("\xB2"); gotoxy(66, 18); printf("\xB2");
		gotoxy(20, 19); printf("\xB2"); gotoxy(66, 19); printf("\xB2");
		gotoxy(20, 20); printf("\xB2"); gotoxy(66, 20); printf("\xB2");
		gotoxy(20, 21); printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(21, 5); printf("\t 1. Danh sach doc gia trong thu vien");
		gotoxy(21, 7); printf("\t 2. Them doc gia");
		gotoxy(21, 9); printf("\t 3. Cap nhat thong tin doc gia");
		gotoxy(21, 11); printf("\t 4. Xoa doc gia");
		gotoxy(21, 13); printf("\t 5. Tim doc gia theo CMND");
		gotoxy(21, 15); printf("\t 6. Tim doc gia theo ten");
		gotoxy(21, 17); printf("\t 7. Quay ve menu chinh");
		gotoxy(21, 19); printf("\t 8. Thoat chuong trinh");
		gotoxy(20, 23); printf("Lua chon cua ban:");
		scanf("%d", &luachon);
		switch (luachon)
		{
		case 1:
		{
			system("cls");
			ViewReader();
			system("pause");
			break;
		}
		case 2:
		{
			system("cls");
			AddReader();
			system("pause");
			break;
		}
		case 3:
		{

			system("cls");
			UpdateReader();
			system("pause");
			break;
		}
		case 4:
		{
			if (login.Permission == 1 || login.Permission == 3)
			{
				system("cls");
				DeleteReader();
			}
			else
			{
				gotoxy(20, 27); printf("Ban khong co quyen su dung chuc nang nay            ");
			}
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			SearchReaderCMND();
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			SearchReaderName();
			system("pause");
			break;
		}
		case 7:
		{
			if (login.Permission == 1)
			{
				MenuAdmin(login);
			}
			else if (login.Permission == 2)
			{
				MenuChuyenVien(login);
			}
			else if (login.Permission == 3)
			{
				MenuQuanLy(login);
			}
			break;
		}
		case 8:
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
			gotoxy(20, 25); printf("\aLua chon khong hop le. Vui long chon lai!      ");
			system("pause");
		}
		}
	} while (luachon != 8);
}

// kiểm tra ID độc giả tồn tại trong Reader.bin ko
bool ExistIDReader(char ID[MAX_PASS])
{
	FILE *f = fopen("Reader.bin", "rb");
	rewind(f);
	READER temp;
	while (fread(&temp, sizeof(READER), 1, f))
	{
		if (strcmp(temp.ID, ID) == 0)
		{
			fclose(f);
			return true;
		}
	}
	fclose(f);
	return false;
}
// kiểm tra ISBN sách tồn tại trong Book.bin ko
bool ExistISBNBook(char ISBN[MAX_PASS])
{
	FILE *f = fopen("Book.bin", "rb");
	rewind(f);
	BOOK temp;
	while (fread(&temp, sizeof(BOOK), 1, f))
	{
		if (strcmp(temp.ISBN, ISBN) == 0)
		{
			fclose(f);
			return true;
		}
	}
	fclose(f);
	return false;
}
// thêm 7 ngày -> ngày trả
void Add7Day(DATES &Return)
{
	if (Return.Month == 1 || Return.Month == 3 || Return.Month == 5 || Return.Month == 7 || Return.Month == 8 || Return.Month == 10 || Return.Month == 12)
	{
		if (Return.Day <= 24)
		{
			Return.Day = Return.Day + 7;
		}
		else if (Return.Month == 12)
		{
			Return.Year++;
			Return.Month = 1;
			Return.Day = 7 - (31 - Return.Day);
		}
		else
		{
			Return.Month++;
			Return.Day = 7 - (31 - Return.Day);
		}
	}
	else if (Return.Month == 2)
	{
		if (Return.Year % 4 == 0)
		{
			if (Return.Day <= 22)
			{
				Return.Day = Return.Day + 7;
			}
			else
			{
				Return.Month++;
				Return.Day = 7 - (29 - Return.Day);
			}
		}
		else
		{
			if (Return.Day <= 21)
			{
				Return.Day = Return.Day + 7;
			}
			else
			{
				Return.Month++;
				Return.Day = 7 - (28 - Return.Day);
			}
		}
	}
	else
	{
		if (Return.Day <= 23)
		{
			Return.Day = Return.Day + 7;
		}
		else
		{
			Return.Month++;
			Return.Day = 7 - (30 - Return.Day);
		}
	}
}
// tăng borrow của sách theo ISBN + check nếu borrow>quantity 
bool IncreaseBorrow(char ISBN[MAX_PASS])
{
	FILE *f = fopen("Book.bin", "rb+");
	BOOK temp;
	rewind(f);
	while (fread(&temp, sizeof(BOOK), 1, f))
	{
		if (strcmp(temp.ISBN, ISBN) == 0)
		{
			temp.Borrow++;
			if (temp.Borrow > temp.Quantity)
			{
				fclose(f);
				return false;
			}
			fseek(f, ftell(f) - sizeof(BOOK), 0);
			fwrite(&temp, sizeof(BOOK), 1, f);
			fclose(f);
			return true;
		}
	}
}
// xuất ra phiếu mượn sách
void OutputPhieuMuonSach(PMS &Phieu)
{
	system("cls");
	gotoxy(36, 1); printf("*****************************************");
	gotoxy(36, 2); printf("|             PHIEU MUON SACH           |");
	gotoxy(36, 3); printf("*****************************************");
	gotoxy(36, 4); printf("|                                       |");
	gotoxy(36, 5); printf("|                                       |");
	gotoxy(36, 6); printf("|                                       |");
	gotoxy(36, 7); printf("|                                       |");
	gotoxy(36, 8); printf("|                                       |");
	gotoxy(36, 9); printf("|                                       |");
	gotoxy(36, 10); printf("|                                       |");
	gotoxy(36, 11); printf("|                                       |");
	gotoxy(36, 12); printf("|                                       |");
	gotoxy(36, 13); printf("|                                       |");
	gotoxy(36, 14); printf("|                                       |");
	gotoxy(36, 15); printf("|                                       |");
	gotoxy(36, 16); printf("|                                       |");
	gotoxy(36, 17); printf("|                                       |");
	gotoxy(36, 18); printf("|                                       |");
	gotoxy(36, 19); printf("|                                       |");
	gotoxy(36, 20); printf("*****************************************");
	gotoxy(40, 5); printf("Ma doc gia: ");
	puts(Phieu.ID);
	gotoxy(40, 7); printf("Thoi gian muon: %d/%d/%d", Phieu.Borrow.Day, Phieu.Borrow.Month, Phieu.Borrow.Year);
	gotoxy(40, 9); printf("Thoi gian tra du kien : %d/%d/%d", Phieu.Return.Day, Phieu.Return.Month, Phieu.Return.Year);
	gotoxy(40, 11); printf("Danh sach ISBN cac sach duoc muon");
	switch (Phieu.SL)
	{
	case 1:
		gotoxy(40, 13); printf("ISBN 1: ");
		puts(Phieu.ISBN1);
		break;
	case 2:
		gotoxy(40, 13); printf("ISBN 1: ");
		puts(Phieu.ISBN1);
		gotoxy(40, 15); printf("ISBN 2: ");
		puts(Phieu.ISBN2);
		break;
	case 3:
		gotoxy(40, 13); printf("ISBN 1: ");
		puts(Phieu.ISBN1);
		gotoxy(40, 15); printf("ISBN 2: ");
		puts(Phieu.ISBN2);
		gotoxy(40, 17); printf("ISBN 3: ");
		puts(Phieu.ISBN3);
		break;
	}
}
// nhập và ghi phiếu mượn sách
void InputPhieuMuonSach()
{
	system("cls");
	gotoxy(10, 4); printf(":::::::::::::::::::::Lap Phieu Muon Sach:::::::::::::::::::::");
	PMS Phieu;
	do {
		while (getchar() != '\n');
		flushall();
		gotoxy(20, 6); printf("Ma doc gia: ");
		fgets(Phieu.ID, sizeof(Phieu.ID), stdin);
		if (ExistIDReader(Phieu.ID) == false)
		{
			gotoxy(20, 8); printf("Doc gia khong ton tai. Vui long nhap lai");
		}
	} while (ExistIDReader(Phieu.ID) == false);
	int check = 0;
	do {
		gotoxy(20, 8); printf("                                        ");
		gotoxy(20, 8); printf("Ngay muon: ");
		scanf("%d", &Phieu.Borrow.Day);
		gotoxy(20, 10); printf("Thang muon: ");
		scanf("%d", &Phieu.Borrow.Month);
		gotoxy(20, 12); printf("Nam muon: ");
		scanf("%d", &Phieu.Borrow.Year);
		check = CheckDate(Phieu.Borrow);
		if (check != 0)
		{
			gotoxy(20, 14); printf("Ngay thang khong hop le. Vui long nhap lai\n");

		}
	} while (check != 0);
	Phieu.Return = Phieu.Borrow;
	Add7Day(Phieu.Return);
	// nhập các ISBN 
	do
	{
		gotoxy(20, 14); printf("                                            ");
		gotoxy(20, 14); printf("Nhap so luong sach muon muon (toi da 3): ");
		scanf("%d", &Phieu.SL);
		if (Phieu.SL < 1 && Phieu.SL > 3)
		{
			gotoxy(20, 16); printf("Chi duoc muon toi da 3 quyen. Vui long nhap lai");
		}
	} while (Phieu.SL < 1 && Phieu.SL > 3);
	switch (Phieu.SL)
	{
	case 1: // 1 ISBN
	{
		bool checkborrow = true; // để ko phải gọi IncreaseBorrow 2 lần (borrow sẽ bị tăng 2 lần)
		do {
			while (getchar() != '\n');
			flushall();
			gotoxy(20, 16); printf("                                               ");
			gotoxy(20, 16); printf("ISBN 1: ");
			fgets(Phieu.ISBN1, sizeof(Phieu.ISBN1), stdin);
			if (ExistISBNBook(Phieu.ISBN1) == false)
			{
				gotoxy(20, 18); printf("Sach khong ton tai. Vui long nhap lai.");
			}
			else if (IncreaseBorrow(Phieu.ISBN1) == false)
			{
				checkborrow = false; // để ko phải gọi IncreaseBorrow 2 lần
				gotoxy(20, 18); printf("Khong con sach de muon. Vui long nhap lai.");
			}
			else
				checkborrow = true;
		} while (ExistISBNBook(Phieu.ISBN1) == false || checkborrow == false);
		break;
	}
	case 2: // 2 ISBN
	{
		bool checkborrow = true;
		do {
			while (getchar() != '\n');
			flushall();
			gotoxy(20, 16); printf("                                               ");
			gotoxy(20, 16); printf("ISBN 1: ");
			fgets(Phieu.ISBN1, sizeof(Phieu.ISBN1), stdin);
			if (ExistISBNBook(Phieu.ISBN1) == false)
			{
				gotoxy(20, 18); printf("Sach khong ton tai. Vui long nhap lai.");
			}
			else if (IncreaseBorrow(Phieu.ISBN1) == false)
			{
				checkborrow = false; // để ko phải gọi IncreaseBorrow 2 lần
				gotoxy(20, 18); printf("Khong con sach de muon. Vui long nhap lai.");
			}
			else
				checkborrow = true;
		} while (ExistISBNBook(Phieu.ISBN1) == false || checkborrow == false);
		checkborrow = true;
		do {
			gotoxy(20, 18); printf("                                               ");
			gotoxy(20, 18); printf("ISBN 2: ");
			fgets(Phieu.ISBN2, sizeof(Phieu.ISBN2), stdin);
			if (ExistISBNBook(Phieu.ISBN2) == false)
			{
				gotoxy(20, 20); printf("Sach khong ton tai. Vui long nhap lai.");
			}
			else if (IncreaseBorrow(Phieu.ISBN2) == false)
			{
				checkborrow = false; // để ko phải gọi IncreaseBorrow 2 lần
				gotoxy(20, 20); printf("Khong con sach de muon. Vui long nhap lai.");
			}
			else
				checkborrow = true;
		} while (ExistISBNBook(Phieu.ISBN2) == false || checkborrow == false);
		break;
	}
	case 3: // 3 ISBN
	{
		bool checkborrow = true;
		do {
			while (getchar() != '\n');
			flushall();
			gotoxy(20, 16); printf("                                               ");
			gotoxy(20, 16); printf("ISBN 1: ");
			fgets(Phieu.ISBN1, sizeof(Phieu.ISBN1), stdin);
			if (ExistISBNBook(Phieu.ISBN1) == false)
			{
				gotoxy(20, 18); printf("Sach khong ton tai. Vui long nhap lai.");
			}
			else if (IncreaseBorrow(Phieu.ISBN1) == false)
			{
				checkborrow = false; // để ko phải gọi IncreaseBorrow 2 lần
				gotoxy(20, 18); printf("Khong con sach de muon. Vui long nhap lai.");
			}
			else
				checkborrow = true;
		} while (ExistISBNBook(Phieu.ISBN1) == false || checkborrow == false);
		checkborrow = true;
		do {
			gotoxy(20, 18); printf("                                               ");
			gotoxy(20, 18); printf("ISBN 2: ");
			fgets(Phieu.ISBN2, sizeof(Phieu.ISBN2), stdin);
			if (ExistISBNBook(Phieu.ISBN2) == false)
			{
				gotoxy(20, 20); printf("Sach khong ton tai. Vui long nhap lai.");
			}
			else if (IncreaseBorrow(Phieu.ISBN2) == false)
			{
				checkborrow = false; // để ko phải gọi IncreaseBorrow 2 lần
				gotoxy(20, 20); printf("Khong con sach de muon. Vui long nhap lai.");
			}
			else
				checkborrow = true;
		} while (ExistISBNBook(Phieu.ISBN2) == false || checkborrow == false);
		checkborrow = true;
		do {
			gotoxy(20, 20); printf("                                               ");
			gotoxy(20, 20); printf("ISBN 3: ");
			fgets(Phieu.ISBN3, sizeof(Phieu.ISBN3), stdin);
			if (ExistISBNBook(Phieu.ISBN3) == false)
			{
				gotoxy(20, 22); printf("Sach khong ton tai. Vui long nhap lai.");
			}
			else if (IncreaseBorrow(Phieu.ISBN3) == false)
			{
				checkborrow = false; // để ko phải gọi IncreaseBorrow 2 lần
				gotoxy(20, 22); printf("Khong con sach de muon. Vui long nhap lai.");
			}
			else
				checkborrow = true;
		} while (ExistISBNBook(Phieu.ISBN3) == false || checkborrow == false);
		break;
	}
	}
	// ghi file
	FILE *fMuon = fopen("PhieuMuon.bin", "ab");
	rewind(fMuon);
	if (fMuon == NULL)
	{
		printf("Mo file khong thanh cong");
	}
	fwrite(&Phieu, sizeof(PMS), 1, fMuon);
	gotoxy(20, 22); printf("Ghi phieu muon sach thanh cong         ");
	fclose(fMuon);
	OutputPhieuMuonSach(Phieu);
}

// PHIẾU TRẢ SÁCH ĐANG BUG T.T
// số ngày trễ hạn
int DayLate(PTS Phieu)
{
	int DayLate = 0;
	if (Phieu.Return.Year < Phieu.ReturnReal.Year)
	{
		Phieu.ReturnReal.Year = Phieu.ReturnReal.Year + 12;
	}
	DayLate = (Phieu.ReturnReal.Month - Phieu.Return.Month) * 2 * 30 - Phieu.Return.Day - (30 - Phieu.ReturnReal.Day);
	return DayLate;
}
// tìm giá của sách
int SearchPrice(char ISBN[MAX_PASS])
{
	FILE *fBook = fopen("Book.bin", "rb+");
	if (fBook == NULL)
	{
		printf("Khong mo duoc file");
	}
	BOOK temp;
	while (fread(&temp, sizeof(BOOK), 1, fBook))
	{
		if (strcmp(ISBN, temp.ISBN) == 0)
		{
			fclose(fBook);
			return temp.Price;
		}
	}
}
// tiền trễ hạn
int Bill(PTS &Phieu)
{
	Phieu.Bill = (DayLate(Phieu) * 5000) + SearchPrice(Phieu.ISBN1) + SearchPrice(Phieu.ISBN2) + SearchPrice(Phieu.ISBN3);
	return Phieu.Bill;
}
// kiểm tra ID độc giả tồn tại trong PhieuMuon.bin ko rồi copy ra PTS
bool ExistIDBorrow(char ID[MAX_PASS], PTS &Phieu)
{
	FILE *f = fopen("PhieuMuon.bin", "rb");
	rewind(f);
	PMS temp;
	while (fread(&temp, sizeof(PMS), 1, f))
	{
		if (strcmp(temp.ID, ID) == 0)
		{
			Phieu.Borrow = temp.Borrow;
			Phieu.Return = temp.Return;
			strcpy(Phieu.ISBN1, temp.ISBN1);
			strcpy(Phieu.ISBN2, temp.ISBN1);
			strcpy(Phieu.ISBN3, temp.ISBN1);
			Phieu.SL = temp.SL;
			fclose(f);
			return true;
		}
	}
	fclose(f);
	return false;
}
void OutputPhieuTraSach(PTS Phieu)
{
	system("cls");
	gotoxy(36, 1); printf("*****************************************");
	gotoxy(36, 2); printf("|              PHIEU TRA SACH           |");
	gotoxy(36, 3); printf("*****************************************");
	gotoxy(36, 4); printf("|                                       |");
	gotoxy(36, 5); printf("|                                       |");
	gotoxy(36, 6); printf("|                                       |");
	gotoxy(36, 7); printf("|                                       |");
	gotoxy(36, 8); printf("|                                       |");
	gotoxy(36, 9); printf("|                                       |");
	gotoxy(36, 10); printf("|                                       |");
	gotoxy(36, 11); printf("|                                       |");
	gotoxy(36, 12); printf("|                                       |");
	gotoxy(36, 13); printf("|                                       |");
	gotoxy(36, 14); printf("|                                       |");
	gotoxy(36, 15); printf("|                                       |");
	gotoxy(36, 16); printf("|                                       |");
	gotoxy(36, 17); printf("|                                       |");
	gotoxy(36, 18); printf("|                                       |");
	gotoxy(36, 19); printf("|                                       |");
	gotoxy(36, 20); printf("|                                       |");
	gotoxy(36, 21); printf("|                                       |");
	gotoxy(36, 22); printf("|                                       |");
	gotoxy(36, 23); printf("|                                       |");
	gotoxy(36, 24); printf("|                                       |");
	gotoxy(36, 25); printf("|                                       |");
	gotoxy(36, 26); printf("|                                       |");
	gotoxy(36, 27); printf("|                                       |");
	gotoxy(36, 28); printf("|                                       |");
	gotoxy(36, 29); printf("|                                       |");
	gotoxy(36, 30); printf("|                                       |");
	gotoxy(36, 31); printf("|                                       |");
	gotoxy(36, 32); printf("|                                       |");
	gotoxy(36, 33); printf("*****************************************");
	gotoxy(40, 5); printf("Ma doc gia: ");
	puts(Phieu.ID);
	gotoxy(40, 7); printf("Thoi gian muon: %d/%d/%d", Phieu.Borrow.Day, Phieu.Borrow.Month, Phieu.Borrow.Year);
	gotoxy(40, 9); printf("Thoi gian tra du kien: %d/%d/%d", Phieu.Return.Day, Phieu.Return.Month, Phieu.Return.Year);
	gotoxy(40, 11); printf("Thoi gian tra thuc te: %d/%d/%d", Phieu.ReturnReal.Day, Phieu.ReturnReal.Month, Phieu.ReturnReal.Year);
	gotoxy(40, 13); printf("Danh sach ISBN cac sach duoc muon");
	switch (Phieu.SL)
	{
	case 1:
	{
		gotoxy(40, 15); printf("ISBN 1: ");
		puts(Phieu.ISBN1);
		break;
	}
	case 2:
	{
		gotoxy(40, 15); printf("ISBN 1: ");
		puts(Phieu.ISBN1);
		gotoxy(40, 17); printf("ISBN 2: ");
		puts(Phieu.ISBN2);
		break;
	}
	case 3:
	{
		gotoxy(40, 15); printf("ISBN 1: ");
		puts(Phieu.ISBN1);
		gotoxy(40, 17); printf("ISBN 2: ");
		puts(Phieu.ISBN2);
		gotoxy(40, 19); printf("ISBN 3: ");
		puts(Phieu.ISBN3);
		break;
	}
	}
	if (Phieu.SLMat != 0)
	{
		gotoxy(40, 21); printf("Danh sach ISBN cac sach mat");
		switch (Phieu.SL)
		{
		case 1:
		{
			gotoxy(40, 23); printf("ISBN mat 1: ");
			puts(Phieu.Lost1);
			break;
		}
		case 2:
		{
			gotoxy(40, 23); printf("ISBN mat 1: ");
			puts(Phieu.Lost1);
			gotoxy(40, 25); printf("ISBN mat 2: ");
			puts(Phieu.Lost2);
			break;
		}
		case 3:
		{
			gotoxy(40, 23); printf("ISBN mat 1: ");
			puts(Phieu.Lost1);
			gotoxy(40, 25); printf("ISBN mat 2: ");
			puts(Phieu.Lost2);
			gotoxy(40, 27); printf("ISBN mat 3: ");
			puts(Phieu.Lost3);
			break;
		}
		}
	}
	gotoxy(40, 29); printf("Tien phai thanh toan: % dong", Phieu.Bill);
}
void InputPhieuTraSach()
{
	system("cls");
	gotoxy(10, 4); printf(":::::::::::::::::::::Lap Phieu Tra Sach:::::::::::::::::::::");
	PTS Phieu;
	do {
		while (getchar() != '\n');
		flushall();
		gotoxy(20, 6); printf("Ma doc gia: ");
		fgets(Phieu.ID, sizeof(Phieu.ID), stdin);
		if (ExistIDBorrow(Phieu.ID, Phieu) == false)
		{
			gotoxy(20, 8); printf("Doc gia nay chua muon sach. Vui long nhap lai");
		}
	} while (ExistIDBorrow(Phieu.ID, Phieu) == false);
	gotoxy(20, 8); printf("                                        ");
	int check = 0;
	do
	{
		gotoxy(20, 8); printf("Ngay tra thuc te: ");
		scanf("%d", &Phieu.ReturnReal.Day);
		gotoxy(20, 10); printf("Thang tra thuc te: ");
		scanf("%d", &Phieu.ReturnReal.Month);
		gotoxy(20, 12); printf("Nam tra thuc te: ");
		scanf("%d", &Phieu.ReturnReal.Year);
		check = CheckDate(Phieu.ReturnReal);
	} while (check != 0);
	gotoxy(20, 14); printf("So sach mat: ");
	scanf("%d", &Phieu.SLMat);
	switch (Phieu.SLMat)
	{
	case 1: // mất 1 cuốn
	{
		while (getchar() != '\n');
		flushall();
		gotoxy(20, 16); printf("ISBN sach mat 1: ");
		fgets(Phieu.Lost1, sizeof(Phieu.Lost1), stdin);
		Phieu.SL--;
		break;
	}
	case 2: // mất 2 cuốn
	{
		while (getchar() != '\n');
		flushall();
		gotoxy(20, 16); printf("ISBN sach mat 1: ");
		fgets(Phieu.Lost1, sizeof(Phieu.Lost1), stdin);
		gotoxy(20, 18); printf("ISBN sach mat 2: ");
		fgets(Phieu.Lost2, sizeof(Phieu.Lost2), stdin);
		Phieu.SL = Phieu.SL - 2;
		break;
	}
	case 3: // mất 3 cuốn
	{
		while (getchar() != '\n');
		flushall();
		printf("ISBN sach mat 1: ");
		fgets(Phieu.Lost1, sizeof(Phieu.Lost1), stdin);
		printf("ISBN sach mat 2: ");
		fgets(Phieu.Lost2, sizeof(Phieu.Lost2), stdin);
		printf("ISBN sach mat 3: ");
		fgets(Phieu.Lost3, sizeof(Phieu.Lost3), stdin);
		Phieu.SL = Phieu.SL - 3;
		break;
	}
	}
	Bill(Phieu);
	// ghi file
	FILE *fTra = fopen("PhieuTra.bin", "ab");
	rewind(fTra);
	if (fTra == NULL)
	{
		printf("Mo file khong thanh cong");
	}
	fwrite(&Phieu, sizeof(PTS), 1, fTra);
	gotoxy(20, 22); printf("Ghi phieu tra sach thanh cong         ");
	fclose(fTra);
	OutputPhieuTraSach(Phieu);
}



// thống kê loại sách
void KhoiTaoName(LIST_NAME &l)
{
	l.pHead = l.pTail = NULL;
}
NODE_NAME* TaoNodeName(char x[MAX_NAME], int quantity)
{
	NODE_NAME *p = new NODE_NAME;
	if (p == NULL)
	{
		return p;
	}
	p->num = quantity;
	strcpy(p->data, x);
	p->pNext = NULL;
	return p;
}
NODE_NAME* ThemDuoiName(LIST_NAME &l, NODE_NAME *p)
{
	if (l.pHead == NULL)
	{
		l.pHead = l.pTail = p;
	}
	else
	{
		l.pTail->pNext = p;
		l.pTail = p;
	}
	return p;
}
void CheckExistName(LIST_NAME &l, char name[MAX_NAME], int &check, int quantity)
{
	//  check 1 la chua co, 2 la da co
	if (l.pHead == NULL)
		check = 1;
	else
	{
		check = 1;
		for (NODE_NAME *p = l.pHead; p != NULL; p = p->pNext)
		{
			if (strcmp(p->data, name) == 0)
			{
				check = 2;
				p->num += quantity;
			}
		}
	}
}
void ViewBookCategory()
{
	system("cls");
	gotoxy(1, 1);
	printf("::::::::::::::::::::::::::::::: Sach theo The loai :::::::::::::::::::::::::::::::::");
	gotoxy(2, 5);
	printf("THE LOAI       SO LUONG");
	FILE *fBook = fopen("Book.bin", "rb");
	if (fBook == NULL)
	{
		printf("Khong mo duoc file");
	}
	LIST_NAME l;
	KhoiTaoName(l);
	int check;
	BOOK temp;
	rewind(fBook);
	while (fread(&temp, sizeof(BOOK), 1, fBook) == 1)
	{
		CheckExistName(l, temp.Categories, check, temp.Quantity);
		if (check == 1) // ten the loai chua co
		{
			NODE_NAME *p = TaoNodeName(temp.Categories, temp.Quantity);
			p = ThemDuoiName(l, p);
		}

	}
	// dem so luong the loai
	int tong = 0;
	for (NODE_NAME *p = l.pHead; p != NULL; p = p->pNext)
	{
		tong++;
	}
	// in so luong the loai ra
	int j = 7;
	for (NODE_NAME *p = l.pHead; p != NULL; p = p->pNext)
	{
		gotoxy(2, j); printf("%s", p->data);
		gotoxy(17, j); printf("%d", p->num);
		printf("\n\n");
		j++;
	}
	gotoxy(2, j + 4); printf("Co %d the loai         ", tong);
	fclose(fBook);
}
// thống kê số lượng sách đang được mượn
void ViewBorrow()
{
	system("cls");
	gotoxy(1, 1);
	printf("::::::::::::::::::::::::::::::: Danh sach Sach Dang Muon :::::::::::::::::::::::::::::::::");
	gotoxy(2, 5);
	printf("ISBN       TEN SACH                TEN TAC GIA        NHA XUAT BAN         NAM   THE LOAI      DON GIA(VND)     SL DANG MUON");
	FILE *fBook = fopen("Book.bin", "rb");
	if (fBook == NULL)
	{
		printf("Khong mo duoc file");
	}
	rewind(fBook);
	int j = 7;
	int tongmuon = 0;
	BOOK temp;
	while (fread(&temp, sizeof(BOOK), 1, fBook))
	{
		if (temp.Borrow != 0)
		{
			gotoxy(2, j); printf("%s", temp.ISBN);
			gotoxy(13, j); printf("%s", temp.Name);
			gotoxy(37, j); printf("%s", temp.Author);
			gotoxy(56, j); printf("NXB %s", temp.Publisher);
			gotoxy(78, j); printf("%d", temp.Issued.Year);
			gotoxy(85, j); printf("%s", temp.Categories);
			gotoxy(99, j); printf("%d", temp.Price);
			gotoxy(116, j); printf("%d          ", temp.Borrow);
			j++;
			tongmuon = tongmuon + temp.Borrow;
		}
	}
	gotoxy(2, j + 4); printf("So luong sach dang duoc muon: %d cuon             ", tongmuon);
	fclose(fBook);
}
// thống kê độc giả theo giới tính
void ViewReaderGenre()
{
	system("cls");
	gotoxy(1, 1);
	printf("::::::::::::::::::::::::::::::: Danh sach Doc Gia Nam :::::::::::::::::::::::::::::::::");
	gotoxy(2, 5);
	printf("ID       HO VA TEN            CMND       PHAI EMAIL                   DIA CHI                           NGAY SINH  HET HAN");
	FILE *fReader = fopen("Reader.bin", "rb");
	if (fReader == NULL)
	{
		printf("Khong mo duoc file");
	}
	rewind(fReader);
	int j = 7;
	int tongnam = 0;
	int tongnu = 0;
	READER temp;
	while (fread(&temp, sizeof(READER), 1, fReader))
	{
		if (temp.Genre == 1)
		{
			gotoxy(2, j); printf("%s", temp.ID);
			gotoxy(11, j); printf("%s", temp.FullName);
			gotoxy(32, j); printf("%s", temp.CMND);
			gotoxy(43, j); printf("Nam");
			gotoxy(48, j); printf("%s", temp.Email);
			gotoxy(72, j); printf("%s", temp.Address);
			gotoxy(106, j); printf("%d/%d/%d", temp.BirthDate.Day, temp.BirthDate.Month, temp.BirthDate.Year);
			gotoxy(117, j); printf("%d/%d/%d         ", temp.EndCard.Day, temp.EndCard.Month, temp.EndCard.Year);
			j++;
			tongnam++;
		}
	}
	j += 4;
	gotoxy(2, j); printf("So luong doc gia nam: %d nguoi             ", tongnam);
	j += 2;
	gotoxy(1, j);
	printf("::::::::::::::::::::::::::::::: Danh sach Doc Gia Nu :::::::::::::::::::::::::::::::::");
	j += 2; gotoxy(2, j);
	printf("ID       HO VA TEN            CMND       PHAI EMAIL                   DIA CHI                           NGAY SINH  HET HAN");
	rewind(fReader);
	j += 2;
	while (fread(&temp, sizeof(READER), 1, fReader))
	{
		if (temp.Genre == 2)
		{
			gotoxy(2, j); printf("%s", temp.ID);
			gotoxy(11, j); printf("%s", temp.FullName);
			gotoxy(32, j); printf("%s", temp.CMND);
			gotoxy(43, j); printf("Nu");
			gotoxy(48, j); printf("%s", temp.Email);
			gotoxy(72, j); printf("%s", temp.Address);
			gotoxy(106, j); printf("%d/%d/%d", temp.BirthDate.Day, temp.BirthDate.Month, temp.BirthDate.Year);
			gotoxy(117, j); printf("%d/%d/%d         ", temp.EndCard.Day, temp.EndCard.Month, temp.EndCard.Year);
			j++;
			tongnu++;
		}
	}
	gotoxy(2, j + 4); printf("So luong doc gia nu: %d nguoi             ", tongnu);
	fclose(fReader);
}
// thống kê đôc giả trễ hạn
void ViewTreHanReader()
{
	system("cls");
	gotoxy(1, 1);
	printf("::::::::::::::::::::::::::::::: Danh sach Doc Gia Tre Han :::::::::::::::::::::::::::::::::");
	gotoxy(2, 5);
	printf("ID");
	FILE *fReader = fopen("PhieuTra.bin", "rb");
	if (fReader == NULL)
	{
		printf("Khong mo duoc file");
	}
	rewind(fReader);
	int j = 7;
	int tong = 0;
	PTS temp;
	while (fread(&temp, sizeof(PTS), 1, fReader))
	{
		if (temp.Bill != 0)
		{
			gotoxy(2, j); printf("%s", temp.ID);
			j++;
			tong++;
		}
	}
	j += 4;
	gotoxy(2, j); printf("So luong doc gia tre han: %d nguoi             ", tong);
}
// menu thống kê
void MenuThongKe(ACCOUNT login)
{
	int luachon;
	do {
		system("cls");
		gotoxy(20, 3); printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 THONG KE CO BAN \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(20, 4); printf("\xB2"); gotoxy(66, 4); printf("\xB2");
		gotoxy(20, 5); printf("\xB2"); gotoxy(66, 5); printf("\xB2");
		gotoxy(20, 6); printf("\xB2"); gotoxy(66, 6); printf("\xB2");
		gotoxy(20, 7); printf("\xB2"); gotoxy(66, 7); printf("\xB2");
		gotoxy(20, 8); printf("\xB2"); gotoxy(66, 8); printf("\xB2");
		gotoxy(20, 9); printf("\xB2"); gotoxy(66, 9); printf("\xB2");
		gotoxy(20, 10); printf("\xB2"); gotoxy(66, 10); printf("\xB2");
		gotoxy(20, 11); printf("\xB2"); gotoxy(66, 11); printf("\xB2");
		gotoxy(20, 12); printf("\xB2"); gotoxy(66, 12); printf("\xB2");
		gotoxy(20, 13); printf("\xB2"); gotoxy(66, 13); printf("\xB2");
		gotoxy(20, 14); printf("\xB2"); gotoxy(66, 14); printf("\xB2");
		gotoxy(20, 15); printf("\xB2"); gotoxy(66, 15); printf("\xB2");
		gotoxy(20, 16); printf("\xB2"); gotoxy(66, 16); printf("\xB2");
		gotoxy(20, 17); printf("\xB2"); gotoxy(66, 17); printf("\xB2");
		gotoxy(20, 18); printf("\xB2"); gotoxy(66, 18); printf("\xB2");
		gotoxy(20, 19); printf("\xB2"); gotoxy(66, 19); printf("\xB2");
		gotoxy(20, 20); printf("\xB2"); gotoxy(66, 20); printf("\xB2");
		gotoxy(20, 21); printf("\xB2"); gotoxy(66, 21); printf("\xB2");
		gotoxy(20, 22); printf("\xB2"); gotoxy(66, 22); printf("\xB2");
		gotoxy(20, 23); printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(21, 5); printf("\t 1. So luong sach trong thu vien");
		gotoxy(21, 7); printf("\t 2. So luong sach theo the loai");
		gotoxy(21, 9); printf("\t 3. So luong doc gia");
		gotoxy(21, 11); printf("\t 4. So luong doc gia theo gioi tinh");
		gotoxy(21, 13); printf("\t 5. So sach dang duoc muon");
		gotoxy(21, 15); printf("\t 6. Doc gia bi tre han");
		gotoxy(21, 17); printf("\t 7. Danh sach tai khoan");
		gotoxy(21, 19); printf("\t 8. Quay ve menu chinh");
		gotoxy(21, 21); printf("\t 9. Thoat chuong trinh");
		gotoxy(20, 25); printf("Lua chon cua ban:");
		scanf("%d", &luachon);
		switch (luachon)
		{
		case 1:
		{
			if (login.Permission == 1 || login.Permission == 3)
			{
				system("cls");
				ViewBook();
			}
			else
			{
				gotoxy(20, 27); printf("Ban khong co quyen su dung chuc nang nay            ");
			}
			system("pause");
			break;
		}
		case 2:
		{
			if (login.Permission == 1 || login.Permission == 3)
			{
				system("cls");
				ViewBookCategory();
			}
			else
			{
				gotoxy(20, 27); printf("Ban khong co quyen su dung chuc nang nay            ");
			}
			system("pause");
			break;
		}
		case 3:
		{
			if (login.Permission == 1 || login.Permission == 3)
			{
				system("cls");
				ViewReader();
			}
			else
			{
				gotoxy(20, 27); printf("Ban khong co quyen su dung chuc nang nay            ");
			}
			system("pause");
			break;
		}
		case 4:
		{
			if (login.Permission == 1 || login.Permission == 3)
			{
				system("cls");
				ViewReaderGenre();
			}
			else
			{
				gotoxy(20, 27); printf("Ban khong co quyen su dung chuc nang nay            ");
			}
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			ViewBorrow();
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			ViewTreHanReader();
			system("pause");
			break;
		}
		case 7:
		{

			if (login.Permission == 1)
			{
				system("cls");
				ViewAcc();
			}
			else
			{
				gotoxy(20, 27); printf("Ban khong co quyen su dung chuc nang nay            ");
			}
			system("pause");
			break;
		}
		case 8:
		{
			if (login.Permission == 1)
			{
				MenuAdmin(login);
			}
			else if (login.Permission == 2)
			{
				MenuChuyenVien(login);
			}
			else if (login.Permission == 3)
			{
				MenuQuanLy(login);
			}
			break;
		}
		case 9:
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
			gotoxy(20, 27); printf("\aLua chon khong hop le. Vui long chon lai!      ");
			system("pause");
		}
		}
	} while (luachon != 9);

}

//menu admin
void MenuAdmin(ACCOUNT &login)
{
	int luachon;
	do {
		system("cls");
		gotoxy(20, 3); printf("\xB2\xB2\xB2\xB2\xB2\xB2 HE THONG QUAN LY THU VIEN - ADMIN \xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(20, 4); printf("\xB2"); gotoxy(66, 4); printf("\xB2");
		gotoxy(20, 5); printf("\xB2"); gotoxy(66, 5); printf("\xB2");
		gotoxy(20, 6); printf("\xB2"); gotoxy(66, 6); printf("\xB2");
		gotoxy(20, 7); printf("\xB2"); gotoxy(66, 7); printf("\xB2");
		gotoxy(20, 8); printf("\xB2"); gotoxy(66, 8); printf("\xB2");
		gotoxy(20, 9); printf("\xB2"); gotoxy(66, 9); printf("\xB2");
		gotoxy(20, 10); printf("\xB2"); gotoxy(66, 10); printf("\xB2");
		gotoxy(20, 11); printf("\xB2"); gotoxy(66, 11); printf("\xB2");
		gotoxy(20, 12); printf("\xB2"); gotoxy(66, 12); printf("\xB2");
		gotoxy(20, 13); printf("\xB2"); gotoxy(66, 13); printf("\xB2");
		gotoxy(20, 14); printf("\xB2"); gotoxy(66, 14); printf("\xB2");
		gotoxy(20, 15); printf("\xB2"); gotoxy(66, 15); printf("\xB2");
		gotoxy(20, 16); printf("\xB2"); gotoxy(66, 16); printf("\xB2");
		gotoxy(20, 17); printf("\xB2"); gotoxy(66, 17); printf("\xB2");
		gotoxy(20, 18); printf("\xB2"); gotoxy(66, 18); printf("\xB2");
		gotoxy(20, 19); printf("\xB2"); gotoxy(66, 19); printf("\xB2");
		gotoxy(20, 20); printf("\xB2"); gotoxy(66, 20); printf("\xB2");
		gotoxy(20, 21); printf("\xB2"); gotoxy(66, 21); printf("\xB2");
		gotoxy(20, 22); printf("\xB2"); gotoxy(66, 22); printf("\xB2");
		gotoxy(20, 23); printf("\xB2"); gotoxy(66, 23); printf("\xB2");
		gotoxy(20, 24); printf("\xB2"); gotoxy(66, 24); printf("\xB2");
		gotoxy(20, 25); printf("\xB2"); gotoxy(66, 25); printf("\xB2");
		gotoxy(20, 26); printf("\xB2"); gotoxy(66, 26); printf("\xB2");
		gotoxy(20, 27); printf("\xB2"); gotoxy(66, 23); printf("\xB2");
		gotoxy(20, 27); printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(21, 5); printf("\t 1. Dang xuat");
		gotoxy(21, 7); printf("\t 2. Thay doi mat khau");
		gotoxy(21, 9); printf("\t 3. Cap nhat thong tin ca nhan");
		gotoxy(21, 11); printf("\t 4. Tao tai khoan moi");
		gotoxy(21, 13); printf("\t 5. Phan quyen tai khoan");
		gotoxy(21, 15); printf("\t 6. Quan ly doc gia");
		gotoxy(21, 17); printf("\t 7. Quan ly sach");
		gotoxy(21, 19); printf("\t 8. Lap phieu muon sach");
		gotoxy(21, 21); printf("\t 9. Lap phieu tra sach");
		gotoxy(21, 23); printf("\t 10. Thong ke");
		gotoxy(21, 25); printf("\t 11. Thoat chuong trinh");
		gotoxy(20, 29); printf("Lua chon cua ban:");
		scanf("%d", &luachon);
		switch (luachon)
		{
		case 1:
		{
			menu();
			break;
		}
		case 2:
		{
			system("cls");
			char passtemp[MAX_PASS];
			bool check = false;
			do {
				// nhập pass 
				gotoxy(20, 8); printf("Nhap lai Password: ");
				// mã hóa mật khẩu
				gotoxy(39, 8);
				int p = 0;
				do {
					passtemp[p] = _getch();
					if (passtemp[p] != '\r')
					{
						printf("*");
					}
					p++;
				} while (passtemp[p - 1] != '\r');
				passtemp[p - 1] = '\0';
				if (strcmp(passtemp, login.Password) == 0)
				{
					check = true;
					system("cls");
					RePass(login);
					system("pause");
				}
				else
				{
					gotoxy(20, 10); printf("Ban da nhap sai Password");
					int choice;
					do {
						gotoxy(20, 12); printf("Thoat ra menu?");
						gotoxy(23, 14); printf("1. Co");
						gotoxy(23, 16); printf("2. Khong, nhap lai.");
						gotoxy(20, 18); printf("Lua chon cua ban: ");
						scanf("%d", &choice);
						if (choice != 1 && choice != 2)
							gotoxy(20, 20); printf("Vui long chi nhap 1 hoac 2 ");
					} while (choice != 1 && choice != 2);
					if (choice == 1)
						break;
					system("cls");
				}
			} while (check == false);
			break;
		}
		case 3:
		{
			// hiển thị thông tin ban đầu trước khi chỉnh sửa
			system("cls");
			gotoxy(10, 4); printf("::::::::::::::::::::Cap nhat thong tin ca nhan::::::::::::::::::::");
			printf("\n\n\t   Thong tin tai khoan\n");
			OutputInfo(login);
			system("pause");
			system("cls");
			//chỉnh sửa thông tin
			UpdateInfo(login);
			break;
		}
		case 4:
		{
			system("cls");
			CreateAcc();
			break;
		}
		case 5:
		{
			system("cls");
			PhanQuyen();
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			MenuDocGia(login);
			break;
		}
		case 7:
		{
			system("cls");
			MenuSach(login);
			break;
		}
		case 8:
		{
			system("cls");
			InputPhieuMuonSach();
			system("pause");
			break;
		}
		case 9:
		{
			system("cls");
			InputPhieuTraSach();
			system("pause");
			break;
		}
		case 10:
		{
			system("cls");
			MenuThongKe(login);
			system("pause");
			break;
		}
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
			gotoxy(20, 31); printf("\aLua chon khong hop le. Vui long chon lai!      ");
			system("pause");
		}
		}
	} while (luachon != 11);
}
// menu chuyên viên
void MenuChuyenVien(ACCOUNT &login)
{
	int luachon;
	do {
		system("cls");
		gotoxy(20, 3); printf("\xB2\xB2\xB2\xB2\xB2\xB2 HE THONG QUAN LY THU VIEN - CHUYEN VIEN \xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(20, 4); printf("\xB2"); gotoxy(72, 4); printf("\xB2");
		gotoxy(20, 5); printf("\xB2"); gotoxy(72, 5); printf("\xB2");
		gotoxy(20, 6); printf("\xB2"); gotoxy(72, 6); printf("\xB2");
		gotoxy(20, 7); printf("\xB2"); gotoxy(72, 7); printf("\xB2");
		gotoxy(20, 8); printf("\xB2"); gotoxy(72, 8); printf("\xB2");
		gotoxy(20, 9); printf("\xB2"); gotoxy(72, 9); printf("\xB2");
		gotoxy(20, 10); printf("\xB2"); gotoxy(72, 10); printf("\xB2");
		gotoxy(20, 11); printf("\xB2"); gotoxy(72, 11); printf("\xB2");
		gotoxy(20, 12); printf("\xB2"); gotoxy(72, 12); printf("\xB2");
		gotoxy(20, 13); printf("\xB2"); gotoxy(72, 13); printf("\xB2");
		gotoxy(20, 14); printf("\xB2"); gotoxy(72, 14); printf("\xB2");
		gotoxy(20, 15); printf("\xB2"); gotoxy(72, 15); printf("\xB2");
		gotoxy(20, 16); printf("\xB2"); gotoxy(72, 16); printf("\xB2");
		gotoxy(20, 17); printf("\xB2"); gotoxy(72, 17); printf("\xB2");
		gotoxy(20, 18); printf("\xB2"); gotoxy(72, 18); printf("\xB2");
		gotoxy(20, 19); printf("\xB2"); gotoxy(72, 19); printf("\xB2");
		gotoxy(20, 20); printf("\xB2"); gotoxy(72, 20); printf("\xB2");
		gotoxy(20, 21); printf("\xB2"); gotoxy(72, 21); printf("\xB2");
		gotoxy(20, 22); printf("\xB2"); gotoxy(72, 22); printf("\xB2");
		gotoxy(20, 23); printf("\xB2"); gotoxy(72, 23); printf("\xB2");
		gotoxy(20, 23); printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(21, 5); printf("\t 1. Dang xuat");
		gotoxy(21, 7); printf("\t 2. Thay doi mat khau");
		gotoxy(21, 9); printf("\t 3. Cap nhat thong tin ca nhan");
		gotoxy(21, 11); printf("\t 4. Quan ly doc gia");
		gotoxy(21, 13); printf("\t 5. Quan ly sach");
		gotoxy(21, 15); printf("\t 6. Lap phieu muon sach");
		gotoxy(21, 17); printf("\t 7. Lap phieu tra sach");
		gotoxy(21, 19); printf("\t 8. Thong ke");
		gotoxy(21, 21); printf("\t 9. Thoat chuong trinh");
		gotoxy(21, 25); printf("Lua chon cua ban:");
		scanf("%d", &luachon);
		switch (luachon)
		{
		case 1:
		{
			menu();
			break;
		}
		case 2:
		{
			system("cls");
			bool check = false;
			char passtemp[MAX_PASS];
			do {
				// nhập pass 
				gotoxy(20, 8); printf("Nhap lai Password: ");
				// mã hóa mật khẩu
				gotoxy(39, 8);
				int p = 0;
				do {
					passtemp[p] = _getch();
					if (passtemp[p] != '\r')
					{
						printf("*");
					}
					p++;
				} while (passtemp[p - 1] != '\r');
				passtemp[p - 1] = '\0';
				if (strcmp(passtemp, login.Password) == 0)
				{
					check = true;
					system("cls");
					RePass(login);
					system("pause");
				}
				else
				{
					gotoxy(20, 10); printf("Ban da nhap sai Password");
					int choice;
					do {
						gotoxy(20, 12); printf("Thoat ra menu?");
						gotoxy(23, 14); printf("1. Co");
						gotoxy(23, 16); printf("2. Khong, nhap lai.");
						gotoxy(20, 18); printf("Lua chon cua ban: ");
						scanf("%d", &choice);
						if (choice != 1 && choice != 2)
							gotoxy(20, 20); printf("Vui long chi nhap 1 hoac 2 ");
					} while (choice != 1 && choice != 2);
					if (choice == 1)
						break;
					system("cls");
				}
			} while (check == false);
			break;
		}
		case 3:
		{
			// hiển thị thông tin ban đầu trước khi chỉnh sửa
			system("cls");
			gotoxy(10, 4); printf("::::::::::::::::::::Cap nhat thong tin ca nhan::::::::::::::::::::");
			printf("\n\n\t   Thong tin tai khoan\n");
			OutputInfo(login);
			system("pause");
			system("cls");
			//chỉnh sửa thông tin
			UpdateInfo(login);
			break;
		}
		case 4:
		{
			system("cls");
			MenuDocGia(login);
			break;
		}
		case 5:
		{
			system("cls");
			MenuSach(login);
			break;
		}
		case 6:
		{
			system("cls");
			InputPhieuMuonSach();
			system("pause");
			break;
		}
		case 7:
		{
			system("cls");
			InputPhieuTraSach();
			system("pause");
			break;
		}
		case 8:
		{
			system("cls");
			MenuThongKe(login);
			system("pause");
			break;
		}
		case 9:
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
			gotoxy(21, 27); printf("\aChon sai, vui long chon lai! "); system("pause");
		}
		}
	} while (luachon != 9);
}
// menu quản lý
void MenuQuanLy(ACCOUNT &login)
{
	int luachon;
	do {
		system("cls");
		gotoxy(20, 3); printf("\xB2\xB2\xB2\xB2\xB2\xB2 HE THONG QUAN LY THU VIEN - QUAN LY \xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(20, 4); printf("\xB2"); gotoxy(68, 4); printf("\xB2");
		gotoxy(20, 5); printf("\xB2"); gotoxy(68, 5); printf("\xB2");
		gotoxy(20, 6); printf("\xB2"); gotoxy(68, 6); printf("\xB2");
		gotoxy(20, 7); printf("\xB2"); gotoxy(68, 7); printf("\xB2");
		gotoxy(20, 8); printf("\xB2"); gotoxy(68, 8); printf("\xB2");
		gotoxy(20, 9); printf("\xB2"); gotoxy(68, 9); printf("\xB2");
		gotoxy(20, 10); printf("\xB2"); gotoxy(68, 10); printf("\xB2");
		gotoxy(20, 11); printf("\xB2"); gotoxy(68, 11); printf("\xB2");
		gotoxy(20, 12); printf("\xB2"); gotoxy(68, 12); printf("\xB2");
		gotoxy(20, 13); printf("\xB2"); gotoxy(68, 13); printf("\xB2");
		gotoxy(20, 14); printf("\xB2"); gotoxy(68, 14); printf("\xB2");
		gotoxy(20, 15); printf("\xB2"); gotoxy(68, 15); printf("\xB2");
		gotoxy(20, 16); printf("\xB2"); gotoxy(68, 16); printf("\xB2");
		gotoxy(20, 17); printf("\xB2"); gotoxy(68, 17); printf("\xB2");
		gotoxy(20, 18); printf("\xB2"); gotoxy(68, 18); printf("\xB2");
		gotoxy(20, 19); printf("\xB2"); gotoxy(68, 19); printf("\xB2");
		gotoxy(20, 20); printf("\xB2"); gotoxy(68, 20); printf("\xB2");
		gotoxy(20, 21); printf("\xB2"); gotoxy(68, 21); printf("\xB2");
		gotoxy(20, 22); printf("\xB2"); gotoxy(68, 22); printf("\xB2");
		gotoxy(20, 23); printf("\xB2"); gotoxy(68, 23); printf("\xB2");
		gotoxy(20, 23); printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(21, 5); printf("\t 1. Dang xuat");
		gotoxy(21, 7); printf("\t 2. Thay doi mat khau");
		gotoxy(21, 9); printf("\t 3. Cap nhat thong tin ca nhan");
		gotoxy(21, 11); printf("\t 4. Quan ly doc gia");
		gotoxy(21, 13); printf("\t 5. Quan ly sach");
		gotoxy(21, 15); printf("\t 6. Lap phieu muon sach");
		gotoxy(21, 17); printf("\t 7. Lap phieu tra sach");
		gotoxy(21, 19); printf("\t 8. Thong ke");
		gotoxy(21, 21); printf("\t 9. Thoat chuong trinh");
		gotoxy(21, 25); printf("Lua chon cua ban:");
		scanf("%d", &luachon);
		switch (luachon)
		{
		case 1:
		{
			menu();
			break;
		}
		case 2:
		{
			system("cls");
			bool check = false;
			char passtemp[MAX_PASS];
			do {
				// nhập pass 
				gotoxy(20, 8); printf("Nhap lai Password: ");
				// mã hóa mật khẩu
				gotoxy(39, 8);
				int p = 0;
				do {
					passtemp[p] = _getch();
					if (passtemp[p] != '\r')
					{
						printf("*");
					}
					p++;
				} while (passtemp[p - 1] != '\r');
				passtemp[p - 1] = '\0';
				if (strcmp(passtemp, login.Password) == 0)
				{
					check = true;
					system("cls");
					RePass(login);
					system("pause");
				}
				else
				{
					gotoxy(20, 10); printf("Ban da nhap sai Password");
					int choice;
					do {
						gotoxy(20, 12); printf("Thoat ra menu?");
						gotoxy(23, 14); printf("1. Co");
						gotoxy(23, 16); printf("2. Khong, nhap lai.");
						gotoxy(20, 18); printf("Lua chon cua ban: ");
						scanf("%d", &choice);
						if (choice != 1 && choice != 2)
							gotoxy(20, 20); printf("Vui long chi nhap 1 hoac 2 ");
					} while (choice != 1 && choice != 2);
					if (choice == 1)
						break;
					system("cls");
				}
			} while (check == false);
			break;
		}
		case 3:
		{
			// hiển thị thông tin ban đầu trước khi chỉnh sửa
			system("cls");
			gotoxy(10, 4); printf("::::::::::::::::::::Cap nhat thong tin ca nhan::::::::::::::::::::");
			printf("\n\n\t   Thong tin tai khoan\n");
			OutputInfo(login);
			system("pause");
			system("cls");
			//chỉnh sửa thông tin
			UpdateInfo(login);
			break;
		}
		case 4:
		{
			system("cls");
			MenuDocGia(login);
			break;
		}
		case 5:
		{
			system("cls");
			MenuSach(login);
			break;
		}
		case 6:
		{
			system("cls");
			InputPhieuMuonSach();
			system("pause");
			break;
		}
		case 7:
		{
			system("cls");
			InputPhieuTraSach();
			system("pause");
			break;
		}
		case 8:
		{
			system("cls");
			MenuThongKe(login);
			system("pause");
			break;
		}
		case 9:
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
			gotoxy(21, 27); printf("\aChon sai, vui long chon lai! "); system("pause");
		}
		}
	} while (luachon != 9);
}






