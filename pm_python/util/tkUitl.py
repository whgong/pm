#D:\Program_Files\Python27

#from Tkinter import *
import ttk

class tkTreeWidg(ttk.Treeview):
    """rebuild ttk:treeview"""
    class TreeNode(object):
        """tkTreeWidg's clild class. used to edit a tree"""
##        def __init__(self, name, content, type):
##            self.nId = hash(self)
##            self.nodeName = name
##            self.nodeContent = content
##            self.nodeType = type
##            self.children = list()
##            self.index = 0
##            self.item = None

        def __init__(self, name, content, type, index = 0):
            self.nId = hash(self)
            self.nodeName = name
            self.nodeContent = content
            self.nodeType = type
            self.children = list()
            self.index = index
            self.item = None
            
        def addChild(self, node):
            if isinstance(node, self.__class__):
                self.children.append(node)
                self.index = self.index + 1
                node.index = len(self.children)
            else :
                pass

##    nodeDict
    
    def __init__(self, master=None, **kw):
        ttk.Treeview.__init__(self, master, **kw)
        self.nodeDict = {}
        
    def buildTree(self, node, parentId):
        if node.children != None:
            if isinstance(node.nodeContent, tuple):
                self.insert(parent = parentId, \
                            index = node.index, iid=node.nId , \
##                            value = node.nId, \
                            values = node.nodeContent, \
                            tags = (node.nId) \
                            )
            elif isinstance(node.nodeName, str):
                self.insert(parent = parentId, \
                            index = node.index, iid=node.nId , \
##                            value = node.nId, \
                            text=node.nodeName, \
                            tags = (node.nId) \
                            )
            self.nodeDict[node.nId] = node

            for n in node.children:
                self.buildTree(n, node.nId)

    def bindTreeNode(self, node, seq, func):
        return self.tag_bind(node.nId, seq, func)

    def bindAllTreeNode(self, seq, func):
        for k1 in self.nodeDict.keys():
            self.bindTreeNode(self.nodeDict[k1], seq, func)

    def getNodeByItemId(self, nId):
        return self.nodeDict[nId]

    def clearTree(self):
        for nid in self.nodeDict.keys():
            tkTreeWidg.delete(self, nid)
            del self.nodeDict[nid]
        pass # the end of func tkTreeWidg.clearTree

    def removeTreeNode(self, nId):
        tkTreeWidg.delete(self, nid)
        del self.nodeDict[nid]
        pass # the end of func tkTreeWidg.removeTreeNode

    @staticmethod
    def rootNode(name, content, type):
        return tkTreeWidg.TreeNode(name, content, type)
