#D:\Program_Files\Python27

class StringEncryptor:
    """
    the object to store password
    """
##    _plnText
##    _cryText
    _key
    _encryptFunc
    _decryptFunc

    def __init__(self,key):
##        self._plnText = ""
##        self._cryText = ""
        self._key = key
        self._encryptFunc = None
        self._decryptFunc = None
        
    