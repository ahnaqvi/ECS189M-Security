import os
filelist = os.listdir("C:/Users/ahnaqvi/classes/ecs189m/python_virus")
SIGNATURE = "CRANKLIN PYTHON VIRUS"
for fname in filelist:
    if SIGNATURE in open(fname).read():
        print(fname)