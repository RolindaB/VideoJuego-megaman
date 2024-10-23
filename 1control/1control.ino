#include <PS4Controller.h>

// Crear una instancia para el controlador
PS4Controller PS4_1; // Instancia para el primer control

// Variable para identificar si el control está conectado
bool isControl1Connected = false;
int buzzerPin = 27; // Pin donde conectas el altavoz o piezo
int led1 = 32, led2 = 33, led3 = 14, led4 = 12; // Pines para los LEDs
int modo;
// Variables para el antirrebote
bool lastUpState = false;
bool lastDownState = false;
bool lastLeftState = false;
bool lastRightState = false;
bool lastSquareState = false;
bool lastCrossState = false;
bool lastCircleState = false;
bool lastTriangleState = false;

// Definir frecuencias de las notas (en Hz)
#define NOTE_C4 261
#define NOTE_As3 233
#define NOTE_D4 293
#define NOTE_Eb4 311
#define NOTE_F4 349
#define NOTE_Fs4 370
#define NOTE_G4 392
#define NOTE_C7 2093
#define NOTE_G6 1568
#define NOTE_E6 1319
#define NOTE_B5 988
#define NOTE_A7 1760
#define NOTE_E5 659  // Tono medio para la caída del disparo
#define NOTE_A4 440  // Tono bajo para finalizar
#define NOTE_G5 784
#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_C6 1046
#define NOTE_G6 1568
#define NOTE_C4 261  // Do
#define NOTE_E4 329  // Mi


// Melodía para el salto (tono que sube rápidamente)
int jumpMelody[] = {
  NOTE_C5, NOTE_E4 // Nota alta seguida de una nota más baja
};

// Duraciones para las notas (cortas para un salto rápido)
int jumpDurations[] = {
  8, 9//, 7  // Duraciones rápidas para simular un salto ágil
};

/*/ Array para la melodía de disparo (melodía 2)
int shootingMelody2[] = {
  NOTE_G6, NOTE_E6//, NOTE_C6          // Eco rápido
};

// Duraciones para la melodía de disparo
int shootingDurations2[] = {
  8, 9//, 8
};*/

int shootingMelody[] = {
 NOTE_E5, NOTE_C4//, NOTE_A4
};

// Duraciones cortas para un sonido más seco
int shootingDurations[] = {
  8, 9//, 9 
};

// Función para reproducir una nota
void playNote(int note, int duration) {
  tone(buzzerPin, note, duration);
  delay(duration * 1.3); // Pausa entre notas
  noTone(buzzerPin); // Apagar el sonido
}

// Función para reproducir una melodía genérica
void playMelody(int melody[], int durations[], int length) {
  for (int i = 0; i < length; i++) {
    int noteDuration = 1000 / durations[i]; // Calcular duración en ms
    playNote(melody[i], noteDuration);       // Reproducir nota
  }
}
/*________________________LEDS ________________________*/
// Función para las secuencias de LEDs
void ledSequence1() {
  // Secuencia 1: Encender los LEDs uno por uno
  digitalWrite(led1, HIGH); delay(200);
  digitalWrite(led2, HIGH); delay(200);
  digitalWrite(led3, HIGH); delay(200);
  digitalWrite(led4, HIGH); delay(200);
  digitalWrite(led1, LOW); delay(200);
  digitalWrite(led2, LOW); delay(200);
  digitalWrite(led3, LOW); delay(200);
  digitalWrite(led4, LOW); delay(200);
}

void ledSequence2() {
  // Secuencia 2: Parpadear todos los LEDs al mismo tiempo
  for (int i = 0; i < 5; i++) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    delay(300);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    delay(300);
  }
}

void ledSequence3() {
  // Secuencia 3: Encender y apagar los LEDs en patrones alternos
  digitalWrite(led1, HIGH); digitalWrite(led3, HIGH);
  digitalWrite(led2, LOW); digitalWrite(led4, LOW);
  delay(500);
  digitalWrite(led1, LOW); digitalWrite(led3, LOW);
  digitalWrite(led2, HIGH); digitalWrite(led4, HIGH);
  delay(500);
}
void ledSequence4() {
  // Secuencia 4: Efecto de carrera
  for (int i = 0; i < 4; i++) {
    digitalWrite(led1, (i == 0) ? HIGH : LOW);
    digitalWrite(led2, (i == 1) ? HIGH : LOW);
    digitalWrite(led3, (i == 2) ? HIGH : LOW);
    digitalWrite(led4, (i == 3) ? HIGH : LOW);
    delay(200);  // Pausa entre encender LEDs
  }

  for (int i = 3; i >= 0; i--) {
    digitalWrite(led1, (i == 0) ? HIGH : LOW);
    digitalWrite(led2, (i == 1) ? HIGH : LOW);
    digitalWrite(led3, (i == 2) ? HIGH : LOW);
    digitalWrite(led4, (i == 3) ? HIGH : LOW);
    delay(200);  // Pausa entre encender LEDs
  }
}

