#pragma once
#include "FType.h"

typedef struct SType_Manager
{
    FMap Types;
} SType_Manager;

extern SType_Manager Global_Type_Manager;

void Type_Manager_Add_Type(FType* type);
void Type_Manager_Free();