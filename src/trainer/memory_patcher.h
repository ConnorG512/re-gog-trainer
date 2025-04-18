#ifndef MEMORY_PATCHER_H
#define MEMORY_PATCHER_H

#include <cstdint>
#include <cstring>
#include <memoryapi.h>
#include <minwindef.h>
#include <vector>
#include <windows.h>
#include <array>

class MemoryPatcher {
  private:
    const HMODULE p_application_base_address{ nullptr };
    const uint32_t m_function_offset { 0 };
    uint8_t* m_target_address { nullptr };
    const std::vector<uint8_t> m_patch_bytes { 0x00 };
    DWORD m_old_protection_value { 0 };

  public:
    MemoryPatcher(const HMODULE p_base_address, const uint32_t function_offset_address, const std::vector<uint8_t>& patch_bytes);
    void changeMemoryProtectionStatus();
    void writeBytesToProcessMemory();
};

#endif // !MEMORY_PATCHER_H
