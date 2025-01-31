#pragma once
#include <string>
class FoodItem {
protected:
	std::string name;
	double price;
public:
	FoodItem(const std::string& name, double price); // Constructor
	virtual ~FoodItem() = default; // Destructor
	virtual void prepare() = 0; // Pure virtual function for polymorphism
	virtual double getPrice() const;
	virtual std::string getName() const;
	
	// Overloaded operator for price comparison
	bool operator<(const FoodItem& other) const;
	// Static member to keep track of total items created
	static int totalItems;
};