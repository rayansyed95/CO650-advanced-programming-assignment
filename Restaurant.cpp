#include "Restaurant.h"
#include "Pizza.h"
#include "Burger.h"
#include <iostream>
#include "Exceptions.h"

Restaurant::Restaurant() : nextOrderId(1), processOrder(nullptr) {}

std::unique_ptr<FoodItem> Restaurant::getFoodItemFromInput() { // Helper method to take food item input from the user
    int itemType;
    std::string name, size;
    double price;
    bool hasCheese;

    std::cout << "Choose food item type:\n";
    std::cout << "1. Pizza\n";
    std::cout << "2. Burger\n";
    std::cout << "Enter your choice: ";
    std::cin >> itemType;

    std::cout << "Enter item name: ";
    std::cin.ignore(); // Clear the input buffer
    std::getline(std::cin, name);

    std::cout << "Enter item price: ";
    std::cin >> price;

    if (itemType == 1) {
        // Pizza-specific input
        std::cout << "Enter pizza size (e.g., Small, Medium, Large): ";
        std::cin.ignore();
        std::getline(std::cin, size);
		return std::make_unique<Pizza>(name, price, size); // used smart pointer to create object. 
    }
    else if (itemType == 2) {
        // Burger-specific input
        std::cout << "Does the burger have cheese? (1 for Yes, 0 for No): ";
        std::cin >> hasCheese;
		return std::make_unique<Burger>(name, price, hasCheese); // used smart again pointer to create object.
    }
    else {
        throw std::runtime_error("Invalid food item type.");
    }
}

void Restaurant::addCustomer(const std::string& name) { // this method adds a customer to the restaurant
	customers.push_back(std::make_unique<Customer>(name)); // used smart pointer to create object. Part of memory management
}

void Restaurant::createOrder(const std::string& customerName) { // this method creates an order for a customer
	auto it = std::find_if(customers.begin(), customers.end(),
		[&](const auto& customer) { return customer->getName() == customerName; });
	if (it != customers.end()) {
		(*it)->createOrder(nextOrderId++);
	}
	else {
		throw std::runtime_error("Customer not found.");
	}
}

void Restaurant::addItemToOrder(const std::string& customerName, std::unique_ptr<FoodItem> item) { // this method adds an item to the order
	auto it = std::find_if(customers.begin(), customers.end(),
		[&](const auto& customer) { return customer->getName() == customerName; });
	if (it != customers.end()) {
		(*it)->addToOrder(std::move(item));
	}
	else {
		throw std::runtime_error("Customer not found.");
	}
}

void Restaurant::placeOrder(const std::string& customerName) { // this method places an order for a customer
	auto it = std::find_if(customers.begin(), customers.end(),
		[&](const auto& customer) { return customer->getName() == customerName; });
	if (it != customers.end()) {
		(*it)->placeOrder();
		if (processOrder) {
			processOrder(*((*it)->getCurrentOrder()));
		}
		winsockClient.sendMessage("Order placed successfully. Waiting server confirmation...");
	}
	else {
		throw std::runtime_error("Customer not found.");
	}
}
void Restaurant::setOrderProcessStrategy(OrderProcessStrategy strategy) { // this method sets the order processing strategy
	processOrder = strategy;
}

void Restaurant::run() { // this method runs the main loop of the restaurant
    int choice = 0;
    std::string customerName;

    std::cout << "Welcome to the Online Food Ordering System!\n";

    while (true) {
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Add a Customer\n";
        std::cout << "2. Create an Order\n";
        std::cout << "3. Add Items to Order\n";
        std::cout << "4. Place an Order\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        try {
            switch (choice) {
            case 1:
                // Add Customer
                std::cout << "Enter customer name: ";
                std::cin.ignore();
                std::getline(std::cin, customerName);
                addCustomer(customerName);
                std::cout << "Customer " << customerName << " added successfully.\n";
                break;

            case 2:
                // Create Order
                std::cout << "Enter customer name: ";
                std::cin.ignore();
                std::getline(std::cin, customerName);
                createOrder(customerName);
                std::cout << "Order created for " << customerName << ".\n";
                break;

            case 3:
                // Add Items to Order
                std::cout << "Enter customer name: ";
                std::cin.ignore();
                std::getline(std::cin, customerName);
                addItemToOrder(customerName, getFoodItemFromInput());
                break;

            case 4:
                // Place Order
                winsockClient.connectToServer("127.0.0.1", 8080); // Ensure connection
                std::cout << "Enter customer name: ";
                std::cin.ignore();
                std::getline(std::cin, customerName);
                placeOrder(customerName);
                break;

            case 5:
                std::cout << "Exiting the system. Goodbye!\n";
                return;

            default:
                std::cout << "Invalid choice. Please try again.\n";
            }
        }
        catch (const FoodOrderException& e) {
            std::cerr << "Food Order Exception: " << e.what() << "\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Standard Exception: " << e.what() << "\n";
        }
    }
}
