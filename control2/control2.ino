#include <PS4Controller.h>

// Crear una instancia para el controlador
PS4Controller PS4_1; // Instancia para el primer control

// Variable para identificar si el control está conectado
bool isControl1Connected = false;
int buzzerPin = 4; // Pin donde conectas el altavoz o piezo
int modo = 2;
// Variables para el antirrebote
bool lastUpState = false;
bool lastDownState = false;
bool lastLeftState = false;
bool lastRightState = false;
bool lastSquareState = false;
bool lastCrossState = false;
bool lastCircleState = false;
bool lastTriangleState = false;
//*******************************************************
// Definir frecuencias de las notas (en Hz)
// Definir frecuencias de las notas (en Hz)
#define NOTE_C4 261   // Do
#define NOTE_As3 233  // La# 
#define NOTE_D4 293   // Re
#define NOTE_Eb4 311  // Re#
#define NOTE_F4 349   // Fa
#define NOTE_Fs4 370  // Fa#
#define NOTE_G4 392   // Sol
#define NOTE_C7 2093  // Do (octava superior)
#define NOTE_G6 1568  // Sol (octava superior)
#define NOTE_E6 1319  // Mi (octava superior)
#define NOTE_B5 988   // Si (octava superior)
#define NOTE_A7 1760  // La (octava superior)
#define NOTE_E5 659   // Mi (octava superior)
#define NOTE_A4 440   // La
#define NOTE_G5 784   // Sol (octava superior)
#define NOTE_C5 523   // Do (octava superior)
#define NOTE_D5 587   // Re (octava superior)
#define NOTE_C6 1046  // Do (dos octavas superiores)
#define NOTE_G6 1568  // Sol (octava superior)
#define NOTE_E4 329   // Mi
#define NOTE_B4 494  // Si (B4)
#define NOTE_B3 247
#define NOTE_A3 220 
#define NOTE_Gs4 415 // Sol#


// Nueva melodía de fondo
int melody3[] = {
  NOTE_E4, NOTE_E4, NOTE_E4, NOTE_G4,  // 4 notas: Mi Mi Mi Sol
  NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,  // 4 notas: La Si La Sol
  NOTE_E4, NOTE_E4, NOTE_E4, NOTE_G4,  // 4 notas: Mi Mi Mi Sol
  NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,  // 4 notas: La Si La Sol
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4,  // 4 notas: Do Si La Sol
  NOTE_E4, NOTE_E4, NOTE_D4, NOTE_C4   // 4 notas: Mi Mi Re Do
};

// Duraciones de las notas para la nueva melodía (valores variados)
int noteDurations3[] = {
  4, 4, 4, 4, // 4 notas
  4, 4, 4, 4, // 4 notas
  4, 4, 4, 4, // 4 notas
  4, 4, 4, 4, // 4 notas
  4, 4, 4, 4, // 4 notas
  4, 4, 4, 4  // 4 notas
};
int melody2[] = {
  NOTE_Gs4, NOTE_Gs4, NOTE_Fs4, NOTE_Fs4, // Sol# Sol# Fa# Fa#
  NOTE_Fs4, NOTE_Fs4, NOTE_Fs4, NOTE_E4, // Fa# Fa# Fa# Mi
  NOTE_E4, NOTE_E4, NOTE_E4, NOTE_Fs4,    // Mi Mi Mi Fa#
  NOTE_Gs4, NOTE_Gs4, NOTE_Fs4, NOTE_Fs4, // Sol# Sol# Fa# Fa#
  NOTE_Fs4, NOTE_Fs4,NOTE_Fs4, NOTE_F4,   // Fa# Fa# Fa# Fa
  NOTE_F4, NOTE_F4, NOTE_F4, NOTE_Fs4     // Fa Fa Fa Fa#              // E D C
};

// Duraciones de las notas para la nueva melodía (valores variados)
int noteDurations2[] = {
  4, 2, 4, 3, // 4 notas
  6, 7, 3, 3, // 4 notas
  7, 7, 7, 7, // 4 notas
  4, 2,
  4, 3, // 4 notas
  6, 7, 3, 3,    // 3 notas
  7, 7, 7, 7   // 4 notas
  /*5, 5, 5, 5, // 4 notas
  5, 5, 5, 5, // 4 notas
  5, 5, 5, 5, // 4 notas
  5, 5, 5, 5, // 4 notas
  5, 5, 5,    // 3 notas
  5, 5, 5, 5   // 4 notas*/
};
// Array de frecuencias de la partitura principal (melodía 1)
int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_C4, NOTE_As3, NOTE_C4,  // Do Do Do La# Do
  NOTE_D4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_D4,   // Re Re Re Do Re
  NOTE_Eb4, NOTE_Eb4, NOTE_Eb4,                  // Re# Re# Re#
  NOTE_Fs4, NOTE_Fs4, NOTE_Fs4,                  // Fa# Fa# Fa#
  NOTE_G4, NOTE_F4, NOTE_Eb4, NOTE_G4            // Sol Fa Re# Sol
};

