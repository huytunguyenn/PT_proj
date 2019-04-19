// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include "iostream"
#include "string.h"
#include <windows.h>
#include <conio.h>

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

struct User
{
	ACCOUNT Acc;
	char FullName[64]{ 0 };
	DATE BirthDate;
	int CMND{ 0 };
	char Address[64]{ 0 };
	bool Genre{ 0 }; // 0 is female, 1 is male
	bool Condition{ 0 }; // 0 is block, 1 is activated	
};
typedef User USER;
struct Database // using linked list
{
	USER data;
	USER *pNext;
};
typedef Database DATABASE;

// TODO: reference additional headers your program requires here
