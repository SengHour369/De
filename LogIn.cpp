//
// Created by seng hour on 1/31/2026.
//

#include "LogIn.h"

#include "AppUser.h"

LogIn::LogIn(UserService userService, Admin admin,RestaurantService restaurantService) {
    int n;

    do{
        cout << "\n=== USER MANAGEMENT ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "Enter your choice: ";
        cin>>n;
        switch (n) {
            case 1: {
                string username, password, gender, dob, email, phone, address, role;
                cout << "Enter username: ";
                cin>>username;
                cout << "Enter password: ";
                cin>> password;
                cout << "Enter gender: ";
                cin>>gender;
                cout << "Enter date of birth (YYYY-MM-DD): ";
                cin>>dob;
                cout << "Enter email: ";
                cin>>email;
                cout << "Enter phone number: ";
                cin>>phone;
                cout << "Enter address: ";
                cin>>address;
                cout << "Enter role (ADMIN/STAFF/CUSTOMER): ";
                cin>> role;

                userService.registerUser(username, password, gender, dob,
                                       email, phone, address, role);
                break;
            }

            case 2: {

                string username, password;
                cout << "Enter username: ";
                cin>> username;
                cout << "Enter password: ";
                cin>> password;

                if (  userService.login(username, password).getRole() == "ADMIN") {
                    admin.runAdminMenu();
                }
                else {
                    new AppUser(userService,restaurantService);
                }

                break;
            }
        }
    }while(n!=3);
}
