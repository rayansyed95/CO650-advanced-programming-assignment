#pragma once
#include <stdexcept>

// Custom exception classes inherit from std::exception

class FoodOrderException : public std::exception { // FoodOrderException is a subclass of std::exception its puspose is to throw an exception when the order is invalid or the customer is not found
protected:
	std::string message;
public:
	FoodOrderException(const std::string& msg) : message(msg) {}
	virtual const char* what() const noexcept override {
		return message.c_str();
	}
};
class InvalidOrderException : public FoodOrderException { // InvalidOrderException is a subclass of FoodOrderException its puspose is to throw an exception when the order is invalid
public:
	InvalidOrderException(const std::string& msg) : FoodOrderException(msg) {}
};
class CustomerNotFoundException : public FoodOrderException { // CustomerNotFoundException is a subclass of FoodOrderException its puspose is to throw an exception when the customer is not found
public:
	CustomerNotFoundException(const std::string& msg) : FoodOrderException(msg) {}
};