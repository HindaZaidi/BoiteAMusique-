const int led1Pin = 4;  // Pin de la LED 1 (DO)
const int led2Pin = 3;  // Pin de la LED 2 (DO)
const int led3Pin = 2;  // Pin de la LED 3 (DO)

const int led4Pin = 7;  // Pin de la LED 4 (RE)
const int led5Pin = 6;  // Pin de la LED 5 (RE)
const int led6Pin = 5;  // Pin de la LED 6 (RE)

const int photoDO_Pin = A0;  // Pin de la photoresistance pour DO
const int photoRE_Pin = A1;  // Pin de la photoresistance pour RE

void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);
  pinMode(led5Pin, OUTPUT);
  pinMode(led6Pin, OUTPUT);
  
  Serial.begin(9600);  // Initialiser la communication série
}

void loop() {
  // Allumer la rangée DO
  digitalWrite(led1Pin, HIGH);
  delay(200);
  digitalWrite(led1Pin, LOW);
  
  digitalWrite(led2Pin, HIGH);
  delay(200);
  digitalWrite(led2Pin, LOW);
  
  digitalWrite(led3Pin, HIGH);
  delay(50);
  digitalWrite(led3Pin, LOW);
  
  // Vérifier si la photoresistance pour DO détecte la lumière
  int photoDO_Value = analogRead(photoDO_Pin);
  if (photoDO_Value < 500) {
    // Envoyer la note DO via le port série
    Serial.println("DO");
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, LOW);
    
    // Attendre une seconde pour laisser le temps au message d'être envoyé
    delay(50);
    
    // Attendre la réponse du script Python pour la note DO
    while (true) {
      if (Serial.available() > 0) {
        String response = Serial.readStringUntil('\n');
        if (response == "NotePlayed") {
          // La note DO a été jouée, éteindre toutes les LED de la rangée DO
          digitalWrite(led1Pin, LOW);
          digitalWrite(led2Pin, LOW);
          digitalWrite(led3Pin, LOW);
          break;
        }
      }
    }
  }
  
  // Allumer la rangée RE
  digitalWrite(led4Pin, HIGH);
  delay(200);
  digitalWrite(led4Pin, LOW);
  
  digitalWrite(led5Pin, HIGH);
  delay(200);
  digitalWrite(led5Pin, LOW);
  
  digitalWrite(led6Pin, HIGH);
  delay(50);
  digitalWrite(led6Pin, LOW);
  
  // Vérifier si la photoresistance pour RE détecte la lumière
  int photoRE_Value = analogRead(photoRE_Pin);
  if (photoRE_Value < 500) {
    // Envoyer la note RE via le port série
    Serial.println("RE");
    digitalWrite(led5Pin, LOW);
    digitalWrite(led6Pin, LOW);
    
    // Attendre une seconde pour laisser le temps au message d'être envoyé
    delay(50);
    
    // Attendre la réponse du script Python pour la note RE
    while (true) {      if (Serial.available() > 0) {
        String response = Serial.readStringUntil('\n');
        if (response == "NotePlayed") {
          // La note RE a été jouée, éteindre toutes les LED de la rangée RE
          digitalWrite(led4Pin, LOW);
          digitalWrite(led5Pin, LOW);
          digitalWrite(led6Pin, LOW);
          break;
        }
      }
    }
  }

  // Éteindre toutes les LED après la séquence
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  digitalWrite(led3Pin, LOW);
  digitalWrite(led4Pin, LOW);
  digitalWrite(led5Pin, LOW);
  digitalWrite(led6Pin, LOW);

  // Attendre un court délai avant de poursuivre la prochaine itération
  delay(100);
}
