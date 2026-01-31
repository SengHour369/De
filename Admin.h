#ifndef RESTAURANT_PROJECT_ADMIN_H
#define RESTAURANT_PROJECT_ADMIN_H

#include "RestaurantService.h"
#include "MenuItemService.h"
#include "UserService.h"
#include <vector>

class Admin {
private:
    RestaurantService& restaurantService;
    MenuItemService& menuItemService;
    UserService& userService;

public:
    Admin(RestaurantService& restaurantService,
          MenuItemService& menuItemService,
          UserService& userService);

    void runAdminMenu();
    void manageRestaurants();
    void manageMenuItems();
    void manageUsers();
    void displayAdminDashboard();

private:
    void displayRestaurantMenu();
    void displayMenuItemMenu();
    void displayUserMenu();
    void displayAdminMainMenu();
};

#endif // RESTAURANT_PROJECT_ADMIN_H