#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <ctime>
//TODO create file for Admin to View. log with time all login, logout
// , failed login, add user, change credentials, remove user,

// Enum for user roles
enum UserRole { ADMIN, GUEST, CUSTOM, NONE };

// Struct to store a user's details
struct UserData {
    std::string username;
    std::string password;
    UserRole role;
};

// Function to check if a string contains special characters
bool specialChar(const std::string& checkString) {
    return checkString.find_first_of("!@#$%^&*()-_+=[]{}\\|:;'\"<>,.?/`~") != std::string::npos;
}

// Class for handling login operations
class LoginSystem {
    private:
        std::vector<UserData> users = {
            {"admin", "password123", UserRole::ADMIN},
            {"guest", "guestpass", UserRole::GUEST}
        };

        bool login = false;
        int userTries = 0;
        UserRole loggedInRole = UserRole::NONE;
        std::string loggedInUsername; // Store the logged-in username

    public:
        bool attemptLogin();
        void displayRole();
        void addUserRole();
        void removeUserRole();
        void showMenu();
        void changeOwnCredentials();
        void viewAndModifyUsers();
        void viewLog();

    };
#include <ctime>  // Required for time functions

void LoginSystem::displayRole() {
    if (loggedInRole == UserRole::ADMIN) {
        std::cout << "You have **Admin Privileges**. You can manage users, settings, and system security.\n";
    } else if (loggedInRole == UserRole::GUEST) {
        std::cout << "You have **Guest Access**. You can only view basic information.\n";
    } else if (loggedInRole == UserRole::CUSTOM) {
        std::cout << "You have **Custom Role Access**. You can perform specific tasks assigned by Admin.\n";
    } else {
        std::cout << "Error: No valid role assigned.\n";
    }
}

void logEvent(const std::string& username, const std::string& action) {
    std::ofstream logFile("SecurityLog.txt", std::ios::app);  // Append mode
    if (!logFile.is_open()) {
        std::cerr << "Error: Could not open log file.\n";
        return;
    }

    // Get current time
    std::time_t now = std::time(nullptr);
    char timestamp[30];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    // Write to log file
    logFile << "[" << timestamp << "] "
            << "[" << username << "] "
            << action << "\n";

    logFile.close();
}


//TODO open file when menu clicked

void LoginSystem::viewLog() {
    if (loggedInRole != UserRole::ADMIN) {
        std::cout << "Access Denied: Only Admin can view logs.\n";
        return;
    }

    std::ifstream logFile("SecurityLog.txt");
    if (!logFile.is_open()) {
        std::cerr << "Error: Could not open SecurityLog.txt\n";
        return;
    }

    std::string line;
    std::cout << "\n--- System Activity Log ---\n";
    while (std::getline(logFile, line)) {
        std::cout << line << "\n";
    }
    logFile.close();

    logEvent(loggedInUsername, "VIEWED LOG");
}