//*********************************
void notifyControls() {
    // Si Control 1 está conectado, verifica sus botones
    if (isControl1Connected) {
        // Verificar botones de la cruceta (d-pad)
        bool currentUpState = PS4_1.Up();
        if (currentUpState && !lastUpState) {
            Serial.println("w");  // Control 1, botón Arriba
        }
        lastUpState = currentUpState;  // Actualizar el estado anterior*/

        bool currentDownState = PS4_1.Down();
        if (currentDownState && !lastDownState) {
            Serial.println("s");  // Control 1, botón Abajo
        }
        lastDownState = currentDownState;  // Actualizar el estado anterior

        bool currentLeftState = PS4_1.Left();
        if (currentLeftState && !lastLeftState) {
            Serial.println("a");  // Control 1, botón Izquierda
            //playMelody(jumpMelody, jumpDurations, sizeof(jumpMelody) / sizeof(jumpMelody[0]));
            //ledSequence1();  // Activar secuencia 1
        }
        lastLeftState = currentLeftState;  // Actualizar el estado anterior

        bool currentRightState = PS4_1.Right();
        if (currentRightState && !lastRightState) {
            Serial.println("d");  // Control 1, botón Derecha
            //playMelody(shootingMelody, shootingDurations, sizeof(shootingMelody) / sizeof(shootingMelody[0]));
            //ledSequence2();  // Activar secuencia 2
        }
        lastRightState = currentRightState;  // Actualizar el estado anterior
    }

    // Verificar otros botones
    if (isControl1Connected) {
        bool currentSquareState = PS4_1.Square();
        if (currentSquareState && !lastSquareState) {
            Serial.println("x");  // Control 1, botón Square
        }
        lastSquareState = currentSquareState;  // Actualizar el estado anterior

        bool currentCrossState = PS4_1.Cross();
        if (currentCrossState && !lastCrossState) {
            Serial.println("e");  // Control 1, botón Cross
        }
        lastCrossState = currentCrossState;  // Actualizar el estado anterior

        bool currentCircleState = PS4_1.Circle();
        if (currentCircleState && !lastCircleState) {
            Serial.println("q");  // Control 1, botón Circle
        }
        lastCircleState = currentCircleState;  // Actualizar el estado anterior

        bool currentTriangleState = PS4_1.Triangle();
        if (currentTriangleState && !lastTriangleState) {
            Serial.println("d");  // Control 1, botón Triangle
        }
        lastTriangleState = currentTriangleState;  // Actualizar el estado anterior*/
    }
}

void onConnectControl1() {
    Serial.println("Control 1 Conectado");
    isControl1Connected = true; // Marca el Control 1 como conectado
}

void onDisConnectControl1() {
    Serial.println("Control 1 Desconectado");
    isControl1Connected = false; // Marca el Control 1 como desconectado
}

void setup() {
    Serial.begin(9600);
    // Configurar pines de LEDs como salida
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    // Inicializar el primer control
    PS4_1.attach(notifyControls);
    PS4_1.attachOnConnect(onConnectControl1);
    PS4_1.attachOnDisconnect(onDisConnectControl1);
    PS4_1.begin();  // Iniciar Control 1

    Serial.println("Listo para recibir datos del control.");
}
void buttonMusic(){
   // Verifica si hay datos disponibles en el puerto serie
  if (Serial.available() > 0) {
    char incomingChar = Serial.read(); // Lee el carácter recibido

    // Ejecuta una acción en función del carácter recibido
    if (incomingChar == 's') {
      playMelody(shootingMelody, shootingDurations, sizeof(shootingMelody) / sizeof(shootingMelody[0]));
    } 
    else if (incomingChar == 'z') {
      playMelody(jumpMelody, jumpDurations, sizeof(jumpMelody) / sizeof(jumpMelody[0]));

    }else if (incomingChar == '1') {
      modo = 1;
      ledSequence1();  // Activar secuencia 1

    }else if (incomingChar == '2') {
      modo = 2;
      ledSequence2();  // Activar secuencia 2

    }else if (incomingChar == '3') {
      modo = 3;
      ledSequence3();  // Activar secuencia 3

    }else if (incomingChar == '4') {
      //ganador
      modo = 4;
      ledSequence4();  // Activar secuencia 4
    }    
    
  }

}
void lucesmod(){
   if (modo == 1) {
      ledSequence1();  // Activar secuencia 1

    }else if (modo == 2) {
      ledSequence2();  // Activar secuencia 2

    }else if (modo == 3) {
      ledSequence3();  // Activar secuencia 3

    }else if (modo == 4) {
      //ganador
      ledSequence4();  // Activar secuencia 4
    }    
}
void loop() {
  buttonMusic();
  lucesmod();

   
}
