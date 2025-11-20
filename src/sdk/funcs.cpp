#include "Funcs.hpp"
#include <Windows.h>
#include <cwchar>
#include <cstddef>
#include <cstring>
#include <string>
#include "IL2CPP/il2cpp-api.hpp"
#include <Vector3.hpp>

Il2CppString* WriteIl2CppString(const char* string) {
    if (!string || !Il2CppAPI::IsInitialized()) {
        return nullptr;
    }

    return Il2CppAPI::string_new(string);
}

char* ReadIl2CppString(Il2CppString* il2cppString) {
    if (!il2cppString || !Il2CppAPI::IsInitialized()) {
        return nullptr;
    }

    int32_t length = Il2CppAPI::string_length(il2cppString);
    if (length < 0 || length > 10000) {
        return nullptr;
    }

    const char* chars = Il2CppAPI::string_chars(il2cppString);
    if (!chars) {
        return nullptr;
    }

    // Convert UTF-16 to UTF-8
    const uint16_t* utf16_chars = reinterpret_cast<const uint16_t*>(chars);

    int requiredSize = WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<const wchar_t*>(utf16_chars), length, nullptr, 0, nullptr, nullptr);

    if (requiredSize <= 0) {
        return nullptr;
    }

    char* result = new char[requiredSize + 1];
    WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<const wchar_t*>(utf16_chars), length, result, requiredSize, nullptr, nullptr);
    result[requiredSize] = '\0';

    return result;
}

std::string Il2CppStringToStdString(Il2CppString* il2cppString) {
    if (!il2cppString || !Il2CppAPI::IsInitialized()) {
        return "";
    }

    int32_t length = Il2CppAPI::string_length(il2cppString);
    if (length < 0 || length > 10000) {
        return "";
    }

    const char* chars = Il2CppAPI::string_chars(il2cppString);
    if (!chars) {
        return "";
    }

    // Convert UTF-16 to UTF-8
    const uint16_t* utf16_chars = reinterpret_cast<const uint16_t*>(chars);

    int requiredSize = WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<const wchar_t*>(utf16_chars), length, nullptr, 0, nullptr, nullptr);

    if (requiredSize <= 0) {
        return "";
    }

    std::string result(requiredSize, '\0');
    WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<const wchar_t*>(utf16_chars), length, &result[0], requiredSize, nullptr, nullptr);

    return result;
}

template <typename T>
inline T GetField(void* obj, std::ptrdiff_t offset) {
    if (!obj) return T{};
    return *(T*)((uint8_t*)obj + offset);
}

template <typename T>
inline void SetField(void* obj, std::ptrdiff_t offset, T val) {
    if (!obj) return;
    *(T*)((uint8_t*)obj + offset) = val;
}

template<typename T>
inline T SafeGetField(void* obj, std::ptrdiff_t offset, T default_value) {
    if (!obj) return default_value;

    MEMORY_BASIC_INFORMATION mbi = { 0 };
    if (VirtualQuery(obj, &mbi, sizeof(mbi)) == 0) {
        return default_value;
    }
    if (mbi.State != MEM_COMMIT) {
        return default_value;
    }

    if (offset < 0 || offset > 0x1000) {
        return default_value;
    }

    return GetField<T>(obj, offset);
}

bool IsValidPointer(void* ptr) {
    if (!ptr) return false;
    if (reinterpret_cast<uintptr_t>(ptr) < 0x10000) return false;

    MEMORY_BASIC_INFORMATION mbi = { 0 };
    if (VirtualQuery(ptr, &mbi, sizeof(mbi)) == 0) {
        return false;
    }
    return (mbi.State == MEM_COMMIT);
}

bool IsValidString(Il2CppString* str) {
    if (!str || !Il2CppAPI::IsInitialized()) return false;

    if (!IsValidPointer(str)) return false;

    int32_t length = Il2CppAPI::string_length(str);
    if (length < 0 || length > 10000) return false;

    const char* chars = Il2CppAPI::string_chars(str);
    if (!chars) return false;

    if (!IsValidPointer(const_cast<char*>(chars))) return false;

    return true;
}


template int GetField<int>(void* obj, std::ptrdiff_t offset);
template float GetField<float>(void* obj, std::ptrdiff_t offset);
template double GetField<double>(void* obj, std::ptrdiff_t offset);
template void* GetField<void*>(void* obj, std::ptrdiff_t offset);
template bool GetField<bool>(void* obj, std::ptrdiff_t offset);
template uintptr_t GetField<uintptr_t>(void* obj, std::ptrdiff_t offset);
template uint32_t GetField<uint32_t>(void* obj, std::ptrdiff_t offset);
template uint64_t GetField<uint64_t>(void* obj, std::ptrdiff_t offset);
template Il2CppString* GetField<Il2CppString*>(void* obj, std::ptrdiff_t offset);


template void SetField<int>(void* obj, std::ptrdiff_t offset, int val);
template void SetField<float>(void* obj, std::ptrdiff_t offset, float val);
template void SetField<double>(void* obj, std::ptrdiff_t offset, double val);
template void SetField<void*>(void* obj, std::ptrdiff_t offset, void* val);
template void SetField<bool>(void* obj, std::ptrdiff_t offset, bool val);
template void SetField<uintptr_t>(void* obj, std::ptrdiff_t offset, uintptr_t val);
template void SetField<uint32_t>(void* obj, std::ptrdiff_t offset, uint32_t val);
template void SetField<uint64_t>(void* obj, std::ptrdiff_t offset, uint64_t val);
template void SetField<Il2CppString*>(void* obj, std::ptrdiff_t offset, Il2CppString* val);


template int SafeGetField<int>(void* obj, std::ptrdiff_t offset, int default_value);
template float SafeGetField<float>(void* obj, std::ptrdiff_t offset, float default_value);
template bool SafeGetField<bool>(void* obj, std::ptrdiff_t offset, bool default_value);
template void* SafeGetField<void*>(void* obj, std::ptrdiff_t offset, void* default_value);
template Il2CppString* SafeGetField<Il2CppString*>(void* obj, std::ptrdiff_t offset, Il2CppString* default_value);
template Vector3 SafeGetField<Vector3>(void* obj, std::ptrdiff_t offset, Vector3 default_value);