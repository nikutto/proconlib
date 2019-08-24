import sys
argvs = sys.argv
argc = len(argvs)

def message(msg):
    sys.stderr.write(msg)

def help():
    message("usage: "+argvs[0]+" <file>\n")
    
if argc==1:
    help()
    exit(0)

if argc>2:
    message("Confirm usage. See '"+ argvs[0] + " --help'.\n")
    exit(0)

if argc==2 and argvs[1]=="--help":
    help()
    exit(0)

target_name = argvs[1]

try:
    with open(target_name) as tf:
        target_lines = tf.readlines()
except:
    message("Failed to open target file.\n")
    exit(0)

import re

def expand_line(line,path):
    pattern = r'#include"*"'
    content = line[:-1]
    m = re.match(pattern,content)
    if not m: return line
    lib_name= (content[9:-1])
    try:
        with open(path+lib_name) as lib:
            ret=lib.readlines()
            
            relationalPath = lib_name
            while relationalPath and  relationalPath[-1]!='/' :
                relationalPath=relationalPath[:-1]
            res=expand_all(ret,path+relationalPath)
            message("Sucess : Expanded '" + content +"'.\n")                
            return res
    except Hoge:
        desp = "Warning : Failed to expand '" + content +"'.\n" 
        sys.stderr.write(desp)
        return line

def expand_all(lines,path):
    res=""
    for line in lines:
        ret=expand_line(line,path)
        res+=ret
    return res

res=expand_all(target_lines,"./")
print(res)

sys.stderr.write("Completed.\n")