#
# Generic CmakeList file
#
# @author Natesh Narain

cmake_minimum_required(VERSION 3.28.1)

project(CFT)

#FIND_PACKAGE(Lua 5.4 REQUIRED)
#set(INCLUDE_DIRS ${LUA_INCLUDE_DIR})
#add_definitions(-DLUA)

#include_directories(${INCLUDE_DIRS})


# find packages

# includes
#add_subdirectory(${PROJECT_SOURCE_DIR}/External/luacpp/Source/)

# find header & source

set(CONFIGURE_DEPENDS true)

add_executable(
  ${PROJECT_NAME}
  ${Extra_Includes}
  ${PROJECT_SOURCE_DIR}/Main.c
  ${PROJECT_SOURCE_DIR}/Internal/CFT_Error.h
  ${PROJECT_SOURCE_DIR}/Internal/FMap.h
  ${PROJECT_SOURCE_DIR}/Internal/FMap.c
  ${PROJECT_SOURCE_DIR}/Internal/FVector.h
  ${PROJECT_SOURCE_DIR}/Internal/FVector.c
  ${PROJECT_SOURCE_DIR}/Internal/FString.h
  ${PROJECT_SOURCE_DIR}/Internal/FString.c
  ${PROJECT_SOURCE_DIR}/Internal/Utility.h
  ${PROJECT_SOURCE_DIR}/Internal/Utility.c
  ${PROJECT_SOURCE_DIR}/Internal/Object_System/FType.h
  ${PROJECT_SOURCE_DIR}/Internal/Object_System/FType.c
  ${PROJECT_SOURCE_DIR}/Internal/Object_System/FObject.h
  ${PROJECT_SOURCE_DIR}/Internal/Object_System/SType_Manager.c
  ${PROJECT_SOURCE_DIR}/Internal/Object_System/SType_Manager.h
  ${PROJECT_SOURCE_DIR}/Internal/Type_Info.h
  ${PROJECT_SOURCE_DIR}/Internal/Type_Info.c
  ${PROJECT_SOURCE_DIR}/Internal/Switch_String.h
  ${PROJECT_SOURCE_DIR}/Internal/CFT_Macros.h
)

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${PROJECT_NAME} PRIVATE -ftrack-macro-expansion=0)
endif()

# link libraries
#target_link_libraries(${PROJECT_NAME} libluacpp.a)
#target_link_libraries(${PROJECT_NAME} ${LUA_LIBRARY})

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 23)