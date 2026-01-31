// Main.cpp
#include <iostream>
#include "UserService.h"
#include "RestaurantService.h"
#include "MenuItemService.h"
#include "OrderService.h"
#include "Admin.h"
using namespace std;

void displayMainMenu() {
    cout << "\n=== RESTAURANT ORDERING SYSTEM ===\n";
    cout << "1. User Management\n";
    cout << "2. Restaurant Management\n";
    cout << "3. Order Management\n";
    cout << "4. Admin Menu\n";
    cout << "5. Save All Data\n";
    cout << "6. Load All Data\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

void displayUserMenu() {
    cout << "\n=== USER MANAGEMENT ===\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. View Profile\n";
    cout << "4. Update Profile\n";
    cout << "5. Change Password\n";
    cout << "6. Logout\n";
    cout << "7. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

void displayRestaurantMenu() {
    cout << "\n=== RESTAURANT MANAGEMENT ===\n";
    cout << "1. View All Restaurants\n";
    cout << "2. View Restaurant Details\n";
    cout << "3. View Restaurant Menu\n";
    cout << "4. Rate Restaurant\n";
    cout << "5. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

void displayOrderMenu() {
    cout << "\n=== ORDER MANAGEMENT ===\n";
    cout << "1. Create New Order\n";
    cout << "2. View My Orders\n";
    cout << "3. Cancel Order\n";
    cout << "4. View Order Details\n";
    cout << "5. Process Payment\n";
    cout << "6. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

// Function to save all data
void saveAllData(UserService& userService, RestaurantService& restaurantService,
                 MenuItemService& menuItemService, OrderService& orderService) {
    cout << "\n=== SAVING ALL DATA ===\n";
    if (userService.saveToFile()) {
        cout << "✓ Users saved successfully!\n";
    } else {
        cout << "✗ Failed to save users!\n";
    }

    if (restaurantService.saveToFile()) {
        cout << "✓ Restaurants saved successfully!\n";
    } else {
        cout << "✗ Failed to save restaurants!\n";
    }

    if (menuItemService.saveToFile()) {
        cout << "✓ Menu items saved successfully!\n";
    } else {
        cout << "✗ Failed to save menu items!\n";
    }
    cout << "Data save completed!\n";
}

// Function to load all data
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
        cout << " Failed to load restaurants!\n";
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
    // OrderService doesn't have file storage yet
    OrderService orderService;

    restaurantService.setMenuItemService(&menuItemService);

    // Initialize admin
    Admin admin(restaurantService, menuItemService, userService);

    int mainChoice;
    bool running = true;

    cout << "\n========================================\n";
    cout << "   RESTAURANT ORDERING SYSTEM v2.0\n";
    cout << "   with Binary File Storage\n";
    cout << "========================================\n";

    while (running) {
        displayMainMenu();
        cin >> mainChoice;
        cin.ignore();

        switch (mainChoice) {
            case 1: {
                int userChoice;
                bool inUserMenu = true;

                while (inUserMenu) {
                    displayUserMenu();
                    cin >> userChoice;
                    cin.ignore();

                    switch (userChoice) {
                        case 1: {
                            string username, password, gender, dob, email, phone, address, role;
                            cout << "Enter username: ";
                            getline(cin, username);
                            cout << "Enter password: ";
                            getline(cin, password);
                            cout << "Enter gender: ";
                            getline(cin, gender);
                            cout << "Enter date of birth (YYYY-MM-DD): ";
                            getline(cin, dob);
                            cout << "Enter email: ";
                            getline(cin, email);
                            cout << "Enter phone number: ";
                            getline(cin, phone);
                            cout << "Enter address: ";
                            getline(cin, address);
                            cout << "Enter role (ADMIN/STAFF/CUSTOMER): ";
                            getline(cin, role);

                            userService.registerUser(username, password, gender, dob,
                                                   email, phone, address, role);
                            break;
                        }

                        case 2: {
                            string username, password;
                            cout << "Enter username: ";
                            getline(cin, username);
                            cout << "Enter password: ";
                            getline(cin, password);

                            userService.login(username, password);
                            break;
                        }

                        case 3: {
                            User* currentUser = userService.getCurrentUser();
                            if (currentUser) {
                                cout << "\n=== PROFILE ===\n";
                                cout << "Username: " << currentUser->getUsername() << "\n";
                                cout << "Email: " << currentUser->getEmail() << "\n";
                                cout << "Phone: " << currentUser->getPhoneNumber() << "\n";
                                cout << "Address: " << currentUser->getAddress() << "\n";
                                cout << "Role: " << currentUser->getRole() << "\n";
                                cout << "Status: " << currentUser->getStatus() << "\n";
                            } else {
                                cout << "Please login first!\n";
                            }
                            break;
                        }

                        case 4: {
                            User* currentUser = userService.getCurrentUser();
                            if (!currentUser) {
                                cout << "Please login first!\n";
                                break;
                            }

                            string email, phone, address, gender, dob;
                            cout << "Current Email: " << currentUser->getEmail() << "\n";
                            cout << "Enter new email: ";
                            getline(cin, email);

                            cout << "Current Phone: " << currentUser->getPhoneNumber() << "\n";
                            cout << "Enter new phone: ";
                            getline(cin, phone);

                            cout << "Current Address: " << currentUser->getAddress() << "\n";
                            cout << "Enter new address: ";
                            getline(cin, address);

                            cout << "Current Gender: " << currentUser->getGender() << "\n";
                            cout << "Enter new gender: ";
                            getline(cin, gender);

                            cout << "Current DOB: " << currentUser->getDateOfBirth() << "\n";
                            cout << "Enter new date of birth: ";
                            getline(cin, dob);

                            User updatedUser = *currentUser;
                            updatedUser.setEmail(email);
                            updatedUser.setPhoneNumber(phone);
                            updatedUser.setAddress(address);
                            updatedUser.setGender(gender);
                            updatedUser.setDateOfBirth(dob);

                            userService.updateProfile(updatedUser);
                            break;
                        }

                        case 5: {
                            string oldPassword, newPassword;
                            cout << "Enter current password: ";
                            getline(cin, oldPassword);
                            cout << "Enter new password: ";
                            getline(cin, newPassword);

                            userService.changePassword(oldPassword, newPassword);
                            break;
                        }

                        case 6:
                            userService.logout();
                            break;

                        case 7:
                            inUserMenu = false;
                            break;

                        default:
                            cout << "Invalid choice!\n";
                    }
                }
                break;
            }

            case 2: {
                int restChoice;
                bool inRestMenu = true;

                while (inRestMenu) {
                    displayRestaurantMenu();
                    cin >> restChoice;
                    cin.ignore();

                    switch (restChoice) {
                        case 1: {
                            vector<Restaurant> restaurants = restaurantService.getAllRestaurants();
                            cout << "\n=== ALL RESTAURANTS ===\n";
                            for (const Restaurant& rest : restaurants) {
                                cout << "ID: " << rest.getId()
                                     << " | Name: " << rest.getName()
                                     << " | Category: " << rest.getCategory()
                                     << " | Rating: " << rest.getRating() << "/5"
                                     << " | Location: " << rest.getLocation() << "\n";
                            }
                            break;
                        }

                        case 2: {
                            int id;
                            cout << "Enter restaurant ID: ";
                            cin >> id;
                            cin.ignore();

                            Restaurant* restaurant = restaurantService.getRestaurantById(id);
                            if (restaurant) {
                                cout << "\n=== RESTAURANT DETAILS ===\n";
                                cout << "ID: " << restaurant->getId() << "\n";
                                cout << "Name: " << restaurant->getName() << "\n";
                                cout << "Category: " << restaurant->getCategory() << "\n";
                                cout << "Rating: " << restaurant->getRating() << "/5\n";
                                cout << "Phone: " << restaurant->getPhoneNumber() << "\n";
                                cout << "Location: " << restaurant->getLocation() << "\n";
                            } else {
                                cout << "Restaurant not found!\n";
                            }
                            break;
                        }

                        case 3: {
                            int id;
                            cout << "Enter restaurant ID: ";
                            cin >> id;
                            cin.ignore();

                            vector<MenuItem> menu = restaurantService.getMenuByRestaurant(id);
                            cout << "\n=== RESTAURANT MENU ===\n";
                            for (const MenuItem& item : menu) {
                                cout << "ID: " << item.getId()
                                     << " | Name: " << item.getName()
                                     << " | Price: $" << item.getPrice()
                                     << " | Available: " << (item.getAvailable() ? "Yes" : "No") << "\n";
                                cout << "   Description: " << item.getDescription() << "\n";
                            }
                            break;
                        }

                        case 4: {
                            int id, rating;
                            cout << "Enter restaurant ID: ";
                            cin >> id;
                            cout << "Enter rating (1-5): ";
                            cin >> rating;
                            cin.ignore();

                            restaurantService.rateRestaurant(id, rating);
                            break;
                        }

                        case 5:
                            inRestMenu = false;
                            break;

                        default:
                            cout << "Invalid choice!\n";
                    }
                }
                break;
            }

            case 3: {
                // Order Management (unchanged from original)
                cout << "\nNote: Order management requires additional modifications\n";
                cout << "for file storage. Currently using in-memory storage only.\n";

                int orderChoice;
                bool inOrderMenu = true;

                while (inOrderMenu) {
                    displayOrderMenu();
                    cin >> orderChoice;
                    cin.ignore();

                    switch (orderChoice) {
                        case 1:
                            cout << "Order creation requires additional modifications.\n";
                            break;

                        case 2:
                            cout << "View orders requires additional modifications.\n";
                            break;

                        case 3:
                            cout << "Order cancellation requires additional modifications.\n";
                            break;

                        case 4:
                            cout << "View order details requires additional modifications.\n";
                            break;

                        case 5:
                            cout << "Process payment requires additional modifications.\n";
                            break;

                        case 6:
                            inOrderMenu = false;
                            break;

                        default:
                            cout << "Invalid choice!\n";
                    }
                }
                break;
            }

            case 4: {
                User* currentUser = userService.getCurrentUser();
                if (!currentUser || currentUser->getRole() != "ADMIN") {
                    cout << "Access denied! Admin privileges required.\n";
                    break;
                }
                admin.runAdminMenu();
                break;
            }

            case 5:
                saveAllData(userService, restaurantService, menuItemService, orderService);
                break;

            case 6:
                loadAllData(userService, restaurantService, menuItemService, orderService);
                break;

            case 7:
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