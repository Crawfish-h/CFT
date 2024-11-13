#pragma once
#include "../Type_Info.h"
#include "../FMap.h"
#include "../Utility.h"
#include "../FString.h"

typedef struct TType_Field
{
    FString* Field_Name;
    String Field_Type;
    String Metadata;
    EAccess_Types Access_Type;
    bool Is_Const;
    bool Is_Function;
} TType_Field;

typedef struct FType
{
    FType* Super;
    String Name;
    FMap Fields;
    FMap Templates;
} FType;

#define Type_Field_Add_Template(template_Value) \
    { \
        Map_Add(def_Type_Type__.Templates, String, Stringify(template_Value), Stringify(template_Value)); \
    }

#define Type_Add_Public(arg) \
    Type_Field_Add_Public(def_Type_Type__, Stringify(arg));

#define Type_Field_Add_Private(map, is_Const, field_Type) \
    { \
        TType_Field field; \
        field = args; \
        field.Is_Public = false; \
        Map_Add(def_Type_Type__.Fields, field.Field_Type, field.Field_Type); \
    }


#define _Templates_(...) \
    Apply(Type_Field_Add_Template, __VA_ARGS__); \

#define _Public_(...) \
    Apply(Type_Add_Public, __VA_ARGS__) \

#define _Fields_(...) __VA_ARGS__

void Def_Type_Add_Fields(FType* type, String field_Data);

#define Def_Type(name, template_Macro, arg) \
    { \
        FType def_Type_Type__; \
        def_Type_Type__.Name = name; \
        Map_Init(def_Type_Type__.Fields, TType_Field); \
        Map_Init(def_Type_Type__.Templates, String); \
        template_Macro \
        Def_Type_Add_Fields(&def_Type_Type__, Stringify(arg)); \
    } 

