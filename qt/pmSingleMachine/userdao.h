#include"userinfo.h"
#include"string"
#include "sqlite3.h"

#ifndef USERDAO_H
#define USERDAO_H

namespace pmdao {
    class UserDAO;
}

class UserDAO
{
public:
    UserDAO();
    ~UserDAO();

    void addNewUser(UserInfo u);

    void removeUser(UserInfo u);
    void removeUserById(long uid);

    void modifyUser(UserInfo u);

    bool validUserByNamePasswd(std::string nm, std::string pwd);

private:
    sqlite3* db;
};

#endif // USERDAO_H
