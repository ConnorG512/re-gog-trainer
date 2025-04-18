#include "logger.h"

void Logger::printTextToTerminal(std::string &log_message, LogType log_type) 
{
  switch (log_type) {
    case LogType::LOG_INFO:
      m_file << "INFO: " << log_message << "\n"; 
      break;
    case Logger::LogType::LOG_ERROR:
      m_file << "ERROR: " << log_message << "\n"; 
      break;
  }
}
