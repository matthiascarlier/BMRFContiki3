import csv
import numpy as np
import scipy.stats as sp
import math
import os
from collections import defaultdict

def cast_list(data_list):
	result = []
	for element in data_list:
		try:
			casted_float = float(element)
			result.append(casted_float)
		except Exception, e:
			continue
	return result

def mean_confidence_interval(data, confidence):
	a = 1.0*np.array([float(data0) for data0 in data])
	n = len(a)
	mean, std = np.mean(a), np.std(a,ddof=1)
	h = sp.norm.interval(confidence,mean,std/math.sqrt(n))
	return mean, h[1]-mean

CLOCK_SECOND = 32768
RX_CONS = 56.4
TX_CONS = 52.2
LPM_CONS = 0.0015
CPU_CONS = 8.76

iterations = 10
'''
configurations_names = ['SMRF_MIXED_1', 'BMRF_BROADCAST_1', 'BMRF_MIXED_1', 'BMRF_MIXED_2', 'BMRF_MIXED_3', 'BMRF_MIXED_4', 'BMRF_MIXED_5', 'BMRF_MIXED_6', 'BMRF_UNICAST_1']
configurations_names_well_written=['SMRF', 'BMRF\ Broadcast', 'BMRF\ Mixed-1', 'BMRF\ Mixed-2', 'BMRF\ Mixed-3', 'BMRF\ Mixed-4', 'BMRF\ Mixed-5', 'BMRF\ Mixed-6', 'BMRF\ Unicast']
scenarios = ['25', '50', '75', '100']
topologies = ['random_topology_A', 'random_topology_B', 'random_topology_C']

colnames = ['timestamp', 'ID_id', 'ID', 'PDR', 'radio_trans', 'packt_trans', 'rx_time', 'tx_time', 'lpm_time', 'cpu_time']
macProtocols = ['contikiMAC32']

'''
configurations_names = ['BMRF_UNICAST_1']
scenarios = ['100']
topologies = ['topology_3_childZ1']

colnames = ['timestamp', 'ID_id', 'ID', 'PDR', 'radio_trans', 'packt_trans', 'rx_time', 'tx_time', 'lpm_time', 'cpu_time']
macProtocols = ['ContikiMAC8']

for macProtocol in macProtocols:
	for scenario in scenarios:
		allPDR = defaultdict(list)
		allEnergy = defaultdict(list)
		allDelay1 = defaultdict(list)
		allDelay2 = defaultdict(list)
		allDelay3 = defaultdict(list)
		for mcast_conf in configurations_names:
			pdr = defaultdict(list)
			energy = defaultdict(list)
			delay1 = defaultdict(list)
			delay2 = defaultdict(list)
			delay3 = defaultdict(list)
			for topology in topologies:
				path = macProtocol + '/' + topology + '/'
				for i in xrange(1, iterations+1):
					print(macProtocol + ":" + topology+ ":"+scenario+ ":"+mcast_conf)
					itPDR = defaultdict(list)
					itEnergy = defaultdict(list)
					itDelay1 = defaultdict(list)
					itDelay2 = defaultdict(list)
					itDelay3 = defaultdict(list)
					with open(path + "raw_results_" + scenario + "-percent_" + mcast_conf + "_iteration-" + str(i) + ".csv", 'rU') as fraw:
						reader = csv.reader(fraw, delimiter=";",dialect=csv.excel_tab)
						for row in reader:
							if(not row[3]=='n'):
									itPDR[int(row[10])].append(int(row[3]))
									itEnergy[int(row[10])].append((int(row[6])*RX_CONS + int(row[7])*TX_CONS + int(row[8])*LPM_CONS + int(row[9])*CPU_CONS)/(1000*CLOCK_SECOND))
						for j in itPDR:
							mean, ci = mean_confidence_interval(itPDR[j], 0.95)
							pdr[j].append(mean)
							mean, ci = mean_confidence_interval(itEnergy[j], 0.95)
							energy[j].append(mean)

					with open(path + "delay_results_" + scenario + "-percent_" + mcast_conf + "_iteration-" + str(i) + ".csv", 'rU') as fraw:
						reader = csv.reader(fraw, delimiter=";",dialect=csv.excel_tab)
						ctr = 0;
						currentPckt = 0;
						for row in reader:
							if(currentPckt != int(row[0])):
								ctr = 0
								currentPckt = int(row[0])
							if(row[3] == "1"):
								ctr += 1
								#print(str(currentPckt) + ":" + str(ctr) + ":" + row[2])
								if(ctr == 1):
									itDelay1[int(row[3])].append(int(row[2]))
								if(ctr == 2):
									itDelay2[int(row[3])].append(int(row[2]))
								if(ctr == 3):
									itDelay3[int(row[3])].append(int(row[2]))
									ctr = 0
		
						for j in itDelay1:
							mean, ci = mean_confidence_interval(itDelay1[j], 0.95)
							delay1[j].append(mean)
						for j in itDelay2:
							mean, ci = mean_confidence_interval(itDelay2[j], 0.95)
							delay2[j].append(mean)
						for j in itDelay3:
							mean, ci = mean_confidence_interval(itDelay3[j], 0.95)
							delay3[j].append(mean)

			allPDR[mcast_conf] = pdr
			allEnergy[mcast_conf] = energy
			allDelay1[mcast_conf] = delay1
			allDelay2[mcast_conf] = delay2
			allDelay3[mcast_conf] = delay3
		'''
		with open("computed_hops_" + macProtocol + "_" +scenario+"-percent.csv", 'a') as  fp:
			os.chmod(fp.name, 0o666)
			writefile = csv.writer(fp, delimiter='\t')
			for conf in allPDR:
				pdr = allPDR[conf]					
				print(pdr)
				writefile.writerow(["hops", "PDR", "PDR-CI"])
				for row in pdr:
					#print(pdr[row])
					mean, ci = mean_confidence_interval(pdr[row], 0.95)
					writefile.writerow([row, mean, ci])
		'''
		with open("computed_hops_" + macProtocol + "_" +scenario+"-percent.csv", 'w') as  fp:
			os.chmod(fp.name, 0o666)
			writefile = csv.writer(fp, delimiter='\t')
				
			row = ["hops"]
			for conf in configurations_names:
				row.append("PDR_" + conf)
				row.append("CI")
				row.append("Energy_" + conf)
				row.append("CI")
				row.append("Delay1_" + conf)
				row.append("CI")
				row.append("Delay2_" + conf)
				row.append("CI")
				row.append("Delay3_" + conf)
				row.append("CI")
			writefile.writerow(row)
			
			for i in xrange(1, 7):
				row = [i]
				for conf in configurations_names:
					mean, ci = mean_confidence_interval(allPDR[conf][i], 0.95)
					row.append(mean)
					row.append(ci)
					mean, ci = mean_confidence_interval(allEnergy[conf][i], 0.95)
					row.append(mean)
					row.append(ci)
					mean, ci = mean_confidence_interval(allDelay1[conf][i], 0.95)
					row.append(mean)
					row.append(ci)
					mean, ci = mean_confidence_interval(allDelay2[conf][i], 0.95)
					row.append(mean)
					row.append(ci)
					mean, ci = mean_confidence_interval(allDelay3[conf][i], 0.95)
					row.append(mean)
					row.append(ci)

				writefile.writerow(row)
			
				
