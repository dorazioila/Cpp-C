#include "PasswordException.h"

PasswordException::PasswordException(const std::string& msg, int errorCode) : Exception(msg), code(errorCode) {
}

int PasswordException::getCode() const {
    return code;
}