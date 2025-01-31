#pragma once
#include "FoodItem.h"

class Burger : public FoodItem {
private:
    bool hasChese;

public:
	Burger(const std::string& name, double price, bool hasChese); // Constructor
    void prepare() override; // Overridden function - polymorphism is achieved here. 
};

