#pragma once
#include <vector>
#include <memory>
#include "FoodItem.h"
class Order {
private:
	int orderId;
	std::vector<std::unique_ptr<FoodItem>> items;
public:
	Order(int orderId); // Constructor
	void addItem(std::unique_ptr<FoodItem> item); // smart pointer to FoodItem. Memory management is handled here. 
	double getTotalPrice() const; // Get total price of the order
	void prepareOrder(); // Prepare all items in the order
	
	// Friend function to print order details
	// The printOrderDetails function is declared as a friend of the Order class, allowing it to access private members.
	friend void printOrderDetails(const Order& order);
};