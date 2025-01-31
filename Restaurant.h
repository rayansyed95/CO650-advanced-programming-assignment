#pragma once

#include <vector>
#include <memory>
#include "Customer.h"
#include "WinsockClient.h"

class Restaurant {
private:
	std::vector<std::unique_ptr<Customer>> customers; // Vector to store customers
    int nextOrderId;
	WinsockClient winsockClient; // Winsock client object

    // This is a Function pointer for order processing strategy
    typedef void (*OrderProcessStrategy)(Order&);
    OrderProcessStrategy processOrder;

    // Helper method to take food item input from the user
	std::unique_ptr<FoodItem> getFoodItemFromInput(); // Helper method to take food item input from the user, smart pointer to FoodItem
	

public:
	Restaurant(); // Constructor
    void addCustomer(const std::string& name);
    void createOrder(const std::string& customerName);
    void addItemToOrder(const std::string& customerName, std::unique_ptr<FoodItem> item);
    void placeOrder(const std::string& customerName);
    void setOrderProcessStrategy(OrderProcessStrategy strategy);
    void run();
};
