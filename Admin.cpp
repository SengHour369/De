#include "Admin.h"
#include "RestaurantService.h"
#include "MenuItemService.h"
#include "UserService.h"
#include "Restaurant.h"
#include "User.h"
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

Admin::Admin(RestaurantService& restaurantService,
             MenuItemService& menuItemService,
             UserService& userService)
    : restaurantService(restaurantService),
      menuItemService(menuItemService),
      userService(userService) {
}

void Admin::runAdminMenu() {
    int choice;
    bool running = true;

    while (running) {
        displayAdminMainMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: manageRestaurants(); break;
            case 2: manageMenuItems(); break;
            case 3: manageUsers(); break;
            case 4: displayAdminDashboard(); break;
            case 0:
                cout << "Returning to main menu...\n";
                running = false;
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}

void Admin::displayAdminMainMenu() {
    cout << "\n=== ADMIN DASHBOARD ===\n";
    cout << "1. Manage Restaurants\n";
    cout << "2. Manage Menu Items\n";
    cout << "3. Manage Users\n";
    cout << "4. View Dashboard\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

void Admin::manageUsers() {
    int choice;
    bool inMenu = true;

    while (inMenu) {
        displayUserMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                userService.display(userService.getAllUsers());
                break;
            }
            case 2: {
                userService.display(userService.sortByName());
                break;
            }
            case 3: {
                string userId, status;
                cout << "Enter user ID: ";
                cin >> userId;
                cout << "Enter new status (Active/Inactive): ";
                cin >> status;

                if (userService.updateUserStatus(userId, status))
                    cout << "User status updated successfully!\n";
                break;
            }
            case 4: {
                string userId;
                cout << "Enter user ID to delete: ";
                cin >> userId;

                char confirm;
                cout << "Are you sure? (y/n): ";
                cin >> confirm;

                if (confirm == 'y' || confirm == 'Y') {
                    if (userService.deleteUser(userId))
                        cout << "User deleted successfully!\n";
                }
                break;
            }
            case 0:
                inMenu = false;
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}

void Admin::displayUserMenu() {
    cout << "\n=== USER MANAGEMENT ===\n";
    cout << "1. View All Users\n";
    cout << "2. View Users (Sorted by Name)\n";
    cout << "3. Update User Status\n";
    cout << "4. Delete User\n";
    cout << "0. Back to Admin Menu\n";
    cout << "Enter your choice: ";
}

void Admin::manageRestaurants() {
    int choice;
    bool inMenu = true;

    while (inMenu) {
        displayRestaurantMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                vector<Restaurant> restaurants = restaurantService.getAllRestaurants();
                cout << "\n=== ALL RESTAURANTS ===\n";
                if (restaurants.empty())
                    cout << "No restaurants found.\n";
                else {
                    restaurantService.displayRestaurants(restaurants);
                }
                break;
            }
                case 2: {
                vector<Restaurant> restaurants = restaurantService.getAllRestaurants();
                cout << "\n=== ALL RESTAURANTS ===\n";
                if (restaurants.empty())
                    cout << "No restaurants found.\n";
                else {
                    restaurantService.displayRestaurants(restaurantService.sortByName());
                }
                break;
            }
            case 0:
                inMenu = false;
                break;
            default:
                cout << "Option not implemented yet!\n";
        }
    }
}

void Admin::displayRestaurantMenu() {
    cout << "\n=== RESTAURANT MANAGEMENT ===\n";
    cout << "1. View All Restaurants\n";
    cout << "2. View All Restaurants Sort By name\n";
    cout << "0. Back to Admin Menu\n";
    cout << "Enter your choice: ";
}

void Admin::manageMenuItems() {
    int choice;
    bool inMenu = true;

    while (inMenu) {
        displayMenuItemMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                string name, description;
                double price;
                bool available;
                int restaurantId;

                cout << "Enter menu item name: ";
                getline(cin, name);
                cout << "Enter description: ";
                getline(cin, description);
                cout << "Enter price: ";
                cin >> price;
                cout << "Is available? (1 for Yes, 0 for No): ";
                cin >> available;
                cout << "Enter restaurant ID: ";
                cin >> restaurantId;
                cin.ignore();

                if (menuItemService.createMenuItem(name, description, price, available, restaurantId)) {
                    cout << "Menu item created successfully!\n";
                } else {
                    cout << "Failed to create menu item!\n";
                }
                break;
            }
            case 0:
                inMenu = false;
                break;
            default:
                cout << "Option not implemented yet!\n";
        }
    }
}

void Admin::displayMenuItemMenu() {
    cout << "\n=== MENU ITEM MANAGEMENT ===\n";
    cout << "1. Create Menu Item\n";
    cout << "0. Back to Admin Menu\n";
    cout << "Enter your choice: ";
}

void Admin::displayAdminDashboard() {
    cout << "\n=== ADMIN DASHBOARD ===\n";

    vector<User> users = userService.getAllUsers();
    cout << "Total Users: " << users.size() << "\n";

    int admin = 0, staff = 0, customer = 0;
    for (const User& u : users) {
        string role = u.getRole();
        if (role == "ADMIN") admin++;
        else if (role == "STAFF") staff++;
        else if (role == "CUSTOMER") customer++;
    }

    cout << "Admins: " << admin << "\n";
    cout << "Staff: " << staff << "\n";
    cout << "Customers: " << customer << "\n";

    vector<Restaurant> restaurants = restaurantService.getAllRestaurants();
    cout << "Total Restaurants: " << restaurants.size() << "\n";

    vector<MenuItem> items = menuItemService.getAllMenuItems();
    cout << "Total Menu Items: " << items.size() << "\n";

    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}