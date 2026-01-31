//
// Created by seng hour on 1/31/2026.
//

#include "AppUser.h"

#include <iostream>
#include <string>

#include "Order.h"
#include "OrderService.h"

using namespace std;
void displayUserMenu() {
    cout << "1. View Profile\n";
    cout << "2. Update Profile\n";
    cout << "3. Change Password\n";
    cout << "4. Logout\n";
    cout << "5. Back to Main Menu\n";
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
void displayProfile() {
    cout << "1. View Profile\n";
    cout << "2. View Restaurants\n";
    cout << "3. Order Management\n";
    cout << "Enter your choice: ";
}
//
// void displayOrderMenu() {
//     cout << "\n=== ORDER MANAGEMENT ===\n";
//     cout << "1. Create New Order\n";
//     cout << "2. View My Orders\n";
//     cout << "3. Cancel Order\n";
//     cout << "4. View Order Details\n";
//     cout << "5. Process Payment\n";
//     cout << "6. Back to Main Menu\n";
//     cout << "Enter your choice: ";
// }
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

void handleOrderManagement(UserService& userService, RestaurantService& restaurantService,
                          OrderService& orderService) {
    int orderChoice;
    bool inOrderMenu = true;

    while (inOrderMenu) {
        displayOrderMenu();
        cin >> orderChoice;
        cin.ignore();

        switch (orderChoice) {
            case 1: {
                // Create order logic
                User* currentUser = userService.getCurrentUser();
                if (!currentUser) {
                    cout << "Please login first!\n";
                    break;
                }

                // Show available restaurants
                vector<Restaurant> restaurants = restaurantService.getAllRestaurants();
                if (restaurants.empty()) {
                    cout << "No restaurants available!\n";
                    break;
                }

                cout << "\n=== AVAILABLE RESTAURANTS ===\n";
                for (const Restaurant& rest : restaurants) {
                    cout << "ID: " << rest.getId()
                         << " | Name: " << rest.getName()
                         << " | Location: " << rest.getLocation() << "\n";
                }

                int restaurantId;
                cout << "Enter restaurant ID: ";
                cin >> restaurantId;
                cin.ignore();

                Restaurant* restaurant = restaurantService.getRestaurantById(restaurantId);
                if (!restaurant) {
                    cout << "Restaurant not found!\n";
                    break;
                }

                // Show menu items
                vector<MenuItem> menu = restaurantService.getMenuByRestaurant(restaurantId);
                if (menu.empty()) {
                    cout << "No menu items available!\n";
                    break;
                }

                cout << "\n=== MENU ITEMS ===\n";
                for (const MenuItem& item : menu) {
                    if (item.getAvailable()) {
                        cout << "ID: " << item.getId()
                             << " | " << item.getName()
                             << " - $" << item.getPrice() << "\n";
                        cout << "   " << item.getDescription() << "\n";
                    }
                }

                vector<MenuItem> selectedItems;
                int itemId;
                char moreItems = 'y';

                while (moreItems == 'y' || moreItems == 'Y') {
                    cout << "Enter menu item ID: ";
                    cin >> itemId;
                    cin.ignore();

                    // Find and add the menu item
                    for (const MenuItem& item : menu) {
                        if (item.getId() == itemId && item.getAvailable()) {
                            selectedItems.push_back(item);
                            cout << "Added: " << item.getName() << "\n";
                            break;
                        }
                    }

                    cout << "Add more items? (y/n): ";
                    cin >> moreItems;
                    cin.ignore();
                }

                if (selectedItems.empty()) {
                    cout << "No items selected!\n";
                    break;
                }

                string paymentType;
                cout << "Enter payment type (Cash/Card): ";
                getline(cin, paymentType);

                Order* newOrder = orderService.createOrder(currentUser, restaurant,
                                                          selectedItems, paymentType);
                if (newOrder) {
                    cout << "Order created successfully! ID: " << newOrder->getId() << "\n";
                }
                break;
            }

            case 2: {
                User* currentUser = userService.getCurrentUser();
                if (!currentUser) {
                    cout << "Please login first!\n";
                    break;
                }

                vector<Order*> userOrders = orderService.getOrdersByUser(currentUser->getId());
                cout << "\n=== MY ORDERS ===\n";
                if (userOrders.empty()) {
                    cout << "No orders found!\n";
                } else {
                    for (Order* order : userOrders) {
                        cout << "Order ID: " << order->getId()
                             << " | Total: $" << order->getTotalPrice()
                             << " | Status: " << order->getStatus() << "\n";
                        cout << "Restaurant: " << order->getRestaurant()->getName() << "\n";
                        cout << "--------------------------------\n";
                    }
                }
                break;
            }

            case 3: {
                int orderId;
                cout << "Enter order ID to cancel: ";
                cin >> orderId;
                cin.ignore();

                if (orderService.cancelOrder(orderId)) {
                    cout << "Order cancelled successfully!\n";
                } else {
                    cout << "Failed to cancel order!\n";
                }
                break;
            }

            case 4: {
                int orderId;
                cout << "Enter order ID: ";
                cin >> orderId;
                cin.ignore();

                Order* order = orderService.getOrderById(orderId);
                if (order) {
                    cout << "\n=== ORDER DETAILS ===\n";
                    cout << order->getOrderSummary();
                } else {
                    cout << "Order not found!\n";
                }
                break;
            }

            case 5: {
                int orderId;
                cout << "Enter order ID to process payment: ";
                cin >> orderId;
                cin.ignore();

                Order* order = orderService.getOrderById(orderId);
                if (order && order->getPayment()) {
                    if (orderService.processPayment(order->getPayment()->getId())) {
                        cout << "Payment processed successfully!\n";
                    }
                } else {
                    cout << "Order or payment not found!\n";
                }
                break;
            }

            case 6:
                inOrderMenu = false;
                break;

            default:
                cout << "Invalid choice!\n";
        }
    }
}

AppUser::AppUser( UserService userService,RestaurantService restaurantService,OrderService& orderService) {
    int userChoice;
    bool inUserMenu = true;
    int n;
    do {
        displayProfile();
        cin>> n;
        switch (n) {
            case 1: {
                while (inUserMenu) {
                    displayUserMenu();
                    cin >> userChoice;
                    cin.ignore();

                    switch (userChoice) {

                        case 1: {
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

                        case 2: {
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

                        case 3: {
                            string oldPassword, newPassword;
                            cout << "Enter current password: ";
                            getline(cin, oldPassword);
                            cout << "Enter new password: ";
                            getline(cin, newPassword);

                            userService.changePassword(oldPassword, newPassword);
                            break;
                        }

                        case 4:
                            userService.logout();
                            break;

                        case 5:
                            inUserMenu = false;
                            break;

                        default:
                            cout << "Invalid choice!\n";
                    }
                }
                break;
            }
            case 2: {
                //==============================================================================
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
                handleOrderManagement( userService,  restaurantService,
                          orderService);
                break;
            }
        }
    }while (n != 4);
}




