#D:\Program_Files\Python27

from model.PMDataModel import UserPassword
from Tkinter import *
##from ui.addnew import *
from ui.home import *
##from control import pmMsgRec
import model.PMDAO


##pm1 = UserPassword("a","b","c","d")
##pm2 = UserPassword("a2","b2","c2","d2")
##pm3 = UserPassword("a3","b3","c3","d3")
##dict = {}
##dict[1] = pm1
##dict[2] = pm2
##dict[3] = pm3

##msgrec = pmMsgRec.pmMsgRec()

dict = model.PMDAO.UserPasswordDAO().getUserPasswords()

winm = Tk()

home = HomePage(master = winm, context = {"updict":dict})

home.show()


#winm.mainloop()

##print dir(pm1)
##
##print pm1
#print str(pm1)
