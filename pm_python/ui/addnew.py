#D:\Program_Files\Python27
# -*- coding: gb2312 -*-

from Tkinter import *
import ttk
from util import Observe
import control.pmMsgRec
##from util.tkUitl import *
import util.Context

class AddNewPage(ttk.Frame, Observe.Observable, \
                 util.Context.ContextSensitive):
    """"""
##    __label_objnm = None
##    __entry_objnm = None
##    __label_usernm = None
##    __entry_usernm = None
##    __label_passwd = None
##    __entry_passwd = None
##    __label_desc = None
##    __entry_desc = None
##    __btn_ok = None
##    __btn_cancel = None
    
    def __init__(self, master=None, msgrec = None, \
                 context = None, **kw):
        Observe.Observable.__init__(self)
        self.__msgrec = control.pmMsgRec.pmMsgRec()
        self.addObserver(self.__msgrec)

        util.Context.ContextSensitive.__init__(self)
        self.__copyContext(context)
        #self.__updict = updict

        ttk.Frame.__init__(self, master, **kw)
        self.__createWidgets()
        
        self.__setEntryValue()
        self.__setLayout()
        self.__bindEvent()
        #self.__win = master
        pass # the end of func AddNewPage.__init__
    
    def __del__(self):
        ttk.Frame.__del__(self)
        Observe.Observable.__del__(self)
        del self.__updict
##        self.destroy()
        pass # the end of func AddNewPage.__del__
    
    def show(self):
        self.mainloop()
        pass # the end of func AddNewPage.show
    
    def close(self):
        self.winfo_toplevel().destroy()
        pass # the end of func AddNewPage.close

    def __copyContext(self, context):
        for key, value in context.items():
            self.addToContext(key, value)
        pass # the end of func AddNewPage.__copyContext
    
    def __createWidgets(self):
        """ """
        self.__label_objnm = ttk.Label(master = self, text = "Object Name:")
        self.__entry_objnm = ttk.Entry(master = self)

        self.__label_usernm = ttk.Label(master = self, text = "User Name:  ")
        self.__entry_usernm = ttk.Entry(master = self)

        self.__label_passwd = ttk.Label(master = self, text = "Password:   ")
        self.__entry_passwd = ttk.Entry(master = self)

        self.__label_desc = ttk.Label(master = self, text = "Descriptor: ")
        self.__entry_desc = ttk.Entry(master = self)

        self.__btn_ok = ttk.Button(master = self, text = "     OK     ")
        self.__btn_cancel = ttk.Button(master = self, text = "   Cancel   ")

        pass # the end of func AddNewPage.__createWidgets

    def __setEntryValue(self):
        updict = self.getFromContext("updict")
        if len(updict) > 0 :
            self.__upid = updict.items()[0][0]
            up = updict.items()[0][1]
            up1 = up.getObjname()
            up2 = up.getUsername()
            up3 = up.getPassword()
            up4 = up.getDescriptor()
        else :
            self.__upid = None
            up1 = ""
            up2 = ""
            up3 = ""
            up4 = ""
        self.__tsv_objnm =StringVar()
        self.__tsv_objnm.set(up1)
        self.__entry_objnm.configure(textvariable = self.__tsv_objnm)
        self.__tsv_usrnm =StringVar()
        self.__tsv_usrnm.set(up2)
        self.__entry_usernm.configure(textvariable = self.__tsv_usrnm)
        self.__tsv_psswd =StringVar()
        self.__tsv_psswd.set(up3)
        self.__entry_passwd.configure(textvariable = self.__tsv_psswd)
        self.__tsv_odesc =StringVar()
        self.__tsv_odesc.set(up4)
        self.__entry_desc.configure(textvariable = self.__tsv_odesc)
        pass # the end of func AddNewPage.__setDefValue

    def __setLayout(self):
        """ """
        self.__label_objnm.grid(column = 0, row = 0, padx = 3, pady = 3) 
        self.__entry_objnm.grid(column = 1, row = 0, padx = 3, pady = 3) 
        self.__label_usernm.grid(column = 0, row = 1, padx = 3, pady = 3) 
        self.__entry_usernm.grid(column = 1, row = 1, padx = 3, pady = 3) 
        self.__label_passwd.grid(column = 0, row = 2, padx = 3, pady = 3) 
        self.__entry_passwd.grid(column = 1, row = 2, padx = 3, pady = 3) 
        self.__label_desc.grid(column = 0, row = 3, padx = 3, pady = 3) 
        self.__entry_desc.grid(column = 1, row = 3, padx = 3, pady = 3) 
        self.__btn_ok.grid(column = 0, row = 4, padx = 3, pady = 3) 
        self.__btn_cancel.grid(column = 1, row = 4, padx = 3, pady = 3)
        self.pack(padx = 10, pady = 10)
        pass # then end of func AddNewPage.__setLayout

    def __bindEvent(self):
        self.__btn_ok.configure(command = (lambda x=2001 : self.__sendMessage(x)))
        self.__btn_cancel.configure(command = (lambda x=2002 : self.__sendMessage(x)))
        pass # the end of func AddNewPage.__bindEvent

    def __sendMessage(self, msgCode):
        if msgCode == 2001:
            msgCtnt = {
                "addNewWin":self,
                "homePage":self.getFromContext("homePage"),
                "upid":self.__upid,
                "objnm":self.__tsv_objnm.get(),
                "usrnm":self.__tsv_usrnm.get(),
                "psswd":self.__tsv_psswd.get(),
                "odesc":self.__tsv_odesc.get()
                }
            msg = Observe.pmMessage(msgCode,"OK","AddNewPage","Control",msgCtnt)
        elif msgCode == 2002:
            msg = Observe.pmMessage(msgCode,"Cancel","AddNewPage","Control",{"addNewWin":self})
        self.publishMessage(msg)
        self.notifyObservers()
        pass # the end of func AddNewPage.__sendMessage

    pass # the end of class AddNewPage

if __name__ == "__main__":
##    from model.PMDataModel import UserPassword
##    from Tkinter import *
##    from ui.addnew import *
##    from ui.home import *

##    pm1 = UserPassword("a","b","c","d")
##    pm2 = UserPassword("a2","b2","c2","d2")
##    pm3 = UserPassword("a3","b3","c3","d3")
    dict = {}
##    dict[1] = pm1
##    dict[2] = pm2
##    dict[3] = pm3
    winm = Tk()
    #home = HomePage(dict, master = winm)
    #winc = Toplevel(winm)
    addnew = AddNewPage(dict, master = winm)
    addnew.show()
    #winm.mainloop()
    del addnew
    pass
