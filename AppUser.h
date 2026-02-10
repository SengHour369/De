#ifndef RESTAURANT_PROJECT_APPUSER_H
#define RESTAURANT_PROJECT_APPUSER_H

class UserService;
class RestaurantService;
class OrderService;

class AppUser {
public:
    AppUser(UserService& userService, RestaurantService& restaurantService, OrderService& orderService);
};

#endif //RESTAURANT_PROJECT_APPUSER_H