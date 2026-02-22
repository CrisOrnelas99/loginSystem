#ifndef LOGINSYSTEM_CONFIGSERVICE_HPP
#define LOGINSYSTEM_CONFIGSERVICE_HPP

#include <string>

class ConfigService // Manages runtime security configuration.
{
public:
    bool loadFromEnvFile(const std::string& path = ".env"); // Loads config values from .env.

    int getMaxLoginAttempts() const; // Returns allowed failed attempts.
    int getLockoutMinutes() const; // Returns lockout duration minutes.
    int getMfaCodeTtlSeconds() const; // Returns MFA code lifetime seconds.
    int getSessionTimeoutMinutes() const; // Returns session timeout minutes.
    int getPasswordMinLength() const; // Returns minimum password length.

    std::string getAppPepper() const; // Returns application pepper secret.
    std::string getAuditLogPath() const; // Returns audit log destination path.

    void setMaxLoginAttempts(int value); // Updates maximum failed attempts.
    void setLockoutMinutes(int value); // Updates lockout duration minutes.
    void setMfaCodeTtlSeconds(int value); // Updates MFA lifetime seconds.
    void setSessionTimeoutMinutes(int value); // Updates session timeout minutes.
    void setPasswordMinLength(int value); // Updates password minimum length.
    void setAppPepper(const std::string& value); // Updates application pepper secret.
    void setAuditLogPath(const std::string& value); // Updates audit log destination.
};

#endif // LOGINSYSTEM_CONFIGSERVICE_HPP
