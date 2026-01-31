// RestaurantService.h
#ifndef RESTAURANT_PROJECT_RESTAURANTSERVICE_H
#define RESTAURANT_PROJECT_RESTAURANTSERVICE_H

#include <vector>
#include <string>
#include "Restaurant.h"
#include "MenuItem.h"
#include "FileStorage.h"
using namespace std;

class MenuItemService;

class RestaurantService {
private:
    vector<Restaurant> restaurants;
    MenuItemService* menuItemService;
    FileStorage fileStorage;

public:
    RestaurantService();
    RestaurantService(const string& filename);
    ~RestaurantService();


    bool addRestaurant(const string& name, const string& category,
                      const string& phone_number, const string& location);
    bool updateRestaurant(int id, const Restaurant& updatedRestaurant);
    bool deleteRestaurant(int id);
    bool rateRestaurant(int id, int rating);


    Restaurant* getRestaurantById(int id);
    Restaurant* getRestaurantByName(const string& name);
    vector<Restaurant> getAllRestaurants() const;
    vector<MenuItem> getMenuByRestaurant(int restaurantId) const;


    void setMenuItemService(MenuItemService* service);
    bool addMenuItem(int restaurantId, const string& name,
                    const string& description, double price);
    MenuItem* getMenuItemById(int id);
    vector<MenuItem> getAllMenuItems() const;

    // File storage methods
    bool saveToFile();
    bool loadFromFile();
    void setDataFilename(const string& filename);

private:
    int generateRestaurantId();
};

#endif // RESTAURANT_PROJECT_RESTAURANTSERVICE_H