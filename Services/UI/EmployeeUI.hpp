#ifndef LOGINSYSTEM_EMPLOYEEUI_HPP
#define LOGINSYSTEM_EMPLOYEEUI_HPP

#include "UIService.hpp"

class EmployeeUI : public UIService // Renders employee workflow screens.
{
public:
    void showWelcome() override; // Displays employee welcome view.
    void showLoginScreen() override; // Displays employee login prompt.
    void showMainMenu() override; // Displays employee main menu.
    void showRoleMenu() override; // Displays employee role options.
    void showMessage(const std::string& message) override; // Displays employee status message.
    void showError(const std::string& errorMessage) override; // Displays employee error message.
    void showUserProfile(const UserData& user) override; // Displays employee user profile.

    void showEmployeeDashboard(); // Displays employee dashboard view.
    void showTaskMenu(); // Displays employee task actions.
    void showAccountMenu(); // Displays employee account actions.
};

#endif // LOGINSYSTEM_EMPLOYEEUI_HPP
