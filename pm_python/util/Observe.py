#D:\Program_Files\Python27
# -*- coding: gb2312 -*-
#######################################################################
class Observable(object):
    """
    为对象实现受观察接口,直接继承使用
    def ClassName(Observable):
        pass
    """
    #__obs = set()
    #__msg = pmMessage()
    def __init__(self):
        self.__obs = set()
        self.__msg = None
        pass # the end of func Observable.__init__
    def __del__(self):
        del self.__msg
        del self.__obs
        pass # the end of func Observable.__del__
    def addObserver(self, observer):
        """向观察者目标中增加目标"""
        if self.__checkObserver(observer): raise ValueError("observer is not an instance of Observer")
        if observer == None:    return 
        if observer not in self.__obs:  self.__obs.add(observer)
        pass # the end of func Observable.addObserver

    def removeObserver(self, observer):
        """将目标从观察者队列中移除"""
        if self__.checkObserver(observer):  raise ValueError("observer is not an instance of Observer")
        if observer == None:    return 
        if observer in self.__obs:  self.__obs.remove(observer)
        pass # the end of func Observable.removeObserver

    def __checkObserver(self, observer):
        """内部方法 检查observer是否为"""
        return not isinstance(observer, Observer)
        pass # the end of func Observable.__checkObserver
    
    def notifyObservers(self, arg = None):
        """发出通知"""
        if(self.__msg==None):   return
        for o in self.__obs:    o.update(self.__msg, arg)
        self.__clearMessage()
        pass # the end of func Observable.notifyObservers
    
    def __clearMessage(self):
        """内部方法 清空消息"""
        self.__msg = None
        pass # the end of func Observable.__clearMessage
    
    #发布消息
    def publishMessage(self, message):
        """"""
        self.__msg = message
        pass # the end of func publishMessage

    pass #the end of class Observable

##############################################################################
class Observer(object):
    """为对象实现观察者接口"""
    def update(self, msg, arg=None):
        """收到消息后的回调方法,必须被子类override,否则抛出语法错误"""
        raise SyntaxError("please override the method update(msg, arg=None)")
        pass #the end of func Observer.update
    
    pass # the end of class Observer

##############################################################################
class pmMessage(object):
    """统一消息类型"""
    #__head = dict()
    #__content = list()
    def __init__(self, msgCode , msgTitle, usrFrom, usrTo, content):
        self.__head = {"from":usrFrom, "to":usrTo, "code":msgCode, "title":msgTitle}
        self.__content = content
        pass # the end of func pmMessage.__init__
    def getMsgCode(self):
        return self.__head["code"]
        pass # the end of func pmMessage.getMsgCode
    def getMsgTitle(self):
        return self.__head["title"]
        pass # the end of func pmMessage.getMsgTitle
    def getMsgTo(self):
        return self.__head["to"]
        pass # the end of func pmMessage.getMsgTo
    def getMsgFrom(self):
        return self.__head["from"]
        pass # the end of func pmMessage.getMsgFrom
    def getMsgContent(self):
        return self.__content
        pass # the end of func pmMessage.getMsgContent
    def __del__(self):
        del self.__head 
        del self.__content 
        pass # the end of func pmMessage.__del__
    
    def __str__(self):
        return "<[" \
               + "tilte=" + self.__head["title"] + ";" \
               + "from=" + self.__head["from"] + ";" \
               + "to=" + self.__head["to"] + ";" \
               + "code=" + str(self.__head["code"]) + ";" \
               + "]" + self.__content + ">"
        pass # the end of func pmMessage.__str__
    
    pass # the end of class pmMessage

##################################################################
if __name__ == "__main__" :
    msgContent = "hello world"
    msg = pmMessage(100,"hello","gong","chen",msgContent)
    print msg
    pass
