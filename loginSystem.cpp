/*	Log : 4/12 created the basic functions, enum roles, User class, SystemOn class
	log: 4/13 created loop for login screen for both guest and admin, as well as a working logout code
	log 4/15 added Guest, created the View User function, created while loop for login screen until lockout
	log 4/19 moved userData info to separate class
	log 4/20 code maintenance
	log 4/26 created change credentials function
	log 4/28 make sure change userName doesn't accept already used userName in database.
	log 4/29 verify passwords before modifying, initialized create account option for admin, started modify accounts function
*/

/*
  TODO :: beginner
  TODO :: have admin modify all user's****
  TODO :: add/ remove user's
  TODO :: error handling class****
  TODO :: Create log class and file for tracking everything
  TODO :: clean code up
  TODO :: Flow Chart and PseudoCode(simple login System) ****
  -----------------------------------------------------------------------------------------
  TODO :: intermediate
  TODO :: use basic DataBase(SQL)
  TODO :: forgot userName/ password system
  TODO :: some kind of networking concept(get MAC or IP address of Device for verification)
  TODO :: Find out how to encrypt the files data and decrypt in code
  TODO :: create Visual GUI for frontEnd(QT framework)
  TODO :: Organization/ clean code and separation of .cpp files and classes ****
  TODO :: update flowChart and PseudCode (intermediate login System)
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
		//access private
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
	//class for data base
class UserDataBase
{
	std::vector<UserData> users;
	public:
		//move to private?
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
//
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
		//TODO :: username alphanumerical only, password can have any character(input validation), can't copy any one userName, display if same userName/password
		void changeCredentials(UserData *currentUser)
		{
			if (currentUser == nullptr)
			{
				std::cout << "No user logged in.\n";
				return;
			}
			std::string confirmPass;
			char userOption;
			std::cout << "Enter password to confirm:" << std::endl;
			std::cin >> confirmPass;
			if (currentUser->getPass() != confirmPass)
			{
				std::cout << "Password confirmation failed!\n";
				return;
			}

			std::cout << "Change Username[U] or Password[P]";
			std::cin >> userOption;
			if (userOption == 'U')
			{
				std::string newUser;
				std::cout << "Enter new username:";
				std::cin >> newUser;

				if (newUser == currentUser->getName())
				{
					std::cout << "New userName is the same as the current one\n";
					return;
				}
				for (const auto &user : userDataBase-> getUsers())
				{
					if (newUser == user.getName())
					{
						std::cout << "UserName already exists. Choose a different one.\n";
						return;
					}
				}
				currentUser->setName(newUser);
				std::cout << "username changed successfully!\n";

			}
			else if (userOption == 'P')
			{
				std::string newPass;
				std::cout << "Enter new password:";
				std::cin >> newPass;
				if (newPass == currentUser->getName())
				{
					std::cout << "New password is the same as the current one\n";
					return;
				}
				currentUser->setPass(newPass);
				std::cout << "Password changed successfully!\n";
			}
		}

		void modifyAccounts()
		{
			std::string employeeName;
			std::cout << "Choose Employee Account to modify:" << std::endl;
			auto userList = userDataBase->getUsers();
			for (const UserData& user : userList)
				std::cout << "[" << user.getEmployee() << "]" << std::endl;
			while (true)
			{
				std::cin >> employeeName;

				for (const UserData& user : userList)
				{
					if (employeeName == user.getEmployee())
					{
						std::cout << "Update role Status[U], change Employee Name[E], change userName[U] change password[P] or remove user[R]";
					}
					else
						return;
				}
			}
		}
		//TODO :: create function definition
		void createAccount()
		{
			std::cout << "Test" << std::endl;
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

		SystemLogin() : modifyView(&userDataBase)
		{
			userDataBase.initializeData();
		}

		void displayAdminScreen()
		{
			bool userIn = true;
			while (userIn)
			{
				char userChoice;
				std::cout << "Change Credentials[C], Modify Accounts[M], Display Users[D], create User[U] or Logout[L]\n" << std::endl;
				std::cin >> userChoice;
				switch (userChoice)
				{
					case 'C':
					modifyView.changeCredentials(currentUser);
					break;
				case 'M':
					modifyView.modifyAccounts();
					break;
				case 'D':
					std::cout << "Displaying Current Employees...\n";
					modifyView.viewUsers();
					break;
				case 'U':
					std::cout << "coming soon\n";
					modifyView.createAccount();
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
				std::cout << "Change Credentials [C] or Logout [L]\n";
				std::cin >> userChoice;
				if (userChoice == 'L')
				{
					std::cout << "Logging out...\n\n";
					userIn = false;
				}
				else if (userChoice == 'C')
					modifyView.changeCredentials(currentUser);
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
							std::cout << "Welcome " << matchedUser->getEmployee()  << std::endl;
							displayAdminScreen();
						}
						else if (matchedUser->getRole() == EMPLOYEE || matchedUser->getRole() == GUEST)
						{
							std::cout << "Welcome " << matchedUser->getEmployee()  << std::endl;
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
