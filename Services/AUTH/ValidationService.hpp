#ifndef LOGINSYSTEM_VALIDATIONSERVICE_HPP
#define LOGINSYSTEM_VALIDATIONSERVICE_HPP

#include <cctype>
#include <iostream>
#include <limits>
#include <string>

class ValidationService // Validates raw user input fields.
{
public:
    std::string validateUsername() // Validates username formatting rules.
    {
        std::string username;

        while (true)
        {
            std::getline(std::cin >> std::ws, username);

            bool validChars = true;

            for (int index = 0; index < username.length(); index++)
            {
                char ch = username[index];

                bool isLower = (ch >= 'a' && ch <= 'z');
                bool isUpper = (ch >= 'A' && ch <= 'Z');
                bool isDigit = (ch >= '0' && ch <= '9');
                bool isSpecial = (ch == '_' || ch == '.');

                if (!(isLower || isUpper || isDigit || isSpecial))
                {
                    validChars = false;
                    break;
                }
            }

            if (username.length() == 0)
                std::cerr << "Invalid Input! Username cannot be empty.\n";

            else if (username.length() < 3 || username.length() > 20)
                std::cerr << "Invalid Input! Username must be 3-20 characters.\n";

            else if (username[0] == ' ' || username[username.length() - 1] == ' ')
                std::cerr << "Invalid Input! No leading/trailing spaces.\n";

            else if (!validChars)
                std::cerr << "Invalid Input! Use letters, numbers, '_' or '.'.\n";

            else
                break;
        }

        return username;
    }

    std::string validatePassword() // Validates password strength rules.
    {
        std::string password;

        while (true)
        {
            std::getline(std::cin >> std::ws, password);

            bool hasUpper = false;
            bool hasLower = false;
            bool hasDigit = false;
            bool hasSymbol = false;
            bool hasSpace = false;

            for (int index = 0; index < password.length(); index++)
            {
                char ch = password[index];

                if (ch >= 'A' && ch <= 'Z')
                    hasUpper = true;
                else if (ch >= 'a' && ch <= 'z')
                    hasLower = true;
                else if (ch >= '0' && ch <= '9')
                    hasDigit = true;
                else if (ch == ' ')
                    hasSpace = true;
                else
                    hasSymbol = true;
            }

            if (password.length() < 8)
                std::cerr << "Invalid Input! Password must be at least 8 chars.\n";

            else if (hasSpace)
                std::cerr << "Invalid Input! Password cannot contain spaces.\n";

            else if (!(hasUpper && hasLower && hasDigit && hasSymbol))
                std::cerr << "Invalid Input! Need upper, lower, number, symbol.\n";

            else if (password == "password" || password == "12345678" || password == "qwerty123")
                std::cerr << "Invalid Input! Password is too common.\n";

            else
                break;
        }

        return password;
    }

    std::string validateMFACode() // Validates MFA code digits.
    {
        std::string code;

        while (true)
        {
            std::getline(std::cin >> std::ws, code);

            bool digitsOnly = true;

            for (int index = 0; index < code.length(); index++)
            {
                if (code[index] < '0' || code[index] > '9')
                {
                    digitsOnly = false;
                    break;
                }
            }

            if (!digitsOnly)
                std::cerr << "Invalid Input! Digits only.\n";

            else if (code.length() != 6)
                std::cerr << "Invalid Input! Enter exactly 6 digits.\n";

            else
                break;
        }

        return code;
    }

    char validateMenuOptionChar() // Validates single-char menu option.
    {
        char option;

        while (true)
        {
            if (!(std::cin >> option))
                std::cerr << "Invalid Input! Enter valid character.\n";

            else if (std::cin.peek() != '\n')
                std::cerr << "Invalid Input! Extra characters not allowed.\n";

            else if (option != 'A' && option != 'B' && option != 'C')
                std::cerr << "Invalid Input! Enter A, B, or C.\n";

            else
                break;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        return option;
    }

    int validateMenuOptionInt() // Validates numeric menu option.
    {
        int option;

        while (true)
        {
            if (!(std::cin >> option))
                std::cerr << "Invalid Input! Enter a valid integer.\n";

            else if (std::cin.peek() != '\n')
                std::cerr << "Invalid Input! No extra characters allowed.\n";

            else if (option < 1 || option > 9)
                std::cerr << "Invalid Input! Option out of range.\n";

            else
                break;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        return option;
    }

    char validateRoleInput() // Validates role choice input.
    {
        char roleType;

        while (true)
        {
            if (!(std::cin >> roleType))
                std::cerr << "Invalid Input! Enter valid character.\n";

            else if (std::cin.peek() != '\n')
                std::cerr << "Invalid Input! Extra characters not allowed.\n";

            else if (roleType >= 'a' && roleType <= 'z')
                roleType = roleType - 32;

            if (roleType != 'A' && roleType != 'E' && roleType != 'G')
                std::cerr << "Invalid Input! Enter A, E, or G.\n";
            else
                break;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        return roleType;
    }

    int validateUserId() // Validates positive user identifier.
    {
        int userId;

        while (true)
        {
            if (!(std::cin >> userId))
                std::cerr << "Invalid Input! Enter a valid integer.\n";

            else if (std::cin.peek() != '\n')
                std::cerr << "Invalid Input! No extra characters allowed.\n";

            else if (userId <= 0 || userId > 1000000)
                std::cerr << "Invalid Input! User ID out of range.\n";

            else
                break;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        return userId;
    }

    char validateYesNo() // Validates yes or no input.
    {
        char answer;

        while (true)
        {
            if (!(std::cin >> answer))
                std::cerr << "Invalid Input! Enter y or n.\n";

            else if (std::cin.peek() != '\n')
                std::cerr << "Invalid Input! Extra characters not allowed.\n";

            else
            {
                if (answer >= 'a' && answer <= 'z')
                    answer = answer - 32;

                if (answer == 'Y' || answer == 'N')
                    break;
                else
                    std::cerr << "Invalid Input! Enter y or n.\n";
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        return answer;
    }
};

#endif // LOGINSYSTEM_VALIDATIONSERVICE_HPP
