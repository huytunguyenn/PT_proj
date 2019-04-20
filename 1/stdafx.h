// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#include "targetver.h"


#define _CRT_SECURE_NO_WARNINGS
#define MAX_PASS 25 //độ dài mật khẩu
#define MAX_USERNAME 25
#include <tchar.h>
#include "stdio.h"
#include "iostream"
#include "string.h"
#include "windows.h"
#include "conio.h"


struct Account
{
	char Username[64]{ 0 };
	char Password[64]{ 0 };
};
typedef Account ACCOUNT;
struct Date  // format: DD/MM/YY
{
	int Day{ 0 };
	int Month{ 0 };
	int Year{ 0 };
};
typedef Date DATES;
struct User
{
	int id;
	ACCOUNT Acc;
	char FullName[64]{ 0 };
	struct Date BirthDate;
	int CMND{ 0 };
	char Address[64]{ 0 };
	bool Genre{ 0 }; // 0 is female, 1 is male
	bool Condition{ 0 }; // 0 is block, 1 is activated	
};
typedef User USER;
struct Book
{
	int id{ 0 };
	char stname[20];
	char name[20];
	char Author[20];
	int quantity;
	float Price;
	int count;
	int rackno;
	char *cat;
	struct Date  issued;
	struct Date  duedate;
};
typedef Book BOOK;


// TODO: reference additional headers your program requires here