// Duraciones de las notas para la melodía 1
int noteDurations[] = {
  6, 6, 6, 4, 2,   // Duraciones para la primera línea
  7, 7, 7, 4, 2,   // Duraciones para la segunda línea
  8, 8, 3,         // Tercera línea
  8, 8, 3,         // Cuarta línea
  9, 8, 7, 2       // Última línea
  /*7, 6, 7, 3, 8,   // Duraciones para la primera línea
  7, 8, 7, 3, 7,   // Duraciones para la segunda línea
  9, 9, 9,         // Tercera línea
  8, 8, 8,         // Cuarta línea
  9, 8, 7, 2       // Última línea*/
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
//***********************************************************************************************
void notifyControls() {
    // Si Control 1 está conectado, verifica sus botones
    if (isControl1Connected) {
        // Verificar botones de la cruceta (d-pad)
        bool currentUpState = PS4_1.Up();
        if (currentUpState && !lastUpState) {
            Serial.println("i");  // Control 1, botón Arriba
        }
        lastUpState = currentUpState;  // Actualizar el estado anterior

        bool currentDownState = PS4_1.Down();
        if (currentDownState && !lastDownState) {
            Serial.println("k");  // Control 1, botón Abajo
        }
        lastDownState = currentDownState;  // Actualizar el estado anterior

        bool currentLeftState = PS4_1.Left();
        if (currentLeftState && !lastLeftState) {
            Serial.println("j");  // Control 1, botón Izquierda
        }
        lastLeftState = currentLeftState;  // Actualizar el estado anterior

        bool currentRightState = PS4_1.Right();
        if (currentRightState && !lastRightState) {
            Serial.println("l");  // Control 1, botón Derecha
        }
        lastRightState = currentRightState;  // Actualizar el estado anterior
    }

    // Verificar otros botones
    if (isControl1Connected) {
        bool currentSquareState = PS4_1.Square();
        if (currentSquareState && !lastSquareState) {
            Serial.println("m");  // Control 1, botón Square
        }
        lastSquareState = currentSquareState;  // Actualizar el estado anterior

        bool currentCrossState = PS4_1.Cross();
        if (currentCrossState && !lastCrossState) {
            Serial.println("o");  // Control 1, botón Cross
        }
        lastCrossState = currentCrossState;  // Actualizar el estado anterior

        bool currentCircleState = PS4_1.Circle();
        if (currentCircleState && !lastCircleState) {
            Serial.println("u");  // Control 1, botón Circle
        }
        lastCircleState = currentCircleState;  // Actualizar el estado anterior

        /*bool currentTriangleState = PS4_1.Triangle();
        if (currentTriangleState && !lastTriangleState) {
            Serial.println("D1");  // Control 1, botón Triangle
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
    fondomodo();
    
    // Inicializar el primer control
    PS4_1.attach(notifyControls);
    PS4_1.attachOnConnect(onConnectControl1);
    PS4_1.attachOnDisconnect(onDisConnectControl1);
    PS4_1.begin();  // Iniciar Control 1

    Serial.println("Listo para recibir datos del control.");
}
void fondoMusic(){
   // Verifica si hay datos disponibles en el puerto serie
  if (Serial.available() > 0) {
    char incomingChar = Serial.read(); // Lee el carácter recibido
    Serial.println(incomingChar);
    
    // Ejecuta una acción en función del carácter recibido
    if (incomingChar == '1') {
      //intro
      modo =1;
      fondomodo();
    } 
    else if (incomingChar == '2') {
      //menú
      modo = 2;
      fondomodo();
      
    } else if (incomingChar == '3') {
      //fondo
      modo = 3;
      fondomodo();
    } 
    
  }

}
void fondomodo(){
  if (modo == 1) {
      playMelody(melody2, noteDurations2, sizeof(melody2) / sizeof(melody2[0]));

    }else if (modo == 2) {
      playMelody(melody, noteDurations, sizeof(melody) / sizeof(melody[0]));

    }else if (modo == 3) {
       playMelody(melody3, noteDurations3, sizeof(melody3) / sizeof(melody3[0]));
    }
      
}
void loop() {
  //funcion del fondo
    fondoMusic();
    //fondomodo();
}
