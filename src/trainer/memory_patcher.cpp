#include "memory_patcher.h"
#include <cstdint>
#include <errhandlingapi.h>
#include <format>

MemoryPatcher::MemoryPatcher(const HMODULE p_base_address, const uint32_t function_offset_address, const std::vector<uint8_t>& patch_bytes, Logger* logger_file)
  : p_application_base_address { p_base_address }
  , m_function_offset { function_offset_address }
  , m_target_address { reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(p_application_base_address) + m_function_offset ) }
  , m_patch_bytes ( patch_bytes )
  , m_logger_file( logger_file )
{
  m_logger_file->printTextToLogFile(std::format("{}{}", "Application Base Address:", static_cast<const void*>(p_application_base_address)), Logger::LogType::LOG_INFO);
  m_logger_file->printTextToLogFile(std::format("{}{:X}", "Function offset: " , m_function_offset), Logger::LogType::LOG_INFO);
  m_logger_file->printTextToLogFile(std::format("{}{}", "Function + base address: ", static_cast<void*>(m_target_address)), Logger::LogType::LOG_INFO);
}

void MemoryPatcher::changeMemoryProtectionStatus() 
{
  if (!VirtualProtect(m_target_address, m_patch_bytes.size(), PAGE_EXECUTE_READWRITE, &m_old_protection_value)) 
  {
    m_logger_file->printTextToLogFile(std::format("{}{}", "Failed to change the protection status! GLE: ", GetLastError()), Logger::LogType::LOG_ERROR);
  }
}

void MemoryPatcher::writeBytesToProcessMemory()  
{
  memcpy(m_target_address, m_patch_bytes.data(), m_patch_bytes.size());
}
