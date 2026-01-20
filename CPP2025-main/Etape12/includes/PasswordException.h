#ifndef PASSWORDEXCEPTION_H
#define PASSWORDEXCEPTION_H

#include "Exception.h"

class PasswordException : public Exception {
    private:
        int code;

    public:
        
        static const int INVALID_LENGTH = 1;
        static const int ALPHA_MISSING = 2;
        static const int DIGIT_MISSING = 3;
        static const int NO_PASSWORD = 4;

        PasswordException(const std::string& msg, int errorCode = 0);
        
        int getCode() const;
};

#endif