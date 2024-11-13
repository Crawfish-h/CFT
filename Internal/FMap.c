#include "FMap.h"
#include <stdio.h>
#include "CFT_Error.h"

void CFT_Map_Init_(FMap* map)
{
    map->Size_ = 0;
    map->Capacity_ = 10;
    map->Keys_ = malloc(map->Capacity_ * sizeof(Key));

    //printf("Map type: %s\n", map->Value_Type);
}

void* CFT_Map_Get_(FMap* map, String key_Val)
{
    for (int i = 0; i < map->Size_; i++)
    {
        if (strcmp(map->Keys_[i].Key_Val, key_Val) == 0)
        {
            return map->Keys_[i].Value;
        }
    }

    printf("ERROR: could not find key in FMap.");
    exit(EXIT_FAILURE);
    return NULL;
}

void Map_Free(FMap* map)
{
    map->Size_ = 0;
    map->Capacity_ = 10;
    free(map->Keys_);
}

size_t CFT_Map_Remove_(FMap* map, String key_Val)
{
    TArray(Key) keys_Temp = malloc(map->Capacity_ * sizeof(Key));

    int j = 0;
    size_t new_Size = map->Size_;
    for (int i = 0 ; i < map->Size_; i++)
    {
        if (strcmp(map->Keys_[i].Key_Val, key_Val) != 0)
        {
            keys_Temp[j] = map->Keys_[i];
            j++;
        }else
        {
            new_Size--;
        }
    }

    free(map->Keys_);
    map->Keys_ = keys_Temp;
    map->Size_ = new_Size;
    return j;
}

bool CFT_Map_Add_(FMap* map, String key, void* value, String value_Type)
{
    if (Map_Contains_Key(map, key) == true)
    {
        return false;
    }

    map->Size_++;

    /*if (map->Value_Type != value_Type)
    {
        printf("ERROR: value type mismatch at CFT_Map_Add_(...). FMap value type:  (%s). Added value type: (%s)", map->Value_Type, value_Type); 
        exit(EXIT_FAILURE); 
    }*/

    if (map->Size_ == map->Capacity_)
    {
        map->Capacity_ *= 2;
        TArray(Key) keys_Temp = realloc(map->Keys_, map->Capacity_ * sizeof(Key));
        if (keys_Temp != NULL)
        {
            map->Keys_ = keys_Temp;
        }else
        {
            perror("ERROR: 'map->Keys_' could not be reallocated.");
            free(map->Keys_);
            exit(EXIT_FAILURE);
        }
    }

    map->Keys_[map->Size_ - 1].Key_Val = key;
    map->Keys_[map->Size_ - 1].Value = value;
    map->Keys_[map->Size_ - 1].Value_Type = value_Type;

    return true;
}

bool Map_Contains_Key(FMap* map, String key_Val)
{
    if (map->Size_ > 0)
    {
        for (int i = 0; i < map->Size_; i++)
        {
            if (strcmp(map->Keys_[i].Key_Val, key_Val) == 0)
            {
                return true;
            }
        }
    }

    return false;
}