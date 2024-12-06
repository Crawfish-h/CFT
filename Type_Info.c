#include "Type_Info.h"
#include <stdio.h>
#include <stdlib.h>

String Get_Var_Type_Err()
{
    printf("ERROR: an unsupported type was used as an argument for the macro 'Get_Var_Type(var).'");
    exit(EXIT_FAILURE);
    return "Unsupported Type";
}

bool Type_Is_Pointer_Internal_(String type)
{
    if (strstr(Stringify(type), "*") == 0) 
    {
        return true;
    }

    return false;
}