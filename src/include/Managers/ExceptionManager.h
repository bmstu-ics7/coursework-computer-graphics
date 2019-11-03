#ifndef __EXCEPTIONMANAGER_H
#define __EXCEPTIONMANAGER_H

#include <exception>

class ManagerException : public std::exception
{
public:
    ManagerException(const char* msg) : message(msg) { }
    virtual ~ManagerException() = default;
    virtual const char* what() const noexcept = 0;

protected:
    const char* message;
};

class BuilderException : public ManagerException
{
public:
    BuilderException(const char* msg) : ManagerException(msg) { }
    const char* what() const noexcept { return message; }
};

class FileException : public ManagerException
{
public:
    FileException(const char* msg) : ManagerException(msg) { }
    const char* what() const noexcept { return message; }
};

class DrawException : public ManagerException
{
public:
    DrawException(const char* msg) : ManagerException(msg) { }
    const char* what() const noexcept { return message; }
};

class TransformException : public ManagerException
{
public:
    TransformException(const char* msg) : ManagerException(msg) { }
    const char* what() const noexcept { return message; }
};

#endif // __EXCEPTIONMANAGER_H
