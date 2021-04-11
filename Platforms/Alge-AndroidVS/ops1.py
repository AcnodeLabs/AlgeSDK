import os
import subprocess
import time
import string
import subprocess
import random

#output = subprocess.check_output("cat /etc/services", shell=True)

def get_stat():
    stat = subprocess.check_output("cd ..\.. && git pull && git log --pretty=oneline && cd Platforms\Alge-AndroidVS", shell=True)
    return str(stat)[:30]

def deploy(appname):
    os.system('adb usb && cd ..\.. && git pull && cd Platforms\Alge-AndroidVS && build-android.bat "com.acnodelabs.alge.'+appname+'" "'+appname+'" 1 27 landscape bcasper')

def stat_loop(appname,sec):
    oldstat = ''
    while(True):
        stat = get_stat()
        if (oldstat != stat):
            deploy(appname)
        oldstat = stat
        r = random.randint(0,16)
        print('Monitoring git , will deploy "'+appname+'".app on android on any change detected after roughly after '+str(sec+r)+' sec')
        time.sleep(sec+r)

stat_loop('Planets', 30)

