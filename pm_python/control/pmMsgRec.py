#D:\Program_Files\Python27
# -*- coding: gb2312 -*-
from util import Observe
import homePageControl as homeCtrl
import addNewPageControl as anCtrl

class pmMsgRec(Observe.Observer):
    """pm消息接收、分发单元"""
##    def __init__():
##        pass # the end of func pmControl.__init__
    def update(self, msg, arg=None):
        code = msg.getMsgCode()
        frm = msg.getMsgFrom()
        # HomePage
        if code == 1001 and frm == "HomePage": #HomePage.addnew
            crtl = homeCtrl.homePageControl()
            crtl.mergeContext(msg.getMsgContent())
##            crtl.addToContext("Toplevel",msg.getMsgContent()["Toplevel"])
##            crtl.addToContext("homePage",msg.getMsgContent()["homePage"])
            crtl.addToContext("updict",dict())
            crtl.addnew_action()
        elif code == 1002 and frm == "HomePage": #HomePage.remove
            crtl = homeCtrl.homePageControl()
            crtl.mergeContext(msg.getMsgContent())
##            crtl.addToContext("upid",msg.getMsgContent()["upid"])
##            crtl.addToContext("homePage",msg.getMsgContent()["homePage"])
            crtl.remove_action()
        elif code == 1003 and frm == "HomePage": #HomePage.modify
            crtl = homeCtrl.homePageControl()
            crtl.mergeContext(msg.getMsgContent())
##            crtl.addToContext("Toplevel",msg.getMsgContent()["Toplevel"])
##            crtl.addToContext("upid",msg.getMsgContent()["upid"])
##            crtl.addToContext("homePage",msg.getMsgContent()["homePage"])
            crtl.modify_action()
        elif code == 1004 and frm == "HomePage": #HomePage.search
            crtl = homeCtrl.homePageControl()
            crtl.mergeContext(msg.getMsgContent())
            crtl.search_action()
        elif code == 1005 and frm == "HomePage": #HomePage.clear
            crtl = homeCtrl.homePageControl()
            crtl.mergeContext(msg.getMsgContent())
            crtl.clearSearch_action()
        # AddNewPage
        elif code == 2001 and frm == "AddNewPage": #AddNewPage.OK
            crtl = anCtrl.addNewPageControl()
            crtl.mergeContext(msg.getMsgContent())
##            crtl.addToContext("addNewWin",msg.getMsgContent()["addNewWin"])
##            crtl.addToContext("homePage",msg.getMsgContent()["homePage"])
##            crtl.addToContext("objnm",msg.getMsgContent()["objnm"])
##            crtl.addToContext("usrnm",msg.getMsgContent()["usrnm"])
##            crtl.addToContext("psswd",msg.getMsgContent()["psswd"])
##            crtl.addToContext("odesc",msg.getMsgContent()["odesc"])
            crtl.OK_action() 
        elif code == 2002 and frm == "AddNewPage": #AddNewPage.Cancel
            crtl = anCtrl.addNewPageControl()
            crtl.mergeContext(msg.getMsgContent())
##            crtl.addToContext("addNewWin",msg.getMsgContent()["addNewWin"])
            crtl.Cancel_action()
        pass # the end of func pmControl.update
    
    pass # the end of class pmControl

