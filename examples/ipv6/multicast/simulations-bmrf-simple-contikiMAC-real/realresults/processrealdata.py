import csv
import numpy as np
import scipy.stats as sp
import math
import os
from collections import defaultdict
from datetime import datetime

path = ""
filename = "realtest2hops-2.txt"

sender = " 102"
receivers = [" 103", " 104"]

sentPackets = []
receivedPackets = []
timeFMT = '%Y-%m-%d %H:%M:%S.%f'

started = 0
previousPacketID = [0]*200

with open(path + filename) as fraw:
	reader = csv.reader(fraw, delimiter=",",dialect=csv.excel_tab)
	for row in reader:
		if(not len(row) ==11): 
			continue
		
		if((row[1] == sender) & ((started==1) | (row[3]=="0"))):
			if(int(row[3]) < previousPacketID[int(row[1])]):
				row[3] = str(int(row[3])+64)
				
			previousPacketID[int(row[1])] = int(row[3])
			if(previousPacketID[int(row[1])] == 99):
				started=2
			else:
				started=1
				
			sentPackets.append(row)
			continue
			
		if(row[1] in receivers):
			if(started > 0):
				if((int(row[3]) < previousPacketID[int(row[1])])):
					row[3] = str(int(row[3])+64)
				
				previousPacketID[int(row[1])] = int(row[3])
				receivedPackets.append(row)

#print(sentPackets)
#print(receivedPackets)

for sPacket in sentPackets:
	print(sPacket)
	print("packetID;moteID;delay;hop")
	
	for rPacket in receivedPackets:
		if((sPacket[3] == rPacket[3]) & (int(sPacket[2]) < int(rPacket[2]))):
			#print(rPacket)
			interval = int((datetime.strptime(rPacket[0], timeFMT) - datetime.strptime(sPacket[0], timeFMT)).total_seconds()*1000)
			if(interval < 1*60*1000):
				print(rPacket[3] + ";" + rPacket[1].strip() + ";" + str(interval) + ";" + str(receivers.index(rPacket[1])+1))
			
	print("")

