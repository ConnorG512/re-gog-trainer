#include <cstdio>
#include <cstring>
#include <sec_api/stdio_s.h>
#include <vector>
#include <windows.h>
#include <wincon.h>
#include <wingdi.h>
#include <winnt.h>

#include "memory_patcher.h"
#include "../util/logger.h"

BOOL WINAPI DllMain (
    HINSTANCE hinstDLL,
    DWORD fdwReason,
    LPVOID lpvReserved )
{
  switch ( fdwReason ) {
    case DLL_PROCESS_ATTACH:
      {
        Sleep(1000);
        Logger dll_log {};
        
        HMODULE executeable_module { GetModuleHandleA( NULL )};
        if (executeable_module == NULL) 
        {
          MessageBoxA(NULL, "DLL Error","Could not get module handle!", MB_OK | MB_ICONERROR);
        }       
                
        MemoryPatcher infinite_ammo(executeable_module, 0x0005815D, { 0xfe, 0x0c, 0x41, 0x90 });
        infinite_ammo.changeMemoryProtectionStatus();
        infinite_ammo.writeBytesToProcessMemory();
      }
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

