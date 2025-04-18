#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

class Logger {
  private:
    std::ofstream m_file { "re-trainer.log" };
  public:
    enum class LogType {
      LOG_INFO,
      LOG_ERROR,
    };
  private:
    void printTextToTerminal(std::string &log_message, LogType log_type);
};

#endif // !LOGGER_H
