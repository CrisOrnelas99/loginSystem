#ifndef LOGINSYSTEM_PASSWORDSERVICE_HPP
#define LOGINSYSTEM_PASSWORDSERVICE_HPP

#include <string>

class PasswordService // Handles password security operations.
{
public:
    std::string hashPassword(const std::string& plainPassword); // Returns derived password hash.
    bool verifyPassword(const std::string& plainPassword, const std::string& storedHash); // Compares plain input with hash.
    bool changePassword(const std::string& username, const std::string& currentPassword, const std::string& newPassword); // Changes user password securely.
    std::string addSalt(const std::string& plainPassword); // Adds per-password random salt.
    std::string addPepper(const std::string& saltedPassword); // Adds global application pepper.
    bool isStrongPassword(const std::string& plainPassword); // Checks password complexity rules.
};

#endif // LOGINSYSTEM_PASSWORDSERVICE_HPP
