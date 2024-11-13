#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "Internal/FMap.h"
#include "Internal/FVector.h"
#include "Internal/FString.h"
#include "Internal/CFT_Macros.h"
#include "Internal/Object_System/FType.h"
#include "Internal/Object_System/FObject.h"
#include "Internal/Object_System/SType_Manager.h"

typedef struct Test_Struct
{
    int Number;
    bool Boolean;
    String str;
} Test_Struct;

Test_Struct test_Fn(Test_Struct test)
{
    return test;
}

#define test_Macro(arg, arg_2) arg ## Stringify(arg_2)

int main(int argc, char* argv[])
{
    FMap(String, int) map;
    FMap(String) map_1;
    Map_Init(map, String);
    String str_str = "String string";
    Map_Add(map, String, "str", str_str);
    printf("map: %s\n", Map_Get(map, "str", String));

    FVector vector;
    Vector_Init(vector, String, int);
    String str = "Str Str Str";
    Vector_Push_Back(vector, String, str);
    printf("vector str: %s\n", Vector_Get(vector, 0, String));

    Map_Init(Global_Type_Manager.Types, FType);

    Def_Type("New_Type", _Templates_(T, Type, G),
    (
    public:
        const int Num_Val,
        float Deciaml
    ));

    FType* type = &Map_Get(Global_Type_Manager.Types, "New_Type", FType);
    TType_Field* field = &Map_Get(type->Fields, "Num_Val", TType_Field);
    printf("New_Type.Num_Val type: %d\n", field->Field_Type);
    
    char final_Str[100];
    fgets(final_Str, 100, stdin);
    Type_Manager_Free();
    return 0;
}