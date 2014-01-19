#include "utilconfig.h"
#include<fstream>
#include<iostream>
#include<string.h>
#include "globalvariable.h"

static void dealConfigFile(std::ifstream *ifs, std::map<std::string, std::string> * res){
    char * tmpstr, *key, *value;
    tmpstr = new char[256];

    while(ifs->eof()!=true){
        ifs->getline(tmpstr,256);
        key = strtok(tmpstr,"=");
        value = strtok(NULL,";");
        if(key!=NULL){
            res->insert(std::pair<std::string,std::string>(std::string(key),std::string(value)));
        }
    }
}

std::map<std::string, std::string> * UtilConfig::loadConfig(){
    std::map<std::string, std::string> * res;
    std::ifstream *ifs;
    try{
        res = new std::map<std::string, std::string>();
        if(res==NULL)throw -1;
        ifs = new std::ifstream("config.ini", std::ifstream::in);
        if(ifs->good()!=true)throw -2;

        dealConfigFile(ifs,res);
    }
    catch(int errcd){
        if(errcd==-1){
            std::cout<<"内存分配失败"<<std::endl;
        }
        else if(errcd==-2){
            std::cout<<"文件打开失败"<<std::endl;
            delete res;
        }
        return NULL;
    }
    ifs->close();
    return res;
}

std::string UtilConfig::getConfValueByKey(std::string key){
    std::map<std::string, std::string>::iterator it;
    std::string mkey;
    for(it=cfg->begin();it!=cfg->end();it++){
        if(key.compare(it->first)==0){
            return it->second;
        }
    }
    return "";
}
