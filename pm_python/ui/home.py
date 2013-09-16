#D:\Program_Files\Python27

from Tkinter import *
import ttk
from util.tkUitl import *
from util import Observe
import control.pmMsgRec
import util.Context

class HomePage(ttk.Frame, Observe.Observable, \
               util.Context.ContextSensitive):
    """"""
##    # data dict
##    __updict = None
##    # windows menu
##    __menubar = None
##    __menu_file = None
##    __menu_edit = None
##    # content table
##    __tree = None
##    # control button
##    __frm_btns = None
##    __btn_addnew = None
##    __btn_remove = None
##    __btn_modify = None
##    #search bar
##    __frm_search = None
##    __btn_search = None
##    __ety_search = None
    
    def __init__(self, master = None, msgrec = None, \
                 context = None, **kw):
        ttk.Frame.__init__(self, master, **kw)
        Observe.Observable.__init__(self)
        util.Context.ContextSensitive.__init__(self)
        
        self.__copyContext(context)

        self.__msgrec = control.pmMsgRec.pmMsgRec()
        self.addObserver(self.__msgrec)
        
        self.__createWidgets()
        self.__setEntryValue()
        self.__setLayout()
        self.__bindEvent()
        self.__selectedNodeId = None
        pass
    
    def __del__(self):
        ttk.Frame.__del__(self)
        Observe.Observable.__del__(self)
        util.Context.ContextSensitive.__del__(self)
        #del self.__updict
        pass
    
    def show(self):
        self.mainloop()
        pass
    
    def close(self):
        self.winfo_toplevel().destroy()
        pass

    def __copyContext(self, context):
        for key, value in context.items():
            self.addToContext(key, value)
        pass # the end of func HomePage.__copyContext

    def __createWidgets(self):
        """ """
        self.__menubar = Menu(master = self.winfo_toplevel())
        self.__menu_file = Menu(master = self.__menubar)
        self.__menu_edit = Menu(master = self.__menubar)
        self.__menubar.add_cascade(menu=self.__menu_file, label='File')
        self.__menubar.add_cascade(menu=self.__menu_edit, label='Edit')
##        self.__frm_btns = ttk.Frame(self)
        self.__btn_addnew = ttk.Button(master = self, text = "addNew")
        self.__btn_remove = ttk.Button(master = self, text = "remove")
        self.__btn_modify = ttk.Button(master = self, text = "modify")
##        self.__frm_search = ttk.Frame(self)
        self.__btn_search = ttk.Button(master = self, text = "search")
        self.__btn_clear = ttk.Button(master = self, text = "clear")
        self.__ety_search = ttk.Entry(master = self)
        
        self.__tree = self.__createContentTable()
        pass

    def __setEntryValue(self):
        self.__tsv_search =StringVar()
        self.__tsv_search.set("")
        self.__ety_search.configure(textvariable = self.__tsv_search)
        pass # the end of func AddNewPage.__setDefValue

    def __setLayout(self):
        """ """
        self.winfo_toplevel()['menu'] = self.__menubar
##        self.__menubar.grid(column = 0, row = 0) 
        self.__ety_search.grid(column = 0, row = 0, columnspan = 4, padx=3, pady=3, sticky = "NSEW")
        self.__btn_search.grid(column = 4, row = 0, padx=3, pady=3, sticky = "NSEW")
        self.__btn_clear.grid(column = 5, row = 0, padx=3, pady=3, sticky = "NSEW")
##        self.__frm_search.grid(column = 0, row = 0)
##        self.__tree.columnconfigure(4, weight = 3)
        self.__tree.grid(column = 0, row = 1, columnspan = 6, padx=3, pady=3, sticky = "NSEW")

        self.__btn_addnew.grid(column = 3, row = 2, padx=3, pady=3, sticky = "NSEW")
        self.__btn_remove.grid(column = 4, row = 2, padx=3, pady=3, sticky = "NSEW")
        self.__btn_modify.grid(column = 5, row = 2, padx=3, pady=3, sticky = "NSEW")
##        self.__frm_btns.grid(column = 0, row = 2)
        self.pack(fill="both",expand=True)
        pass

    def __createContentTable(self):
        """ """
        updict = self.getFromContext("updict")
        tree = tkTreeWidg(master = self,columns=(1,2,3,4), show="headings")
        tree.heading(1, text="object name")
        tree.heading(2, text="user name")
        tree.heading(3, text="password")
        tree.heading(4, text="descriptor")
