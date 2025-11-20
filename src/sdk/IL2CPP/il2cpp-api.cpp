#include "il2cpp-api.hpp"
#include <iostream>
#include <il2cpp-api-types.h>
#include <il2cpp-class-internals.h>
#include <il2cpp-object-internals.h>

#include "il2cpp-api.hpp"
#include <iostream>
#include <il2cpp-api-types.h>
#include <il2cpp-class-internals.h>
#include <il2cpp-object-internals.h>
#include <Psapi.h>

#pragma comment(lib, "Psapi.lib")

uintptr_t PatternScan(HMODULE module, const char* pattern, const char* mask) {
    MODULEINFO info = { 0 };
    GetModuleInformation(GetCurrentProcess(), module, &info, sizeof(info));

    uintptr_t base = reinterpret_cast<uintptr_t>(module);
    uintptr_t size = info.SizeOfImage;

    size_t patternLength = strlen(mask);

    for (uintptr_t i = 0; i < size - patternLength; i++) {
        bool found = true;

        for (size_t j = 0; j < patternLength; j++) {
            if (mask[j] != '?' && pattern[j] != *reinterpret_cast<char*>(base + i + j)) {
                found = false;
                break;
            }
        }

        if (found) {
            return base + i;
        }
    }
    return 0;
}

template<typename T>
T GetIl2CppExport(HMODULE gameAssembly, const char* functionName) {
    T function = reinterpret_cast<T>(GetProcAddress(gameAssembly, functionName));
    if (function) {
        std::cout << "[Il2CppAPI] Resolved " << functionName << " via export" << std::endl;
    }
    else {
        std::cout << "[Il2CppAPI] Failed to resolve " << functionName << std::endl;
    }
    return function;
}

bool Il2CppAPI::Initialize() {
    if (s_initialized) return true;

    HMODULE gameAssembly = GetModuleHandleA("GameAssembly.dll");
    if (!gameAssembly) {
        std::cout << "[Il2CppAPI] Failed to get GameAssembly.dll" << std::endl;
        return false;
    }


    // Unity 2020.3.28f1 should have all these functions exported
    s_string_new = GetIl2CppExport<il2cpp_string_new_t>(gameAssembly, "il2cpp_string_new");
    s_string_new_len = GetIl2CppExport<il2cpp_string_new_len_t>(gameAssembly, "il2cpp_string_new_len");
    s_string_chars = GetIl2CppExport<il2cpp_string_chars_t>(gameAssembly, "il2cpp_string_chars");
    s_string_length = GetIl2CppExport<il2cpp_string_length_t>(gameAssembly, "il2cpp_string_length");
    s_domain_get = GetIl2CppExport<il2cpp_domain_get_t>(gameAssembly, "il2cpp_domain_get");
    s_class_from_name = GetIl2CppExport<il2cpp_class_from_name_t>(gameAssembly, "il2cpp_class_from_name");
    s_class_get_method_from_name = GetIl2CppExport<il2cpp_class_get_method_from_name_t>(gameAssembly, "il2cpp_class_get_method_from_name");
    s_object_new = GetIl2CppExport<il2cpp_object_new_t>(gameAssembly, "il2cpp_object_new");
    s_array_new = GetIl2CppExport<il2cpp_array_new_t>(gameAssembly, "il2cpp_array_new");
    s_array_new_specific = GetIl2CppExport<il2cpp_array_new_specific_t>(gameAssembly, "il2cpp_array_new_specific");
    s_array_new_full = GetIl2CppExport<il2cpp_array_new_full_t>(gameAssembly, "il2cpp_array_new_full");
    s_array_class_get = GetIl2CppExport<il2cpp_array_class_get_t>(gameAssembly, "il2cpp_array_class_get");


    if (!s_string_new || !s_class_from_name) {
        std::cout << "[Il2CppAPI] Critical functions missing exports may not be available" << std::endl;
        return false;
    }

    s_initialized = true;
    std::cout << "[Il2CppAPI] Initialized successfully using exports" << std::endl;
    return true;
}


void Il2CppAPI::ResolveFunctionsByPattern(HMODULE gameAssembly) {
    uintptr_t base = reinterpret_cast<uintptr_t>(gameAssembly);


    const char* string_new_pattern = "\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x48\x8B\xD9\x48\x85\xC9"; //pretty common one but we dont need it anyway LMFAO
    const char* string_new_mask = "xxxx?xxxxxx";

    uintptr_t string_new_addr = PatternScan(gameAssembly, string_new_pattern, string_new_mask);
    if (string_new_addr) {
        s_string_new = reinterpret_cast<il2cpp_string_new_t>(string_new_addr);
    }

}

Il2CppString* Il2CppAPI::string_new(const char* str) {
    if (!s_initialized || !s_string_new) return nullptr;
    return s_string_new(str);
}

