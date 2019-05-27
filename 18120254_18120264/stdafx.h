#pragma once
#ifndef __STDAFX_H__
#define __STDAFX_H__

#include "targetver.h"
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <windows.h>
#include <conio.h>


// DEFINE 
#define MAX_PASS 25		 // độ dài tối đa
#define MAX_USERNAME 25 
#define MAX_PRICE 9
#define MAX_NAME 64 
#define THIS_YEAR 2020  // năm hiện tại để check date
#define LIMIT_YEAR 1900


// STRUCT
// dslk dùng để thống kê sách theo thể loại
struct NodeName {
	char data[MAX_NAME];
	int num; // số lượng sách của thể loại đó
	struct NodeName *pNext;
};
typedef struct NodeName NODE_NAME;

struct ListName {
	struct NodeName *pHead;
	struct NodeName *pTail;
};
typedef struct ListName LIST_NAME;

// format: D/M/Y
struct Date
{
	int Day;
	int Month;
	int Year;
};
typedef Date DATES;
// thông tin người dùng
struct Account
{
	char Username[MAX_USERNAME];
	char Password[MAX_PASS];
	char FullName[MAX_NAME];
	DATES BirthDate;
	char CMND[MAX_PASS];
	char Address[MAX_NAME];
	int Genre;		   // 1:Nam, 2:Nu
	int Status;		  // 1:Active, 2:Blocked
	int Permission;  // 1:Admin, 2:ChuyenVien, 3:QuanLy
};
typedef Account ACCOUNT;
// thông tin thẻ độc giả
struct Reader
{
	char ID[MAX_PASS];
	char FullName[MAX_NAME];
	char CMND[MAX_PASS];
	DATES BirthDate;
	int Genre;					// 1:Nam, 2:Nu
	char Email[MAX_NAME];
	char Address[MAX_NAME];
	DATES BornCard;
	DATES EndCard; // 48 months since born
};
typedef Reader READER;
// thông tin sách
struct Book
{
	char ISBN[MAX_PASS];
	char Name[MAX_NAME];
	char Author[MAX_NAME];
	char Publisher[MAX_NAME];
	DATES Issued;
	char Categories[MAX_NAME];
	int Price;
	int Quantity;
	int Borrow; // số sách đang được mượn
};
typedef Book BOOK;
struct phieumuonsach
{
	char ID[MAX_PASS];
	DATES Borrow;
	DATES Return;
	char ISBN1[MAX_PASS];
	char ISBN2[MAX_PASS];
	char ISBN3[MAX_PASS];
	int SL;
};
typedef struct phieumuonsach PMS;
struct phieumuontrasach
{
	char ID[MAX_PASS];
	DATES Borrow;
	DATES Return;
	char ISBN1[MAX_PASS];
	char ISBN2[MAX_PASS];
	char ISBN3[MAX_PASS];
	int SL;
	int SLMat;
	DATES ReturnReal;
	char Lost1[MAX_PASS];
	char Lost2[MAX_PASS];
	char Lost3[MAX_PASS];
	int Bill;
};
typedef struct phieumuontrasach PTS;

// PROTOTYPE
void gotoxy(int x, int y);
// kiểm tra ngày hợp lệ
int CheckDate(DATES BirthDate);
// xuất thông tin 1 tài khoản
void OutputInfo(ACCOUNT login);
// thay đổi mật khẩu
void RePass(ACCOUNT &login);
// cập nhật thông tin cá nhân 
void UpdateInfo(ACCOUNT &login);
// nhập thông tin 1 tài khoản
void InputInfo(ACCOUNT &acc);
//kiểm tra tài khoản đã tồn tại, return true nếu có tồn tại
bool ExistAcc(FILE *f, ACCOUNT acc);
// thêm tài khoản
void CreateAcc();
// kiểm tra tài khoản đăng nhập  
void CheckLogin(FILE *f, char username[MAX_PASS], char pass[MAX_USERNAME], ACCOUNT &login, int &checkacc);
// phân quyền tài khoản
void PhanQuyen();
// xem tài khoản
void ViewAcc();


// xem sách
void ViewBook();
// thêm sách
void InputBook(BOOK &book);
bool ExistBook(FILE *f, BOOK book);
void AddBook();
// Chỉnh sửa thông tin 1 quyển sách
void UpdateBook();
// xuất thông tin 1 quyển sách
void OutputBook(BOOK book);
//Tìm kiếm sách theo ISBN
void SearchBookISBN();
//Tìm kiếm sách theo tên sách
void SearchBookName();
//Xóa thông tin sách theo ISBN
void DeleteBook();
// menu quản lý sách
void MenuSach(ACCOUNT login);


// thêm độc giả
void InputReader(READER &reader);
bool ExistReader(FILE *f, READER reader);
void AddReader();
// xem độc giả
void ViewReader();
// Chỉnh sửa thông tin 1 độc giả
void UpdateReader();
// xuất thông tin 1 độc giả
void OutputReader(READER reader);
//Tìm kiếm độc giả theo CMND
void SearchReaderCMND();
//Tìm kiếm độc giả theo họ tên
void SearchReaderName();
//Xóa thông tin độc giả theo ID
void DeleteReader();
// menu quản lý độc giả
void MenuDocGia(ACCOUNT login);


// kiểm tra ID độc giả tồn tại ko
bool ExistIDReader(char ID[MAX_PASS]);
// kiểm tra ISBN sách tồn tại ko
bool ExistISBNBook(char ISBN[MAX_PASS]);
// thêm 7 ngày -> ngày trả
void Add7Day(DATES &Return);
// tăng borrow của sách theo ISBN + check nếu borrow>quantity 
bool IncreaseBorrow(char ISBN[MAX_PASS]);
// xuất ra phiếu mượn sách
void OutputPhieuMuonSach(PMS &Phieu);
// nhập và ghi phiếu mượn sách
void InputPhieuMuonSach();

// số ngày trễ hạn
int DayLate(PTS Phieu);
// tìm giá của sách
int SearchPrice(char ISBN[MAX_PASS]);
// tiền trễ hạn
int Bill(PTS &Phieu);
// kiểm tra ID độc giả tồn tại trong PhieuMuon.bin ko rồi copy ra PTS
bool ExistIDBorrow(char ID[MAX_PASS], PTS &Phieu);
void OutputPhieuTraSach(PTS Phieu);
void InputPhieuTraSach();


// thống kê loại sách
void KhoiTaoName(LIST_NAME &l);
NODE_NAME* TaoNodeName(char x[MAX_NAME], int quantity);
NODE_NAME* ThemDuoiName(LIST_NAME &l, NODE_NAME *p);
void CheckExistName(LIST_NAME &l, char name[MAX_NAME], int &check, int quantity);
void ViewBookCategory();
// thống kê số lượng sách đang được mượn
void ViewBorrow();
// thống kê độc giả theo giới tính
void ViewReaderGenre();
// thống kê đôc giả trễ hạn
void ViewTreHanReader();
// menu thống kê
void MenuThongKe(ACCOUNT login);


//menu đăng nhập
void menu();
// đăng nhập
void Login(int &luachon);
//menu admin
void MenuAdmin(ACCOUNT &login);
// menu chuyên viên
void MenuChuyenVien(ACCOUNT &login);
// menu quản lý
void MenuQuanLy(ACCOUNT &login);
#endif