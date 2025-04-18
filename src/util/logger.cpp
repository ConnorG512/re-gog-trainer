#include "logger.h"

Logger::Logger(std::string title) 
  : m_log_title { title } {}
void Logger::printTextToLogFile(std::string log_message, LogType log_type) 
{
  switch (log_type) {
    case LogType::LOG_INFO:
      m_log_file << "INFO: " << log_message << "\n"; 
      break;
    case Logger::LogType::LOG_ERROR:
      m_log_file << "ERROR: " << log_message << "\n"; 
      break;
  }
}
