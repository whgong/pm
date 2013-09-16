#D:\Program_Files\Python27
# -*- coding: gb2312 -*-
#######################################################################
class Observable(object):
    """
    Ϊ����ʵ���ܹ۲�ӿ�,ֱ�Ӽ̳�ʹ��
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
        """��۲���Ŀ��������Ŀ��"""
        if self.__checkObserver(observer): raise ValueError("observer is not an instance of Observer")
        if observer == None:    return 
        if observer not in self.__obs:  self.__obs.add(observer)
        pass # the end of func Observable.addObserver

    def removeObserver(self, observer):
        """��Ŀ��ӹ۲��߶������Ƴ�"""
        if self__.checkObserver(observer):  raise ValueError("observer is not an instance of Observer")
        if observer == None:    return 
        if observer in self.__obs:  self.__obs.remove(observer)
        pass # the end of func Observable.removeObserver

    def __checkObserver(self, observer):
        """�ڲ����� ���observer�Ƿ�Ϊ"""
        return not isinstance(observer, Observer)
        pass # the end of func Observable.__checkObserver
    
    def notifyObservers(self, arg = None):
        """����֪ͨ"""
        if(self.__msg==None):   return
        for o in self.__obs:    o.update(self.__msg, arg)
        self.__clearMessage()
        pass # the end of func Observable.notifyObservers
    
    def __clearMessage(self):
        """�ڲ����� �����Ϣ"""
        self.__msg = None
        pass # the end of func Observable.__clearMessage
    
    #������Ϣ
    def publishMessage(self, message):
        """"""
        self.__msg = message
        pass # the end of func publishMessage

    pass #the end of class Observable

##############################################################################
class Observer(object):
    """Ϊ����ʵ�ֹ۲��߽ӿ�"""
    def update(self, msg, arg=None):
        """�յ���Ϣ��Ļص�����,���뱻����override,�����׳��﷨����"""
        raise SyntaxError("please override the method update(msg, arg=None)")
        pass #the end of func Observer.update
    
    pass # the end of class Observer

##############################################################################
class pmMessage(object):
    """ͳһ��Ϣ����"""
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
