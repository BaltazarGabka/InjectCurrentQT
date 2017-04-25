#ifndef ILOGGER_HPP
#define ILOGGER_HPP

#include <string>

class ILogger
{
public:
   virtual void put(const std::string& data) = 0;
   virtual ~ILogger(){}
};

#endif // ILOGGER_HPP
