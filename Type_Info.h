#pragma once
#include <stdbool.h>
#include <string.h>

typedef enum EAccess_Types 
{ EAccess_Types_Public, EAccess_Types_Private, EAccess_Types_Protected } EAccess_Types;

#define TArray(type) type*

#define Stringify_2(x) #x
#define Stringify(x) Stringify_2(x)

typedef char* String;
//#define String char*

typedef struct FMap FMap;
typedef struct FType FType;
typedef struct FObject FObject;

String Get_Var_Type_Err();

#define Get_Typename(var) \
    _Generic((var), \
        int : "int", \
        long : "long", \
        float : "float", \
        char : "char", \
        char* : "char*", \
        _Bool : "_Bool", \
        double : "double", \
        long long : "long long", \
        FMap : "FMap", \
        FType : "FType", \
        FObject : "FObject", \
        default : Get_Var_Type_Err())

/*#define TInt "int"
#define TLong "long"
#define TLong_Long "long long"
#define TFloat "float"
#define TChar "char"
#define TBool "_Bool"
#define TArray(type) Stringify(type*)
#define TDouble "double"
#define TMap "FMap"
#define TObject "FObject"*/

#define TI_Pair(first, second)

// This is here because my intellisense does not recognize stdbool.h.
#if defined false || defined true || defined bool
    #else
        #define bool	_Bool
        #define true	1
        #define false	0
    #endif

bool Type_Is_Pointer_Internal_(String type);

// This does not work with typedefed pointers, i.e., typedef char* String. 
// The type argument can be of a actual type: int
// Or a string: "int".
#define Type_Is_Pointer(type) \
    Type_Is_Pointer_Internal_(Stringify(type))
