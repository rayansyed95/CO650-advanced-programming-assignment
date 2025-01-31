#include "Burger.h"
#include <iostream>

Burger::Burger(const std::string& name, double price, bool hasChese)
	: FoodItem(name, price), hasChese(hasChese) { // constructor for the Burger class with the relevant parameters.
}

void Burger::prepare() {
    // this is an overridden function from the base class FoodItem whose purpose is to print out the details of the burger being prepared.
    std::cout << "Preparing " << name << " burger" << (hasChese ? " with cheese." : ".") << std::endl;
}

