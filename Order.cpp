#include "Order.h"
#include <iostream>

Order::Order(int orderId) : orderId(orderId) {}

void Order::addItem(std::unique_ptr<FoodItem> item) { // smart pointer to FoodItem. Memory management is handled here.
	items.push_back(std::move(item));
}

double Order::getTotalPrice() const {
	// This method calculates the total price of the order by summing the prices of all items in the order.
	double total = 0.0; for (const auto& item : items) {
		total += item->getPrice();
	}
	return total;
}

void Order::prepareOrder() {
	// This method prepares all items in the order by calling the prepare method of each item.
	std::cout << "Preparing order #" << orderId << std::endl;
	for (const auto& item : items) { item->prepare();
	}
}

// Friend function implementation
// The printOrderDetails function is defined outside the Order class, but it has access to the private members of the Order class because it is declared as a friend.
void printOrderDetails(const Order& order) {
	std::cout << "Order #" << order.orderId << " details:" << std::endl;
	for (const auto& item : order.items) {
		std::cout << "- " << item->getName() << ": $" << item->getPrice() << std::endl;
	}
	std::cout << "Total: $" << order.getTotalPrice() << std::endl;
}