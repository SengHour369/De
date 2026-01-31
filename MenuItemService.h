// MenuItemService.h
#ifndef RESTAURANT_PROJECT_MENUITEMSERVICE_H
#define RESTAURANT_PROJECT_MENUITEMSERVICE_H

#include <vector>
#include <string>
#include "MenuItem.h"
#include "FileStorage.h"

class MenuItemService {
private:
    std::vector<MenuItem> menuItems;
    FileStorage fileStorage;

public:
    MenuItemService();
    MenuItemService(const std::string& filename);


    bool createMenuItem(const std::string& name, const std::string& description,
                       double price, bool available, int restaurantId);

    MenuItem* getMenuItemById(int id);
    std::vector<MenuItem> getAllMenuItems() const;
    std::vector<MenuItem> getMenuItemsByRestaurant(int restaurantId) const;

    bool updateMenuItem(int id, const std::string& name, const std::string& description,
                       double price, bool available);

    bool deleteMenuItem(int id);


    std::vector<MenuItem> searchMenuItemsByName(const std::string& name) const;


    bool updateMenuItemPrice(int id, double newPrice);
    bool toggleMenuItemAvailability(int id);
    bool updateMenuItemDescription(int id, const std::string& newDescription);


    bool isValidMenuItem(const MenuItem& item) const;
    bool isMenuItemNameUnique(const std::string& name, int restaurantId) const;


    int countMenuItemsByRestaurant(int restaurantId) const;
    double getAveragePriceByRestaurant(int restaurantId) const;


    bool saveToFile();
    bool loadFromFile();
    void setDataFilename(const std::string& filename);

private:
    int generateMenuItemId();
};

#endif // RESTAURANT_PROJECT_MENUITEMSERVICE_H