#include <cstdio>
#include <windows.h>
#include <winnt.h>

BOOL WINAPI DllMain (
    HINSTANCE hinstDLL,
    DWORD fdwReason,
    LPVOID lpvReserved )
{
  switch ( fdwReason ) {
    case DLL_PROCESS_ATTACH:
      printf("DLL Library RE Trainer has been loaded!\n");
      MessageBoxA(NULL, "Dll has been successfully attached!", "RE GoG trainer", MB_OK);
      break;
    case DLL_THREAD_ATTACH:
      break;
    case DLL_THREAD_DETACH:
      break;
    case DLL_PROCESS_DETACH:
      break;
  }
  return TRUE;
}


