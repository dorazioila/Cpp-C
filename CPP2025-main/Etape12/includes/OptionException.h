#ifndef OPTIONEXCEPTION_H
#define OPTIONEXCEPTION_H
#include <string>
#include "Exception.h"

class OptionException : public Exception {
    public:
        OptionException(const std::string& msg);
};

#endif