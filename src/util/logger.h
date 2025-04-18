#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

class Logger {
  private:
    std::string m_log_title { "default.log" };
    std::ofstream m_log_file { m_log_title };
  public:
    enum class LogType {
      LOG_INFO,
      LOG_ERROR,
    };
  public:
    Logger(std::string title);
    void printTextToLogFile(std::string log_message, LogType log_type);
};

#endif // !LOGGER_H
