#Arduino home control using a webpage.
Connect Arduino with Ethernet Shield to a router or a laptop with a network bridge. 
The webpage is uploaded on the local server using the ip address and mac address given to the ethernet shield. 
This webpage can be accessed on the same local area network by other devices like your mobile or some other compyters in order to control the devices.
The devices can be anything ranging from lights, fans, motors, automatic doors etc.

#New feature added: Intrusion Detedction with mail alert along with data analysis


#Arduino Intrusion  Detection system with mail alert using Ultrasonic sensor and data analysis.
Connect the arduino with a ultrasonic sensor, buzzer and an led light. 
//Schematic diagram will be uploaded soon.
The arduino is connected to the laptop with internet connectivity.
(thus avoiding the need for an ethernet shild or wifi shield and reducing costs)
The python script is run and kept running till whatever time you require detection.
The python scrpt reads from the serial port whihc the Arduino sends messages to.
On detectoin of intrusion the python script sends the mail using smtp to whichever mail ID required.
The data from the arduino ultrasonic sensor is read by python script which creates a MySQL connection and 
inserts the data.


The data stored in the database is retreived using another python script which plots the value and generates graphs for analysis.

