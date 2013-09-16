#D:\Program_Files\Python27
# -*- coding: gb2312 -*-

import pmControl
import model.PMDataModel
import model.PMDAO

class addNewPageControl(pmControl.pmControl):
    """addNewPage流程控制单元"""
    
    def OK_action(self):
        print "OK_action is trigged!"
        addNewWin = self.getFromContext("addNewWin")
        upid = self.getFromContext("upid")
        objnm = self.getFromContext("objnm")
        usrnm = self.getFromContext("usrnm")
        psswd = self.getFromContext("psswd")
        odesc = self.getFromContext("odesc")
        homePage = self.getFromContext("homePage")
        up = model.PMDataModel.UserPassword(objnm,usrnm,psswd,odesc)
        dao = model.PMDAO.UserPasswordDAO()
        if upid==None:
            dao.addUserPassword(up)
        else:
            dao.updateUserPassword(upid, up)
        updict = dao.getUserPasswords()
        homePage.addToContext("updict",updict)
        homePage.refleshContentTable()
        addNewWin.close()
        pass # the end of func addNewPageControl.OK_action

    def Cancel_action(self):
        print "Cancel_action is trigged!"
        addNewWin = self.getFromContext("addNewWin")
        addNewWin.close()
        pass # the end of func addNewPageControl.Cancel_action
    
    pass # the end of class addNewPageControl

