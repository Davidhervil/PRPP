import os
import subprocess
import time

#########################################
#				FUNCIONES				#
#########################################

def runInstances(source, dest):
	# EL ALGORITMO DE C++ Recibe el archivo
	# Tambien recibe el archivo en el que escribira la salida
	# Devuelve la ganancia obtenida por el algoritmo.
	results = {}
	for root, dirs, files in os.walk(source):
		for f in files:
			err = 0
			name = f.split(".")[0]
			src = root + "\\" + f
			print("Running: ", src)
			# EJECUCION DEL ALGORITMO
			t_start = time.time()
			try:
				ganancia = os.system("PRPP.exe < " + src)
			except:
				err = 1 
			t_diff 	= time.time() - t_start
			# FIN DE LA EJECUCION
			if err == 1:
				print("		Ocurrio un error ejecutando", src, "tiempo: ", t_diff)
			else:
				msj = f+"\t"+str(ganancia)+"\t"+str(t_diff)+"\n"
				print(msj)
				with open("resultados.txt",'a') as fp:
					fp.write(msj)

def readRef(refFile):
	# Lee el archivo de referencias y lo almacena en un diccionario.
	# El diccionario es instances[name] = [Vo, Aprox]
	instances = {}
	i = -1
	with open(refFile, "r") as ref:
		for line in ref:
			l = line.split(",")
			v0_ref = [int(l[7]),int(l[8])] 
			instances[l[0]+"NoRPP"] = v0_ref
			print(l[0]+"NoRPP",v0_ref)
	return instances

#########################################
#				VARIABLES				#			
#########################################
cwd		  = os.getcwd()
cCode	  = cwd + "\PRPP.exe"
insFolder = cwd + "\\instanciasPRPP\\instanciasPRPP"
refFile   = cwd + "\\reference.txt"
outFolder = cwd + "\output"
tableFile = cwd + "\\tables.txt"
#########################################

if __name__ == "__main__":
	references = readRef(refFile)
	results    = runInstances(insFolder, outFolder)
	#genTables(results, references, tableFile) 
