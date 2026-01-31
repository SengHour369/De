#include <iostream>
#include "UserService.h"
#include "RestaurantService.h"
#include "MenuItemService.h"
#include "OrderService.h"
#include "Admin.h"
#include "AppUser.h"
#include "LogIn.h"
using namespace std;

void displayMainMenu() {
    cout << "\n=== RESTAURANT ORDERING SYSTEM ===\n";
    cout << "1. User Management\n";
    cout << "2. Restaurant Management\n";
    cout << "3. Save All Data\n";
    cout << "4. Load All Data\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}


void saveAllData(UserService& userService, RestaurantService& restaurantService,
                 MenuItemService& menuItemService, OrderService& orderService) {
    cout << "\n=== SAVING ALL DATA ===\n";
    if (userService.saveToFile()) {
        cout << " Users saved successfully!\n";
    } else {
        cout << " Failed to save users!\n";
    }

    if (restaurantService.saveToFile()) {
        cout << " Restaurants saved successfully!\n";
    } else {
        cout << " Failed to save restaurants!\n";
    }

    if (menuItemService.saveToFile()) {
        cout << " Menu items saved successfully!\n";
    } else {
        cout << " Failed to save menu items!\n";
    }


    cout << "Data save completed!\n";
}

void loadAllData(UserService& userService, RestaurantService& restaurantService,
                MenuItemService& menuItemService, OrderService& orderService) {
    cout << "\n=== LOADING ALL DATA ===\n";
    if (userService.loadFromFile()) {
        cout << " Users loaded successfully!\n";
    } else {
        cout << " Failed to load users!\n";
    }

    if (restaurantService.loadFromFile()) {
        cout << " Restaurants loaded successfully!\n";
    } else {
        cout << "   Failed to load restaurants!\n";
    }

    if (menuItemService.loadFromFile()) {
        cout << " Menu items loaded successfully!\n";
    } else {
        cout << " Failed to load menu items!\n";
    }

    cout << "Data load completed!\n";
}


int main() {
    // Initialize services with default filenames
    UserService userService("users.dat");
    MenuItemService menuItemService("menuitems.dat");
    RestaurantService restaurantService("restaurants.dat");
    OrderService orderService;


    restaurantService.setMenuItemService(&menuItemService);


    Admin admin(restaurantService, menuItemService, userService);

    int mainChoice;
    bool running = true;

    cout << "\n========================================\n";
    cout << "   RESTAURANT ORDERING SYSTEM v2.0\n";
    cout << "   with Binary File Storage\n";
    cout << "========================================\n";

    // Try to load existing data
    loadAllData(userService, restaurantService, menuItemService, orderService);

    while (running) {
        displayMainMenu();
        cin >> mainChoice;
        cin.ignore();

        switch (mainChoice) {
            case 1: {
                // User management
                LogIn login(userService, admin, restaurantService,orderService);
                break;
            }

            case 2: {
                // Restaurant management
                User* currentUser = userService.getCurrentUser();
                if (!currentUser) {
                    cout << "Please login first!\n";
                    break;
                }
                AppUser appUser(userService, restaurantService,orderService);
                break;
            }

            case 3:
                saveAllData(userService, restaurantService, menuItemService, orderService);
                break;

            case 4:
                loadAllData(userService, restaurantService, menuItemService, orderService);
                break;

            case 5:
                saveAllData(userService, restaurantService, menuItemService, orderService);
                running = false;
                cout << "\nThank you for using Restaurant Ordering System!\n";
                cout << "All data has been saved to binary files.\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}