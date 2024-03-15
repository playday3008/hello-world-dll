#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tchar.h>

extern "C"
DWORD WINAPI MessageBoxThread(LPVOID CONST lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    const int ret = MessageBox(nullptr, _T("Hello World!"), _T("hello-world-dll"), MB_OK);
    return ret == 0 ? GetLastError() : ret;
}

extern "C"
BOOL APIENTRY DllMain(
    HMODULE CONST hModule,
    CONST DWORD  ul_reason_for_call,
    LPVOID CONST lpReserved
)
{
    // Mark all unused parameters
    UNREFERENCED_PARAMETER(lpReserved);

    HANDLE hThread{};
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);

        hThread = CreateThread(nullptr, 0, MessageBoxThread, nullptr, 0, nullptr);

        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
    default:
        break;
    }

    if (hThread != nullptr)
    {
        CloseHandle(hThread);
        return TRUE;
    }
    return FALSE;
}
