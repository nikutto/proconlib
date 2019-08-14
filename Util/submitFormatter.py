import sys
argvs = sys.argv
argc = len(argvs)

def help():
    desp = "usage: python3 compFormatter.py <file>\n"
    sys.stderr.write(desp)

if argc==1:
    help()
    exit(0)

if argc>2:
    desp = "Confirm usage. See 'python3 compFormatter.py --help'.\n"
    sys.stderr.write(desp)
    exit(1)

if argc==2 and argvs[1]=="--help":
    help()
    exit(0)

target_name = argvs[1]


try:
    with open(target_name) as tf:
        target_lines = tf.readlines()
except:
    desp = "Failed to open file.\n"
    sys.stderr.write(desp)        
    exit(1)

import re
def expand(line):
    pattern = r'#include"*"'
    content = line[:-1]
    m = re.match(pattern,content)
    if not m: return line
    lib_name= (content[9:-1])
    try:
        with open(lib_name) as lib:
            ret=lib.read()
            desp = "Sucess : Expanded '" + content +"'.\n"
            sys.stderr.write(desp)
            ret+="\n"
            return ret
    except:
        desp = "Warning : Failed to expand '" + content +"'.\n" 
        sys.stderr.write(desp)
        return line

res = ""
for line in target_lines:
    res+=expand(line)

print(res)

sys.stderr.write("Successfully completed.\n")