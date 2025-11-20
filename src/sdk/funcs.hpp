#pragma once
#include <il2cpp-api-types.h>
#include <il2cpp-object-internals.h>
#include <cstddef>
#include <cstring>
#include <string>

Il2CppString* WriteIl2CppString(const char* string);
char* ReadIl2CppString(Il2CppString* il2cppString);
std::string Il2CppStringToStdString(Il2CppString* il2cppString);

template <typename T>
T GetField(void* obj, std::ptrdiff_t offset);

template <typename T>
void SetField(void* obj, std::ptrdiff_t offset, T val);

template<typename T>
 T SafeGetField(void* obj, std::ptrdiff_t offset, T default_value = T{});

bool IsValidPointer(void* ptr);
bool IsValidString(Il2CppString* str);