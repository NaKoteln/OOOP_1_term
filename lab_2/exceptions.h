#ifndef LAB_2_EXCEPTIONS_H
#define LAB_2_EXCEPTIONS_H

#include <exception>
#include <string>
#include "strategy.h"

class StrategyNotFoundException : public std::exception {
private:
    std::string message;
public:
    StrategyNotFoundException(std::string& strategyName) {
        message = "Strategy with name \"" + strategyName + "\" not found";
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class MappingNotFoundException : public std::exception {
private:
    std::string message;

public:
    MappingNotFoundException(const std::vector<ActionType>& answers) {
        message += "Mapping for answer: {";
        auto it = answers.begin();
        for ( ; it < (answers.end() - 1); it++) {
            message = message + "[" + ((*it == COOPERATE)? "COOPERATE" : "DEFECT") + "], ";
        }

        if (it != (answers.end())) {
            message = message + "[" + ((*it == COOPERATE)? "COOPERATE" : "DEFECT") + "]";
        }

        message += "} not found in the game matrix";
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class MatrixCreatingException : public std::exception {
private:
    std::string message;
public:
    MatrixCreatingException(const std::string& message) {
        this->message = "Matrix creating exception: \"" + message + "\"";
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class DuplicateStrategyNameException : public std::exception {
private:
    std::string message;
public:
    DuplicateStrategyNameException(const std::string& strategyName) {
        message = "Found duplicate strategy: \"" + strategyName + "\"";
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class UnknownOptionException : public std::exception {
private:
    std::string message;
public:
    UnknownOptionException(const std::string& option) {
        message = "Unknown option: \"" + option + "\"";
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class MissingArgumentException : public std::exception {
private:
    std::string message;
public:
    MissingArgumentException(const std::string& option) {
        message = "A missing argument for option: \"" + option + "\"";
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidInputException : public std::exception {
private:
    std::string message;
public:
    InvalidInputException(const std::string& message) {
        this->message = "Invalid input error: \"" + message + "\"";
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};


#endif //LAB_2_EXCEPTIONS_H
