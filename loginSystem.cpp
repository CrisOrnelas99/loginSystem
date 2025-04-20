/*	Log : 4/12 created the basic functions, enum roles, User class, SystemOn class
	log: 4/13 created loop for login screen for both guest and admin, as well as a working logout code
	log 4/15 added Guest, created the View User function, created while loop for login screen until lockout
*/

/*
  TODO :: Seperate .cpp files for error handling class, encryption, moveANdModify class separate, Access control list, userData doc, and File handling/Log files
  TODO :: have user and admin, view and change self credentials, and verify password, with passcode(Badge)
  TODO :: have admin modify all user's
  TODO :: Create log class and file for tracking everything.
  TODO :: create error handling class
  TODO :: Find out how to encrypt the files data and decrypt in code
  TODO :: some kind of network security
  TODO :: Organization/ clean code and seperation of .cpp files and classes
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
		std::vector<UserData> userList;

	public:

		UserData(std::string wEmployee, std::string uName, std::string pWord, Roles uRole )
		{
			userName = uName;
			passWord = pWord;
			userRole = uRole;
			employee = wEmployee;
		}

		UserData()
		{
			userList.push_back({ "Cris","admin", "Password123", ADMIN });
			userList.push_back({ "employee1" ,"employee", "123Pass", EMPLOYEE });
			userList.push_back({ "Janitor1", "guestA", "guest123", GUEST });
		}

		std::string getName() const { return userName; }
		std::string getPass() const { return passWord; }
		Roles getRole() const { return userRole; }
		std::string getEmployee() const { return employee; }
		std::vector<UserData> getUserData() { return userList; }
};


class ModifyAndView
{
	public:

		UserData userdata;

		void viewUsers()
		{
			auto userList = userdata.getUserData();
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

		void changeCredentials()
		{
			std::cout << "Still in the works....\n";
		}

		void modifyAccounts()
		{
			std::cout << "Still in the works...\n";
		}
};


//class for LogIn system loop functions
class SystemLogin
{
	public:

		ModifyAndView modifyView;
		UserData userdata;

		void displayAdminScreen()
		{
			bool userIn = true;
			while (userIn)
			{
				char userChoice;
				std::cout << "Modify(M), Display Users(D), or Logout(L)\n" << std::endl;
				std::cin >> userChoice;
				switch (userChoice)
				{
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
				std::cout << "Logout? (Y or any other key to ignore)\n";
				std::cin >> userChoice;
				if (userChoice == 'Y')
				{
					std::cout << "Logging out...\n\n";
					userIn = false;
				}
			}
			loginScreen();
		}

		bool checkCredentials(std::string userName, std::string passWord, int* attempts, UserData& matchedUser) {
			for (const auto& user : userdata.getUserData())
			{
				if (user.getName() == userName && user.getPass() == passWord)
				{
					matchedUser = user;
					return true;
				}
			}
			std::cout << "Failed Login!" << std::endl;
			(*attempts)++;
			std::cout << 3 - *attempts << " attempts left" << std::endl;
			return false;
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

				UserData matchedUser("" ,"" ,"" , GUEST);
				if (checkCredentials(inputUser, inputPass, &attempts, matchedUser))
				{
					if (matchedUser.getRole() == ADMIN)
					{
						std::cout << "Admin Logged In\n";
						displayAdminScreen();
					}
					else if (matchedUser.getRole() == EMPLOYEE)
					{
						std::cout << "Employee Logged In\n";
						displayUsersScreen();
					}
					else if (matchedUser.getRole() == GUEST)
					{
						std::cout << "Guest Logged In\n";
						displayUsersScreen();
					}
					return;
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
