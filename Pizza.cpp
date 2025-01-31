#include "Pizza.h"
#include <iostream>

Pizza::Pizza(const std::string& name, double price, const std::string& size)
	: FoodItem(name, price), size(size) { // constructor for the Pizza class with the relevant parameters.
}

void Pizza::prepare() {
	// this is an overridden function from the base class FoodItem whose purpose is to print out the details of the pizza being prepared.
    std::cout << "Preparing " << size << " " << name << " pizza." << std::endl;
}

