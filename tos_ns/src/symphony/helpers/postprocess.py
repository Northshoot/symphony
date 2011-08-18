#!/usr/bin/python
"""
/**
* File: setup.py
* Version: 1.0
* Description:post processing script
* 
* Author: Laurynas Riliskis
* E-mail: Laurynas.Riliskis@ltu.se
* Date:   April 28, 2010
*
* Copyright notice
*
* Copyright (c) Communication Networks, Lulea University of Technology.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
* 3. All advertising materials mentioning features or use of this software
*    must display the following acknowledgement:
*    This product includes software developed by the Communication Networks
*   Group at Lulea University of Technology.
* 4. Neither the name of the University nor of the group may be used
*    to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
* SUCH DAMAGE.
*/
"""
import sys
import os

if sys.version < '2.6':
    print "Too old python version."
    print "Please install python 2.6"
    raise SystemExit

pre = open('app.c', 'r')
post = open('post_app.c','w')

post.write("#ifdef __cplusplus\n \
 extern \"C\" { \n \
 #endif \n")

pre_lines=pre.readlines()

for line in pre_lines:
    if "typedef uint8_t bool" in line:
        pass
    elif "FALSE = 0, TRUE = 1" in line:
        post.write(line);
    elif "TRUE" in line:        
        post.write(line.replace("TRUE","true"))
    elif "FALSE" in line:
        post.write(line.replace("FALSE","false"))   
    else:
        post.write(line)
    
post.write(" #ifdef __cplusplus \n \
 } \n \
 #endif \n")

pre.close()
post.close()
