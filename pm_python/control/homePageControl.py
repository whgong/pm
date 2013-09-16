#D:\Program_Files\Python27
# -*- coding: gb2312 -*-

import pmControl
from ui import addnew
import model.PMDataModel
import model.PMDAO

class homePageControl(pmControl.pmControl):
    """homePage流程控制单元"""
    
    def addnew_action(self):
        print "addnew_home_action is trigged!"
        toplevel = self.getFromContext("Toplevel")
        homePage = self.getFromContext("homePage")
        updict = self.getFromContext("updict")
        ctx = {
            "homePage":homePage,
            "updict":updict
            }
        an = addnew.AddNewPage(master = toplevel, context = ctx)
        an.show()
        pass # the end of func homePageControl.addnew_action

    def remove_action(self):
        print "remove_home_action is trigged!"
        homePage = self.getFromContext("homePage")
        upid = self.getFromContext("upid")
        dao = model.PMDAO.UserPasswordDAO()
        dao.deleteUserPasswordById(upid)
        updict = dao.getUserPasswords()
        homePage.addToContext("updict",updict)
        homePage.refleshContentTable()
        pass # the end of func homePageControl.remove_action

    def modify_action(self):
        print "modify_home_action is trigged!"
        toplevel = self.getFromContext("Toplevel")
        homePage = self.getFromContext("homePage")
        upid = self.getFromContext("upid")
        dao = model.PMDAO.UserPasswordDAO()
        up = dao.getUserPasswordById(upid)
        updict = {upid:up}
        ctx = {
            "homePage":homePage,
            "updict":updict
            }
        an = addnew.AddNewPage(master = toplevel, context = ctx)
        an.show()
        pass # the end of func homePageControl.modify_action

    def search_action(self):
        print "search_action is trigged!"
        homePage = self.getFromContext("homePage")
        searchword = self.getFromContext("searchword")
        dao = model.PMDAO.UserPasswordDAO()
        updict = dao.getFilteredUserPasswords(searchword)
        homePage.addToContext("updict",updict)
        homePage.refleshContentTable()
        pass # the end of func homePageControl.search_action

    def clearSearch_action(self):
        print "clearSearch_action is trigged!"
        homePage = self.getFromContext("homePage")
        dao = model.PMDAO.UserPasswordDAO()
        updict = dao.getUserPasswords()
        homePage.addToContext("updict",updict)
        homePage.refleshContentTable()
        pass # the end of func homePageControl.search_action

    pass # the end of class homePageControl

