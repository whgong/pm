#include <string>
#ifndef USERPASSWORD_H
#define USERPASSWORD_H

namespace pmmodel {
    class UserPassword;
}

class UserPassword
{
public:
    UserPassword(std::string objNm, std::string userNm, std::string passwd, std::string desc);
    UserPassword(int objid,std::string objNm, std::string userNm, std::string passwd, std::string desc);
    long getObjId();
    std::string getObjName();
    void setObjName(std::string *objnm);
    std::string getUserName();
    void setUserName(std::string *usernm);
    std::string getPassword();
    void setPassword(std::string *passwd);
    std::string getDecriptor();
    void setDecriptor(std::string *desc);
    std::string toString();

private:
    long objId;
    std::string objName;
    std::string userName;
    std::string password;
    std::string decriptor;
};

#endif // USERPASSWORD_H
