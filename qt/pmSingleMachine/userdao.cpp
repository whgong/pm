#include "userdao.h"
#include<string.h>
#include<iostream>
#include<QMessageBox>
#include"utilconfig.h"
//#include "globalvariable.h"

UserDAO::UserDAO()
{
    QMessageBox mb;
    sqlite3 *db;
    int rc;
    rc = sqlite3_open(UtilConfig::getConfValueByKey("sqlite_file_name").c_str(),&db);
    if(rc!=SQLITE_OK){
        mb.setText("资源库连接失败，请联系管理员！");
        mb.exec();
        sqlite3_close(db);
    }
    this->db = db;
    //create table user(id integer primary key desc, username text, password text);
    //insert into user(id, username, password)values(1,'rake','qqq111=');
}

UserDAO::~UserDAO(){
    sqlite3_close(this->db);
}

void UserDAO::addNewUser(UserInfo u){
    std::string sql;
    sql = "insert into user(id, username, password)values() ";
    u.getPasswd();
}

bool UserDAO::validUserByNamePasswd(std::string nm, std::string pwd){
    QMessageBox mb;
    bool res = false;
    int rc;
    sqlite3_stmt *ppStmt = NULL;
    const char *sql;
    char *r_un, *r_pwd;
    sql = "SELECT username,password FROM user WHERE username=? AND password=?;";

    rc = sqlite3_prepare_v2(this->db,sql,-1,&ppStmt,NULL);
    if(rc!=SQLITE_OK ){
//        mb.setText(sqlite3_errmsg(this->db));
        mb.setText("用户信息获取失败，请联系管理员！");
        mb.exec();
        return false;
    }
    rc = sqlite3_bind_text(ppStmt,1,nm.c_str(),-1,NULL);
    rc = sqlite3_bind_text(ppStmt,2,pwd.c_str(),-1,NULL);
    if(rc!=SQLITE_OK ){
        mb.setText("用户信息获取失败，请联系管理员！");
        mb.exec();
        return false;
    }
    rc = sqlite3_step(ppStmt);
    if(rc!=SQLITE_DONE && rc!=SQLITE_ROW){
        return false;
    }
    r_un = (char *)sqlite3_column_text(ppStmt, 0);
    r_pwd = (char *)sqlite3_column_text(ppStmt, 1);

    if(r_un!=NULL&&r_pwd!=NULL)res=true;
    sqlite3_reset(ppStmt);
    sqlite3_finalize(ppStmt);
    return res;
}
