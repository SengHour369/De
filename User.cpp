// User.cpp
#include "User.h"

User::User() : id(""), username(""), password(""), gender(""), 
               date_of_birth(""), email(""), status(""), 
               phone_number(""), address(""), role("") {
}

User::User(const string& username, const string& password,
           const string& gender, const string& date_of_birth,
           const string& email, const string& status,
           const string& phone_number, const string& address,
           const string& role) :
    id(""), username(username), password(password), gender(gender),
    date_of_birth(date_of_birth), email(email), status(status),
    phone_number(phone_number), address(address), role(role) {
}


string User::getId() const { return id; }
string User::getUsername() const { return username; }
string User::getPassword() const { return password; }
string User::getGender() const { return gender; }
string User::getDateOfBirth() const { return date_of_birth; }
string User::getEmail() const { return email; }
string User::getStatus() const { return status; }
string User::getPhoneNumber() const { return phone_number; }
string User::getAddress() const { return address; }
string User::getRole() const { return role; }


void User::setId(const string& id) { this->id = id; }
void User::setUsername(const string& username) { this->username = username; }
void User::setPassword(const string& password) { this->password = password; }
void User::setGender(const string& gender) { this->gender = gender; }
void User::setDateOfBirth(const string& date_of_birth) { this->date_of_birth = date_of_birth; }
void User::setEmail(const string& email) { this->email = email; }
void User::setStatus(const string& status) { this->status = status; }
void User::setPhoneNumber(const string& phone_number) { this->phone_number = phone_number; }
void User::setAddress(const string& address) { this->address = address; }
void User::setRole(const string& role) { this->role = role; }