//TODO add view Log for admin
void LoginSystem::showMenu() {
    while (true)
        {
        if (loggedInRole == UserRole::ADMIN) {
            int choice;
            std::cout << "\n1. Add User Role\n2. Change Your Credentials\n3. View/Modify Users\n4. View System Log\n5. Remove User\n6. Logout\nChoose an option: ";

            std::cin >> choice;

            if (choice == 1) {
                addUserRole();
            } else if (choice == 2) {
                changeOwnCredentials();
            } else if (choice == 3) {
                viewAndModifyUsers();
            } else if (choice == 4) {
                viewLog();
            } else if (choice == 5) {
                removeUserRole();
            } else if (choice == 6) {
                std::cout << "Logging out...\n";
                login = false;
                loggedInRole = UserRole::NONE;
                logEvent(loggedInUsername, "LOGOUT");
                break;
            }
         else
            {
            std::cout << "Invalid choice. Try again.\n";
            }


        } else {
            std::cout << "\n1. Change Username/Password\n2. Logout\nChoose an option: ";
            int choice;
            std::cin >> choice;
            if (choice == 1) {
                changeOwnCredentials();
            } else {
                std::cout << "Logging out...\n";
                login = false;
                loggedInRole = UserRole::NONE;
                break;
            }
        }
    }
}
void LoginSystem::removeUserRole() {
    if (loggedInRole != UserRole::ADMIN) {
        std::cout << "Error: Only Admins can remove users!\n";
        return;
    }

    std::string adminPassword;
    std::cout << "Enter your Admin password to confirm: ";
    std::cin >> adminPassword;

    // Confirm it's the actual admin
    bool isVerified = false;
    for (const auto& user : users) {
        if (user.username == "admin" && user.password == adminPassword) {
            isVerified = true;
            break;
        }
    }

    if (!isVerified) {
        std::cout << "Access denied. Incorrect password.\n";
        return;
    }

    std::cout << "\n--- User Accounts ---\n";
    for (size_t i = 0; i < users.size(); ++i) {
        std::cout << i + 1 << ". Username: " << users[i].username << "\n";
    }

    int choice;
    std::cout << "\nEnter the number of the user to remove (0 to cancel): ";
    std::cin >> choice;

    if (choice <= 0 || choice > users.size()) {
        std::cout << "Operation cancelled.\n";
        return;
    }

    choice--; // zero-based index

    if (users[choice].username == "admin") {
        std::cout << "Error: You cannot remove the admin account!\n";
        return;
    }

    std::string removedUser = users[choice].username;
    users.erase(users.begin() + choice);
    std::cout << "User '" << removedUser << "' has been removed.\n";
    logEvent(loggedInUsername, "REMOVED USER: '" + removedUser + "'");
}


//TODO log any changes made
// Function to allow admin to add a new user role
void LoginSystem::addUserRole() {
    if (loggedInRole != UserRole::ADMIN) {
        std::cout << "Error: Only Admins can add new users!\n";
        return;
    }

    std::string newUsername, newPassword;

    std::cout << "\nEnter a new username: ";
    std::cin >> newUsername;

    if (specialChar(newUsername)) {
        std::cout << "Error: Username cannot contain special characters!\n";
        return;
    }

    for (const auto& user : users) {
        if (user.username == newUsername) {
            std::cout << "Error: Username already exists!\n";
            return;
        }
    }

    std::cout << "Enter a new password: ";
    std::cin >> newPassword;

    users.push_back({newUsername, newPassword, UserRole::CUSTOM});
    std::cout << "User '" << newUsername << "' has been added successfully!\n";
    logEvent(loggedInUsername, "ADDED USER: '" + newUsername + "'");

}
//TODO log any changes made
void LoginSystem::changeOwnCredentials() {
    std::string currentPassword, newUsername, newPassword;

    std::cout << "\nEnter your current password to verify: ";
    std::cin >> currentPassword;

    // **Find the logged-in user and update the stored data**
    for (auto& user : users) {
        if (user.username == loggedInUsername && user.password == currentPassword) {
            int choice;
            std::cout << "1. Change Username\n2. Change Password\nChoose an option: ";
            std::cin >> choice;

            if (choice == 1) {
                std::cout << "Enter new username: ";
                std::cin >> newUsername;

                if (specialChar(newUsername)) {
                    std::cout << "Error: Username cannot contain special characters!\n";
                    return;
                }

                for (const auto& existingUser : users) {
                    if (existingUser.username == newUsername) {
                        std::cout << "Error: Username already exists!\n";
                        return;
                    }
                }

                user.username = newUsername;
                loggedInUsername = newUsername;  // Update logged-in username
                std::cout << "Username updated successfully!\n";
                logEvent(loggedInUsername, "CHANGED USERNAME");

            }
            else if (choice == 2) {
                std::cout << "Enter new password: ";
                std::cin >> newPassword;

                user.password = newPassword;  // **Fix: Store the new password properly**
                std::cout << "Password updated successfully!\n";
                logEvent(loggedInUsername, "CHANGED PASSWORD");

            }
            else {
                std::cout << "Invalid choice.\n";
            }
            return;
        }
    }

    std::cout << "Error: Incorrect password!\n";
}

