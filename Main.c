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
//#include <metalang99/datatype99.h>

/*datatype
(
    N_Type,
    (var, int),
    (car, char)
);*/

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
    FMap map;
    FMap map_1;
    Map_Init(map, String);
    String str_str = "String string";
    String str_Test = "str_str";
    //Map_Add(map, float, "integer", 108.5f);
    Map_Add(map, String, "str", str_Test);
    str_Test = "addd";
    Map_Add(map, String, "add", str_Test);
    str_Test = "subb";
    Map_Add(map, String, "sub", str_Test);
    str_Test = "multt";
    Map_Add(map, String, "mult", str_Test);
    str_Test = "divv";
    Map_Add(map, String, "div", str_Test);

    FVector vector;
    Vector_Init(vector, String, int);
    String str = "Str Str Str";
    Vector_Push_Back(vector, String, str);
    Vector_Push_Back(vector, String, "1 aaa");
    Vector_Push_Back(vector, String, "2 bbb");
    Vector_Push_Back(vector, String, "3 ccc");


    Map_Init(Global_Type_Manager.Types, FType*);

    Def_Type("New_Type", _Templates_(T, Type, G),
    (
    public:
        const int Num_Val,
        float Decimal,
    ));

    FType* type = Map_Get(Global_Type_Manager.Types, "New_Type", FType*);
    for (int i = 0; i < 2; i++)
    {
        String str = type->Fields.Keys_[i].Key_Val;
        printf("type->Fields map 2: %s\n", str);
    }

    TType_Field* field = &Map_Get(type->Fields, "Decimal", TType_Field);

    printf("New_Type.Num_Val type: %s\n", field->Field_Type->Data_);
    printf("New_Type.Num_Val name: %s\n", field->Field_Name->Data_);

    
    char final_Str[100];
    fgets(final_Str, 100, stdin);
    Type_Manager_Free();
    return 0;
}