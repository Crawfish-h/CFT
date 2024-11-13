#pragma once
#include <stdlib.h>
#include <string.h>
#include "Type_Info.h"

typedef struct FString_t
{
    TArray(char) Data_;
    size_t Size_;
    size_t Capacity_;
} FString;

FString* FString_Init(String string_Data);
void FString_Push(FString* string, String new_Str);
void FString_Remove(FString* string, const String sub_Str);
void FString_Free(FString* string);