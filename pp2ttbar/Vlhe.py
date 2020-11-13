import numpy as np

class Particles:
	def __init__(self, pdg_id, status, mother1, mother2, color1, color2, px, py, pz, e, m, tau, spin):
		self.pdg_id = pdg_id
		self.status = status
		self.mother1 = mother1
		self.mother2 = mother2
		self.color1 = color1
		self.color2 = color2
		self.px = px
		self.py = py
		self.pz = pz
		self.e = e
		self.m = m
		self.tau = tau
		self.spin = spin
			
		
		
def readLHE(file_name):
	data = np.genfromtxt(file_name,comments = '<', delimiter = " ")
	particle = []
	
	for i in range(len(data)):
		particle.append(Particles(pdg_id = data[i][0], status = data[i][1], mother1 = data[i][2], mother2 = data[i][3], color1 = data[i][4], color2 = data[i][5], px = data[i][6], py = data[i][7], pz = data[i][8], e = data[i][9], m = data[i][10], tau = data[i][11], spin = data[i][12]))
	
	return particle
	
	
	

