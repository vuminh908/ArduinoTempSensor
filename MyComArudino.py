import serial
import io
import datetime

filename = 'temp_log.txt'
serPort = 'COM3'
baudRate = 9600
#ser = serial.Serial(serPort, baudRate)
print ('Serial port ' + serPort + ', Baudrate ' + str(baudRate))

with serial.Serial(serPort, baudRate) as serialPort, open(filename, 'wb') as file:
    for x in range(0, 60):
        line = serialPort.readline()
        
        currDT = datetime.datetime.now();
        strDT = currDT.strftime("%Y-%m-%d %H:%M:%S")
        strDT += ','
        
        tempVal = line.decode('ascii').strip()
        print (strDT + tempVal)

        file.write(strDT.encode('ascii'))
        file.write(line)
        file.flush()
    print ('Finished recording data')
    serialPort.close
