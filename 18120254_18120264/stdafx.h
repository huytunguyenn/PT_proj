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

// độ dài tối đa
#define MAX_PASS 25 
#define MAX_USERNAME 25 
#define MAX_NAME 64 
#define THIS_YEAR 2019 // năm hiện tại để check date
#define LIMIT_YEAR 1900

struct Date  // format: DD/MM/YY
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
	char ID[15];
	char FullName[MAX_NAME];
	char CMND[15];
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
	char ISBN;
	char Name[MAX_NAME];
	char Author[MAX_NAME];
	char Publisher[MAX_NAME];
	DATES Issued;
	char Catagories[MAX_NAME];
	char Price;
	int Quantity;
};
typedef Book BOOK;


void gotoxy(int x, int y);
#endif