Il2CppString* Il2CppAPI::string_new_len(const char* str, int32_t length) {
    if (!s_initialized || !s_string_new_len) return nullptr;
    return s_string_new_len(str, length);
}

const char* Il2CppAPI::string_chars(Il2CppString* str) {
    if (!s_initialized || !s_string_chars || !str) return nullptr;
    return s_string_chars(str);
}

int32_t Il2CppAPI::string_length(Il2CppString* str) {
    if (!s_initialized || !s_string_length || !str) return 0;
    return s_string_length(str);
}

void* Il2CppAPI::domain_get() {
    if (!s_initialized || !s_domain_get) return nullptr;
    return s_domain_get();
}

const Il2CppClass* Il2CppAPI::class_from_name(const Il2CppImage* image, const char* namespaze, const char* name) {
    if (!s_initialized || !s_class_from_name) return nullptr;
    return s_class_from_name(image, namespaze, name);
}

const MethodInfo* Il2CppAPI::class_get_method_from_name(const Il2CppClass* klass, const char* name, int argsCount) {
    if (!s_initialized || !s_class_get_method_from_name) return nullptr;
    return s_class_get_method_from_name(klass, name, argsCount);
}

void* Il2CppAPI::object_new(const Il2CppClass* klass) {
    if (!s_initialized || !s_object_new || !klass) return nullptr;
    return s_object_new(klass);
}

Il2CppArray* Il2CppAPI::array_new(const Il2CppClass* klass, uintptr_t length) {
    if (!s_initialized || !s_array_new || !klass) return nullptr;
    return s_array_new(klass, length);
}

Il2CppArray* Il2CppAPI::array_new_specific(const Il2CppClass* arrayType, uintptr_t length) {
    if (!s_initialized || !s_array_new_specific || !arrayType) return nullptr;
    return s_array_new_specific(arrayType, length);
}

Il2CppArray* Il2CppAPI::array_new_full(const Il2CppClass* arrayType, uint32_t rank, const uint32_t* lengths, const uint32_t* lowerBounds) {
    if (!s_initialized || !s_array_new_full || !arrayType) return nullptr;
    return s_array_new_full(arrayType, rank, lengths, lowerBounds);
}

void* Il2CppAPI::array_get(Il2CppArray* array, uint32_t idx) {
    if (!s_initialized || !array) return nullptr;

    return nullptr;
}

void Il2CppAPI::array_set(Il2CppArray* array, uint32_t idx, void* value) {
    if (!s_initialized || !array) return;

}

Il2CppClass* Il2CppAPI::array_class_get(const Il2CppClass* elementClass, uint32_t rank) {
    if (!s_initialized || !s_array_class_get || !elementClass) return nullptr;
    return s_array_class_get(elementClass, rank);
}

Il2CppArray* Il2CppAPI::create_int32_array(int32_t* values, int count) {
    if (!s_initialized || !values || count <= 0) return nullptr;

    auto int32Class = class_from_name(nullptr, "System", "Int32");
    if (!int32Class) return nullptr;

    auto arrayClass = array_class_get(int32Class, 1); // 1-dimensional array :nerd:
    if (!arrayClass) return nullptr;

    auto array = array_new_specific(arrayClass, count);
    if (!array) return nullptr;

    uintptr_t dataStart = reinterpret_cast<uintptr_t>(array) + 20; // Approximate offset

    for (int i = 0; i < count; i++) {
        *reinterpret_cast<int32_t*>(dataStart + (i * sizeof(int32_t))) = values[i];
    }

    return array;
}

Il2CppArray* Il2CppAPI::create_single_array(float* values, int count) {
    if (!s_initialized || !values || count <= 0) return nullptr;

    auto singleClass = class_from_name(nullptr, "System", "Single");
    if (!singleClass) return nullptr;

    auto arrayClass = array_class_get(singleClass, 1);
    if (!arrayClass) return nullptr;

    auto array = array_new_specific(arrayClass, count);
    if (!array) return nullptr;

    uintptr_t dataStart = reinterpret_cast<uintptr_t>(array) + 20; // Approximate offset 

    for (int i = 0; i < count; i++) {
        *reinterpret_cast<float*>(dataStart + (i * sizeof(float))) = values[i];
    }

    return array;
}

Il2CppArray* Il2CppAPI::create_bool_array(bool* values, int count) {
    if (!s_initialized || !values || count <= 0) return nullptr;

    auto boolClass = class_from_name(nullptr, "System", "Boolean");
    if (!boolClass) return nullptr;

    auto arrayClass = array_class_get(boolClass, 1);
    if (!arrayClass) return nullptr;

    auto array = array_new_specific(arrayClass, count);
    if (!array) return nullptr;

    uintptr_t dataStart = reinterpret_cast<uintptr_t>(array) + 20; // Approximate offset LMFAO

    for (int i = 0; i < count; i++) {
        *reinterpret_cast<bool*>(dataStart + (i * sizeof(bool))) = values[i];
    }

    return array;
}