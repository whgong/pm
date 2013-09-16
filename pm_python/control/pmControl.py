#D:\Program_Files\Python27
# -*- coding: gb2312 -*-

import util.Context

class pmControl(util.Context.ContextSensitive):
    """pm流程控制单元"""
    # __context
    def __init__(self):
        util.Context.ContextSensitive.__init__(self)
        pass # the end of func pmControl.__init__
    def __del__(self):
        util.Context.ContextSensitive.__del__(self)
        pass # the end of func pmControl.__del__

##    def getFromContext(self, name):
##        return self.__context[name]
##        pass # the end of func pmControl.getFromContext
##    
##    def addToContext(self, name, content):
##        self.__context[name] = content
##        pass # the end of func pmControl.addToContext
    
    pass # the end of class pmControl

