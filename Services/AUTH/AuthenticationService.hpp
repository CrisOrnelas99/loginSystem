#ifndef LOGINSYSTEM_AUTHENTICATIONSERVICE_HPP
#define LOGINSYSTEM_AUTHENTICATIONSERVICE_HPP

#include <string>
#include "../../UserData.hpp"

class AuthenticationService // Handles authentication state and flow.
{
private:
    UserData* currentUser; // Tracks currently authenticated user.

public:
    AuthenticationService(); // Initializes authentication state.
    bool login(const std::string& username, const std::string& password, int mfaCode); // Attempts user login flow.

    bool verifyPassword(const UserData& user, const std::string& plainPassword); // Validates password against stored hash.
    bool verifyMFA(const UserData& user, int mfaCode); // Validates MFA code value.

    bool isAccountLocked(const UserData& user); // Checks whether account is locked.
    void recordFailedAttempts(const std::string& username); // Increments failed attempt counter.
    void resetFailedAttempts(const std::string& username); // Clears failed attempt counter.

    bool isAuthenticated() const; // Returns authentication status flag.
    const UserData* getCurrentUser() const; // Returns active authenticated user.
    void logout(); // Clears current authentication session.

};

#endif // LOGINSYSTEM_AUTHENTICATIONSERVICE_HPP
