#include "FType.h"
#include <string.h>
#include "../Switch_String.h"
#include "SType_Manager.h"

void Def_Type_Add_Fields(FType* type, String field_Data)
{
    TType_Field field;

    String token;
    String token_Context;
    FString* field_Data_Copy = FString_Init(field_Data);

    FVector token_Vector;
    Vector_Init(token_Vector, String);

    token = strtok_r(field_Data_Copy->Data_, " :()", &token_Context);
    while (token != NULL)
    {
        //&&  && strcmp(token, "protected") == 0)
        if (strcmp(token, "public") == 0)
        { 
            field.Access_Type = EAccess_Types_Public;
            printf("public\n");
        }else if (strcmp(token, "private") == 0)
        {
            field.Access_Type = EAccess_Types_Private;
            printf("private\n");
        }else if (strcmp(token, "protected") == 0)
        {
            field.Access_Type = EAccess_Types_Protected;
            printf("protected\n");
        }else
        {
            Vector_Push_Back(token_Vector, String, token);
        }

        token = strtok_r(NULL, " :()", &token_Context);

        if (token == NULL)
            break;

        printf("token: %s\n", token);

        if (strstr(token, ",") != NULL)
        {
            field.Field_Name = FString_Init(Vector_Back(&token_Vector)->Value_);
            FString_Remove(field.Field_Name, ",");
            field.Field_Type = Vector_Get(token_Vector, 0, String);
            printf("field.Field_Name: %s\n", field.Field_Name);
            Map_Add(type->Fields, TType_Field, field.Field_Name->Data_, field);

            Vector_Free(&token_Vector);
            field.Is_Const = false;
            Vector_Init(token_Vector, String);
        }

        if (strcmp(token, "const") == 0)
            field.Is_Const = true;

        if (strcmp(token, "call_dtor") == 0)
            field.Is_Const = true;
    }
    
    Vector_Free(&token_Vector);
    FString_Free(field_Data_Copy);
    printf("type name: %s\n", type->Name);
    Type_Manager_Add_Type(type);
}