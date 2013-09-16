#D:\Program_Files\Python27
# -*- coding: gb2312 -*-

import logging
import Singleton
#import datetime

class Logger(Singleton.Singleton):
    """"""
    def __init__(self):
        logger = logging.getLogger('pm_application')
        logger.setLevel(logging.DEBUG)
        fh = logging.FileHandler('log.txt',mode = 'a')
        fmt = logging.Formatter('%(asctime)-15s [%(levelname)-10s] - %(message)s')
        fh.setFormatter(fmt)
        logger.addHandler(fh)
        self.__logger = logger
        pass # the end of func Logger.__init__

    def __del__(self):
        del self.__logger
        pass # the end of func Logger.__del__
    
    def debug(self, msg, *args, **kwargs):
        self.__logger.debug(msg, *args, **kwargs)
        pass
    def info(self, msg, *args, **kwargs):
        self.__logger.info(msg, *args, **kwargs)
        pass
    def warning(self, msg, *args, **kwargs):
        self.__logger.warning(msg, *args, **kwargs)
        pass
    def error(self, msg, *args, **kwargs):
        self.__logger.error(msg, *args, **kwargs)
        pass
    def critical(self, msg, *args, **kwargs):
        self.__logger.critical(msg, *args, **kwargs)
        pass

    pass # the end of class Logger

#moudle func
def debug(msg, *args, **kwargs):
    l = Logger.getInstance()
    l.debug(msg, *args, **kwargs)
    pass
def info(msg, *args, **kwargs):
    l = Logger.getInstance()
    l.info(msg, *args, **kwargs)
    pass
def warning(msg, *args, **kwargs):
    l = Logger.getInstance()
    l.warning(msg, *args, **kwargs)
    pass
def error(msg, *args, **kwargs):
    l = Logger.getInstance()
    l.error(msg, *args, **kwargs)
    pass
def critical(msg, *args, **kwargs):
    l = Logger.getInstance()
    l.critical(msg, *args, **kwargs)
    pass
    