##        tree.heading("object name", text="object name",command=lambda c="object name": sortby(tree, c, 0))
        for upid,up in updict.items():
            node = tkTreeWidg.rootNode(name = upid, \
                                       content = up.getUserPassword(), \
                                       type = None)
            tree.buildTree(node,'')
        return tree

    def refleshContentTable(self):
        updict = self.getFromContext("updict")
        self.__tree.clearTree()
        for upid,up in updict.items():
            node = tkTreeWidg.rootNode(name = upid, \
                                       content = up.getUserPassword(), \
                                       type = None)
            self.__tree.buildTree(node,'')
        pass # the end of func HomePage.refleshContentTable

    def __bindEvent(self):
        self.__btn_addnew.configure(command = (lambda x=1001 : self.__sendMessage(x)))
        self.__btn_remove.configure(command = (lambda x=1002 : self.__sendMessage(x)))
        self.__btn_modify.configure(command = (lambda x=1003 : self.__sendMessage(x)))
        self.__btn_search.configure(command = (lambda x=1004 : self.__sendMessage(x)))
        self.__btn_clear.configure(command = (lambda x=1005 : self.__sendMessage(x)))
##        self.bindTreeItemEvent()
        pass 

##    def bindTreeItemEvent(self):
##        for nid, node in self.__tree.nodeDict.items():
##            print nid, node
##            self.__tree.bindTreeNode(node, \
##                                     "<<TreeviewSelect>>",\
##                                     func = (lambda x = int(nid) : self.__selTreeNodeAction(x))\
##                                     )
##        pass # the end of func HomePage.__bindTreeItemEvent
##
##    def __selTreeNodeAction(self, nid):
##        print nid
##        self.__selectedNodeId = nid
##        print "selectedNodeId:",self.__selectedNodeId
##        pass # the end of func HomePage.__selTreeNodeAction

    def __sendMessage(self, msgCode):
        if msgCode == 1001:
            msgCtnt = {
                "Toplevel":Toplevel(self),
                "homePage":self
                }
            msg = Observe.pmMessage(msgCode,"addnew","HomePage","Control",msgCtnt)
        elif msgCode == 1002:
            if self.__tree.selection() == "" :
                return 
            selNodeId = self.__tree.selection()[0]
            upid = self.__tree.nodeDict[int(selNodeId)].nodeName
            msgCtnt = {
                "upid":upid,
                "homePage":self
                }
            msg = Observe.pmMessage(msgCode,"remove","HomePage","Control",msgCtnt)
        elif msgCode == 1003:
            if self.__tree.selection() == "" :
                return
            selNodeId = self.__tree.selection()[0]
            upid = self.__tree.nodeDict[int(selNodeId)].nodeName
            msgCtnt = {
                "upid":upid,
                "homePage":self,
                "Toplevel":Toplevel(self)
                }
            msg = Observe.pmMessage(msgCode,"modify","HomePage","Control",msgCtnt)
        elif msgCode == 1004:
            msgCtnt = {
                "searchword":self.__tsv_search.get(),
                "homePage":self
                }
            msg = Observe.pmMessage(msgCode,"search","HomePage","Control",msgCtnt)
        elif msgCode == 1005:
            msgCtnt = {
                "homePage":self
                }
            msg = Observe.pmMessage(msgCode,"clear","HomePage","Control",msgCtnt)
        self.publishMessage(msg)
        self.notifyObservers()
        pass # then end of func HomePage.__sendMessage
    
    
##if __name__ == "__main__":
##    from model.PMDataModel import UserPassword
##    from Tkinter import *
##    from ui.addnew import *
##    from ui.home import *
##
##    pm1 = UserPassword("a","b","c","d")
##    pm2 = UserPassword("a2","b2","c2","d2")
##    pm3 = UserPassword("a3","b3","c3","d3")
##    dict = {}
##    dict[1] = pm1
##    dict[2] = pm2
##    dict[3] = pm3
##    winm = Tk()
##    #home = HomePage(dict, master = winm)
##    #winc = Toplevel(winm)
##    home = HomePage(dict, master = winm)
##    home.show()
##    #winm.mainloop()
##    del home
##    pass
