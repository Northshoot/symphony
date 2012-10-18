import os
import sys
import time
import string
import datetime
from subprocess import call
from shutil import copy2 as copyfile
from xml.etree import ElementTree as ET


class Ns3ToTosProxyGenerator:
    """
    Generates Ns3ToTosProxyGenerator.cc and Ns3ToTosProxyGenerator.h files
       from symphony.xml file
    """
    def __init__(self, xml_file):
        self.xml_file   = 'build/symphony.xml'
        self.cwd        = os.getcwd() + '/'
        self.text       = self.TextFolder()
        self.standart_xml = "src/symphony/helper/symphony.xml"
        self.header_name     = "src/symphony/model/ns3-to-tos-proxy_auto.h"
        self.cpp_name        = "src/symphony/model/ns3-to-tos-proxy_auto.cc"
        self.tree       = None
        self.root_element = None
        self.external_elements = None
        self.val_return = 0
        self.val_num_var = 1
        self.val_func_name = 2
        self.val_func_proto = 3
        self.var_name = string.ascii_lowercase
        self.val_class = "Ns3ToTosProxy::"
        self.functions = []
        self.typedefs = []
        self.checkLastModified()
     
    #we first check if there is a need to create new file
    def checkLastModified(self):
        self.header = open(self.cwd + self.header_name,'w')
        self.cpp  = open(self.cwd + self.cpp_name,'w')
        try:
            xml=open(self.xml_file, 'r')
            xml.close()
        except IOError:
            #no xml file so we prebuild with standart
            print "No file"
            self.xml_file = self.standart_xml
            copyfile(self.standart_xml, "build/")
        self.createProxy()
        
    #everything needs to be performed in order otherwise you will get bogus output
    def createProxy(self):
        self.readXML()
        self.makeFunctionsPrototypes()
        self.text.setTypeDef(self.typedefs)
        self.generateHeader()
        self.generateCpp()
        self.testGeneratedFiles()
    
    def testGeneratedFiles(self):
        exe = 'g++ -Wall -c ' + self.cpp_name
        return_code = call(exe, shell=True)
        if return_code !=0:
            print "Error compiling proxy!"
            sys.exit(1)
        else:
            rm=call('rm  ns3-to-tos-proxy_auto.o', shell=True)            
            if rm != 0:
                print "could not delete test object"
        print "Generated and successfully compiled proxy!"
        
    def readXML(self):
        try:
            self.tree = ET.parse(self.xml_file)
        except Exception, inst:
            print "Unexpected error opening %s: %s" % (self.xml_file, inst)
        return
    
    def generateHeader(self):
        header_ =  self.text.getHeaderStart()
        for f in self.functions:
            header_ += '\t\t' + f[self.val_return] + ' ' + f[self.val_func_proto] + ';\n'
        header_+="""
    ~Ns3ToTosProxy();
    void * getFunction(std::string name);
    std::map<std::string, void *> m_tos_functions;
"""            
        header_ += self.text.getHeaderClose()
        self.header.write(header_)
        self.header.close()
    
    def makeFunctionsPrototypes(self):
        for e in self.tree.iter("callback"):
            try:
                params = int(e.attrib['params'])
                function = []
                
                try:
                    funk_name = e.attrib['name']
                    t_def = 'typedef ' + str(e.attrib['return'])+ '(*tos'+funk_name+')('# int (*tosfunc)(int);
                except Exception, inst:
                    print "atr %s text %s errno %s" % (e.attrib['return'], funk_name, inst)
                function.append(e.attrib['return']) #num 0
                function.append(params) #num 1
                function.append(funk_name) #num 2 function name
                f_name = funk_name + '('
                for p in range(1,params+1):
                    f_n =  e.attrib['param'+str(p)]
                    t_def = t_def + f_n
                    f_name = f_name + f_n + ' ' + self.var_name[p]
                    if p is not params:
                        f_name = f_name + ' , '
                        t_def = t_def + ','
                f_name = f_name + ')'
                t_def = t_def + '); //typedef for tos function ' + f_name
                function.append(f_name) #num 3
                self.functions.append(function)
                self.typedefs.append(t_def)
            except ValueError:
                sys.exit(-1)

            

    
    def generateCpp(self):
        cpp = self.text.getCppStart()
        cpp += '\n'
        for f in self.functions:
            cpp += f[self.val_return] + '\n' 
            cpp += self.val_class + f[self.val_func_proto] + '\n'
            cpp += '{\n \t'
            if f[self.val_return] != 'void':
                cpp += 'return '
            cpp += '((tos'+ f[self.val_func_name] + ')m_tos_functions["' + f[self.val_func_name] + '"])('
            params = f[self.val_num_var]
            for p in range(1,params+1):
                           cpp += self.var_name[p]
                           if p is not params:
                               cpp += ' , '
            cpp += ');'
            
            cpp += '\n}\n'
        cpp+="""void* \nNs3ToTosProxy::getFunction(std::string name){
\treturn (void *)m_tos_functions[name]; \n}"""

        cpp += self.text.getCppEnd()
        self.cpp.write(cpp)
        self.cpp.close()
        
    

    
    class TextFolder:
        def __init__(self):
                self.datetime = str(datetime.date.today())
                self.typedef = None
        
        def getCppStart(self):
            part = self.getComment("ns3-to-tos-proxy.cc")
            part += """
#include <iostream>
#include "ns3-to-tos-proxy_auto.h"


Ns3ToTosProxy::Ns3ToTosProxy() {
    //m_tos_functions.set_empty_key("empty");
}            

void
Ns3ToTosProxy::addFunction(std::string name, void * pointer){
    m_tos_functions[name]=pointer;

}
          
            """
            return part
        
        def getCppEnd(self):
            part = """
Ns3ToTosProxy::~Ns3ToTosProxy() { }
"""                      
            return part
        
        def setTypeDef(self, typedef):
            self.typedefs = typedef
        
        def getComment(self, name):
            comment = """
/*
 * """      
            comment += name
            comment += """
 *
 *  Created on: Mars 20, 2011
 *      Author: laurynas
 *     Autogenerated on: """
            comment += self.datetime
            comment += """
 */
 """
            return comment
        
        def getHeaderStart(self):
            part = self.getComment("ns3-to-tos-proxy.h")
            part +="""

#ifndef NS3TOTOSPROXYAUTO_H_
#define NS3TOTOSPROXYAUTO_H_
#include <stdint.h>
#include <string>
#include <map>

"""
            for type in self.typedefs:
                part += type +' \n'
            
            part = part + '\n'
            part = part + """


class Ns3ToTosProxy {
    public:
        Ns3ToTosProxy();
        void addFunction(std::string name, void * pointer);
"""
            return part
        
        def getHeaderClose(self):
            return """
};

#endif /* NS3TOTOSPROXYAUTO_H_ */
"""
        
        
