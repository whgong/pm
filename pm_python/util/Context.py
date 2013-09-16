#D:\Program_Files\Python27
# -*- coding: gb2312 -*-

class ContextSensitive(object):
    """pm流程控制单元"""
    # __context
    def __init__(self):
        object.__init__(self)
        self.__context = dict()
        pass # the end of func ContextSensitive.__init__
    def __del__(self):
        del self.__context
        pass # the end of func ContextSensitive.__del__
    
    def getFromContext(self, name):
        return self.__context[name]
        pass # the end of func ContextSensitive.getFromContext
    
    def addToContext(self, name, content):
        self.__context[name] = content
        pass # the end of func ContextSensitive.addToContext

    def cloneContext(self):
        nCtxt = dict()
        for key, val in self.__context.items():
            nCtxt[key] = val
        pass # the end of func ContextSensitive.cloneContext

    def mergeContext(self, anotherContext):
        for key, val in anotherContext.items():
            self.__context[key] = val
        pass # the end of func ContextSensitive.mergeContext
    
    pass # the end of class ContextSensitive

