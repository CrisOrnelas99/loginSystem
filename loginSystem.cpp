#include <iostream>
#include <string>
#include <limits>

enum class Role{Admin, Employee, Guest};

class UserData
{
	int userId;
	std::string name;
	std::string hashedPass;
	int mfaKey;	//other multifactor authentication method
	Role role;

public:
	UserData( int i, std::string n, std::string h, int m, Role r) :
		userId( i ), name( n ), hashedPass( h ), mfaKey( m ), role( r ) { }

	int getId() const {}
	std::string getName() const {}
	std::string getHash() const {}
	int getMFAKey() const {}
	Role getRole() const {}

};


class MasterService{};		//main controller
class UIService{};	//show UI and displays info
class AdminUI : public UIService{};
class EmployeeUI : public UIService{};
class GuestUI : public UIService{};


class ValidationService{};	//user input, check username,
class DatabaseService{};	//store user information, uses hash table with linked list for collision
class PasswordService{}; //hash, salt, pepper, compare hash,forgot pass
class AuthenticationService{};	//password, check mfa, lockout,
class AuthorizationService{};	//check role/permissions
class AuditLogService{};	//record security events
class ConfigService{};	//update security settings


int main( )
{
  	return 0;
}