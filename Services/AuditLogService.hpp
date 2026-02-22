#ifndef LOGINSYSTEM_AUDITLOGSERVICE_HPP
#define LOGINSYSTEM_AUDITLOGSERVICE_HPP

#include <string>
#include <vector>

class AuditLogService // Captures security and system events.
{
public:
    void logInfo(const std::string& message); // Records informational event message.
    void logWarning(const std::string& message); // Records warning-level event message.
    void logError(const std::string& message); // Records error-level event message.

    void logLoginSuccess(const std::string& username); // Records successful user login.
    void logLoginFailure(const std::string& username); // Records failed login attempt.
    void logAccountLockout(const std::string& username); // Records account lockout event.
    void logPasswordChange(const std::string& username); // Records password update event.
    void logRoleChange(const std::string& username, const std::string& oldRole, const std::string& newRole); // Records user role modification.

    std::vector<std::string> getLogs() const; // Returns all stored log entries.
    void clearLogs(); // Clears all stored log entries.
};

#endif // LOGINSYSTEM_AUDITLOGSERVICE_HPP
