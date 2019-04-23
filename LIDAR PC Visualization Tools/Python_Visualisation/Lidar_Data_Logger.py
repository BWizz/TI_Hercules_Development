import csv
import serial
ser = serial.Serial('COM5')
ser.baudrate = 115200
ser.bytesize = 8
ser.parity='N'
ser.stopbits=1

print('Begin!')
with open('LidarData.csv','w') as csvfile:
	fieldnames = ['Distance','Angle','New Scan Flag']
	writer = csv.DictWriter(csvfile,fieldnames=fieldnames, lineterminator = '\n')
	writer.writeheader()
	print('Begin Loop')
	for i in range(0,100000):
		x = ser.readline().strip()
		if i > 2:
			A = x.decode().split(',')
			r = A[0]
			a = A[1]
			s = A[2]
			writer.writerow({'Distance': r,'Angle': a,'New Scan Flag': s})
ser.close()
print('Done!')