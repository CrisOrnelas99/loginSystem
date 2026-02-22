//
// Created by Cris239 on 2/22/2026.
//

#ifndef LOGINSYSTEM_USERDATA_H
#define LOGINSYSTEM_USERDATA_H

#include <string>


enum class Role{Admin, Employee, Guest};

class UserData // Stores core account attributes.
{
	int userId;
	std::string name;
	std::string hashedPass;
	int mfaKey;	//other multifactor authentication method
	Role role;
    bool isLocked;

public:
	UserData( int i, std::string n, std::string h, int m, Role r) : // Builds a user record.
		userId( i ), name( n ), hashedPass( h ), mfaKey( m ), role( r ), isLocked(false) { }

	int getId() const // Returns unique user id.
	{
		return userId;
	}
	std::string getName() const // Returns username string.
	{
		return name;
	}
	std::string getHash() const // Returns password hash.
	{
		return hashedPass;
	}
	int getMFAKey() const // Returns MFA secret code.
	{
		return mfaKey;
	}
	Role getRole() const // Returns assigned role.
	{
		return role;
	}
};

#endif // LOGINSYSTEM_USERDATA_H
