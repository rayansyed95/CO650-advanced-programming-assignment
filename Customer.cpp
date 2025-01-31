#include "Customer.h"
#include <iostream>

Customer::Customer(const std::string& name) : name(name) {}

void Customer::createOrder(int orderId) { // method to create an order for a customer
	currentOrder = std::make_unique<Order>(orderId); // used smart pointer to create object. Part of memory management
}

void Customer::addToOrder(std::unique_ptr<FoodItem> item) { // method to add an item to the order
	if (currentOrder) {
		currentOrder->addItem(std::move(item));
	} else {
		throw std::runtime_error("No active order for the customer.");
	}
}

void Customer::placeOrder() { // method to place an order for a customer
	if (currentOrder) {
		std::cout << name << " is placing an order." << std::endl;
		currentOrder->prepareOrder();
		printOrderDetails(*currentOrder);
		currentOrder.reset();
	} else {
		throw std::runtime_error("No active order to place.");
	}
}

std::unique_ptr<Order>& Customer::getCurrentOrder() { // method to get the current order
	return currentOrder;
}

std::string Customer::getName() const { // Add this method
	return name;
}