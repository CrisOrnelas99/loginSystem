#include <iostream>
#include <string>

#include "UserData.hpp"
#include "Services/DatabaseService.hpp"
#include "Services/PasswordService.hpp"
#include "Services/AuthenticationService.hpp"
#include "Services/AuthorizationService.hpp"
#include "Services/AuditLogService.hpp"
#include "Services/ConfigService.hpp"
#include "Services/UI/UIService.hpp"
#include "Services/UI/AdminUI.hpp"
#include "Services/UI/EmployeeUI.hpp"
#include "Services/UI/GuestUI.hpp"

/*
	TODO::
  2. Implement PasswordService (hash + verify) and test it independently.
  3. Implement ValidationService (username/password/MFA input guards).
  4. Implement AuthenticationService using database + password + validation.
  5. Add AuthorizationService checks based on Role.
  6. Add AuditLogService hooks at success/failure points.
  7. Add UI service for console visual
  7. Wire all of it inside MasterService, then call it from main().
*/

class MasterService		//main controller
{

};




int main( )
{
  	return 0;
}
