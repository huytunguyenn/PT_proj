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
#define THIS_YEAR 2019  // năm hiện tại để check date
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
struct User
{
	char ID[MAX_PASS];
	char FullName[MAX_NAME];
	char CMND[MAX_PASS];
	DATES BirthDate;
	bool Genre; // 0 is female, 1 is male	
	char Email[MAX_NAME];
	char Address[MAX_NAME];
	DATES BornCard;
	DATES EndCard; // 48 months since born
};
typedef User USER;
// thông tin sách
struct Book
{
	char ISBN[MAX_PASS];
	char Name[MAX_NAME];
	char Author[MAX_NAME];
	char Publisher[MAX_NAME];
	DATES Issued;
	char Categories[MAX_NAME];
	char Price[MAX_PRICE];
	int Quantity;
	int Borrow; // số sách đang được mượn
};
typedef Book BOOK;


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


// xem sách
void ViewBook();
// thêm sách
void InputBook(BOOK &book);
bool ExistBook(FILE *f, BOOK book);
void AddBook();
// số lượng loại sách
void KhoiTaoName(LIST_NAME &l);
NODE_NAME* TaoNodeName(char x[MAX_NAME], int quantity);
NODE_NAME* ThemDuoiName(LIST_NAME &l, NODE_NAME *p);
void CheckExistName(LIST_NAME &l, char name[MAX_NAME], int &check, int quantity);
void ViewBookCategory();


// menu quản lý sách
void MenuSach(ACCOUNT login);
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