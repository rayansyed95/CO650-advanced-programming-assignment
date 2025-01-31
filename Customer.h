#pragma once
#include <string>
#include <memory>
#include "Order.h"
class Customer {
private:
	std::string name;
	std::unique_ptr<Order> currentOrder;
public:
	Customer(const std::string& name); // Constructor
	void createOrder(int orderId);
	void addToOrder(std::unique_ptr<FoodItem> item); // Memory management is handled using smart pointers
	void placeOrder(); std::unique_ptr<Order>& getCurrentOrder();
	std::string getName() const;
};