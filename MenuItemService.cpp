// MenuItemService.cpp
#include "MenuItemService.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cctype>
using namespace std;

MenuItemService::MenuItemService() : fileStorage("menuitems.dat") {
    loadFromFile();

    if (menuItems.empty()) {
        createMenuItem("Margherita Pizza", "Classic cheese and tomato pizza", 12.99, true, 100);
        createMenuItem("Pepperoni Pizza", "Pizza with pepperoni and cheese", 14.99, true, 100);
        createMenuItem("Cheeseburger", "Classic cheeseburger with fries", 9.99, true, 101);
        createMenuItem("Chicken Burger", "Grilled chicken burger with salad", 10.99, true, 101);
        createMenuItem("California Roll", "Crab, avocado, cucumber", 8.99, true, 102);
        createMenuItem("Salmon Nigiri", "Fresh salmon over rice", 6.99, true, 102);
        saveToFile();
    }
}

MenuItemService::MenuItemService(const std::string& filename) : fileStorage(filename) {
    loadFromFile();

    if (menuItems.empty()) {
        createMenuItem("Margherita Pizza", "Classic cheese and tomato pizza", 12.99, true, 100);
        createMenuItem("Pepperoni Pizza", "Pizza with pepperoni and cheese", 14.99, true, 100);
        createMenuItem("Cheeseburger", "Classic cheeseburger with fries", 9.99, true, 101);
        createMenuItem("Chicken Burger", "Grilled chicken burger with salad", 10.99, true, 101);
        createMenuItem("California Roll", "Crab, avocado, cucumber", 8.99, true, 102);
        createMenuItem("Salmon Nigiri", "Fresh salmon over rice", 6.99, true, 102);
        saveToFile();
    }
}

bool MenuItemService::createMenuItem(const string& name, const string& description,
                                   double price, bool available, int restaurantId) {
    if (name.empty()) {
        cout << "Error: Menu item name cannot be empty!\n";
        return false;
    }

    if (price <= 0) {
        cout << "Error: Price must be greater than 0!\n";
        return false;
    }

    if (!isMenuItemNameUnique(name, restaurantId)) {
        cout << "Error: Menu item with this name already exists in this restaurant!\n";
        return false;
    }

    int newId = generateMenuItemId();
    MenuItem newItem(newId, name, description, price, available, restaurantId);
    menuItems.push_back(newItem);

    saveToFile();

    cout << "Menu item created successfully! ID: " << newId << "\n";
    return true;
}

MenuItem* MenuItemService::getMenuItemById(int id) {
    for (MenuItem& item : menuItems) {
        if (item.getId() == id) {
            return &item;
        }
    }
    return nullptr;
}

vector<MenuItem> MenuItemService::getAllMenuItems() const {
    return menuItems;
}

vector<MenuItem> MenuItemService::getMenuItemsByRestaurant(int restaurantId) const {
    vector<MenuItem> result;
    for (const MenuItem& item : menuItems) {
        if (item.getRestaurantId() == restaurantId) {
            result.push_back(item);
        }
    }
    return result;
}

bool MenuItemService::updateMenuItem(int id, const string& name, const string& description,
                                   double price, bool available) {
    MenuItem* item = getMenuItemById(id);
    if (!item) {
        cout << "Error: Menu item not found with ID: " << id << "\n";
        return false;
    }


    item->setName(name);
    item->setDescription(description);
    item->setPrice(price);
    item->setAvailable(available);

    saveToFile();

    cout << "Menu item updated successfully!\n";
    return true;
}

bool MenuItemService::deleteMenuItem(int id) {
    auto it = remove_if(menuItems.begin(), menuItems.end(),
        [id](const MenuItem& item) { return item.getId() == id; });

    if (it != menuItems.end()) {
        menuItems.erase(it, menuItems.end());

        saveToFile();

        cout << "Menu item deleted successfully!\n";
        return true;
    }

    cout << "Error: Menu item not found with ID: " << id << "\n";
    return false;
}

vector<MenuItem> MenuItemService::searchMenuItemsByName(const string& name) const {
    vector<MenuItem> result;
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    for (const MenuItem& item : menuItems) {
        string itemName = item.getName();
        transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);

        if (itemName.find(lowerName) != string::npos) {
            result.push_back(item);
        }
    }
    return result;
}

bool MenuItemService::updateMenuItemPrice(int id, double newPrice) {
    MenuItem* item = getMenuItemById(id);
    if (!item) {
        cout << "Error: Menu item not found!\n";
        return false;
    }

    if (newPrice <= 0) {
        cout << "Error: Price must be greater than 0!\n";
        return false;
    }

    item->setPrice(newPrice);

    saveToFile();

    cout << "Price updated successfully! New price: $" << newPrice << "\n";
    return true;
}

bool MenuItemService::toggleMenuItemAvailability(int id) {
    MenuItem* item = getMenuItemById(id);
    if (!item) {
        cout << "Error: Menu item not found!\n";
        return false;
    }

    bool newStatus = !item->getAvailable();
    item->setAvailable(newStatus);

    saveToFile();

    cout << "Availability updated to: " << (newStatus ? "Available" : "Not Available") << "\n";
    return true;
}

bool MenuItemService::updateMenuItemDescription(int id, const string& newDescription) {
    MenuItem* item = getMenuItemById(id);
    if (!item) {
        cout << "Error: Menu item not found!\n";
        return false;
    }

    item->setDescription(newDescription);

    saveToFile();

    cout << "Description updated successfully!\n";
    return true;
}

bool MenuItemService::isValidMenuItem(const MenuItem& item) const {
    if (item.getName().empty()) {
        return false;
    }

    if (item.getPrice() <= 0) {
        return false;
    }

    if (item.getRestaurantId() <= 0) {
        return false;
    }

    return true;
}

bool MenuItemService::isMenuItemNameUnique(const string& name, int restaurantId) const {
    for (const MenuItem& item : menuItems) {
        if (item.getName() == name && item.getRestaurantId() == restaurantId) {
            return false;
        }
    }
    return true;
}

int MenuItemService::countMenuItemsByRestaurant(int restaurantId) const {
    int count = 0;
    for (const MenuItem& item : menuItems) {
        if (item.getRestaurantId() == restaurantId) {
            count++;
        }
    }
    return count;
}

double MenuItemService::getAveragePriceByRestaurant(int restaurantId) const {
    double total = 0.0;
    int count = 0;

    for (const MenuItem& item : menuItems) {
        if (item.getRestaurantId() == restaurantId) {
            total += item.getPrice();
            count++;
        }
    }

    return count > 0 ? total / count : 0.0;
}

int MenuItemService::generateMenuItemId() {
    static int counter = 1000;
    return counter++;
}

bool MenuItemService::saveToFile() {
    return fileStorage.saveMenuItems(menuItems);
}

bool MenuItemService::loadFromFile() {
    return fileStorage.loadMenuItems(menuItems);
}

void MenuItemService::setDataFilename(const std::string& filename) {
    fileStorage.setFilename(filename);
}