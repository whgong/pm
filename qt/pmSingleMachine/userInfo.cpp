#include "userinfo.h"

UserInfo::UserInfo()
{
}

long UserInfo::getUsrid(){
    return this->userid;
}

std::string UserInfo::getUsrnm(){
    return this->username;
}

std::string UserInfo::getPasswd(){
    return this->password;
}

void UserInfo::setUsrnm(std::string nm){
    this->username = nm;
}

void UserInfo::setPasswd(std::string pwd){
    this->password = pwd;
}
