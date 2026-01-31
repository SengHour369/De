// RestaurantService.cpp
#include "RestaurantService.h"
#include "MenuItemService.h"
#include <algorithm>
#include <iostream>
using namespace std;

RestaurantService::RestaurantService() : menuItemService(nullptr), fileStorage("restaurants.dat") {
    loadFromFile();

    if (restaurants.empty()) {
        addRestaurant("Pizza Palace", "Italian", "555-1001", "123 Main St");
        addRestaurant("Burger King", "Fast Food", "555-1002", "456 Oak Ave");
        addRestaurant("Sushi Zen", "Japanese", "555-1003", "789 Pine Rd");
        saveToFile();
    }
}

RestaurantService::RestaurantService(const string& filename) : menuItemService(nullptr), fileStorage(filename) {
    loadFromFile();

    if (restaurants.empty()) {
        addRestaurant("Pizza Palace", "Italian", "555-1001", "123 Main St");
        addRestaurant("Burger King", "Fast Food", "555-1002", "456 Oak Ave");
        addRestaurant("Sushi Zen", "Japanese", "555-1003", "789 Pine Rd");
        saveToFile();
    }
}

RestaurantService::~RestaurantService() {
    // Cleanup if needed
}

void RestaurantService::setMenuItemService(MenuItemService* service) {
    menuItemService = service;
}

bool RestaurantService::addRestaurant(const string& name, const string& category,
                                     const string& phone_number, const string& location) {

    for (const Restaurant& restaurant : restaurants) {
        if (restaurant.getName() == name) {
            cout << "Restaurant with this name already exists!\n";
            return false;
        }
    }

    Restaurant newRestaurant(generateRestaurantId(), name, category, 0, phone_number, location);
    restaurants.push_back(newRestaurant);

    saveToFile();

    cout << "Restaurant added successfully! ID: " << newRestaurant.getId() << "\n";
    return true;
}

bool RestaurantService::updateRestaurant(int id, const Restaurant& updatedRestaurant) {
    Restaurant* restaurant = getRestaurantById(id);
    if (restaurant) {
        restaurant->setName(updatedRestaurant.getName());
        restaurant->setCategory(updatedRestaurant.getCategory());
        restaurant->setPhoneNumber(updatedRestaurant.getPhoneNumber());
        restaurant->setLocation(updatedRestaurant.getLocation());

        saveToFile();

        cout << "Restaurant updated successfully!\n";
        return true;
    }
    cout << "Restaurant not found!\n";
    return false;
}

bool RestaurantService::deleteRestaurant(int id) {
    auto it = remove_if(restaurants.begin(), restaurants.end(),
        [id](const Restaurant& restaurant) { return restaurant.getId() == id; });

    if (it != restaurants.end()) {
        restaurants.erase(it, restaurants.end());

        saveToFile();

        cout << "Restaurant deleted successfully!\n";
        return true;
    }

    cout << "Restaurant not found!\n";
    return false;
}

bool RestaurantService::rateRestaurant(int id, int rating) {
    Restaurant* restaurant = getRestaurantById(id);
    if (restaurant) {
        if (rating >= 1 && rating <= 5) {
            restaurant->setRating(rating);

            saveToFile();

            cout << "Restaurant rated successfully!\n";
            return true;
        } else {
            cout << "Rating must be between 1 and 5!\n";
            return false;
        }
    }
    cout << "Restaurant not found!\n";
    return false;
}

Restaurant* RestaurantService::getRestaurantById(int id) {
    for (Restaurant& restaurant : restaurants) {
        if (restaurant.getId() == id) {
            return &restaurant;
        }
    }
    return nullptr;
}

Restaurant* RestaurantService::getRestaurantByName(const string& name) {
    for (Restaurant& restaurant : restaurants) {
        if (restaurant.getName() == name) {
            return &restaurant;
        }
    }
    return nullptr;
}

vector<Restaurant> RestaurantService::getAllRestaurants() const {
    return restaurants;
}

vector<MenuItem> RestaurantService::getMenuByRestaurant(int restaurantId) const {
    if (menuItemService) {
        return menuItemService->getMenuItemsByRestaurant(restaurantId);
    }
    return vector<MenuItem>();
}

bool RestaurantService::addMenuItem(int restaurantId, const string& name,
                                  const string& description, double price) {
    Restaurant* restaurant = getRestaurantById(restaurantId);
    if (!restaurant) {
        cout << "Restaurant not found!\n";
        return false;
    }

    if (menuItemService) {
        bool result = menuItemService->createMenuItem(name, description, price, true, restaurantId);
        if (result) {
            saveToFile(); // Save after adding menu item
        }
        return result;
    }
    return false;
}

MenuItem* RestaurantService::getMenuItemById(int id) {
    if (menuItemService) {
        return menuItemService->getMenuItemById(id);
    }
    return nullptr;
}

vector<MenuItem> RestaurantService::getAllMenuItems() const {
    if (menuItemService) {
        return menuItemService->getAllMenuItems();
    }
    return vector<MenuItem>();
}

int RestaurantService::generateRestaurantId() {
    static int counter = 100;
    return counter++;
}

bool RestaurantService::saveToFile() {
    return fileStorage.saveRestaurants(restaurants);
}

bool RestaurantService::loadFromFile() {
    return fileStorage.loadRestaurants(restaurants);
}

void RestaurantService::setDataFilename(const string& filename) {
    fileStorage.setFilename(filename);
}