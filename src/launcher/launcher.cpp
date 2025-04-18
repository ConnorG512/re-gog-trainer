#include <cstdio>
#include <cstring>
#include <errhandlingapi.h>
#include <libloaderapi.h>
#include <memoryapi.h>
#include <minwinbase.h>
#include <process.h>
#include <processthreadsapi.h>
#include <string>
#include <windows.h>
#include <winnt.h>

#include "../util/logger.h"

Logger launcher_log { "re-gog-trainer-launcher.log" };

// Function declarations
void launchTargetProcess(PROCESS_INFORMATION* process_info);
LPVOID AllocateMemoryInAddressSpace(PROCESS_INFORMATION* process_info, SIZE_T dll_length);
void writeToProcessMemory(PROCESS_INFORMATION* process_info, SIZE_T dll_length, LPVOID p_dll_reserved_address, const char* dll_path);
FARPROC GetProcessAddress();
HANDLE CreateRemoteThreadInProcess(PROCESS_INFORMATION* process_info, FARPROC load_library_address, LPVOID p_dll_reserved_address);

int main (int argc, char *argv[]) {
  launcher_log.printTextToLogFile("Launcher now running!", Logger::LogType::LOG_INFO);

  const char* dll_path = "libre-gog-trainer.dll";
  SIZE_T dll_length = strlen(dll_path) + 1; // + 1 for null terminator byte
  PROCESS_INFORMATION process_info {};
 
  launchTargetProcess(&process_info);
  LPVOID p_dll_reserved_address = AllocateMemoryInAddressSpace(&process_info, dll_length);
  writeToProcessMemory(&process_info, dll_length, p_dll_reserved_address, dll_path);
  FARPROC load_library_address = GetProcessAddress();
  HANDLE process_handle = CreateRemoteThreadInProcess(&process_info, load_library_address, p_dll_reserved_address);

  printf("DLL reserved address: %p\n", p_dll_reserved_address);
  printf("Load Library Address: %p\n", load_library_address);
  printf("Process Handle: %p\n", process_handle);
  return 0;
}

// Function definitions
void launchTargetProcess(PROCESS_INFORMATION *process_info) 
{
  STARTUPINFO startup_info {};

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
        process_info) == FALSE)
  {
    MessageBoxA(NULL, "Failed to create process!", "Launcher Error", MB_OK | MB_ICONERROR);
    abort();
  }
}

LPVOID AllocateMemoryInAddressSpace(PROCESS_INFORMATION* process_info, SIZE_T dll_length) 
{
  // Allocate memory in to the address space of the process
  auto p_dll_reserved_address = VirtualAllocEx(
      process_info -> hProcess, 
      nullptr, 
      dll_length,
      MEM_COMMIT, 
      PAGE_EXECUTE_READWRITE);
  if (p_dll_reserved_address == nullptr) 
  {
    launcher_log.printTextToLogFile("Could not get base address!", Logger::LogType::LOG_ERROR);
    MessageBoxA(NULL, "Failed to get base address!", "Launcher Error", MB_OK | MB_ICONERROR);
  }
  return p_dll_reserved_address;
}

void writeToProcessMemory(PROCESS_INFORMATION* process_info, SIZE_T dll_length, LPVOID p_dll_reserved_address, const char* dll_path)
{
  if (!WriteProcessMemory(
        process_info -> hProcess, 
        p_dll_reserved_address, 
        dll_path, 
        dll_length, 
        nullptr)) 
  {
    launcher_log.printTextToLogFile("Could not write dll into the target memory!", Logger::LogType::LOG_ERROR);
    MessageBoxA(NULL, "Failed to assign data to dll address!", "Launcher Error", MB_OK | MB_ICONERROR);
  }
}

FARPROC GetProcessAddress()
{
  FARPROC p_load_library_address = GetProcAddress(
      GetModuleHandleA("kernel32.dll"), 
      "LoadLibraryA");
  if (p_load_library_address == nullptr) 
  {
    launcher_log.printTextToLogFile("Could not find LoadLibraryA Address", Logger::LogType::LOG_ERROR);
    MessageBoxA(NULL, "Failed to get LoadLibraryA address!", "Launcher Error", MB_OK | MB_ICONERROR);
  }
  return p_load_library_address;
}

HANDLE CreateRemoteThreadInProcess(PROCESS_INFORMATION* process_info, FARPROC load_library_address, LPVOID p_dll_reserved_address) 
{
  HANDLE remote_thread = CreateRemoteThread(
      process_info -> hProcess, 
      nullptr, 
      0, 
      (LPTHREAD_START_ROUTINE)load_library_address, // Cast otherwise, 'No Matching Function Call' 
      p_dll_reserved_address, 
      0, 
      nullptr);
  if (remote_thread == NULL) {
    launcher_log.printTextToLogFile("Could not create remote thread!", Logger::LogType::LOG_ERROR);
    MessageBoxA(NULL, "Failed to create remote thread!", "Launcher Error", MB_OK | MB_ICONERROR);
  }
  return remote_thread;
 }
