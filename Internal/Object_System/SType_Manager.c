#include "SType_Manager.h"
#include <string.h>
#include "../FString.h"

SType_Manager Global_Type_Manager;

void Type_Manager_Add_Type(FType* type)
{
    if (Global_Type_Manager.Types.Size_ > 0)
    {
        for (int i = 0; i < Global_Type_Manager.Types.Size_; i++)
        {
            FType* type_In_Map = Global_Type_Manager.Types.Keys_[i].Value;
            if (strcmp(type->Name, type_In_Map->Name) == 0)
            {
                Map_Add(Global_Type_Manager.Types, FType, type->Name, *type);
            }
        }
    }else
    {
        Map_Add(Global_Type_Manager.Types, FType, type->Name, *type);
    }
}

void Type_Manager_Free()
{
    for (int i = 0; i < Global_Type_Manager.Types.Size_; i++)
    {
        FType* type = Global_Type_Manager.Types.Keys_[i].Value;
        for (int i = 0; i < type->Fields.Size_; i++)
        {
            TType_Field* field = type->Fields.Keys_[i].Value;
            FString_Free(field->Field_Name);
        }

        Map_Free(&type->Fields);
        Map_Free(&type->Templates);
        free(type);
    }

    Map_Free(&Global_Type_Manager.Types);
}