#include <windows.h>
#include <winternl.h>

const ULONG SE_SHUTDOWN_PRIVILEGE = 19;

typedef NTSTATUS(NTAPI *pdef_NtRaiseHardError)(
    NTSTATUS ErrorStatus, ULONG NumberOfParameters,
    ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters,
    ULONG ResponseOption, PULONG Response);
typedef NTSTATUS(NTAPI *pdef_RtlAdjustPrivilege)(ULONG Privilege,
                                                 BOOLEAN Enable,
                                                 BOOLEAN CurrentThread,
                                                 PBOOLEAN Enabled);

int main() {
  HMODULE ntdll = LoadLibrary("ntdll.dll");
  BOOLEAN bEnabled;
  ULONG uResp;
  LPVOID lpRtlAjdustPrivilege = GetProcAddress(ntdll, "RtlAdjustPrivilege");
  LPVOID lpNtRaiseHardError = GetProcAddress(ntdll, "NtRaiseHardError");
  pdef_RtlAdjustPrivilege RtlAdjutPrivilege =
      (pdef_RtlAdjustPrivilege)lpRtlAjdustPrivilege;
  pdef_NtRaiseHardError NtRaiseHardError =
      (pdef_NtRaiseHardError)lpNtRaiseHardError;

  RtlAdjutPrivilege(SE_SHUTDOWN_PRIVILEGE, TRUE, FALSE, &bEnabled);
  NtRaiseHardError(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &uResp);

  return 0;
}