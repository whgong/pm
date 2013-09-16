#D:\Program_Files\Python27

##import model.PMDataModel
##from model.PMDataModel import UserPassword
from datetime import datetime
import pickle

class UserPasswordDAO(object):
##    __instance = None
##    @staticmethod
##    def getInstance():
##        if(PMDAO.__instance == None):
##            PMDAO.__instance = PMDAO()
##        return PMDAO.__instance
##    __datafile
##    __ddata

    def __init__(self):
        object.__init__(self)
        with open("data","r") as datafile:
            try:
                self.__ddata = pickle.load(datafile)
            except EOFError:
                self.__ddata = dict()
        pass # the end of func UserPasswordDAO.__init__

    def __def__(self):
        del __datafile
        pass # the end of func UserPasswordDAO.__def__
        
    def addUserPassword(self, upinfo):
        self.__ddata[datetime.now()] = upinfo
        with open("data","w") as datafile:
            pickle.dump(self.__ddata, datafile);
        pass # the end of func UserPasswordDAO.addUserPassword

    def getUserPasswords(self):
##        with open("data","r") as datafile:
##            self.__ddata = pickle.load(datafile)
        return self.__ddata
        pass # the end of func UserPasswordDAO.getUserPasswords

    def getFilteredUserPasswords(self, searchword):
##        with open("data","r") as datafile:
##            self.__ddata = pickle.load(datafile)
        filtered = dict()
        for key,val in self.__ddata.items():
            objname = val.getObjname()
            usrname = val.getUsername()
            desc = val.getDescriptor()
            if (searchword in str(objname)) or (searchword in str(usrname)) or (searchword in str(desc)):
                filtered[key] = val
        return filtered
        pass # the end of func UserPasswordDAO.getFilteredUserPasswords

    def getUserPasswordById(self, objid):
##        with open("data","r") as datafile:
##            self.__ddata = pickle.load(datafile)
        return self.__ddata[objid]
        pass # the end of func UserPasswordDAO.getUserPasswordById

    def updateUserPassword(self, objid, upinfo):
        self.__ddata[objid] = upinfo
        with open("data","w") as datafile:
            pickle.dump(self.__ddata, datafile);
        pass # the end of func UserPasswordDAO.updateUserPassword
        
    def deleteUserPasswordById(self, objid):
        del self.__ddata[objid]
        with open("data","w") as datafile:
            pickle.dump(self.__ddata, datafile);
        pass # the end of func UserPasswordDAO.deleteUserPasswordById

    def getUserPassword(self):
##        with open("data","r") as datafile:
##            self.__ddata = pickle.load(datafile)
        for up in self.__ddata.items():
            yield up(0),up(1)
        pass # the end of func UserPasswordDAO.getUserPassword

    pass # the end of class UserPasswordDAO

    
