from firebase import firebase
import serial
import time

# the generated root for your project
FIREBASE_ROOT = 'https://sound-guided-car.firebaseio.com'
# init Firebase Database instance
firebase = firebase.FirebaseApplication(FIREBASE_ROOT, None)
firebase.put('location','position','Default')

print("Start")
port="/dev/rfcomm0" #This will be different for various devices and on windows it will probably be a COM port.
bluetooth=serial.Serial(port, 9600)#Start communications with the bluetooth unit
print("Connected")
while 1 : 
	bluetooth.flushInput() #This gives the bluetooth a little kick
	 #send 5 groups of data to the bluetooth
	print("Ping")
	time.sleep(1)
	bluetooth.write(b"A")#These need to be bytes not unicode, plus a number
	print("A sent")
	#bluetooth.write(b'F')
	#time.sleep(5)
	#bluetooth.write(b'S')
	#time.sleep(5)
	#bluetooth.write(b'L')
	#time.sleep(5)
	input_data=bluetooth.readline()
	i=-1
	m=[0,0,0]
	while input_data.find("Done") :
		#This reads the incoming data
		i=i+1
		m[i]=input_data.decode()
		print(m[i])#These are bytes coming in so a decode is needed
		time.sleep(0.1) #A pause between bursts
		input_data=bluetooth.readline()
	aux = m[0]
	micro = 0
	for j in range(1,i+1):
		if m[j]>aux:
			aux=m[j]
			micro=j+1
		if aux == m[0] :
			micro = 1;
	print(aux)
	print("micro")
	print(micro)

	if float(aux)>20 :
		if micro==1:
			firebase.put('location','position','Up')
			bluetooth.write(b"F")
			#time.sleep(1)
			
		if micro==2:
			firebase.put('location','position','Left')
			bluetooth.write(b"G")
			#time.sleep(1)
			
		if micro==3:
			firebase.put('location','position','Right')
			bluetooth.write(b"I")
			#time.sleep(1)
			
	else:
		firebase.put('location','position','Default')
	#bluetooth.write(b'A')
bluetooth.close() #Otherwise the connection will remain open until a timeout which ties up the /dev/thingamabob
print("Done Gut fenomen")