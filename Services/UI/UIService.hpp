#ifndef LOGINSYSTEM_UISERVICE_HPP
#define LOGINSYSTEM_UISERVICE_HPP

#include <string>
#include "../../UserData.hpp"

class UIService // Defines shared UI contract.
{
public:
    virtual ~UIService() = default; // Enables safe polymorphic deletion.

    virtual void showWelcome() = 0; // Displays initial welcome view.
    virtual void showLoginScreen() = 0; // Displays login prompt view.
    virtual void showMainMenu() = 0; // Displays common main options.
    virtual void showRoleMenu() = 0; // Displays role-specific options.
    virtual void showMessage(const std::string& message) = 0; // Displays standard status message.
    virtual void showError(const std::string& errorMessage) = 0; // Displays user-facing error message.
    virtual void showUserProfile(const UserData& user) = 0; // Displays active user details.
};

#endif // LOGINSYSTEM_UISERVICE_HPP
