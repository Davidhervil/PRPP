import os
import subprocess
import time

optimos = {}


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
				if optimos[f] != 0:
					desviacion = 100*(optimos[f] - ganancia)/optimos[f]							# Calcular la desviacion estandar
				else:
					desviacion = 0
				msj = f + "\t" + str(optimos[f]) + "\t" + str(ganancia) + "\t" + str(desviacion) + "\t" + str(t_diff) + "\n"	# 
				print(msj)
				with open("resultados.txt",'a') as fp:
					fp.write(msj)

def readRef(refFile):
	# Lee el archivo de referencias y lo almacena en un diccionario.
	# El diccionario es instances[name] = [Vo, Aprox]
	with open("referencia.txt","r") as fp:
		for line in fp:
			l = line.split('\t')
			name = l[0] + "NoRPP"
			Vopt = l[7]
			optimos[name] = int(Vopt)

#########################################
#				VARIABLES				#			
#########################################
cwd		  = os.getcwd()
cCode	  = cwd + "\PRPP.exe"
insFolder = cwd + "\\instancias"
refFile   = cwd + "\\reference.txt"
#########################################

if __name__ == "__main__":
	references = readRef(refFile)
	results    = runInstances(insFolder, outFolder)
