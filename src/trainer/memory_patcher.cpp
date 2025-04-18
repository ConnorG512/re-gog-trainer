#include "memory_patcher.h"

MemoryPatcher::MemoryPatcher(const HMODULE p_base_address, const uint32_t function_offset_address, const std::vector<uint8_t>& patch_bytes, Logger* logger_file)
  : p_application_base_address { p_base_address }
  , m_function_offset { function_offset_address }
  , m_patch_bytes ( patch_bytes )
  , m_logger_file( logger_file ) {}

void MemoryPatcher::changeMemoryProtectionStatus() 
{
  if (!VirtualProtect(m_target_address, m_patch_bytes.size(), PAGE_EXECUTE_READWRITE, &m_old_protection_value)) 
  {
    m_logger_file -> printTextToLogFile("Failed to change virtual protect status!", Logger::LogType::LOG_ERROR); 
    MessageBoxA(NULL, "DLL Error", "Failed to change virtual protect status!", MB_OK | MB_ICONERROR);
  }
}

void MemoryPatcher::writeBytesToProcessMemory()  
{
  memcpy(m_target_address, m_patch_bytes.data(), m_patch_bytes.size());
}
