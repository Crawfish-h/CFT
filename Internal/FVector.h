#pragma once
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "Type_Info.h"
#include "CFT_Macros.h"


#define Vector_Types_Size 100

typedef char Byte;
typedef unsigned char uByte;

typedef struct Element
{
    String Type_;
    void* Value_;
} Element;

typedef struct FVector
{
    TArray(Element) Elements_;
    String Types_[Vector_Types_Size];
    size_t Types_Count_;
    size_t Types_Capacity_;
    size_t Size_;
    size_t Capacity_;
} FVector;

#define Vector_Init(vector, ...) \
    vector.Types_Count_ = 0; \
    memset(vector.Types_, 0, Vector_Types_Size); \
    Apply_Args(Vector_Add_Type, vector, __VA_ARGS__) \
    CFT_Vector_Init_(&vector)

#define Vector_Get(vector, index, type) \
    *((type*)CFT_Vector_Get_(&vector, index))

#define Vector_Push_Back(vector, type, new_Value) \
    { \
        type pushed_Value__ = new_Value; \
        CFT_Vector_Push_Back_(&vector, &pushed_Value__, Stringify(type)); \
    }

#define Vector_Str_Push(vector, new_Value) \
    { \
        String str = Stringify(new_Value); \
        if (strcmp(str, "String") == 0) \
        { \
            str = "char*"; \
        } \
        Vector_Push_Back(vector, String, str); \
    }

#define Vector_Pop_Back(vector) \
    CFT_Vector_Pop_Back_(&vector)

#define Vector_Size(vector) \
    CFT_Vector_Size_(&vector)

#define Vector_Capacity(vector) \
    CFT_Vector_Capacity_(&vector)

#define Vector_Add_Type(vector, type) \
    CFT_Vector_Add_Type(&vector, Stringify(type))

#define Vector_Remove_At(vector, index) \
    CFT_Vector_Remove_At(&vector, index)

void CFT_Vector_Init_(FVector* vector);
void* CFT_Vector_Get_(FVector* vector, long long index);
void CFT_Vector_Push_Back_(FVector* vector, void* new_Value, String type);
Element CFT_Vector_Pop_Back_(FVector* vector);
Element* Vector_Back(FVector* vector);
void CFT_Vector_Remove_At(FVector* vector, size_t index);

void Vector_Free(FVector* vector);;

size_t CFT_Vector_Size_(const FVector* vector);
size_t CFT_Vector_Capacity_(const FVector* vector);

bool CFT_Vector_Add_Type(FVector* vector, String type);
bool CFT_Vector_Remove_Type(FVector* vector, String type);