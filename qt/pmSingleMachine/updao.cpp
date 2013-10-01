#include "updao.h"
#include<QMessageBox>
#include "utilconfig.h"
//#include "globalvariable.h"

pmsm::UPDao::UPDao()
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
    //create table tb_userpassword(objid integer primary key desc, objname text, username text, password text, decriptor text);
}

pmsm::UPDao::~UPDao(){
    sqlite3_close(this->db);
}

void pmsm::UPDao::createUserPassword(UserPassword up){
    QMessageBox mb;
    int rc;
    sqlite3_stmt *ppStmt = NULL;
    const char *sql;
    sql = "insert into tb_userpassword(objid,objname,username,password,decriptor)values(?,?,?,?,?);";

    rc = sqlite3_prepare_v2(this->db,sql,-1,&ppStmt,NULL);
    if(rc!=SQLITE_OK ){
        mb.setText("用户信息获取失败，请联系管理员！");//mb.setText(sqlite3_errmsg(this->db));
        mb.exec();
        goto Lb_exit;
    }
    rc = sqlite3_bind_int(ppStmt,1,up.getObjId());
    rc = sqlite3_bind_text(ppStmt,2,up.getObjName().c_str(),-1,NULL);
    rc = sqlite3_bind_text(ppStmt,3,up.getUserName().c_str(),-1,NULL);
    rc = sqlite3_bind_text(ppStmt,4,up.getPassword().c_str(),-1,NULL);
    rc = sqlite3_bind_text(ppStmt,5,up.getDecriptor().c_str(),-1,NULL);
    if(rc!=SQLITE_OK ){
        mb.setText("用户信息获取失败，请联系管理员！");
        mb.exec();
        goto Lb_exit;
    }
    rc = sqlite3_step(ppStmt);
    if(rc!=SQLITE_DONE && rc!=SQLITE_ROW){
        mb.setText("用户信息获取失败，请联系管理员！");
        mb.setText(QString(sqlite3_errmsg(db)));
        mb.exec();
        goto Lb_exit;
    }

Lb_exit:
    sqlite3_reset(ppStmt);
    sqlite3_finalize(ppStmt);
    return;
}

void pmsm::UPDao::removeUserPasswordById(long id){
    QMessageBox mb;
    int rc;
    sqlite3_stmt *ppStmt = NULL;
    const char *sql;
    sql = "delete from tb_userpassword where objid=?;";

    rc = sqlite3_prepare_v2(this->db,sql,-1,&ppStmt,NULL);
    if(rc!=SQLITE_OK ){
        mb.setText("用户信息获取失败，请联系管理员！");//mb.setText(sqlite3_errmsg(this->db));
        mb.exec();
        goto Lb_exit;
    }
    rc = sqlite3_bind_int(ppStmt,1,id);
    if(rc!=SQLITE_OK ){
        mb.setText("用户信息获取失败，请联系管理员！");
        mb.exec();
        goto Lb_exit;
    }
    rc = sqlite3_step(ppStmt);
    if(rc!=SQLITE_DONE && rc!=SQLITE_ROW){
        goto Lb_exit;
    }
Lb_exit:
    sqlite3_reset(ppStmt);
    sqlite3_finalize(ppStmt);
    return;
}

void pmsm::UPDao::removeUserPassword(UserPassword up){
    this->removeUserPasswordById(up.getObjId());
}

