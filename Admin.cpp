#include "Admin.h"
#include <iostream>
#include <limits>
using namespace std;

Admin::Admin(RestaurantService& restaurantService,
             MenuItemService& menuItemService,
             UserService& userService) :
    restaurantService(restaurantService),
    menuItemService(menuItemService),
    userService(userService) {
}

void Admin::runAdminMenu() {
    int choice;
    bool running = true;

    while (running) {
        displayAdminMainMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                manageRestaurants();
                break;
            case 2:
                manageMenuItems();
                break;
            case 3:
                manageUsers();
                break;
            case 4:
                displayAdminDashboard();
                break;
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

void Admin::manageRestaurants() {
    int choice;
    bool inMenu = true;

    while (inMenu) {
        displayRestaurantMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                vector<Restaurant> restaurants = restaurantService.getAllRestaurants();
                cout << "\n=== ALL RESTAURANTS ===\n";
                if (restaurants.empty()) {
                    cout << "No restaurants found.\n";
                } else {
                    for (const Restaurant& rest : restaurants) {
                        cout << "ID: " << rest.getId()
                             << " | Name: " << rest.getName()
                             << " | Category: " << rest.getCategory()
                             << " | Rating: " << rest.getRating() << "/5"
                             << " | Location: " << rest.getLocation() << "\n";
                    }
                }
                break;
            }

            case 2: {
                int id;
                cout << "Enter restaurant ID: ";
                cin >> id;

                Restaurant* result = restaurantService.getRestaurantById(id);
                if (result) {
                    cout << "\n=== RESTAURANT DETAILS ===\n";
                    cout << "ID: " << result->getId() << "\n";
                    cout << "Name: " << result->getName() << "\n";
                    cout << "Category: " << result->getCategory() << "\n";
                    cout << "Rating: " << result->getRating() << "/5\n";
                    cout << "Phone: " << result->getPhoneNumber() << "\n";
                    cout << "Location: " << result->getLocation() << "\n";


                    vector<MenuItem> menu = restaurantService.getMenuByRestaurant(id);
                    cout << "Menu Items: " << menu.size() << "\n";
                } else {
                    cout << "Restaurant not found!\n";
                }
                break;
            }

            case 3: {
                string name, category, phone, location;

                cout << "\n=== ADD NEW RESTAURANT ===\n";
                cout << "Enter restaurant name: ";
                getline(cin, name);

                cout << "Enter category: ";
                getline(cin, category);

                cout << "Enter phone number: ";
                getline(cin, phone);

                cout << "Enter location: ";
                getline(cin, location);

                bool success = restaurantService.addRestaurant(name, category, phone, location);
                if (success) {
                    cout << "Restaurant added successfully!\n";
                }
                break;
            }

            case 4: {
                int id;
                cout << "Enter restaurant ID to update: ";
                cin >> id;
                cin.ignore();

                Restaurant* existing = restaurantService.getRestaurantById(id);
                if (!existing) {
                    cout << "Restaurant not found!\n";
                    break;
                }

                string name, category, phone, location;

                cout << "Current Name: " << existing->getName() << "\n";
                cout << "Enter new name (or press enter to keep current): ";
                getline(cin, name);
                if (name.empty()) name = existing->getName();

                cout << "Current Category: " << existing->getCategory() << "\n";
                cout << "Enter new category: ";
                getline(cin, category);
                if (category.empty()) category = existing->getCategory();

                cout << "Current Phone: " << existing->getPhoneNumber() << "\n";
                cout << "Enter new phone: ";
                getline(cin, phone);
                if (phone.empty()) phone = existing->getPhoneNumber();

                cout << "Current Location: " << existing->getLocation() << "\n";
                cout << "Enter new location: ";
                getline(cin, location);
                if (location.empty()) location = existing->getLocation();

                Restaurant updated(id, name, category, existing->getRating(), phone, location);
                bool success = restaurantService.updateRestaurant(id, updated);
                if (success) {
                    cout << "Restaurant updated successfully!\n";
                }
                break;
            }

            case 5: {
                int id;
                cout << "Enter restaurant ID to delete: ";
                cin >> id;

                char confirm;
                cout << "Are you sure you want to delete this restaurant? (y/n): ";
                cin >> confirm;

                if (confirm == 'y' || confirm == 'Y') {
                    bool success = restaurantService.deleteRestaurant(id);
                    if (success) {
                        cout << "Restaurant deleted successfully!\n";
                    }
                } else {
                    cout << "Deletion cancelled.\n";
                }
                break;
            }

            case 6: {
                int id, rating;
                cout << "Enter restaurant ID: ";
                cin >> id;

                cout << "Enter rating (1-5): ";
                cin >> rating;

                bool success = restaurantService.rateRestaurant(id, rating);
                if (success) {
                    cout << "Restaurant rated successfully!\n";
                }
                break;
            }

            case 7: {
                int id;
                cout << "Enter restaurant ID: ";
                cin >> id;

                vector<MenuItem> menu = restaurantService.getMenuByRestaurant(id);
                cout << "\n=== RESTAURANT MENU ===\n";
                if (menu.empty()) {
                    cout << "No menu items found for this restaurant.\n";
                } else {
                    for (const MenuItem& item : menu) {
                        cout << "ID: " << item.getId()
                             << " | Name: " << item.getName()
                             << " | Price: $" << item.getPrice()
                             << " | Available: " << (item.getAvailable() ? "Yes" : "No") << "\n";
                    }
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

void Admin::manageMenuItems() {
    int choice;
    bool inMenu = true;

    while (inMenu) {
        displayMenuItemMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                int restaurantId;
                string name, description;
                double price;
                char availableChar;

                cout << "\n=== CREATE NEW MENU ITEM ===\n";

                vector<Restaurant> restaurants = restaurantService.getAllRestaurants();
                if (restaurants.empty()) {
                    cout << "No restaurants available. Please add a restaurant first.\n";
                    break;
                }

                cout << "Available Restaurants:\n";
                for (const Restaurant& rest : restaurants) {
                    cout << "ID: " << rest.getId() << " - " << rest.getName() << "\n";
                }

                cout << "Enter restaurant ID: ";
                cin >> restaurantId;
                cin.ignore();

                Restaurant* restaurant = restaurantService.getRestaurantById(restaurantId);
                if (!restaurant) {
                    cout << "Invalid restaurant ID!\n";
                    break;
                }

                cout << "Enter item name: ";
                getline(cin, name);

                cout << "Enter description: ";
                getline(cin, description);

                cout << "Enter price: ";
                cin >> price;

                cout << "Is available? (y/n): ";
                cin >> availableChar;
                bool available = (availableChar == 'y' || availableChar == 'Y');

                bool success = menuItemService.createMenuItem(name, description, price, available, restaurantId);
                if (success) {
                    cout << "Menu item added successfully!\n";
                }
                break;
            }

            case 2: {
                vector<MenuItem> allItems = menuItemService.getAllMenuItems();
                cout << "\n=== ALL MENU ITEMS ===\n";
                if (allItems.empty()) {
                    cout << "No menu items found.\n";
                } else {
                    for (const MenuItem& item : allItems) {
                        Restaurant* restaurant = restaurantService.getRestaurantById(item.getRestaurantId());
                        string restaurantName = restaurant ? restaurant->getName() : "Unknown";

                        cout << "ID: " << item.getId()
                             << " | Name: " << item.getName()
                             << " | Restaurant: " << restaurantName
                             << " | Price: $" << item.getPrice()
                             << " | Available: " << (item.getAvailable() ? "Yes" : "No") << "\n";
                    }
                }
                break;
            }

            case 3: {
                cout << "\n=== SEARCH MENU ITEMS ===\n";
                cout << "1. Search by Name\n";
                cout << "2. Search by Restaurant\n";
                cout << "Enter option: ";
                int searchOption;
                cin >> searchOption;
                cin.ignore();

                if (searchOption == 1) {
                    string name;
                    cout << "Enter item name to search: ";
                    getline(cin, name);

                    vector<MenuItem> results = menuItemService.searchMenuItemsByName(name);
                    cout << "\n=== SEARCH RESULTS ===\n";
                    for (const MenuItem& item : results) {
                        cout << "ID: " << item.getId()
                             << " | Name: " << item.getName()
                             << " | Price: $" << item.getPrice() << "\n";
                    }
                } else if (searchOption == 2) {
                    int restaurantId;
                    cout << "Enter restaurant ID: ";
                    cin >> restaurantId;

                    vector<MenuItem> results = restaurantService.getMenuByRestaurant(restaurantId);
                    cout << "\n=== RESTAURANT MENU ===\n";
                    for (const MenuItem& item : results) {
                        cout << "ID: " << item.getId()
                             << " | Name: " << item.getName()
                             << " | Price: $" << item.getPrice() << "\n";
                    }
                }
                break;
            }

            case 4: {
                int itemId;
                cout << "Enter menu item ID to update: ";
                cin >> itemId;
                cin.ignore();

                MenuItem* existingItem = menuItemService.getMenuItemById(itemId);
                if (!existingItem) {
                    cout << "Menu item not found!\n";
                    break;
                }

                string name, description;
                double price;
                char availableChar;

                cout << "Current Name: " << existingItem->getName() << "\n";
                cout << "Enter new name: ";
                getline(cin, name);
                if (name.empty()) name = existingItem->getName();

                cout << "Current Description: " << existingItem->getDescription() << "\n";
                cout << "Enter new description: ";
                getline(cin, description);
                if (description.empty()) description = existingItem->getDescription();

                cout << "Current Price: $" << existingItem->getPrice() << "\n";
                cout << "Enter new price: ";
                cin >> price;
                if (price <= 0) price = existingItem->getPrice();

                cout << "Current Available: " << (existingItem->getAvailable() ? "Yes" : "No") << "\n";
                cout << "Is available? (y/n): ";
                cin >> availableChar;
                bool available = (availableChar == 'y' || availableChar == 'Y');

                bool success = menuItemService.updateMenuItem(itemId, name, description, price, available);
                if (success) {
                    cout << "Menu item updated successfully!\n";
                }
                break;
            }

            case 5: {
                int itemId;
                cout << "Enter menu item ID to delete: ";
                cin >> itemId;

                char confirm;
                cout << "Are you sure? (y/n): ";
                cin >> confirm;

                if (confirm == 'y' || confirm == 'Y') {
                    bool success = menuItemService.deleteMenuItem(itemId);
                    if (success) {
                        cout << "Menu item deleted successfully!\n";
                    }
                } else {
                    cout << "Deletion cancelled.\n";
                }
                break;
            }

            case 6: {
                int itemId;
                cout << "Enter menu item ID: ";
                cin >> itemId;

                bool success = menuItemService.toggleMenuItemAvailability(itemId);
                if (success) {
                    cout << "Availability toggled successfully!\n";
                }
                break;
            }

            case 7: {
                cout << "\n=== MENU STATISTICS ===\n";
                int totalItems = menuItemService.getAllMenuItems().size();
                cout << "Total Menu Items: " << totalItems << "\n";

                vector<Restaurant> restaurants = restaurantService.getAllRestaurants();
                for (const Restaurant& rest : restaurants) {
                    int count = menuItemService.countMenuItemsByRestaurant(rest.getId());
                    if (count > 0) {
                        double avgPrice = menuItemService.getAveragePriceByRestaurant(rest.getId());
                        cout << "\nRestaurant: " << rest.getName() << "\n";
                        cout << "  Items: " << count << "\n";
                        cout << "  Average Price: $" << avgPrice << "\n";
                    }
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

void Admin::manageUsers() {
    int choice;
    bool inMenu = true;

    while (inMenu) {
        displayUserMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                vector<User> users = userService.getAllUsers();
                cout << "\n=== ALL USERS ===\n";
                for (const User& user : users) {
                    cout << "ID: " << user.getId()
                         << " | Username: " << user.getUsername()
                         << " | Role: " << user.getRole()
                         << " | Status: " << user.getStatus() << "\n";
                }
                break;
            }

            case 2: {
                string userId, status;
                cout << "Enter user ID: ";
                cin >> userId;
                cout << "Enter new status (Active/Inactive): ";
                cin >> status;

                bool success = userService.updateUserStatus(userId, status);
                if (success) {
                    cout << "User status updated successfully!\n";
                }
                break;
            }

            case 3: {
                string userId;
                cout << "Enter user ID to delete: ";
                cin >> userId;

                char confirm;
                cout << "Are you sure? (y/n): ";
                cin >> confirm;

                if (confirm == 'y' || confirm == 'Y') {
                    bool success = userService.deleteUser(userId);
                    if (success) {
                        cout << "User deleted successfully!\n";
                    }
                } else {
                    cout << "Deletion cancelled.\n";
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

void Admin::displayRestaurantMenu() {
    cout << "\n=== RESTAURANT MANAGEMENT ===\n";
    cout << "1. View All Restaurants\n";
    cout << "2. Search Restaurant by ID\n";
    cout << "3. Add Restaurant\n";
    cout << "4. Update Restaurant\n";
    cout << "5. Delete Restaurant\n";
    cout << "6. Rate Restaurant\n";
    cout << "7. View Restaurant Menu\n";
    cout << "0. Back to Admin Menu\n";
    cout << "Enter your choice: ";
}

void Admin::displayMenuItemMenu() {
    cout << "\n=== MENU ITEM MANAGEMENT ===\n";
    cout << "1. Create Menu Item\n";
    cout << "2. View All Menu Items\n";
    cout << "3. Search Menu Items\n";
    cout << "4. Update Menu Item\n";
    cout << "5. Delete Menu Item\n";
    cout << "6. Toggle Availability\n";
    cout << "7. Get Statistics\n";
    cout << "0. Back to Admin Menu\n";
    cout << "Enter your choice: ";
}

void Admin::displayUserMenu() {
    cout << "\n=== USER MANAGEMENT ===\n";
    cout << "1. View All Users\n";
    cout << "2. Update User Status\n";
    cout << "3. Delete User\n";
    cout << "0. Back to Admin Menu\n";
    cout << "Enter your choice: ";
}

void Admin::displayAdminDashboard() {
    cout << "\n=== ADMIN DASHBOARD ===\n";

    
    vector<User> users = userService.getAllUsers();
    cout << "Total Users: " << users.size() << "\n";

    int adminCount = 0, staffCount = 0, customerCount = 0;
    for (const User& user : users) {
        if (user.getRole() == "ADMIN") adminCount++;
        else if (user.getRole() == "STAFF") staffCount++;
        else if (user.getRole() == "CUSTOMER") customerCount++;
    }

    cout << "Admins: " << adminCount << "\n";
    cout << "Staff: " << staffCount << "\n";
    cout << "Customers: " << customerCount << "\n\n";


    vector<Restaurant> restaurants = restaurantService.getAllRestaurants();
    cout << "Total Restaurants: " << restaurants.size() << "\n";

    if (!restaurants.empty()) {
        cout << "\n=== RESTAURANTS ===\n";
        for (const Restaurant& rest : restaurants) {
            vector<MenuItem> menu = restaurantService.getMenuByRestaurant(rest.getId());
            cout << rest.getName() << " - " << menu.size() << " menu items\n";
        }
    }


    vector<MenuItem> allItems = menuItemService.getAllMenuItems();
    cout << "\nTotal Menu Items: " << allItems.size() << "\n";
    
    if (!allItems.empty()) {
        int availableCount = 0;
        double totalValue = 0.0;
        
        for (const MenuItem& item : allItems) {
            if (item.getAvailable()) {
                availableCount++;
            }
            totalValue += item.getPrice();
        }
        
        double averagePrice = allItems.size() > 0 ? totalValue / allItems.size() : 0.0;
        
        cout << "Available Items: " << availableCount << "\n";
        cout << "Average Price: $" << averagePrice << "\n";
    }
    
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}