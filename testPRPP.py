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
			dst = dest + "\\" + name +"-salida.txt"
			print("Running: ", src)
			# EJECUCION DEL ALGORITMO
			t_start = time.time()
			try:
				subprocess.check_call([cCode, src, dest])
			except:
				err = 1 
			t_diff 	= time.time() - t_start
			# FIN DE LA EJECUCION
			if err == 1:
				print("		Ocurrio un error ejecutando", src, "tiempo: ", t_diff)
			else:
				with open(dst, "r") as fp:
					gain   = int(fp.readline().strip)
					results[f] = [gain, t_diff]
	return results

def readRef(refFile):
	# Lee el archivo de referencias y lo almacena en un diccionario.
	# El diccionario es instances[name] = [Vo, Aprox]
	instances = {}
	i = -1
	with open(refFile, "r") as ref:
		for line in ref:
			l = line.split(",")
			v0_ref = [int(l[7]),int(l[8])] 
			instances[l[0]] = v0_ref
	return instances

def genTables(results, references, dest):
	with open(dest, "w") as fp:
		for k in results.keys():
			Vo = references[k][0]
			Vp = references[k][1]
			Vh = results[k][0]
			th = results[k][1]
			if Vo != 0:
				dp = (Vo - Vp)/Vo
				dh = (Vo - Vh)/Vo
				if dh >= 0:
					msj = "%s %s %s %s\n" % (k,str(dp),str(dh),str(th))
					fp.write(msj)
					print(k, dp, dh, th)
				else:
					print("ERROR DIFERENCIA NEGATIVA EN ", k, " CON ", diffOpt)
			else:
				msj = "%s %s %s %s\n" % (k,str(dp),str(dh),str(th))
				fp.write(msj)
				print(k, Vp, Vh, th)

#########################################
#				VARIABLES				#			
#########################################
cwd		  = os.getcwd()
cCode	  = cwd + "\PRPP.exe"
insFolder = cwd + "\instanciasPRPP"
refFile   = cwd + "\\reference.txt"
outFolder = cwd + "\output"
tableFile = cwd + "\\tables.txt"
#########################################

if __name__ == "__main__":
	references = readRef(refFile)
	results    = runInstances(insFolder, outFolder)
	genTables(results, references, tableFile) 
