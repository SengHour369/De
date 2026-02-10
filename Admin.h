#ifndef RESTAURANT_PROJECT_ADMIN_H
#define RESTAURANT_PROJECT_ADMIN_H

#include <vector>
#include <string>

class RestaurantService;
class MenuItemService;
class UserService;
class Restaurant;
class MenuItem;
class User;

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
    void displayAdminMainMenu();
    void displayRestaurantMenu();
    void displayMenuItemMenu();
    void displayUserMenu();
};

#endif // RESTAURANT_PROJECT_ADMIN_H