#ifndef LOGINSYSTEM_ADMINUI_HPP
#define LOGINSYSTEM_ADMINUI_HPP

#include "UIService.hpp"

class AdminUI : public UIService // Renders admin workflow screens.
{
public:
    void showWelcome() override; // Displays admin welcome view.
    void showLoginScreen() override; // Displays admin login prompt.
    void showMainMenu() override; // Displays admin main menu.
    void showRoleMenu() override; // Displays admin role options.
    void showMessage(const std::string& message) override; // Displays admin status message.
    void showError(const std::string& errorMessage) override; // Displays admin error message.
    void showUserProfile(const UserData& user) override; // Displays admin user profile.

    void showAdminDashboard(); // Displays admin dashboard view.
    void showManageUsersMenu(); // Displays user management options.
    void showSystemConfigMenu(); // Displays security config menu.
    void showAuditLogMenu(); // Displays audit log options.
};

#endif // LOGINSYSTEM_ADMINUI_HPP
