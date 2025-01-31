#pragma once
#include "FoodItem.h"
class Pizza : public FoodItem {
private:
	std::string size;
public:
	Pizza(const std::string& name, double price, const std::string& size); // Constructor
	void prepare() override; // Overridden function - polymorphism is achieved here. 
};