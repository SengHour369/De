// User.h
#ifndef RESTAURANT_PROJECT_USER_H
#define RESTAURANT_PROJECT_USER_H

#include <string>
using namespace std;

class User {
private:
    string id;
    string username;
    string password;
    string gender;
    string date_of_birth;
    string email;
    string status;
    string phone_number;
    string address;
    string role;

public:
    User();
    User(const string& username,
         const string& password,
         const string& gender,
         const string& date_of_birth,
         const string& email,
         const string& status,
         const string& phone_number,
         const string& address,
         const string& role);


    string getId() const;
    string getUsername() const;
    string getPassword() const;
    string getGender() const;
    string getDateOfBirth() const;
    string getEmail() const;
    string getStatus() const;
    string getPhoneNumber() const;
    string getAddress() const;
    string getRole() const;


    void setId(const string& id);
    void setUsername(const string& username);
    void setPassword(const string& password);
    void setGender(const string& gender);
    void setDateOfBirth(const string& date_of_birth);
    void setEmail(const string& email);
    void setStatus(const string& status);
    void setPhoneNumber(const string& phone_number);
    void setAddress(const string& address);
    void setRole(const string& role);
};

#endif // RESTAURANT_PROJECT_USER_H