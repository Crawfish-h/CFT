#pragma once
#include <stdlib.h>
#include <string.h>
#include "Type_Info.h"
#include "FVector.h"

typedef struct 
{
    String Key_Val;
    void* Value;
    bool Was_Allocated; // If this is true, free this key's Value_ when this vector is freed.
    String Value_Type;
} Key;

typedef struct FMap
{
    TArray(Key) Keys_; 
    void* Values_;
    size_t Size_;
    size_t Capacity_;
    FVector Value_Types_;
} FMap;

#define Cat_Type_Name(type)
#define FMap_T_Internal_2_(types) typedef FMap FMap_ ## types; FMap_ ## types
#define FMap_T_Internal_(types) FMap_T_Internal_2_(types)
#define FMap(...) FMap_T_Internal_(CAT_2(__VA_ARGS__))

#define Map_Set_Types_(vector, type) \
    Vector_Push_Back(vector, String, Stringify(type));

#define Map_Init(map, ...) \
    Vector_Init(map.Value_Types_, String); \
    Apply_Args(Vector_Str_Push, map.Value_Types_, __VA_ARGS__); \
    CFT_Map_Init_(&map)

#define Map_Remove(map, key) \
    CFT_Map_Remove_(&map, key)

#define Map_Add_Internal_(map, type, key, value) \
    ({ \
        type test_Add_Val__ = value; \
        bool map_Add_Result__; \
        void* map_Add_Val__ = malloc(sizeof(test_Add_Val__)); \
        memcpy(map_Add_Val__, &test_Add_Val__, sizeof(test_Add_Val__)); \
        map_Add_Result__ = CFT_Map_Add_(&map, key, &map_Add_Val__, Stringify(type)); \
        map.Keys_[map.Size_ - 1].Value = map_Add_Val__; \
        map.Keys_[map.Size_ - 1].Was_Allocated = true; \
        map_Add_Result__; \
    })

#define Map_Place(map, type, key, value) \
    ({ \
        type map_Add_Val__ = value; \
        bool map_Add_Result__; \
        map_Add_Result__ = CFT_Map_Add_(&map, key, &map_Add_Val__, Stringify(type)); \
        map.Keys_[map.Size_ - 1].Was_Allocated = false; \
        map_Add_Result__; \
    })

#define Map_Add(map, type, key, value) \
    ({ \
        /* Checking if the type is a pointer. */  \
        if (strstr(Stringify(type), "*")) \
        { \
            Map_Place(map, type, key, value); \
        }else \
        { \
            Map_Add_Internal_(map, type, key, value); \
        } \
    })

/*#define Map_Emplace(map, type, key) \
    ({ \
        CFT_Map_Add_(&map, key, NULL, Stringify(type)); \
    })*/

// Both the key and the value share the same argument: value.
#define Map_Add_Arg(map, type, value) \
    ({ \
        typeof(value) map_Add_Val__ = value; \
        bool map_Add_Result__; \
        map_Add_Result__ = CFT_Map_Add_(&map, #value, &map_Add_Val__, Stringify(type)); \
        map_Add_Result__; \
    })    

#define Map_GetT(map, key_Val) \
    CFT_Map_Get_(&map, key_Val)

#define Map_Set(map, key_Val, value, type) \
    void CFT_Map_Set_(map, key_Val, Stringify(type), sizeof(value))

#define Map_Get(map, key_Val, type) \
    *((const type*)CFT_Map_Get_(&map, key_Val))

void CFT_Map_Init_(FMap* map);
const void* CFT_Map_Get_(FMap* map, String key_Val);
void CFT_Map_Set_(FMap* map, String key_Val, void* value, String type, size_t type_Size);
void Map_Free(FMap* map);
void CFT_Map_Type_Check_(FMap* map, String type);
size_t CFT_Map_Remove_(FMap* map, String key_Val);
bool CFT_Map_Add_(FMap* map, String key, void* value, String value_Type);
bool Map_Contains_Key(FMap* map, String key_Val);
