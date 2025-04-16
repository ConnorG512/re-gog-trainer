#include <cstdio>
#include <libloaderapi.h>
#include <minwindef.h>
#include <string>
#include <windows.h>
#include <wincon.h>
#include <wingdi.h>
#include <winnt.h>

BOOL WINAPI DllMain (
    HINSTANCE hinstDLL,
    DWORD fdwReason,
    LPVOID lpvReserved )
{
  switch ( fdwReason ) {
    case DLL_PROCESS_ATTACH:
      {
        if (!AllocConsole()) {
          MessageBoxA(NULL, "DLL Error", "Failed to allocate a console!", MB_OK);
        }
        std::string executeable_title {"ResidentEvil.exe"};
        HMODULE executeable_module { GetModuleHandleA(executeable_title.c_str()) };
        printf("DLL has been attached! Module handle: %p\n", executeable_module);
      }
    case DLL_THREAD_ATTACH:
      break;
    case DLL_THREAD_DETACH:
      break;
    case DLL_PROCESS_DETACH:
      break;
  }
  return TRUE;
}

