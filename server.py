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
        ser.write(bytes([12]))
        current_year = datetime.now().year
        ser.write(bytes([current_year]))

    #getDayOfWeek
    if (s == bytes([0xa8])):
        print("received ", s)
        ser.write(bytes([12]))
        current_month = datetime.now().today()
        ser.write(bytes([current_month]))   

    #getMonth
    if (s == bytes([0xa6])):
        print("received ", s)
        ser.write(bytes([12]))
        current_month = datetime.now().month
        ser.write(bytes([current_month]))

    #getSecond
    if (s == bytes([0xa3])):
        print("received ", s)
        ser.write(bytes([12]))
        current_second = datetime.now().second
        ser.write(bytes([current_second]))

    #getDate
    if (s == bytes([0xa9])):
        print("received ", s)
        ser.write(bytes([12]))
        current_date = datetime.now().day
        ser.write(bytes([current_date]))