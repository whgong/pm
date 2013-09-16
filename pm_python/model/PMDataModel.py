#D:\Program_Files\Python27

class UserPassword(object):
    """
    the object to store user and password
    """
##    __objid = None
##    __objname = None
##    __username = None
##    __password = None
##    __descriptor = None

    def __init__(self, objname, username, password, descriptor):
        object.__init__(self)
        self.__objname = objname
        self.__username = username
        self.__password = password
        self.__descriptor = descriptor

    def __str__(self):
        return self.__objname +","+ self.__username \
               +","+ self.__password +","+ self.__descriptor

    def __del__(self):
        """instance distory function"""
        del self.__objname
        del self.__username
        del self.__password
        del self.__descriptor

    def getObjname(self):
        return self.__objname
    def getUsername(self):
        return self.__username
    def getPassword(self):
        return self.__password
    def getDescriptor(self):
        return self.__descriptor
    def getUserPassword(self):
        return (self.getObjname(),self.getUsername()\
                ,self.getPassword(),self.getDescriptor())

##class StringEncryptor:
##    """
##    the object to store password
##    """
####    _plnText
####    _cryText
##    _key
##    _encryptFunc
##    _decryptFunc
##
##    def __init__(self,key):
####        self._plnText = ""
####        self._cryText = ""
##        self._key = key
##        self._encryptFunc = None
##        self._decryptFunc = None
        
    