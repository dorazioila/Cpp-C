#ifndef XMLFILESERIALIZEREXCEPTION_HPP
#define XMLFILESERIALIZEREXCEPTION_HPP

#include "Exception.h"

class XmlFileSerializerException : public Exception {
private:
    int code;

public:
    static const int NOT_ALLOWED = 1;
    static const int FILE_NOT_FOUND = 2;
    static const int END_OF_FILE = 3;

    XmlFileSerializerException(const std::string& msg, int c)
        : Exception(msg), code(c) {}

    int getCode() const { return code; }
};

#endif
