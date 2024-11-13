#include "Utility.h"
#include <string.h>
#include <stdio.h>



String Str_Remove(String str, const String sub_Str)
{
    char *p, *q, *r;
    if (*sub_Str && (q = r = strstr(str, sub_Str)) != NULL)
    {
        size_t len = strlen(sub_Str);
        while ((r = strstr(p = r + len, sub_Str)) != NULL)
        {
            while (p < r)
                *q++ = *p++;
        }
        while ((*q++ = *p++) != '\0')
            continue;
    }

    return str;
}