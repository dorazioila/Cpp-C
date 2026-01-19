#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <exception>

class Exception : public std::exception {
private:
    std::string message;

public:
    Exception(const std::string& msg);

    std::string getMessage() const { return message; }

    const char* what() const noexcept override;
};

#endif
