import serial

ser = serial.Serial('/dev/tty.usbserial-A9WDK2F4', 115200, timeout=0)

from datetime import datetime

while (1):
    s = ser.read(2)      

    #getHour
    if (s == bytes([0xa1])):
        print("received ", s)
        current_hour = datetime.now().hour
        ser.write(bytes([current_hour]))

    #getMin
    if (s == bytes([0xa2])):
        print("received ", s)
        current_minute = datetime.now().minute
        ser.write(bytes([current_minute]))

    #getYear
    if (s == bytes([0xa5])):
        print("received ", s)
        current_year = datetime.now().year
        ser.write(bytes([((current_year & (0xFF00)) >> 8), current_year & 0xFF]))

    #getDayOfWeek
    if (s == bytes([0xa8])):
         print("received ", s) 
        current_dow = (datetime.now().weekday() + 1) % 7
        ser.write(bytes([current_dow]))   

    #getMonth
    if (s == bytes([0xa6])):
        print("received ", s)
        current_month = datetime.now().month
        ser.write(bytes([current_month]))

    #getSecond
    if (s == bytes([0xa3])):
        print("received ", s)
        current_second = datetime.now().second
        ser.write(bytes([current_second]))

    #getDate
    if (s == bytes([0xa9])):
        print("received ", s)
        current_date = datetime.now().day
        ser.write(bytes([current_date]))

    #sendPillInfo
     if (s == bytes([0xa7])):
        print("received ", s)
        ser.write(bytes([1])) #number of pills.
        while(ser.read(1) != [0xa7])
        ser.write(bytes([14])) #Packet Size.
        ser.write(bytes[])


    