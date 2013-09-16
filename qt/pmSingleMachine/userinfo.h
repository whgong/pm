#include<string>

#ifndef USERINFO_H
#define USERINFO_H

namespace pmmodel {
    class UserInfo;
}

class UserInfo
{
public:
    UserInfo();
    UserInfo(std::string usrnm, std::string passwd);
    long getUsrid();
    std::string getUsrnm();
    std::string getPasswd();
    void setUsrnm(std::string nm);
    void setPasswd(std::string pwd);

private:
    long userid;
    std::string username;
    std::string password;
};

#endif // USERINFO_H
