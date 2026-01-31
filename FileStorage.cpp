// FileStorage.cpp
#include "FileStorage.h"
#include "User.h"
#include "Restaurant.h"
#include "MenuItem.h"
#include <iostream>

// Save Users to binary file
bool FileStorage::saveUsers(const vector<User>& users) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cout << "Error: Cannot open file " << filename << " for writing users!\n";
        return false;
    }

    size_t size = users.size();
    outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));

    for (const User& user : users) {
        saveString(outFile, user.getId());
        saveString(outFile, user.getUsername());
        saveString(outFile, user.getPassword());
        saveString(outFile, user.getGender());
        saveString(outFile, user.getDateOfBirth());
        saveString(outFile, user.getEmail());
        saveString(outFile, user.getStatus());
        saveString(outFile, user.getPhoneNumber());
        saveString(outFile, user.getAddress());
        saveString(outFile, user.getRole());
    }

    bool success = outFile.good();
    outFile.close();

    if (success) {
        cout << "Saved " << size << " users to " << filename << endl;
    }

    return success;
}

// Load Users from binary file
bool FileStorage::loadUsers(vector<User>& users) {
   ifstream inFile(filename, ios::binary);
    if (!inFile) {
        // File doesn't exist yet - that's okay
        return false;
    }

    size_t size;
    inFile.read(reinterpret_cast<char*>(&size), sizeof(size));

    users.clear();

    for (size_t i = 0; i < size; i++) {
        User user;
        user.setId(loadString(inFile));
        user.setUsername(loadString(inFile));
        user.setPassword(loadString(inFile));
        user.setGender(loadString(inFile));
        user.setDateOfBirth(loadString(inFile));
        user.setEmail(loadString(inFile));
        user.setStatus(loadString(inFile));
        user.setPhoneNumber(loadString(inFile));
        user.setAddress(loadString(inFile));
        user.setRole(loadString(inFile));

        users.push_back(user);
    }

    bool success = inFile.good();
    inFile.close();

    if (success) {
        cout << "Loaded " << size << " users from " << filename <<endl;
    }

    return success;
}

// Save Restaurants to binary file
bool FileStorage::saveRestaurants(const vector<Restaurant>& restaurants) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Error: Cannot open file " << filename << " for writing restaurants!\n";
        return false;
    }

    size_t size = restaurants.size();
    outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));

    for (const Restaurant& restaurant : restaurants) {
        int id = restaurant.getId();
        outFile.write(reinterpret_cast<const char*>(&id), sizeof(id));

        saveString(outFile, restaurant.getName());
        saveString(outFile, restaurant.getCategory());

        int rating = restaurant.getRating();
        outFile.write(reinterpret_cast<const char*>(&rating), sizeof(rating));

        saveString(outFile, restaurant.getPhoneNumber());
        saveString(outFile, restaurant.getLocation());
    }

    bool success = outFile.good();
    outFile.close();

    if (success) {
        cout << "Saved " << size << " restaurants to " << filename << endl;
    }

    return success;
}

// Load Restaurants from binary file
bool FileStorage::loadRestaurants(vector<Restaurant>& restaurants) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        return false;
    }

    size_t size;
    inFile.read(reinterpret_cast<char*>(&size), sizeof(size));

    restaurants.clear();

    for (size_t i = 0; i < size; i++) {
        int id, rating;
        inFile.read(reinterpret_cast<char*>(&id), sizeof(id));

        string name = loadString(inFile);
        string category = loadString(inFile);

        inFile.read(reinterpret_cast<char*>(&rating), sizeof(rating));

        string phone = loadString(inFile);
        string location = loadString(inFile);

        Restaurant restaurant(id, name, category, rating, phone, location);
        restaurants.push_back(restaurant);
    }

    bool success = inFile.good();
    inFile.close();

    if (success) {
        cout << "Loaded " << size << " restaurants from " << filename << endl;
    }

    return success;
}

// Save MenuItems to binary file
bool FileStorage::saveMenuItems(const vector<MenuItem>& menuItems) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cout << "Error: Cannot open file " << filename << " for writing menu items!\n";
        return false;
    }

    size_t size = menuItems.size();
    outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));

    for (const MenuItem& item : menuItems) {
        int id = item.getId();
        outFile.write(reinterpret_cast<const char*>(&id), sizeof(id));

        saveString(outFile, item.getName());
        saveString(outFile, item.getDescription());

        double price = item.getPrice();
        outFile.write(reinterpret_cast<const char*>(&price), sizeof(price));

        bool available = item.getAvailable();
        outFile.write(reinterpret_cast<const char*>(&available), sizeof(available));

        int restaurantId = item.getRestaurantId();
        outFile.write(reinterpret_cast<const char*>(&restaurantId), sizeof(restaurantId));
    }

    bool success = outFile.good();
    outFile.close();

    if (success) {
        cout << "Saved " << size << " menu items to " << filename << endl;
    }

    return success;
}

// Load MenuItems from binary file
bool FileStorage::loadMenuItems(vector<MenuItem>& menuItems) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        return false;
    }

    size_t size;
    inFile.read(reinterpret_cast<char*>(&size), sizeof(size));

    menuItems.clear();

    for (size_t i = 0; i < size; i++) {
        int id, restaurantId;
        double price;
        bool available;

        inFile.read(reinterpret_cast<char*>(&id), sizeof(id));

        string name = loadString(inFile);
        string description = loadString(inFile);

        inFile.read(reinterpret_cast<char*>(&price), sizeof(price));
        inFile.read(reinterpret_cast<char*>(&available), sizeof(available));
        inFile.read(reinterpret_cast<char*>(&restaurantId), sizeof(restaurantId));

        MenuItem item(id, name, description, price, available, restaurantId);
        menuItems.push_back(item);
    }

    bool success = inFile.good();
    inFile.close();

    if (success) {
        cout << "Loaded " << size << " menu items from " << filename <<endl;
    }

    return success;
}