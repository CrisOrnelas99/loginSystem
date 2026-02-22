#include "UserData.hpp"
#include "Services/DatabaseService.hpp"
#include "Services/AUTH/PasswordService.hpp"
#include "Services/AUTH/AuthenticationService.hpp"
#include "Services/AUTH/AuthorizationService.hpp"
#include "Services/AUTH/ValidationService.hpp"
#include "Services/AuditLogService.hpp"
#include "Services/ConfigService.hpp"
#include "Services/UI/UIService.hpp"
#include "Services/UI/AdminUI.hpp"
#include "Services/UI/EmployeeUI.hpp"
#include "Services/UI/GuestUI.hpp"

class MasterService // Coordinates top-level app flow.
{
private:
    DatabaseService databaseService; // Stores users and lookups.
    PasswordService passwordService; // Manages password operations.
    AuthenticationService authenticationService; // Handles login workflow.
    AuthorizationService authorizationService; // Enforces role permissions.
    ValidationService validationService; // Validates user input data.
    AuditLogService auditLogService; // Records security-related events.
    ConfigService configService; // Provides security settings.

    AdminUI adminUI; // Renders admin-facing screens.
    EmployeeUI employeeUI; // Renders employee-facing screens.
    GuestUI guestUI; // Renders guest-facing screens.

public:
    MasterService(); // Initializes service dependencies.
    void run(); // Starts the main app loop.
    bool processLogin(); // Executes login request flow.
    void routeRoleMenu(const UserData& user); // Routes role-specific UI flow.
    void processLogout(); // Clears active session state.
};




int main( )
{
  	return 0; // Program entry placeholder.
}
