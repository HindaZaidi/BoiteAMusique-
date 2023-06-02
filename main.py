import serial
import mido
import time

# Configuration de la connexion série
ser = serial.Serial('COM4', 9600)

# Configuration de la sortie MIDI
output = mido.open_output()

# Attendre la lecture du message "DO" du code Arduino
while True:
    data = ser.readline().strip().decode('utf-8')
    if data == "DO":
        # Jouer la note DO
        output.send(mido.Message('note_on', note=60, velocity=127, channel=0))
        print("Note DO jouée")

        # Envoyer la réponse au code Arduino
        ser.write(b'NotePlayed\n')
        break

# Attendre une seconde pour que le code Arduino ait le temps de recevoir la réponse
time.sleep(1)

# Attendre la lecture du message "RE" du code Arduino
while True:
    data = ser.readline().strip().decode('utf-8')
    if data == "RE":
        # Jouer la note RE
        output.send(mido.Message('note_on', note=62, velocity=127, channel=0))
        print("Note RE jouée")

        # Envoyer la réponse au code Arduino
        ser.write(b'NotePlayed\n')
        break

# Attendre une seconde pour que le code Arduino ait le temps de recevoir la réponse
time.sleep(1)

# Fermer la connexion série
ser.close()
