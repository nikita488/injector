/*
    Plugin-SDK (Grand Theft Auto) SHARED header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#pragma warning(push)
#pragma warning(disable: 4244)
#pragma warning(disable: 4267)
#pragma warning(disable: 4302)
#pragma warning(disable: 4311)

#include "Base.h"
#include "DynAddress.h"

namespace plugin {

template <class Type, size_t n>
size_t array_size(Type(&)[n]) { 
    return n; 
}

// Gets the virtual method table from the object @self
inline void** GetVMT(const void* self) {
    return *(void***)(self);
}

// Gets the virtual method from @self in the table index @index 
inline void* GetVMT(const void* self, size_t index) {
    return GetVMT(self)[index];
}

template <uintptr_t address, typename... Args>
void Call(Args... args) {
    reinterpret_cast<void(__cdecl *)(Args...)>(address)(args...);
}

template <uintptr_t address, typename... Args>
void CallStd(Args... args) {
    reinterpret_cast<void(__stdcall*)(Args...)>(address)(args...);
}

template <typename Ret, uintptr_t address, typename... Args>
Ret CallStdAndReturn(Args... args) {
    return reinterpret_cast<Ret(__stdcall*)(Args...)>(address)(args...);
}

template <typename Ret, uintptr_t address, typename... Args>
Ret CallAndReturn(Args... args) {
    return reinterpret_cast<Ret(__cdecl *)(Args...)>(address)(args...);
}

template <uintptr_t address, typename C, typename... Args>
void CallMethod(C _this, Args... args) {
    reinterpret_cast<void(__thiscall *)(C, Args...)>(address)(_this, args...);
}

template <typename Ret, uintptr_t address, typename C, typename... Args>
Ret CallMethodAndReturn(C _this, Args... args) {
    return reinterpret_cast<Ret(__thiscall *)(C, Args...)>(address)(_this, args...);
}

template <uintptr_t tableIndex, typename C, typename... Args>
void CallVirtualMethod(C _this, Args... args) {
    reinterpret_cast<void(__thiscall *)(C, Args...)>((*reinterpret_cast<void ***>(_this))[tableIndex])(_this, args...);
}

template <typename Ret, uintptr_t tableIndex, typename C, typename... Args>
Ret CallVirtualMethodAndReturn(C _this, Args... args) {
    return reinterpret_cast<Ret(__thiscall *)(C, Args...)>((*reinterpret_cast<void ***>(_this))[tableIndex])(_this, args...);
}

template <typename... Args>
void CallDyn(uintptr_t address, Args... args) {
    reinterpret_cast<void(__cdecl *)(Args...)>(GetGlobalAddress(address))(args...);
}

template <typename Ret, typename... Args>
Ret CallAndReturnDyn(uintptr_t address, Args... args) {
    return reinterpret_cast<Ret(__cdecl *)(Args...)>(GetGlobalAddress(address))(args...);
}

template <typename... Args>
void CallStdDyn(uintptr_t address, Args... args) {
    reinterpret_cast<void(__stdcall*)(Args...)>(GetGlobalAddress(address))(args...);
}

template <typename Ret, typename... Args>
Ret CallStdAndReturnDyn(uintptr_t address, Args... args) {
    return reinterpret_cast<Ret(__stdcall*)(Args...)>(GetGlobalAddress(address))(args...);
}

template <typename C, typename... Args>
void CallMethodDyn(uintptr_t address, C _this, Args... args) {
    reinterpret_cast<void(__thiscall *)(C, Args...)>(GetGlobalAddress(address))(_this, args...);
}

template <typename Ret, typename C, typename... Args>
Ret CallMethodAndReturnDyn(uintptr_t address, C _this, Args... args) {
    return reinterpret_cast<Ret(__thiscall *)(C, Args...)>(GetGlobalAddress(address))(_this, args...);
}

template <typename... Args>
void CallDynGlobal(uintptr_t address, Args... args) {
    reinterpret_cast<void(__cdecl *)(Args...)>(address)(args...);
}

template <typename Ret, typename... Args>
Ret CallAndReturnDynGlobal(uintptr_t address, Args... args) {
    return reinterpret_cast<Ret(__cdecl *)(Args...)>(address)(args...);
}

template <typename C, typename... Args>
void CallMethodDynGlobal(uintptr_t address, C _this, Args... args) {
    reinterpret_cast<void(__thiscall *)(C, Args...)>(address)(_this, args...);
}

template <typename Ret, typename C, typename... Args>
Ret CallMethodAndReturnDynGlobal(uintptr_t address, C _this, Args... args) {
    return reinterpret_cast<Ret(__thiscall *)(C, Args...)>(address)(_this, args...);
}

}

#pragma warning(pop)
