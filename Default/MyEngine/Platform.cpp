#include "stdafx.h"
#include "Platform.h"


Platform::Platform()
{
}


Platform::~Platform()
{
}


VOID Platform::Initialize(char * n)
{
	char* temp = NULL;
	pos.x = atoi(strtok_s(n, " ", &temp));
	pos.y = atoi(strtok_s(NULL, " ", &temp));
	txtid = atoi(strtok_s(NULL, " ", &temp));
	SetComponent();
}