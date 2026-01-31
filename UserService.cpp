// UserService.cpp
#include "UserService.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <regex>
using namespace std;

UserService::UserService() : currentUserId(""), fileStorage("users.dat") {
    loadFromFile();

    if (users.empty()) {
        users.push_back(User("admin", "admin123", "Male", "1980-01-01",
                            "admin@restaurant.com", "Active", "555-0001",
                            "Admin Street", "ADMIN"));
        users[0].setId("USR0000");
        saveToFile();
        cout << "Created default admin user\n";
    }
}

UserService::UserService(const string& filename) : currentUserId(""), fileStorage(filename) {
    loadFromFile();

    if (users.empty()) {
        users.push_back(User("admin", "admin123", "Male", "1980-01-01",
                            "admin@restaurant.com", "Active", "555-0001",
                            "Admin Street", "ADMIN"));
        users[0].setId("USR0000");
        saveToFile();
        cout << "Created default admin user\n";
    }
}

bool UserService::registerUser(const string& username, const string& password,
                              const string& gender, const string& date_of_birth,
                              const string& email, const string& phone_number,
                              const string& address, const string& role) {

    if (!isUsernameAvailable(username)) {
        cout << "Username already exists!\n";
        return false;
    }

    if (!isEmailAvailable(email)) {
        cout << "Email already registered!\n";
        return false;
    }

    if (password.length() < 6) {
        cout << "Password must be at least 6 characters!\n";
        return false;
    }

    if (!validateRole(role)) {
        cout << "Invalid role! Must be 'ADMIN', 'STAFF', or 'CUSTOMER'\n";
        return false;
    }

    User newUser(username, password, gender, date_of_birth, email,
                "Active", phone_number, address, role);
    newUser.setId(generateUserId());
    users.push_back(newUser);

    saveToFile();

    cout << "User registered successfully! ID: " << newUser.getId() << "\n";
    return true;
}

bool UserService::login(const string& username, const string& password) {
    for (User& user : users) {
        if (user.getUsername() == username && user.getPassword() == password) {
            if (user.getStatus() == "Active") {
                currentUserId = user.getId();
                cout << "Login successful! Welcome " << username << "\n";
                return true;
            } else {
                cout << "Account is not active!\n";
                return false;
            }
        }
    }
    cout << "Invalid username or password!\n";
    return false;
}

bool UserService::logout() {
    if (currentUserId.empty()) {
        cout << "No user is logged in!\n";
        return false;
    }

    User* currentUser = getCurrentUser();
    if (currentUser) {
        cout << "Goodbye " << currentUser->getUsername() << "!\n";
    }

    currentUserId = "";
    return true;
}

bool UserService::updateProfile(const User& updatedUser) {
    User* currentUser = getCurrentUser();
    if (!currentUser) {
        cout << "No user is logged in!\n";
        return false;
    }

    currentUser->setEmail(updatedUser.getEmail());
    currentUser->setPhoneNumber(updatedUser.getPhoneNumber());
    currentUser->setAddress(updatedUser.getAddress());
    currentUser->setGender(updatedUser.getGender());
    currentUser->setDateOfBirth(updatedUser.getDateOfBirth());

    saveToFile();

    cout << "Profile updated successfully!\n";
    return true;
}

bool UserService::changePassword(const string& oldPassword, const string& newPassword) {
    User* currentUser = getCurrentUser();
    if (!currentUser) {
        cout << "No user is logged in!\n";
        return false;
    }

    if (currentUser->getPassword() != oldPassword) {
        cout << "Current password is incorrect!\n";
        return false;
    }

    if (newPassword.length() < 6) {
        cout << "New password must be at least 6 characters!\n";
        return false;
    }

    currentUser->setPassword(newPassword);

    saveToFile();

    cout << "Password changed successfully!\n";
    return true;
}

User* UserService::getCurrentUser() {
    if (currentUserId.empty()) {
        return nullptr;
    }

    for (User& user : users) {
        if (user.getId() == currentUserId) {
            return &user;
        }
    }
    return nullptr;
}

User* UserService::getUserById(const string& id) {
    for (User& user : users) {
        if (user.getId() == id) {
            return &user;
        }
    }
    return nullptr;
}

User* UserService::getUserByUsername(const string& username) {
    for (User& user : users) {
        if (user.getUsername() == username) {
            return &user;
        }
    }
    return nullptr;
}

vector<User> UserService::getAllUsers() const {
    return users;
}

bool UserService::deleteUser(const string& userId) {
    auto it = remove_if(users.begin(), users.end(),
        [userId](const User& user) { return user.getId() == userId; });

    if (it != users.end()) {
        users.erase(it, users.end());

        if (currentUserId == userId) {
            currentUserId = "";
        }

        saveToFile();

        cout << "User deleted successfully!\n";
        return true;
    }

    cout << "User not found!\n";
    return false;
}

bool UserService::updateUserStatus(const string& userId, const string& status) {
    User* user = getUserById(userId);
    if (user) {
        user->setStatus(status);

        saveToFile();

        cout << "User status updated to: " << status << "\n";
        return true;
    }
    return false;
}

bool UserService::isUsernameAvailable(const string& username) const {
    for (const User& user : users) {
        if (user.getUsername() == username) {
            return false;
        }
    }
    return true;
}

bool UserService::isEmailAvailable(const string& email) const {
    for (const User& user : users) {
        if (user.getEmail() == email) {
            return false;
        }
    }
    return true;
}

string UserService::generateUserId() {
    static int counter = 1000;
    stringstream ss;
    ss << "USR" << setw(4) << setfill('0') << counter++;
    return ss.str();
}

bool UserService::validateRole(const string& role) {
    return (role == "ADMIN" || role == "STAFF" || role == "CUSTOMER");
}

bool UserService::saveToFile() {
    return fileStorage.saveUsers(users);
}

bool UserService::loadFromFile() {
    return fileStorage.loadUsers(users);
}

void UserService::setDataFilename(const string& filename) {
    fileStorage.setFilename(filename);
}