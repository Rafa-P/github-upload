#
# PROGRAMA DE CONTROL DE LA CENTRIFUGADORA
#

import serial
import time
import os

arduino = serial.Serial('/dev/ttyUSB0',9600)

os.system("clear")

print("###########################################")
print("#    Zippe Centrifuge Uranium Enrichment  #")
print("#             Control Program             #")
print("###########################################")
while True:
      comando = raw_input('Introduce un comando: ')
      if comando == 'STOP': #Apagado de centrifugadora
            arduino.write('O') #OPEN
            time.sleep(.300)
            arduino.write('r') #Led rojo ON
            time.sleep(.300)
            arduino.write('A') #Led amarillo OFF
            time.sleep(.300)
            arduino.write('x') #Led centrifugado OFF
            time.sleep(.300)
            print('CENTRIFUGADORA APAGADA')

      elif comando == 'ON':
            arduino.write('C') # Puerta cerrada
            time.sleep(.300)
            arduino.write('R') # Led rojo OFF
            time.sleep(.300)
            arduino.write('a') # Led amarillo ON
            time.sleep(.300)
            arduino.write('X') # Centrifugadora en marcha
            time.sleep(.300)
            print('CENTRIFUGADO EN CURSO')

arduino.close()

