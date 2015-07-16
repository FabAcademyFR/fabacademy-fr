import time
import ttk
from Tkinter import *
import sys
import glob
import serial
import tkMessageBox

Fabkit = serial.Serial()

def serial_ports():
    
    if sys.platform.startswith('win'):
        ports = ['COM' + str(i + 1) for i in range(256)]

    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
          ports = glob.glob('/dev/tty[A-Za-z]*')

    elif sys.platform.startswith('darwin'):
          ports = glob.glob('/dev/tty.*')

    else:
        raise EnvironmentError('Unsupported platform')

    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    return result

def serialCTRL():
    print("OK")
    dati = Fabkit.read(1)  
    print(dati)
    window.after(300, serialCTRL)  

def Connect():
    try:
        global Fabkit
        Fabkit = serial.Serial("COM4",9600,timeout=0)

    except (OSError, serial.SerialException):
        tkMessageBox.showerror("Error", "NO CONNECTION")
        
    window.after(1000, serialCTRL) 

def Dance(Command):
    global Fabkit
    arduino.write(Command)
    print "%s" % (Command)    
    return

def Forward(Command):
    global Fabkit
    arduino.write(Command)
    print "%s" % (Command)    
    return

def Backward(Command):
    global Fabkit
    arduino.write(Command)
    print "%s" % (Command)    
    return
    
def Stop(Command):
    global Fabkit
    arduino.write(Command)
    print "%s" % (Command)    
    return
        
def Right(Command):
    global Fabkit
    arduino.write(Command)
    print "%s" % (Command)    
    return
    
def Left(Command):
    global Fabkit
    arduino.write(Command)
    print "%s" % (Command)    
    return

def Exit ():
    window.destroy()
        
window = Tk ()
var = StringVar()

window.title('Control Intreface')


serialPort = serial_ports()
for name in serialPort:
    var.set(name)


button_6 = Button(text="EXIT", command=Exit, width = 10, borderwidth = 5, relief = GROOVE, fg="white", bg="#b9322b", font=("Helvetica",50)).grid(row=2, column=3)
button_7 = Button(text="COM",command=Connect, fg="white", width = 10, borderwidth = 5, relief = GROOVE, bg="#b9322b", font=("Helvetica",50)).grid(row=0, column=3)
button_8 = Button(text="DANCE",command= lambda:Dance('X'), fg="white", height = 5, width = 10, borderwidth = 5, relief = GROOVE, bg="#b9322b", font=("Helvetica",50)).grid(row=1, column=3)

button_1 = Button(text="F",command= lambda: Forward('A'), width = 10, borderwidth = 5, relief = GROOVE, bg="#3b5061", fg="white", font=("Helvetica",50)).grid(row=0, column=5)
button_2 = Button(text="B",command= lambda: Backward('B'), width = 10, borderwidth = 5, relief = GROOVE, bg="#3b5061", fg="white", font=("Helvetica",50)).grid(row=2, column=5)
button_3 = Button(text="STOP",command= lambda: Stop('S'), width = 10, height = 5, borderwidth = 5, relief = GROOVE, fg="white", bg="#3b5061", font=("Helvetica",50)).grid(row=1, column=5)
button_4 = Button(text="R",command= lambda: Right('D'), height = 5, borderwidth = 5, relief = GROOVE, bg="#3b5061", fg="white", font=("Helvetica",50)).grid(row=1, column=6, sticky=E)
button_5 = Button(text="L",command= lambda: Left('C'), height = 5, borderwidth = 5, relief = GROOVE, bg="#3b5061", fg="white", font=("Helvetica",50)).grid(row=1, column=4, sticky=W)

window.mainloop()


