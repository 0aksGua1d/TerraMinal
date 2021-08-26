#pragma once
#include <windows.h>
#include "Position.h"


typedef struct
{
	WCHAR ch;
	WORD attr;
	Position pos;
	unsigned long id;
} Letter;

