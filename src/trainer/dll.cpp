#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <libloaderapi.h>
#include <memoryapi.h>
#include <minwindef.h>
#include <processthreadsapi.h>
#include <sec_api/stdio_s.h>
#include <synchapi.h>
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
        Sleep(2000);

        // Log File 
        std::ofstream logFile { "re-trainer.log" };
        if (!logFile) 
        {
          MessageBoxA(
              NULL, "Could not open log file!", 
              "DLL Error", 
              MB_OK | MB_ICONERROR);
        }

        HMODULE executeable_module { GetModuleHandleA( NULL )};
        if (executeable_module == NULL) 
        {
          MessageBoxA(NULL, "Could not get module handle!","DLL Error", MB_OK | MB_ICONERROR);
        }       

        logFile << "executeable_module: " << executeable_module << "\n";

        // Create a pointer to the base module + offset
        uint8_t* address_to_patch = reinterpret_cast<uint8_t*>(executeable_module) + 0x0005815D;

        logFile << "address_to_patch: " << static_cast<void*>(address_to_patch) << "\n";
        
        DWORD old_protection_value = {};
        if (!VirtualProtect(
              address_to_patch, 
              4, 
              PAGE_EXECUTE_READWRITE, 
              &old_protection_value)) 
        {
          MessageBoxA(NULL, "Failed to change memory protections!", "DLL Error", MB_OK | MB_ICONERROR); 
        }

        uint8_t buffer[4] { 0xfe, 0x0c, 0x41, 0x90 };
        memcpy(address_to_patch, buffer, 4);


        // if (!WriteProcessMemory(
        //       GetCurrentProcess(), 
        //       address_to_patch, 
        //       buffer, 
        //       4, 
        //       nullptr)) 
        // {
        //   MessageBoxA(NULL, "Could not write bytes to memory!","DLL Error", MB_OK | MB_ICONERROR);
        // }
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