//TODO log any changes made
void LoginSystem::viewAndModifyUsers() {
    if (loggedInRole != UserRole::ADMIN) {
        std::cout << "Error: Only Admins can view and modify user accounts!\n";
        return;
    }

    // **Require Admin to Enter Their Own Password Before Proceeding**
    std::string adminPassword;
    std::cout << "\nEnter your Admin password to confirm: ";
    std::cin >> adminPassword;

    // **Find the Admin user and check the password**
    bool isAdminVerified = false;
    for (const auto& user : users) {
        if (user.username == "admin" && user.password == adminPassword) {
            isAdminVerified = true;
            break;
        }
    }

    if (!isAdminVerified) {
        std::cout << "Error: Incorrect Admin password! Access denied.\n";
        return;
    }
    logEvent(loggedInUsername, "VIEWED/MODIFIED USERS");

    std::cout << "\n--- User Accounts ---\n";
    for (size_t i = 0; i < users.size(); ++i) {
        std::cout << i + 1 << ". Username: " << users[i].username
                  << " | Role: " << (users[i].role == UserRole::ADMIN ? "Admin" :
                                     users[i].role == UserRole::GUEST ? "Guest" : "Custom") << "\n";
    }

    int choice;
    std::cout << "\nEnter the number of the user to modify (0 to cancel): ";
    std::cin >> choice;

    if (choice <= 0 || choice > users.size()) {
        std::cout << "Returning to menu...\n";
        return;
    }

    choice--; // Convert to zero-based index

    std::string newUsername, newPassword;
    int option;
    std::cout << "1. Change Username\n2. Change Password\nChoose an option: ";
    std::cin >> option;

    if (option == 1) {
        std::cout << "Enter new username: ";
        std::cin >> newUsername;

        if (specialChar(newUsername)) {
            std::cout << "Error: Username cannot contain special characters!\n";
            return;
        }

        for (const auto& existingUser : users) {
            if (existingUser.username == newUsername) {
                std::cout << "Error: Username already exists!\n";
                return;
            }
        }

        users[choice].username = newUsername;
        std::cout << "Username updated successfully!\n";
    }
    else if (option == 2) {
        std::cout << "Enter new password: ";
        std::cin >> newPassword;

        users[choice].password = newPassword;
        std::cout << "Password updated successfully!\n";
    }
    else {
        std::cout << "Invalid choice.\n";
    }
}


//TODO log any failed attemps and login.
bool LoginSystem::attemptLogin() {
    userTries = 0;

    while (!login && userTries < 3) {
        std::cout << "\nEnter username: ";
        std::cin >> loggedInUsername;

        if (specialChar(loggedInUsername)) {
            std::cout << "Error: Username cannot contain special characters!\n";
            userTries++;
            continue;
        }

        std::string loginPass;
        std::cout << "Enter password: ";
        std::cin >> loginPass;

        for (const auto& user : users) {
            if (user.username == loggedInUsername && user.password == loginPass) {
                std::cout << "Access Granted!\n";
                login = true;
                loggedInRole = user.role;
                logEvent(loggedInUsername, "LOGIN SUCCESS");
                return true;  // success
            }
        }

        userTries++;
        std::cout << "Access Denied: " << (3 - userTries) << " attempts left\n";
        logEvent(loggedInUsername, "FAILED LOGIN");

    }

    return false;  // locked out
}


//TODO any changes with the file handling here
int main() {
    LoginSystem loginSystem;

    while (true) {
        if (loginSystem.attemptLogin()) {
            loginSystem.displayRole();
            loginSystem.showMenu();
        } else {
            std::cout << "You have been locked out.\n";
            break;
        }
    }
    return 0;
}
