import sys
argvs = sys.argv
argc = len(argvs)

def message(msg):
    sys.stderr.write(msg)

def help():
    message("usage: "+argvs[0]+" <file> " + "<# of files>"+"\n")
    
if argc==1 or argvs[1]=="--help":
    help()
    exit(0)

if argc==2 or argc>4:
    message("Confirm usage. See '"+ argvs[0] + " --help'.\n")
    exit(0)

name = argvs[1]
num = argvs[2]

isok=True
try:
    num=int(num)
except:
    isok=False

if (not isok) or num<0:
    message("Confirm usage. See '"+ argvs[0] + " --help'.\n")
    exit(0)


import shutil
import string
target_names=string.ascii_uppercase
for i in range(num):
    target_name=target_names[i]
    shutil.copyfile(name,target_name + ".cpp")

shutil.copyfile(name,"tmp.cpp")

