#ifndef LOGINSYSTEM_AUTHORIZATIONSERVICE_HPP
#define LOGINSYSTEM_AUTHORIZATIONSERVICE_HPP

#include <string>
#include "../../UserData.hpp"

class AuthorizationService // Enforces role-based access decisions.
{
public:
    bool hasRole(const UserData& user, Role role); // Checks user role match.
    bool canAccess(const UserData& user, const std::string& permission); // Checks named permission access.
    bool canAccessAdminFeatures(const UserData& user); // Checks admin feature access.
    bool canAccessEmployeeFeatures(const UserData& user); // Checks employee feature access.
    bool canAccessGuestFeatures(const UserData& user); // Checks guest feature access.
};

#endif // LOGINSYSTEM_AUTHORIZATIONSERVICE_HPP
