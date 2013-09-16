#D:\Program_Files\Python27

from Tkinter import *
import ttk
from util.tkUitl import *

class HomePage(ttk.Frame):
    """"""
    # data dict
    __updict = None
    # windows menu
    __menubar = None
    __menu_file = None
    __menu_edit = None
    # content table
    __tree = None
    # control button
    __frm_btns = None
    __btn_addnew = None
    __btn_remove = None
    __btn_modify = None
    #search bar
    __frm_search = None
    __btn_search = None
    __ety_search = None
    
    def __init__(self, updict, master=None, **kw):
        ttk.Frame.__init__(self, master, **kw)
        self.__updict = updict
        self.__createWidgets()
        self.__setLayout()
        pass
##    def __del__(self):
##        pass
    def show(self):
        pass
##    def dispear(self):
##        pass
    def __createWidgets(self):
        """ """
        self.__menubar = Menu(master = self.winfo_toplevel())
        self.__menu_file = Menu(master = self.__menubar)
        self.__menu_edit = Menu(master = self.__menubar)
        self.__menubar.add_cascade(menu=self.__menu_file, label='File')
        self.__menubar.add_cascade(menu=self.__menu_edit, label='Edit')

##        self.__frm_btns = ttk.Frame(self)
        self.__btn_addnew = ttk.Button(self.__frm_btns,text = "addNew")
        self.__btn_remove = ttk.Button(self.__frm_btns,text = "remove")
        self.__btn_modify = ttk.Button(self.__frm_btns,text = "modify")

##        self.__frm_search = ttk.Frame(self)
        self.__btn_search = ttk.Button(self.__frm_search,text = "search")
        self.__ety_search = ttk.Entry(self.__frm_search)
        
        self.__tree = self.__createContentTable()
        pass
    
    def __setLayout(self):
        """ """
        self.winfo_toplevel()['menu'] = self.__menubar
##        self.__menubar.grid(column = 0, row = 0) 
        
        self.__ety_search.grid(column = 4, row = 0, padx=3, pady=3)
        self.__btn_search.grid(column = 5, row = 0, padx=3, pady=3)
##        self.__frm_search.grid(column = 0, row = 0)

##        self.__tree.columnconfigure(4, weight = 3)
        self.__tree.grid(column = 0, row = 1, columnspan = 6, padx=3, pady=3)

        self.__btn_addnew.grid(column = 3, row = 2, padx=3, pady=3)
        self.__btn_remove.grid(column = 4, row = 2, padx=3, pady=3)
        self.__btn_modify.grid(column = 5, row = 2, padx=3, pady=3)
##        self.__frm_btns.grid(column = 0, row = 2)
        
        pass

    def __createContentTable(self):
        """ """
        print self.__updict
        tree = tkTreeWidg(master = self,columns=(1,2,3,4), show="headings")
        tree.heading(1, text="object name")
        tree.heading(2, text="user name")
        tree.heading(3, text="password")
        tree.heading(4, text="descriptor")
##        tree.heading("object name", text="object name",command=lambda c="object name": sortby(tree, c, 0))
##        tree.heading("user name", text="user name",command=lambda c="user name": sortby(tree, c, 0))
##        tree.heading("password", text="password",command=lambda c="password": sortby(tree, c, 0))
##        tree.heading("descriptor", text="descriptor",command=lambda c="descriptor": sortby(tree, c, 0))
        for upid,up in self.__updict.items():
            node = tkTreeWidg.rootNode(name = upid, \
                                       content = up.getUserPassword(), \
                                       type = None)
            tree.buildTree(node,'')
        return tree
    