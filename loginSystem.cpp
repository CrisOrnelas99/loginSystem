/*	Log : 4/12 created the basic functions, enum roles, User class, SystemOn class
	log: 4/13 created loop for login screen for both guest and admin, as well as a working logout code
	log 4/15 added Guest, created the View User function, created while loop for login screen until lockout
	log 4/19 moved userData info to separate class
	log 4/20 code maintenance
	log 4/26 created change credentials function
*/

/*
  TODO :: Seperate .cpp files for error handling class, encryption, moveANdModify class separate, Access control list, userData doc, and File handling/Log files
  TODO :: have user and admin, view and change self credentials, and verify password, with passcode(Badge)
  TODO :: have admin modify all user's
  TODO :: Create log class and file for tracking everything.
  TODO :: create error handling class/ polymorphism
  TODO :: add pointers
  TODO :: Find out how to encrypt the files data and decrypt in code
  TODO :: some kind of network security
  TODO :: Organization/ clean code and separation of .cpp files and classes
  TODO :: Flow Chart and PseudoCode
*/


#include <iostream>
#include <vector>

//roles in the system
enum Roles { ADMIN, EMPLOYEE, GUEST };


//class for the user's data
class UserData
{
	private:

		std::string employee;
		std::string userName;
		std::string passWord;
		Roles userRole;
	public:

		UserData(std::string wEmployee, std::string uName, std::string pWord, Roles uRole )
		{
			userName = uName;
			passWord = pWord;
			userRole = uRole;
			employee = wEmployee;
		}
		std::string getName() const { return userName; }
		std::string getPass() const { return passWord; }
		Roles getRole() const { return userRole; }
		std::string getEmployee() const { return employee; }

		void setName(const std::string &newName) {userName = newName; }
		void setPass(const std::string &newPass) {passWord = newPass; }
};

class UserDataBase
{
	std::vector<UserData> users;
	public:
		void initializeData()
		{
			users.clear();
			users.push_back({ "Cris","admin", "Password123", ADMIN });
			users.push_back({ "employee1" ,"employee", "123Pass", EMPLOYEE });
			users.push_back({ "Janitor1", "guestA", "guest123", GUEST });
		}
		std::vector<UserData>& getUsers()
		{
			return users;
		}
};

class ModifyAndView
{
	private:
		UserDataBase* userDataBase;
	public:

		ModifyAndView(UserDataBase* ptr)
		{
			userDataBase = ptr;
		}

		void viewUsers()
		{
			auto userList = userDataBase->getUsers();
			for (const UserData& user : userList)
			{
				std::cout << "----------------------\n";
				std::cout << "Name: " << user.getEmployee() << "\n";
				std::cout << "UserName: " << user.getName() << "\n";
				std::cout << "Password: " << user.getPass() << "\n";
				if (user.getRole() == ADMIN)
					std::cout << "Role: ADMIN\n";
				else if (user.getRole() == EMPLOYEE)
					std::cout << "Role: EMPLOYEE\n";
				else if (user.getRole() == GUEST)
					std::cout << "Role: GUEST\n";
			}
			std::cout << "-----------------------\n\n";
		}

		void changeCredentials(UserData *currentUser)
		{

			if (currentUser == nullptr)
			{
				std::cout << "No user logged in.\n";
				return;
			}
			char userOption;
			std::cout << "Change Username[U] or Password[P]";
			std::cin >> userOption;
			if (userOption == 'U')
			{
				std::string newUser;
				std::cout << "Enter new username:";
				std::cin >> newUser;
				currentUser->setName(newUser);

			}
			else if (userOption == 'P')
			{
				std::string newPass;
				std::cout << "Enter new password:";
				std::cin >> newPass;
				currentUser->setPass(newPass);
			}

		}

		void modifyAccounts()
		{
			std::cout << "Coming soon\n";
		}
};


//class for LogIn system loop functions
class SystemLogin
{
	private:
		UserDataBase userDataBase;
		ModifyAndView modifyView;
		UserData* currentUser = nullptr;
	public:

		SystemLogin() : modifyView(&userDataBase) {}

		void displayAdminScreen()
		{
			bool userIn = true;
			while (userIn)
			{
				char userChoice;
				std::cout << "Change Credentials[C], Modify Accounts[M], Display Users[D], or Logout[L]\n" << std::endl;
				std::cin >> userChoice;
				switch (userChoice)
				{
					case 'C':
					std::cout << "Change Account Info chosen!\n";
					modifyView.changeCredentials(currentUser);
					break;
				case 'M':
					std::cout << "Modify option chosen!\n";
					modifyView.modifyAccounts();
					break;
				case 'D':
					std::cout << "Displaying Current Employees...\n";
					modifyView.viewUsers();
					break;
				case 'L':
					std::cout << "Logging out...\n\n";
					userIn = false;
					break;
				default:
					std::cout << "option not available\n";
				}
			}
			loginScreen();
		}

		void displayUsersScreen()
		{
			bool userIn = true;
			while (userIn)
			{
				char userChoice;
				std::cout << "Logout? (L or any other key to ignore)\n";
				std::cin >> userChoice;
				if (userChoice == 'L')
				{
					std::cout << "Logging out...\n\n";
					userIn = false;
				}
				else if (userChoice == 'C')
				{
					continue;
				}
			}
			loginScreen();
		}

		UserData* checkCredentials(const std::string& userName, const std::string& passWord)
			{
				for (auto& user : userDataBase.getUsers())
				{
					if (user.getName() == userName && user.getPass() == passWord)
					{
						return &user;
					}
				}
				return nullptr;
			}

		void loginScreen()
			{
				std::string inputUser, inputPass;
				std::cout << "--------------------Login System--------------------\n\n";
				userDataBase.initializeData();
				int attempts = 0;

				while (attempts < 3)
				{
					std::cout << "Enter your UserName: ";
					std::cin >> inputUser;
					std::cout << "Enter the Password: ";
					std::cin >> inputPass;

					UserData* matchedUser = checkCredentials(inputUser, inputPass);
					if (matchedUser != nullptr)
					{
						currentUser = matchedUser;
						if (matchedUser->getRole() == ADMIN)
						{
							std::cout << "Admin Logged In\n";
							displayAdminScreen();
						}
						else if (matchedUser->getRole() == EMPLOYEE)
						{
							std::cout << "Employee Logged In\n";
							displayUsersScreen();
						}
						else if (matchedUser->getRole() == GUEST)
						{
							std::cout << "Guest Logged In\n";
							displayUsersScreen();
						}
						return;
					}
					else
					{
						std::cout << "Failed Login!" << std::endl;
						attempts++;
						std::cout << 3 - attempts << " attempts left" << std::endl;
					}
				}
				std::cout << "Locking System... ***Call System admin for assistance***" << std::endl;
			}
};

int main()
{
	SystemLogin powerOn;
	powerOn.loginScreen();
}
