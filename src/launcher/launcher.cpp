#include <cstdio>
#include <cstring>
#include <errhandlingapi.h>
#include <libloaderapi.h>
#include <memoryapi.h>
#include <minwinbase.h>
#include <processthreadsapi.h>
#include <windows.h>
#include <winnt.h>

int main (int argc, char *argv[]) {
  STARTUPINFO startup_info {};
  PROCESS_INFORMATION process_info {};
  
  // Create the executeable process
  if (CreateProcessA(
        "ResidentEvil.exe",
        nullptr, 
        nullptr, 
        nullptr, 
        false, 
        0, 
        nullptr, 
        nullptr, 
        &startup_info, 
        &process_info) == FALSE) 
  {
    MessageBoxA(NULL, "Failed to create process!", "Launcher Error", MB_OK | MB_ICONERROR);
    return 1;
  }
  
  // Allocate memory in to the address space of the process
  SIZE_T dll_length = strlen("re-trainer.dll") + 1; // + 1 for null terminator byte
  auto p_dll_reserved_address = VirtualAllocEx(
      process_info.hProcess, 
      nullptr, 
      dll_length,
      MEM_COMMIT, 
      PAGE_EXECUTE_READWRITE);
  if (p_dll_reserved_address == nullptr) 
  {
    printf("Error! could not get base address: %lu", GetLastError());
    MessageBoxA(NULL, "Failed to get base address!", "Launcher Error", MB_OK | MB_ICONERROR);
    return 1;
  }
  
  printf("DLL reserved address: %p\n", p_dll_reserved_address);

  const char* dll_path = "re-trainer.dll";
  if (!WriteProcessMemory(
        process_info.hProcess, 
        p_dll_reserved_address, 
        dll_path, 
        dll_length, 
        nullptr)) 
  {
    printf("Error! could not write dll to memroy: %lu\n", GetLastError());
    MessageBoxA(NULL, "Failed to assign data to dll address!", "Launcher Error", MB_OK | MB_ICONERROR);
    return 1;
  }

  auto p_load_library_address = GetProcAddress(
      GetModuleHandleA("kernel32.dll"), 
      "LoadLibraryA");
  if (p_load_library_address == nullptr) 
  {
    printf("Error finding LoadLibraryA address! %lu\n", GetLastError());
    MessageBoxA(NULL, "Failed to get LoadLibraryA address!", "Launcher Error", MB_OK | MB_ICONERROR);
    return 1;
  }
  
  HANDLE remote_thread = CreateRemoteThread(
      process_info.hProcess, 
      nullptr, 
      0, 
      (LPTHREAD_START_ROUTINE)p_load_library_address, // Cast otherwise, 'No Matching Function Call' 
      p_dll_reserved_address, 
      0, 
      nullptr);
  if (remote_thread == NULL) {
    printf("Error creating remote thread! %lu\n", GetLastError());
    MessageBoxA(NULL, "Failed to create remote thread!", "Launcher Error", MB_OK | MB_ICONERROR);
  }
  return 0;
}
