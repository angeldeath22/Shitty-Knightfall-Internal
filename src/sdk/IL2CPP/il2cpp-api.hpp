#pragma once
#include <il2cpp-api-types.h>
#include <Windows.h>
#include <il2cpp-object-internals.h>
typedef Il2CppString* (*il2cpp_string_new_t)(const char* str);
typedef Il2CppString* (*il2cpp_string_new_len_t)(const char* str, int32_t length);
typedef char* (*il2cpp_string_chars_t)(Il2CppString* str);
typedef int32_t(*il2cpp_string_length_t)(Il2CppString* str);
typedef void* (*il2cpp_domain_get_t)();
typedef const Il2CppAssembly* (*il2cpp_domain_get_assemblies_t)(void** iter);
typedef const Il2CppImage* (*il2cpp_assembly_get_image_t)(const Il2CppAssembly* assembly);
typedef const Il2CppClass* (*il2cpp_class_from_name_t)(const Il2CppImage* image, const char* namespaze, const char* name);
typedef const MethodInfo* (*il2cpp_class_get_method_from_name_t)(const Il2CppClass* klass, const char* name, int argsCount);
typedef void* (*il2cpp_object_new_t)(const Il2CppClass* klass);
typedef Il2CppArray* (*il2cpp_array_new_t)(const Il2CppClass* klass, uintptr_t length);
typedef Il2CppArray* (*il2cpp_array_new_specific_t)(const Il2CppClass* arrayType, uintptr_t length);
typedef Il2CppArray* (*il2cpp_array_new_full_t)(const Il2CppClass* arrayType, uint32_t rank, const uint32_t* lengths, const uint32_t* lowerBounds);
typedef void* (*il2cpp_array_get_t)(Il2CppArray* array, uint32_t idx);
typedef void (*il2cpp_array_set_t)(Il2CppArray* array, uint32_t idx, void* value);
typedef Il2CppClass* (*il2cpp_array_class_get_t)(const Il2CppClass* elementClass, uint32_t rank);

class Il2CppAPI {
private:
    static inline bool s_initialized = false;

    static inline il2cpp_string_new_t s_string_new = nullptr;
    static inline il2cpp_string_new_len_t s_string_new_len = nullptr;
    static inline il2cpp_string_chars_t s_string_chars = nullptr;
    static inline il2cpp_string_length_t s_string_length = nullptr;
    static inline il2cpp_domain_get_t s_domain_get = nullptr;
    static inline il2cpp_class_from_name_t s_class_from_name = nullptr;
    static inline il2cpp_class_get_method_from_name_t s_class_get_method_from_name = nullptr;
    static inline il2cpp_object_new_t s_object_new = nullptr;

    static inline il2cpp_array_new_t s_array_new = nullptr;
    static inline il2cpp_array_new_specific_t s_array_new_specific = nullptr;
    static inline il2cpp_array_new_full_t s_array_new_full = nullptr;
    static inline il2cpp_array_get_t s_array_get = nullptr;
    static inline il2cpp_array_set_t s_array_set = nullptr;
    static inline il2cpp_array_class_get_t s_array_class_get = nullptr;

public:
    static bool Initialize();

    static void ResolveFunctionsByPattern(HMODULE gameAssembly);

    static Il2CppString* string_new(const char* str);
    static Il2CppString* string_new_len(const char* str, int32_t length);
    static const char* string_chars(Il2CppString* str);
    static int32_t string_length(Il2CppString* str);

    static void* domain_get();

    static const Il2CppClass* class_from_name(const Il2CppImage* image, const char* namespaze, const char* name);
    static const MethodInfo* class_get_method_from_name(const Il2CppClass* klass, const char* name, int argsCount);
    static void* object_new(const Il2CppClass* klass);

    static Il2CppArray* array_new(const Il2CppClass* klass, uintptr_t length);
    static Il2CppArray* array_new_specific(const Il2CppClass* arrayType, uintptr_t length);
    static Il2CppArray* array_new_full(const Il2CppClass* arrayType, uint32_t rank, const uint32_t* lengths, const uint32_t* lowerBounds);
    static void* array_get(Il2CppArray* array, uint32_t idx);
    static void array_set(Il2CppArray* array, uint32_t idx, void* value);
    static Il2CppClass* array_class_get(const Il2CppClass* elementClass, uint32_t rank);


    static Il2CppArray* create_int32_array(int32_t* values, int count);
    static Il2CppArray* create_single_array(float* values, int count);
    static Il2CppArray* create_bool_array(bool* values, int count);

    static bool IsInitialized() { return s_initialized; }
};