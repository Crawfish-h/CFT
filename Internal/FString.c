#include "FString.h"
#include <string.h>
#include "CFT_Error.h"

FString* FString_Init(String string_Data)
{
    FString* string = malloc(sizeof(FString));
    string->Size_ = strlen(string_Data);
    string->Capacity_ = string->Size_ * 2;
    string->Data_ = malloc(string->Capacity_ * sizeof(char));
    Err_Alloc(string->Data_);
    
    strcpy(string->Data_, string_Data);

    return string;
}

void FString_Push(FString* string, String new_Str)
{
    size_t old_Size = string->Size_;
    string->Size_ += strlen(new_Str);
    
    if (string->Size_ >= string->Capacity_)
    {
        string->Capacity_ = string->Size_ * 2;
        TArray(char) temp = malloc(string->Capacity_ * sizeof(char));
        strcpy(temp, new_Str);
        if (temp != NULL)
        {
            for (int i = 0; i < strlen(new_Str); i++)
            {
                if (temp[i] != '\0')
                {
                    string->Data_[old_Size + i] = temp[i];
                }
            }

            string->Data_[string->Size_] = '\0';
        }else
        {
            perror("ERROR: 'string->Data_' could not be reallocated.");
            free(string->Data_);
            exit(EXIT_FAILURE);
        }
    }
}

void FString_Remove(FString* string, const String sub_Str)
{
        char *p, *q, *r;
        if (*sub_Str && (q = r = strstr(string, sub_Str)) != NULL)
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

        string->Size_ = strlen(string);
}

void FString_Free(FString* string)
{
    string->Size_ = 0;
    string->Capacity_ = 10;
    free(string->Data_);
    free(string);
}