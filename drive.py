from firebase import firebase
import serial
import time

# the generated root for  project
FIREBASE_ROOT = 'https://sound-guided-car.firebaseio.com'
# init Firebase Database instance
firebase = firebase.FirebaseApplication(FIREBASE_ROOT, None)
firebase.put('location','position','Default')

print("Start")
port="/dev/rfcomm0"
bluetooth=serial.Serial(port, 9600)#Start communications with the bluetooth unit
print("Connected")
while 1 : 
	bluetooth.flushInput() #This gives the bluetooth a little kick
	 #send 5 groups of data to the bluetooth
	print("Ping")
	time.sleep(1)
	bluetooth.write(b"A")#bytes not unicode
	print("A sent")
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

	if float(aux)>420 :
		if micro==1:
			firebase.put('location','position','Up')
			bluetooth.write(b"F")
			
		if micro==2:
			firebase.put('location','position','Left')
			bluetooth.write(b"G")
			
		if micro==3:
			firebase.put('location','position','Right')
			bluetooth.write(b"I")
			
	else:
		firebase.put('location','position','Default')

bluetooth.close() #Otherwise the connection will remain open until a timeout
print("Done, Sound Found!")