#include "userpassword.h"
#include <ctime>
#include <iostream>

static time_t getStartTime();

UserPassword::UserPassword(std::string objNm, std::string userNm, std::string passwd, std::string desc)
{
    time_t t1;
    long ns;
    ns = time(&t1)-getStartTime();
//    std::cout<<"objid:"<<ns<<'\n';

    this->objName = objNm;
    this->userName = userNm;
    this->password = passwd;
    this->decriptor = desc;
    this->objId = ns;
}

UserPassword::UserPassword(int objid,std::string objNm, std::string userNm, std::string passwd, std::string desc){
    this->objName = objNm;
    this->userName = userNm;
    this->password = passwd;
    this->decriptor = desc;
    this->objId = objid;
}

static time_t getStartTime(){
    struct tm t;
    t.tm_year = 0;
    t.tm_yday = 1;
    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;
    return mktime(&t);
}

long UserPassword::getObjId(){
    return this->objId;
}

std::string UserPassword::getObjName(){
    return this->objName;
}

std::string UserPassword::getUserName(){
    return this->userName;
}

std::string UserPassword::getPassword(){
    return this->password;
}

std::string UserPassword::getDecriptor(){
    return this->decriptor;
}

void UserPassword::setObjName(std::string objnm){
    this->objName = objnm;
}

void UserPassword::setUserName(std::string usernm){
    this->userName = usernm;
}

void UserPassword::setPassword(std::string passwd){
    this->password = passwd;
}

void UserPassword::setDecriptor(std::string desc){
    this->decriptor = desc;
}

std::string UserPassword::toString(){
    return "UserPassword:{"
            //+std::string(this->getObjId())+","
            +this->getObjName()+","
            +this->getUserName()+","
            +this->getPassword()+","
            +this->getDecriptor()+"};";
}
