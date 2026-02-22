#ifndef LOGINSYSTEM_GUESTUI_HPP
#define LOGINSYSTEM_GUESTUI_HPP

#include "UIService.hpp"

class GuestUI : public UIService // Renders guest workflow screens.
{
public:
    void showWelcome() override; // Displays guest welcome view.
    void showLoginScreen() override; // Displays guest login prompt.
    void showMainMenu() override; // Displays guest main menu.
    void showRoleMenu() override; // Displays guest role options.
    void showMessage(const std::string& message) override; // Displays guest status message.
    void showError(const std::string& errorMessage) override; // Displays guest error message.
    void showUserProfile(const UserData& user) override; // Displays guest user profile.

    void showGuestDashboard(); // Displays guest dashboard view.
    void showLimitedAccessInfo(); // Displays guest access limitations.
};

#endif // LOGINSYSTEM_GUESTUI_HPP
