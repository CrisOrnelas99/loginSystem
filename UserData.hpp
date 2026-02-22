//
// Created by Cris239 on 2/22/2026.
//

#ifndef LOGINSYSTEM_USERDATA_H
#define LOGINSYSTEM_USERDATA_H

#include <string>


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

	int getId() const
	{
		return userId;
	}
	std::string getName() const
	{
		return name;
	}
	std::string getHash() const
	{
		return hashedPass;
	}
	int getMFAKey() const
	{
		return mfaKey;
	}
	Role getRole() const
	{
		return role;
	}
};

#endif // LOGINSYSTEM_USERDATA_H
