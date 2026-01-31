// UserService.h
#ifndef RESTAURANT_PROJECT_USERSERVICE_H
#define RESTAURANT_PROJECT_USERSERVICE_H

#include <vector>
#include <string>
#include "User.h"
#include "FileStorage.h"
using namespace std;

class UserService {
private:
    vector<User> users;
    string currentUserId;
    FileStorage fileStorage;

public:
    UserService();
    UserService(const string& filename);


    bool registerUser(const string& username, const string& password,
                     const string& gender, const string& date_of_birth,
                     const string& email, const string& phone_number,
                     const string& address, const string& role);

    User login(const string& username, const string& password);
    bool logout();
    bool updateProfile(const User& updatedUser);
    bool changePassword(const string& oldPassword, const string& newPassword);


    User* getCurrentUser();
    User* getUserById(const string& id);
    User* getUserByUsername(const string& username);
    vector<User> getAllUsers() const;


    bool deleteUser(const string& userId);
    bool updateUserStatus(const string& userId, const string& status);


    bool isUsernameAvailable(const string& username) const;
    bool isEmailAvailable(const string& email) const;

    // File storage methods
    bool saveToFile();
    bool loadFromFile();
    void setDataFilename(const string& filename);

private:
    string generateUserId();
    bool validateRole(const string& role);
};

#endif // RESTAURANT_PROJECT_USERSERVICE_H