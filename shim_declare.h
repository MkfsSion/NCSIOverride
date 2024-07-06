/* This file will be included twice, */
/* provided different definition of SHIM() macro.*/

SHIM(ServiceMain)
SHIM(SvchostPushServiceGlobalsEx)

#ifdef SHIM_DECLARE
/* included in global scope */
#include <windows.h>
#include "fuckncsi.h"
static HMODULE LoadTargetLibrary() {
    wchar_t *dllPath = (wchar_t*)HeapAlloc(GetProcessHeap(), 0, 65536);
    if (dllPath && (GetSystemDirectoryW(dllPath, 32768) != 0)) {
        lstrcatW(dllPath, L"\\netprofmsvc.dll");
        HMODULE hDll = LoadLibraryW(dllPath);
        HeapFree(GetProcessHeap(), 0, dllPath);
        return hDll;
    }
    return NULL;
}

#endif

#ifdef SHIM_FILL
/* included in function scope */
HMODULE ncsi = LoadLibraryW(L"ncsi.dll");
if (ncsi) {
    NCSIOverrideAttach(ncsi);
} else {
    OutputDebugStringA("failed to load ncsi.dll");
}
#endif
