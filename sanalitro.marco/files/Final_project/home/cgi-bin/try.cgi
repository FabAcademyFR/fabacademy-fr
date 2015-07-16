#!/usr/bin/env python
print "Content-type: text/html\n\n" #Header must be first printed line, or Internal Server Error (Apache must know content type to handle something

import cgi
import cgitb #Enable CGI Traceback, useful to see most python error in the browser (otherwise they go in apache error's log)
import serial

cgitb.enable()

try:
	sLink = serial.Serial('/dev/ttyAMA0', 9600) #Raspb UART (Not USB)
#	sLink = serial.Serial('/dev/ttyACM0', 9600)
	print "Connesso!"
except:
	print "Errore porta seriale"

form = cgi.FieldStorage() 
cmd = form["cmd"].value
if cmd == 'U':
	sLink.write(bytes(1))
elif cmd == "D":
	sLink.write(bytes(2))
elif cmd == "R":
	sLink.write(bytes(4))
elif cmd == "L":
	sLink.write(bytes(3))
elif cmd == "CW":
	sLink.write(bytes(6))
elif cmd == "CCW":
	sLink.write(bytes(5))
elif cmd == "TU":
	sLink.write(bytes(7))
elif cmd == "TD":
	sLink.write(bytes(8))
elif cmd == "H":
	sLink.write(bytes(9))

if sLink.isOpen():
	sLink.close()

print '<script type="text/javascript">'
print 'window.location.href = "../index.html"'
print '</script>'