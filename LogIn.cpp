#include "LogIn.h"
#include "UserService.h"
#include "Admin.h"
#include "RestaurantService.h"
#include "OrderService.h"
#include "AppUser.h"
#include "User.h"
#include <iostream>
#include <string>
using namespace std;

LogIn::LogIn(UserService& userService, Admin& admin, RestaurantService& restaurantService, OrderService& orderService) {
    int n;

    do {
        cout << "\n=== USER MANAGEMENT ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> n;
        cin.ignore();
        
        switch (n) {
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

                User loggedInUser = userService.login(username, password);
                if (!loggedInUser.getRole().empty()) {
                    if (loggedInUser.getRole() == "ADMIN") {
                        admin.runAdminMenu();
                    } else {
                        AppUser appUser(userService, restaurantService, orderService);
                    }
                }
                break;
            }
            case 3:
                return;
            default:
                cout << "Invalid choice!\n";
        }
    } while (n != 3);
}