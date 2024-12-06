#include "FVector.h"
#include <stdlib.h>
#include <stdbool.h>
#include "CFT_Error.h"

void CFT_Vector_Init_(FVector* vector)
{
    vector->Size_ = 0;
    vector->Capacity_ = 10;
    vector->Elements_ = calloc(vector->Capacity_, sizeof(Element));
    Err_Alloc(vector->Elements_);
}

const void* CFT_Vector_Get_(FVector* vector, ssize_t index)
{     
    if (index > -1)
    {
        return vector->Elements_[index].Value_;
    }else
    {
        return vector->Elements_[vector->Size_ + index].Value_;
    }
}

void CFT_Vector_Set_(FVector* vector, ssize_t index, void* value, String type, size_t type_Size)
{
    CFT_Vector_Type_Check_(vector, type);

    Element* element;
    if (index > -1)
    {
        element = &vector->Elements_[index];
    }else
    {
        element = &vector->Elements_[vector->Size_ + index];
    }

    if (element->Was_Allocated == true)
    {
        free(element->Value_);
    }
    
    element->Type_ = type;
    if (Type_Is_Pointer(type) == true)
    {
        element->Value_ = value;
        element->Was_Allocated = false;
    }else
    {
        element->Value_ = malloc(type_Size);
        element->Was_Allocated = true;
        memcpy(element->Value_, value, type_Size);
    }
}

void CFT_Vector_Push_Back_(FVector* vector, void* new_Value, String type)
{
    vector->Size_++;

    if (strcmp(type, "String") == 0) type = "char*";

    CFT_Vector_Type_Check_(vector, type);
    
    if (vector->Size_ == vector->Capacity_)
    {
        vector->Capacity_ *= 2;
        TArray(Element) temp = realloc(vector->Elements_, vector->Capacity_ * sizeof(Element));
        if (temp != NULL)
        {
            vector->Elements_ = temp;
        }else
        {
            perror("ERROR: 'vector->Elements_' could not be reallocated.");
            free(vector->Elements_);
            exit(EXIT_FAILURE);
        }
    }

    vector->Elements_[vector->Size_ - 1].Value_ = new_Value;
    vector->Elements_[vector->Size_ - 1].Type_ = type;
}

void CFT_Vector_Type_Check_(FVector* vector, String type)
{
    bool correct_Type = false;
    for (int i = 0; i < vector->Types_Count_; i++)
    {
        if (strcmp(type, vector->Types_[i]) == 0) 
        {
            correct_Type = true;
        }
    }

    if (correct_Type == false)
    {
        printf("ERROR: value type mismatch at CPT_Vector_Push_Back_(...). Added value type: %s", type); 
        exit(EXIT_FAILURE); 
    }
}

Element CFT_Vector_Pop_Back_(FVector* vector)
{
    if (vector->Elements_[vector->Size_ - 1].Was_Allocated == true)
    {
        free(vector->Elements_[vector->Size_ - 1].Value_);
    }

    vector->Size_--;
    Element return_Val = vector->Elements_[vector->Size_ - 1];
    vector->Elements_[vector->Size_ - 1].Value_ = NULL;
    vector->Elements_[vector->Size_ - 1].Type_ = "";
    
    return return_Val;
}

Element* Vector_Back(FVector* vector)
{
    return &vector->Elements_[vector->Size_ - 1];
}

void CFT_Vector_Remove_At(FVector* vector, size_t index)
{
    if (index > vector->Size_ -1 || index < 0)
    {
        perror("ERROR: CFT_Vector_Remove_At(...) index out of bounds.\n");
        exit(EXIT_FAILURE);
    }

    TArray(Element) temp_Elements = calloc(vector->Capacity_, sizeof(Element));
    
    if (vector->Elements_[index].Was_Allocated == true)
    {
        free(vector->Elements_[index].Value_);
    }

    int j = 0;
    for (int i = 0; i < vector->Size_; i++)
    {
        if (i == index) continue;
        temp_Elements[j] = vector->Elements_[i];
        j++;
    }

    free(vector->Elements_);
    vector->Elements_ = temp_Elements;
    vector->Size_--;
}

void Vector_Free(FVector* vector)
{
    for (int i = 0; i < vector->Size_; i++)
    {
        if (vector->Elements_[i].Was_Allocated == true)
        {
            free(vector->Elements_[i].Value_);
        }
    }

    vector->Size_ = 0;
    vector->Capacity_ = 10;
    free(vector->Elements_);
}

size_t CFT_Vector_Size_(const FVector* vector)
{
    return vector->Size_;
}

size_t CFT_Vector_Capacity_(const FVector* vector)
{
    return vector->Capacity_;
}

// Returns true if a type string was added to the vector->Types_ array.
bool CFT_Vector_Add_Type(FVector* vector, String type)
{
    if (strcmp(type, "String") == 0) type = "char*";

    if (vector->Types_Count_ == 0)
    {
        vector->Types_Count_++;
        vector->Types_[0] = type;
        return true;
    }

    for (int i = vector->Types_Count_; i < Vector_Types_Size; i++)
    {
        vector->Types_Count_++;
        vector->Types_[i] = type;
        return true;
    }

    for (int i = 0; i < Vector_Types_Size; i++)
    {
        if (strcmp(type, vector->Types_[i]) == 0) return false;
    }

    return true;
}

// Returns true if a type string was removed from the vector->Types_ array.
bool CFT_Vector_Remove_Type(FVector* vector, String type)
{
    for (int i = 0; i < Vector_Types_Size; i++)
    {
        if (strcmp(type, vector->Types_[i]) == 0)
        {
            vector->Types_Count_--;
            vector->Types_[i] = NULL;
            return true;
        }
    }

    return false;
}