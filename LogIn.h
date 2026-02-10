#ifndef RESTAURANT_PROJECT_LOGIN_H
#define RESTAURANT_PROJECT_LOGIN_H


class UserService;
class Admin;
class RestaurantService;
class OrderService;

class LogIn {
public:
    LogIn(UserService& userService, Admin& admin, RestaurantService& restaurantService, OrderService& orderService);
};

#endif //RESTAURANT_PROJECT_LOGIN_H