void pmsm::UPDao::modifyUserPassword(UserPassword up){
    QMessageBox mb;
    int rc;
    sqlite3_stmt *ppStmt = NULL;
    const char *sql;
    sql = "update tb_userpassword set objname=?,username=?,password=?,decriptor=? where objid = ?;";

    rc = sqlite3_prepare_v2(this->db,sql,-1,&ppStmt,NULL);
    if(rc!=SQLITE_OK ){
        mb.setText("用户信息获取失败，请联系管理员！");//mb.setText(sqlite3_errmsg(this->db));
        mb.exec();
        goto Lb_exit;
    }
    rc = sqlite3_bind_text(ppStmt,1,up.getObjName().c_str(),-1,NULL);
    rc = sqlite3_bind_text(ppStmt,2,up.getUserName().c_str(),-1,NULL);
    rc = sqlite3_bind_text(ppStmt,3,up.getPassword().c_str(),-1,NULL);
    rc = sqlite3_bind_text(ppStmt,4,up.getDecriptor().c_str(),-1,NULL);
    rc = sqlite3_bind_int(ppStmt,5,up.getObjId());
    if(rc!=SQLITE_OK ){
        mb.setText("用户信息获取失败，请联系管理员！");
        mb.exec();
        goto Lb_exit;
    }
    rc = sqlite3_step(ppStmt);
    if(rc!=SQLITE_DONE && rc!=SQLITE_ROW){
        goto Lb_exit;
    }
Lb_exit:
    sqlite3_reset(ppStmt);
    sqlite3_finalize(ppStmt);
    return;
}

std::vector<UserPassword *> *pmsm::UPDao::getAllUserPassword(){
    QMessageBox mb;
    std::vector<UserPassword *> *res;
    int rc;
    long objid;
    char *objnm, *usernm, *passwd, *desc;
    sqlite3_stmt *ppStmt = NULL;
    const char *sql;
    sql = "select objid, objname, username, password, decriptor from tb_userpassword;";
    rc = sqlite3_prepare_v2(this->db,sql,-1,&ppStmt,NULL);
    if(rc!=SQLITE_OK ){
        mb.setText("用户信息获取失败，请联系管理员！");//mb.setText(sqlite3_errmsg(this->db));
        mb.exec();
        goto Lb_exit;
    }
    res = new std::vector<UserPassword *>();
    rc = sqlite3_step(ppStmt);
    while(rc==SQLITE_ROW||rc==SQLITE_DONE){
        if(rc==SQLITE_DONE){
            break;
        }
        objid = sqlite3_column_int(ppStmt, 0);
        objnm = (char *)sqlite3_column_text(ppStmt, 1);
        usernm = (char *)sqlite3_column_text(ppStmt, 2);
        passwd = (char *)sqlite3_column_text(ppStmt, 3);
        desc = (char *)sqlite3_column_text(ppStmt, 4);
        res->push_back(new UserPassword(objid,std::string(objnm),std::string(usernm),std::string(passwd),std::string(desc)));
//        rc=sqlite3_reset(ppStmt);
        rc=sqlite3_step(ppStmt);
    }
Lb_exit:
    sqlite3_reset(ppStmt);
    sqlite3_finalize(ppStmt);
    return res;
}

UserPassword* pmsm::UPDao::getUserPasswordById(long id){
    QMessageBox mb;
    UserPassword * res;
    int rc;
    long objid;
    char *objnm, *usernm, *passwd, *desc;
    sqlite3_stmt *ppStmt = NULL;
    const char *sql;
    sql = "select objid, objname, username, password, decriptor from tb_userpassword where objid = ?;";
    rc = sqlite3_prepare_v2(this->db,sql,-1,&ppStmt,NULL);
    if(rc!=SQLITE_OK ){
        mb.setText("用户信息获取失败，请联系管理员！");//mb.setText(sqlite3_errmsg(this->db));
        mb.exec();
        goto Lb_exit;
    }

    rc = sqlite3_bind_int(ppStmt,5,id);
    if(rc!=SQLITE_OK ){
        mb.setText("用户信息获取失败，请联系管理员！");
        mb.exec();
        goto Lb_exit;
    }
    rc = sqlite3_step(ppStmt);
    if(rc!=SQLITE_DONE && rc!=SQLITE_ROW){
        goto Lb_exit;
    }
    objid = sqlite3_column_int(ppStmt, 0);
    objnm = (char *)sqlite3_column_text(ppStmt, 1);
    usernm = (char *)sqlite3_column_text(ppStmt, 2);
    passwd = (char *)sqlite3_column_text(ppStmt, 3);
    desc = (char *)sqlite3_column_text(ppStmt, 4);
    res = new UserPassword(objid,std::string(objnm),std::string(usernm),std::string(passwd),std::string(desc));

Lb_exit:
    sqlite3_reset(ppStmt);
    sqlite3_finalize(ppStmt);
    return res;
}
