#include <iostream>
#include "Restaurant.h"
#include "Exceptions.h"

int main() {
	// entry point of the program
    try {
		Restaurant restaurant; // Create a Restaurant object
		restaurant.run(); // Run the restaurant application
    }
    catch (const FoodOrderException& e) {
        std::cerr << "Food Order Exception: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Standard Exception: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown Exception occurred." << std::endl;
    }

    return 0;
}

