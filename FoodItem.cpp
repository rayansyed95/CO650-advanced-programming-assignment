#include "FoodItem.h"

int FoodItem::totalItems = 0; // Initialize the static member variable totalItems to 0
// This static member keeps track of the total number of FoodItem objects created.

// Polymorphism is implemented through the FoodItem class and its derived classes Pizza and Burger.
// The FoodItem class is an abstract class that has a pure virtual function prepare().

FoodItem::FoodItem(const std::string& name, double price) : name(name), price(price) {
    totalItems++;
}

double FoodItem::getPrice() const {
	// This function returns the price of the food item
    return price;
}

std::string FoodItem::getName() const {
	// This function returns the name of the food item
    return name;
}

bool FoodItem::operator<(const FoodItem& other) const {
	// This function compares the price of two food items
    // The operator < is overloaded to compare the prices of FoodItem objects.
    return price < other.price;
}

