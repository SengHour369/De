//
// Created by seng hour on 1/31/2026.
//

#ifndef RESTAURANT_PROJECT_APPUSER_H
#define RESTAURANT_PROJECT_APPUSER_H
#include "OrderService.h"
#include "RestaurantService.h"
#include "UserService.h"


class AppUser {
public : AppUser( UserService userService,RestaurantService restaurantService,OrderService& orderService);
};


#endif //RESTAURANT_PROJECT_APPUSER_H