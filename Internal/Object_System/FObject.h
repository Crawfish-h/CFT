#pragma once
#include "../Type_Info.h"
#include "../FMap.h"

typedef struct TField
{
    String Type;
    String Name;
    String Metadata;
    EAccess_Types Access_Type;
    bool Is_Const;
    bool Is_Function;
    void* Value;
} TField;

typedef struct FObject
{
    FMap Fields;
} FObject;