import time
import serial
import smtplib
import MySQLdb
#establish connection to MYSQL.
dbConn=MySQLdb.connect("localhost","root","abcd1234","smart_home") or die ("could not connect to database")
#open a cursor to the database
TO = 'saandeepatn@gmail.com'
GMAIL_USER = 'selfstudyise@gmail.com'
GMAIL_PASS = 'weareawesome'
SUBJECT = 'Intrusion!!'
TEXT = 'Your PIR sensor detected movement'
ser = serial.Serial('/dev/ttyACM0', 9600)
def send_email():
    print("Sending Email")
    smtpserver = smtplib.SMTP("smtp.gmail.com",587)
    smtpserver.ehlo()
    smtpserver.starttls()
    smtpserver.ehlo
    smtpserver.login(GMAIL_USER, GMAIL_PASS)
    header = 'To:' + TO + '\n' + 'From: ' + GMAIL_USER
    header = header + '\n' + 'Subject:' + SUBJECT + '\n'
    print header
    msg = header + '\n' + TEXT + ' \n\n'
    smtpserver.sendmail(GMAIL_USER, TO, msg)
    smtpserver.close()

while True:
    message = ser.readline()
    
    print(message)
    if message[0] == 'M' :
        send_email()
        cursor=dbConn.cursor()
        cursor.execute("INSERT INTO sensordata(timestamp,value) VALUES (NOW(),1)")
        #dbConn.commit()
        time.sleep(1)
        cursor.execute("INSERT INTO sensordata(timestamp,value) VALUES (NOW(),0)")
        dbConn.commit()
 #commit the insert
        cursor.close() #close the cursor
        #except: MYSQLdb.IntegrityError:
         #   print"failed to insert data"
        #finally:
        #cursor.close() # close incase it failed
    	#except:
        #print"Processing!"
    time.sleep(0.5)
