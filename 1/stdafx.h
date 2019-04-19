// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

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
typedef Date DATE;
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

// TODO: reference additional headers your program requires here
