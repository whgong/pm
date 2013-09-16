#D:\Program_Files\Python27
# -*- coding: gb2312 -*-

class Singleton(object):
    """"""
    @classmethod
    def getInstance(cls):
        """"""
        try :
            inst = cls.__instance
        except AttributeError:
            cls.__instance = cls()
            inst = cls.__instance
        return inst
        pass # the end of func Singleton.getInstance
    pass # the end of class Singleton