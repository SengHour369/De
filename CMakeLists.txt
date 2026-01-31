cmake_minimum_required(VERSION 4.0)
project(Restaurant_project)

set(CMAKE_CXX_STANDARD 20)

add_executable(Restaurant_project main.cpp
        User.cpp
        User.h
        Order.cpp
        Order.h
        Restaurant.cpp
        Restaurant.h
        OrderItem.cpp
        OrderItem.h
        MenuItem.cpp
        MenuItem.h
        Payment.cpp
        Payment.h
        UserService.cpp
        UserService.h
        RestaurantService.cpp
        RestaurantService.h
        OrderService.cpp
        OrderService.h
        OrderItemService.cpp
        OrderItemService.h
        Admin.cpp
        Admin.h
        MenuItemService.cpp
        MenuItemService.h
        FileStorage.cpp
        FileStorage.h
)
