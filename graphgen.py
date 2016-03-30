import MySQLdb
import matplotlib.pyplot as plt

conn = MySQLdb.connect (host = "localhost",
                           user = "root",
                           passwd = "abcd1234",
                           db = "smart_home")
cursor = conn.cursor ()
cursor.execute ("SELECT timestamp,value from sensordata")
row = cursor.fetchall()
print "RESULT:", row[0]

timestamp,value=zip(*row)
plt.plot(timestamp,value)

plt.grid()
plt.show()
plt.scatter(timestamp,value)
plt.show()
cursor.close ()
conn.close ()
