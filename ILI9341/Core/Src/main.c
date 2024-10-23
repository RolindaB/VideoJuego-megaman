/* USER CODE BEGIN Header */
/**
******************************************************************************
* @file           : main.c
* @brief          : Main program body
******************************************************************************
* @attention
*
* Copyright (c) 2024 STMicroelectronics.
* All rights reserved.
*
* This software is licensed under terms that can be found in the LICENSE file
* in the root directory of this software component.
* If no LICENSE file comes with this software, it is provided AS-IS.
*
******************************************************************************
*/
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <time.h>
#include "ili9341.h"
#include "bitmaps.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
uint8_t option[1];
uint8_t option2[1];
uint8_t tx_buffer[20];

FATFS fs;
FATFS *pfs;
FIL fil;
FRESULT fres;

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart5;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
extern uint8_t fondo[];
uint8_t modo = 0;
//uint8_t IdleIndicator = 1;
uint8_t caminarD = 0;
uint8_t caminarI = 0;
uint8_t caminarD2 = 0;
uint8_t caminarI2 = 0;
uint8_t start = 0;
uint8_t startcounter = 0;
//********SELECCIÓN DE PERSONAJES********
//JUGADOR 1
uint8_t selector1x = 1;
uint8_t selector1y = 1;
uint8_t selector1xAntiguo = 0;
uint8_t selector1yAntiguo = 0;
uint8_t change1 = 1;
uint8_t chselect1 = 0;
uint8_t ch1 = 0;
//JUGADOR 2
uint8_t selector2x = 2;
uint8_t selector2y = 1;
uint8_t selector2xAntiguo = 0;
uint8_t selector2yAntiguo = 0;
uint8_t change2 = 1;
uint8_t chselect2 = 0;
uint8_t ch2 = 0;
//****************PARAMETROS**************
//JUGADOR 1
int x1 = 0;
int y1Estandar = 183;
int y1 = 183;
int w1 = 0;
int h1 = 0;
int column1 = 0;
int frame1 = 1;
int flip1 = 0;
int vY1 = 0;
int jump1 = 0;
int jumpcount1 = 0;
int falling1 = 1;
int running1 = 0;
int shooting1 = 0;
//
int bulletskin1=0;
int bulleth1=0;
int daño1 =0;
int vidas1 = 5; // Inicializa las vidas
int winner1 = 0;
//BALAS J1
int bala = 0;
int bala_x = -1;  // Posición inicial de la bala fuera de la pantalla
int bala_y = 180; // Altura inicial de la bala
#define MAX_BULLETS 3  // Define el número máximo de balas
unsigned char bullet_state[MAX_BULLETS] = {0}; // Estado de cada bala (0: inactiva, 1: activa)
int bullet_x[MAX_BULLETS]; // Posiciones X de cada bala
int bullet_y[MAX_BULLETS]; // Posiciones Y de cada bala
int flip1_[MAX_BULLETS];
//JUGADOR 2
int x2 = 290;
int y2Estandar = 183;
int y2 = 183;
int w2 = 0;
int column2 = 0;
int frame2 = 1;
int flip22 = 0;
int h2 = 0;
int vY2 = 0;
int jump2 = 0;
int jumpcount2 = 0;
int falling2 = 1;
int running2 = 0;
int shooting2 = 0;
//
int bulletskin2=0;
int bulleth2=0;
int daño2 = 0;
int vidas2 =5;
int winner2 = 0;
//BALAS J2
int bala2 = 0;
int bala_x2 = -1;  // Posición inicial de la bala fuera de la pantalla
int bala_y2 = 180; // Altura inicial de la bala
#define MAX_BULLETS2 3  // Define el número máximo de balas
unsigned char bullet_state2[MAX_BULLETS] = {0}; // Estado de cada bala (0: inactiva, 1: activa)
int bullet_x2[MAX_BULLETS]; // Posiciones X de cada bala
int bullet_y2[MAX_BULLETS]; // Posiciones Y de cada bala
int flip22_[MAX_BULLETS];
// codigo konami
#define KONAMI_LENGTH 5
//J1
int current_index1 = 0;  // Para rastrear el índice actual en el buffer
char konami_code1[] = {'w', 'w', 's', 's', 'e'};
char input_buffer1[KONAMI_LENGTH];  // Para almacenar las entradas del usuario
int konami1 = 0;
//J2
int current_index2 = 0;  // Para rastrear el índice actual en el buffer
char konami_code2[] = {'i', 'i', 'k', 'k', 'o'};
char input_buffer2[KONAMI_LENGTH];  // Para almacenar las entradas del usuario
int konami2 = 0;


//TAMAÑO IMAGEN SD
#define IMAGE_SIZE 65000 // Ajusta el tamaño a 243 * 39 * 2

uint8_t image[IMAGE_SIZE];  // Variable para almacenar los datos de la imagen

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_UART5_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void transmit_uart(char *message);
void transmit_uart3(char *message);
void transmit_uart5(char *message);
int load_image_from_sd_to_play(const char* filename);
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
 //PLAYER1CONFIG(character);
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_USART2_UART_Init();
  MX_FATFS_Init();
  MX_UART5_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  // Montar SD

     fres = f_mount(&fs,"/" , 0);
     if(fres == FR_OK){
     //   transmit_uart("Micro SD is mounted successfully\n\n\n\n");
     } else {
      //   transmit_uart("Micro SD is mounted bad\n\n\n\n");
     }

 HAL_UART_Receive_IT(&huart2, option, 1);  // EMPEZAR RECEPCIÓN
 HAL_UART_Receive_IT(&huart3, option, 1);  // EMPEZAR RECEPCIÓN
 HAL_UART_Receive_IT(&huart5, option2, 1);
	LCD_Init();
	//LCD_Clear(0x2104);					//LCD_Clear() PINTA TODA LA PANTALLA DE UN COLOR (EN 5R6G5B)
	LCD_Clear(0x0000);	//PINTAR TODA LA PANTALLA DE NEGRO
	LCD_Bitmap(69, 35, 182, 75, Titulo);
	LCD_Bitmap(38, 199, 243, 39, Referencias);
	// Leer la imagen binaria desde la SD y almacenarla en la variable image
	/*if (load_image_from_sd_to_play("referencias.bin")) {
		LCD_Bitmap(38, 199, 243, 39, image);
	}*/
	transmit_uart3("1");
	transmit_uart5("1");

void disparar_balaJ1() {
		for (int i = 0; i < MAX_BULLETS; i++) {
			if (bullet_state[i] == 0) { // Encuentra una bala inactiva
				bullet_x[i] = flip1 == 1 ? x1 + 26 : x1 -10; // Inicializa la posición
				bullet_y[i] = y1+bulleth1; // Asigna la posición Y inicial si es necesario
				bullet_state[i] = 1; // Marca la bala como activa
				flip1_[i]= flip1;
				break; // Sal de la búsqueda
			}
		}
	}
void disparar_balaJ2() {
		for (int i = 0; i < MAX_BULLETS2; i++) {
			if (bullet_state2[i] == 0) { // Encuentra una bala inactiva
				bullet_x2[i] = flip22_[i] == 1 ? x2 + 26 : x2 -10; // Inicializa la posición
				bullet_y2[i] = y2+bulleth2; // Asigna la posición Y inicial si es necesario
				bullet_state2[i] = 1; // Marca la bala como activa
				flip22_[i]= flip22;
				break; // Sal de la búsqueda
			}
		}
	}
/*_____________________________________Colisiónes__________________________________________________*/
int detectar_colisionJ1(int bullet_x, int bullet_y, int disparo_x, int disparo_y, int disparo_width, int disparo_height) {
	// Verificar si la bala está dentro de los límites del cuadro de disparo
	if (bullet_x >= disparo_x && bullet_x <= (disparo_x + disparo_width) &&
		bullet_y >= disparo_y && bullet_y <= (disparo_y + disparo_height)) {
		// Reducir vidas del jugador 2 con el daño del jugador 1
		vidas1 = vidas1-daño1;
		frame2 = 10;
		// Comprobar si el cubito ha sido destruido
		if (vidas1 <= 0) {
			winner1 = 1;
			modo = 7;
			// Lógica para cuando el cubito se destruye
			//HAL_Delay(10);
			// Por ejemplo: Mostrar un mensaje o reiniciar el juego
			//LCD_Print("GANA JUGADOR 1", 30, 100, 2, 0xFF0000, 0x2104); // Mensaje en rojo
			// Detener el juego o reiniciar
			//HAL_Delay(100);
			//while(1); // Bucle infinito para detener el juego
		}
		return 1; // Colisión detectada
	}
	return 0; // No hay colisión
}
int detectar_colisionJ2(int bullet_x, int bullet_y, int disparo_x, int disparo_y, int disparo_width, int disparo_height) {
	// Verificar si la bala está dentro de los límites del cuadro de disparo
	if (bullet_x >= disparo_x && bullet_x <= (disparo_x + disparo_width) &&
		bullet_y >= disparo_y && bullet_y <= (disparo_y + disparo_height)) {
		// Reducir vidas del jugador 1 con el daño del jugador 2
		vidas2 = vidas2-daño2;
		frame1 = 10;
		// Comprobar si el cubito ha sido destruido
		if (vidas2 <= 0) {
			winner2 = 1;
			modo = 7;
			//HAL_Delay(100);
			//LCD_Print("GANA JUGADOR 2", 30, 100, 2, 0xFF0000, 0x2104); // Mensaje en rojo
			// Detener el juego o reiniciar
			//HAL_Delay(100);
			//while(1); // Bucle infinito para detener el juego
		}
		return 1; // Colisión detectada
	}
	return 0; // No hay colisión
}
void mostrar_vidasJ1() {
	char buffer[20]; // Buffer para el mensaje
	sprintf(buffer, "Vidas: %d", vidas2); // Formatea el mensaje
	LCD_Print(buffer, 20, 7, 1, 0xFFFFFF, 0x2104); // Muestra las vidas en blanco
	//HAL_Delay(400);
	//LCD_Print("         ", 20, 7, 1, 0xFFFFFF, 0x2104);
}
void mostrar_vidasJ2() {
	char buffer[20]; // Buffer para el mensaje
	sprintf(buffer, "Vidas: %d", vidas1); // Formatea el mensaje
	LCD_Print(buffer, 240, 7, 1, 0xFFFFFF, 0x2104); // Muestra las vidas en blanco
	//HAL_Delay(400);
  // LCD_Print("         ", 120, 7, 1, 0xFFFFFF, 0x2104);
}
void mover_balaJ1() {
		for (int i = 0; i < MAX_BULLETS; i++) {
			if (bullet_state[i] == 1) { // Si la bala está activa
				// Borrar la posición anterior de la bala
				if (flip1_[i] == 1) {
					// Si va a la derecha, borrar la posición anterior
					FillRect(bullet_x[i] - 5, bullet_y[i], 11, 9, 0x2104);
				} else if (flip1 == 0){
					// Si va a la izquierda, borrar la posición anterior
					FillRect(bullet_x[i] + 5, bullet_y[i], 11, 9, 0x2104);
				}
				// Mover la bala hacia adelante o hacia atrás dependiendo del flip
				if (flip1_[i] == 1) {
					bullet_x[i] += 5;  // Mover hacia la derecha
				} else {
					bullet_x[i] -= 5;  // Mover hacia la izquierda
				}
				// Verificar colisión
			   if (detectar_colisionJ1(bullet_x[i], bullet_y[i], x2, y2, 24, 24)) {
				   mostrar_vidasJ2();
				   // Borra la bala en caso de colisión
					 FillRect(bullet_x[i] - 3, bullet_y[i], 10, 8, 0x2104); // Borrar la bala
					 bullet_state[i] = 0; // Desactivar la bala
					 bullet_x[i] = -1; // Reiniciar la posición
					 bullet_y[i] = -1; // Reiniciar la posición
				}
				// Verificar si la bala ha salido de la pantalla
				if (bullet_x[i] < -8 || bullet_x[i] > 320) {
					bullet_x[i] = -1; // Reinicia la posición
					bullet_state[i] = 0; // Marca la bala como inactiva
				} else {
					// Dibujar la nueva posición de la bala
					LCD_Sprite(bullet_x[i], bullet_y[i], 10, 8, Bala, 3, bulletskin1, flip1, 0);
				}
			}
		}
	}
void mover_balaJ2() {
		for (int i = 0; i < MAX_BULLETS2; i++) {
			if (bullet_state2[i] == 1) { // Si la bala está activa
				// Borrar la posición anterior de la bala
				if (flip22_[i] == 1) {
					// Si va a la derecha, borrar la posición anterior
					FillRect(bullet_x2[i] - 5, bullet_y2[i], 11, 9, 0x2104);
				} else {
					// Si va a la izquierda, borrar la posición anterior
					FillRect(bullet_x2[i] + 5, bullet_y2[i], 11, 9, 0x2104);
				}
				// Mover la bala hacia adelante o hacia atrás dependiendo del flip
				if (flip22_[i] == 1) {
					bullet_x2[i] += 5;  // Mover hacia la derecha
				} else {
					bullet_x2[i] -= 5;  // Mover hacia la izquierda
				}
				// Verificar colisión
			   if (detectar_colisionJ2(bullet_x2[i], bullet_y2[i], x1, y1, 24, 24)) {
				   mostrar_vidasJ1();
					// Borra la bala en caso de colisión
					 FillRect(bullet_x2[i] - 2, bullet_y2[i], 10, 8, 0x2104); // Borrar la bala
					 bullet_state2[i] = 0; // Desactivar la bala
					 bullet_x2[i] = -1; // Reiniciar la posición
					 bullet_y2[i] = -1; // Reiniciar la posición
				}
				// Verificar si la bala ha salido de la pantalla
				if (bullet_x2[i] < -8 || bullet_x2[i] > 320) {
					bullet_x2[i] = -1; // Reinicia la posición
					bullet_state2[i] = 0; // Marca la bala como inactiva
				} else {
					// Dibujar la nueva posición de la bala
					LCD_Sprite(bullet_x2[i], bullet_y2[i], 10, 8, Bala, 3, bulletskin2, flip22, 0);
				}
			}
		}
	}
/*____________________________________________JUGADOR 1______________________________________________*/
void Jugador1(){
	HAL_Delay(5);
	if(ch1 == 1){
		LCD_Sprite(x1, y1, w1, h1, megamanA, column1, frame1, flip1, 0);
		y1 = y1+vY1;
		if(jump1 == 1){
			vY1++;
			if (falling1 == 0){
				FillRect(x1, y1+31, 33, 9, 0x2104);
			}else if (falling1 == 1){
				FillRect(x1, y1-24, 33, 25, 0x2104);
			}
			if(vY1 == 0){
				falling1 = 1;
			}
			if(y1 >= y1Estandar){
				vY1 = 0;
				jump1 = 0;
				y1 = y1Estandar;
				frame1 = 0;
				jumpcount1 = 0;
			}
		}
		if(caminarD == 1){
			FillRect(x1-7, y1, 7, 32, 0x2104);	//2104
			caminarD = 0;
		}
		if(caminarI == 1){
			FillRect(x1+33, y1, 7, 32, 0x2104);
			caminarI = 0;
		}
		if (bala == 1) {
			disparar_balaJ1(); // Llama a la función para disparar
			bala = 0;
		}
	}else if (ch1 == 5){
		LCD_Sprite(x1, y1, w1, h1, icemanA, column1, frame1, flip1, 0);
		y1 = y1+vY1;
		if(jump1 == 1){
			vY1++;
			if (falling1 == 0){
				FillRect(x1, y1+28, 35, 9, 0x2104);
			}else if (falling1 == 1){
				FillRect(x1, y1-24, 35, 25, 0x2104);
			}
			if(vY1 == 0){
				falling1 = 1;
			}
			if(y1 >= y1Estandar){
				vY1 = 0;
				jump1 = 0;
				y1 = y1Estandar;
				if (shooting1 == 1){
					frame1 = 5;
				}else if (shooting1 == 2){
					frame1 = 6;
				}else {
					frame1 = 0;
				}
				jumpcount1 = 0;
			}
		}
		if(caminarD == 1){
			FillRect(x1-7, y1, 7, 29, 0x2104);	//2104
			caminarD = 0;
		}
		if(caminarI == 1){
			FillRect(x1+33, y1, 7, 29, 0x2104);
			caminarI = 0;
		}
		if (bala == 1) {
			disparar_balaJ1(); // Llama a la función para disparar
			bala = 0;
		}
	}else if (ch1 == 8){
		LCD_Sprite(x1, y1, w1, h1, rollA, column1, frame1, flip1, 0);
		y1 = y1+vY1;
		if(jump1 == 1){
			vY1++;
			if (falling1 == 0){
				FillRect(x1, y1+30, 33, 9, 0x2104);
			}else if (falling1 == 1){
				FillRect(x1, y1-24, 33, 25, 0x2104);
			}
			if(vY1 == 0){
				falling1 = 1;
			}
			if(y1 >= y1Estandar){
				vY1 = 0;
				jump1 = 0;
				y1 = y1Estandar;
				frame1 = 0;
				jumpcount1 = 0;
			}
		}
		if(caminarD == 1){
			FillRect(x1-7, y1, 7, 30, 0x2104);	//2104
			caminarD = 0;
		}
		if(caminarI == 1){
			FillRect(x1+33, y1, 7, 30, 0x2104);
			caminarI = 0;
		}
		if (bala == 1) {
			disparar_balaJ1(); // Llama a la función para disparar
			bala = 0;
		}
	}else if (ch1 == 9){
		LCD_Sprite(x1, y1, w1, h1, marioA, column1, frame1, flip1, 0);
		y1 = y1+vY1;
		if(jump1 == 1){
			vY1++;
			if (falling1 == 0){
				FillRect(x1, y1+25, 26, 9, 0x2104);
			}else if (falling1 == 1){
				FillRect(x1, y1-24, 26, 25, 0x2104);
			}
			if(vY1 == 0){
				falling1 = 1;
			}
			if(y1 >= y1Estandar){
				vY1 = 0;
				jump1 = 0;
				y1 = y1Estandar;
				frame1 = 0;
				jumpcount1 = 0;
			}
		}
		if(caminarD == 1){
			FillRect(x1-7, y1, 7, 26, 0x2104);	//2104
			caminarD = 0;
		}
		if(caminarI == 1){
			FillRect(x1+33, y1, 7, 26, 0x2104);
			caminarI = 0;
		}
		if (bala == 1) {
			disparar_balaJ1(); // Llama a la función para disparar
			bala = 0;
		}
	}
}
void Jugador2(){
	HAL_Delay(5);
	if(ch2 == 1){
		LCD_Sprite(x2, y2, w2, h2, megamanA, column2, frame2, flip22, 0);
		y2 = y2+vY2;
		if(jump2 == 1){
			vY2++;
			if (falling2 == 0){
				FillRect(x2, y2+31, 33, 9, 0x2104);
			}else if (falling2 == 1){
				FillRect(x2, y2-24, 33, 25, 0x2104);
			}
			if(vY2 == 0){
				falling2 = 1;
			}
			if(y2 >= y2Estandar){
				vY2 = 0;
				jump2 = 0;
				y2 = y2Estandar;
				frame2 = 0;
				jumpcount2 = 0;
			}
		}
		if(caminarD2 == 1){
			FillRect(x2-7, y2, 7, 32, 0x2104);	//2104
			caminarD2 = 0;
		}
		if(caminarI2 == 1){
			FillRect(x2+33, y2, 7, 32, 0x2104);
			caminarI2 = 0;
		}
		if (bala2 == 1) {
			disparar_balaJ2(); // Llama a la función para disparar
			bala2 = 0;
		}
	}else if (ch2 == 5){
		LCD_Sprite(x2, y2, w2, h2, icemanA, column2, frame2, flip22, 0);
		y2 = y2+vY2;
		if(jump2 == 1){
			vY2++;
			if (falling2 == 0){
				FillRect(x2, y2+28, 35, 9, 0x2104);
			}else if (falling2 == 1){
				FillRect(x2, y2-24, 35, 25, 0x2104);
			}
			if(vY2 == 0){
				falling2 = 1;
			}
			if(y2 >= y2Estandar){
				vY2 = 0;
				jump2 = 0;
				y2 = y2Estandar;
				if (shooting2 == 1){
					frame2 = 5;
				}else if (shooting2 == 2){
					frame2 = 6;
				}else {
					frame2 = 0;
				}
				jumpcount2 = 0;
			}
		}
		if(caminarD2 == 1){
			FillRect(x2-7, y2, 7, 29, 0x2104);	//2104
			caminarD2 = 0;
		}
		if(caminarI2 == 1){
			FillRect(x2+33, y2, 7, 29, 0x2104);
			caminarI2 = 0;
		}
		if (bala2 == 1) {
			disparar_balaJ2(); // Llama a la función para disparar
			bala2 = 0;
		}
	}else if (ch2 == 8){
		LCD_Sprite(x2, y2, w2, h2, rollA, column2, frame2, flip22, 0);
		y2 = y2+vY2;
		if(jump2 == 1){
			vY2++;
			if (falling2 == 0){
				FillRect(x2, y2+30, 33, 9, 0x2104);
			}else if (falling1 == 1){
				FillRect(x2, y2-24, 33, 25, 0x2104);
			}
			if(vY2 == 0){
				falling2 = 1;
			}
			if(y2 >= y2Estandar){
				vY2 = 0;
				jump2 = 0;
				y2 = y2Estandar;
				frame2 = 0;
				jumpcount2 = 0;
			}
		}
		if(caminarD2 == 1){
			FillRect(x2-7, y2, 7, 30, 0x2104);	//2104
			caminarD2 = 0;
		}
		if(caminarI2 == 1){
			FillRect(x2+33, y2, 7, 30, 0x2104);
			caminarI2 = 0;
		}
		if (bala2 == 1) {
			disparar_balaJ2(); // Llama a la función para disparar
			bala2 = 0;
		}
	}else if (ch2 == 9){
		LCD_Sprite(x2, y2, w2, h2, marioA, column2, frame2, flip22, 0);
		y2 = y2+vY2;
		if(jump2 == 1){
			vY2++;
			if (falling2 == 0){
				FillRect(x2, y2+25, 26, 9, 0x2104);
			}else if (falling1 == 1){
				FillRect(x2, y2-24, 26, 25, 0x2104);
			}
			if(vY2 == 0){
				falling2 = 1;
			}
			if(y2 >= y2Estandar){
				vY2 = 0;
				jump2 = 0;
				y2 = y2Estandar;
				frame2 = 0;
				jumpcount2 = 0;
			}
		}
		if(caminarD2 == 1){
			FillRect(x2-7, y2, 7, 26, 0x2104);	//2104
			caminarD2 = 0;
		}
		if(caminarI2 == 1){
			FillRect(x2+33, y2, 7, 26, 0x2104);
			caminarI2 = 0;
		}
		if (bala2 == 1) {
			disparar_balaJ2(); // Llama a la función para disparar
			bala2 = 0;
		}
	}
}

// Función para leer una imagen desde la SD y almacenarla en la variable play

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
		if(modo==0){

			if(start==0){
				LCD_Bitmap(117, 145, 86, 7, PressStart);
			}
			else if(start==1){
				FillRect(117, 145, 86, 7, 0x0000);
				HAL_Delay(100);
				LCD_Bitmap(117, 145, 86, 7, PressStart);
				HAL_Delay(100);
				startcounter++;
			}
			if (startcounter == 7){
				start = 0;
				modo = 1;
			}
		}
		else if(modo==50){
			FillRect(0, 0, 320, 81, 0x039D);
			//FillRect(0, 81, 320, 80, 0xF5E7);
			FillRect(0, 81, 320, 80, 0x19EB);
			LCD_Print("VS.", 138, 111, 2, 0xFFFF, 0x19EB);		//LETRAS QUE DICEN "VS"
			//LCD_Print("VS.", 140, 111, 2, 0x9FFE, 0x039D);	//LETRAS QUE DICEN "VS"
			FillRect(0, 161, 320, 80, 0x039D);
			LCD_Sprite(80, 110, 20, 27, marioB, 1, 1, 1, 0);	//9
			LCD_Sprite(214, 110, 21, 28, rollB, 1, 1, 0, 0);	//8
			FillRect(0, 135, 320, 5, 0xFFFF);
			HAL_Delay(10000);
			FillRect(0, 0, 320, 81, 0x039D);
			//FillRect(0, 81, 320, 80, 0xF5E7);
			FillRect(0, 81, 320, 80, 0x19EB);
			LCD_Print("VS.", 138, 111, 2, 0xFFFF, 0x19EB);		//LETRAS QUE DICEN "VS"
			//LCD_Print("VS.", 140, 111, 2, 0x9FFE, 0x039D);	//LETRAS QUE DICEN "VS"
			FillRect(0, 161, 320, 80, 0x039D);
			LCD_Sprite(80, 110, 21, 28, rollB, 1, 1, 1, 0);		//8
			LCD_Sprite(214, 110, 20, 27, marioB, 1, 1, 0, 0);	//9
			FillRect(0, 135, 320, 5, 0xFFFF);
			HAL_Delay(7000);
		}
		else if(modo==1){
			LCD_Clear(0x039D);					//PINTAR TODA LA PANTALLA DE UN COLOR (EN 5R6G5B)
			LCD_Bitmap(104, 59, 45, 45, selectorJ1);
			LCD_Print("MEGAMAN", 100, 105, 1, 0x9FFE, 0x039D);	//LETRAS QUE DICEN "MEGAMAN"
			LCD_Bitmap(104, 127, 45, 45, selector);
			LCD_Print("ROLL", 110, 173, 1, 0x9FFE, 0x039D);	//LETRAS QUE DICEN "ELECMAN"
			LCD_Bitmap(172, 59, 45, 45, selectorJ2);
			LCD_Print("MARIO", 176, 105, 1, 0x9FFE, 0x039D);	//LETRAS QUE DICEN "CUTMAN"
			LCD_Bitmap(172, 127, 45, 45, selector);
			LCD_Print("ICEMAN", 171, 173, 1, 0x9FFE, 0x039D);	//LETRAS QUE DICEN "ICEMAN"
			modo = 2;
		}
		else if(modo==2){
			//if (chselect1 == 1 && chselect2 == 1){		//SI AMBOS JUGADORES SELECCIONARON PERSONAJE, CAMBIAR DE ESCENA
			if (chselect1 == 1 && chselect2 == 1){		//SI AMBOS JUGADORES SELECCIONARON PERSONAJE, CAMBIAR DE ESCENA
				modo = 3;
			}
			HAL_Delay(5);
			LCD_Bitmap(114, 72, 23, 25, megaman);
			LCD_Bitmap(186, 73, 16, 24, mario);
			LCD_Bitmap(117, 141, 17, 24, roll);
			LCD_Bitmap(182, 141, 24, 24, iceman);
			//LCD_Bitmap(150, 178, 17, 24, roll);
			//LCD_Bitmap(218, 178, 16, 24, mario);
			//CASILLA MEGAMAN (1,1) J1
			if(selector1x == 1 && selector1y == 1 && change1 == 1){
				if (selector1xAntiguo == 2 && selector1yAntiguo == 1){		//SI LA CASILLA ANTERIOR EN LA QUE ESTABA EL SELECTOR ERA LA (2,1)
					LCD_Bitmap(172, 59, 45, 45, selector);					//REGRESARLA A SU COLOR ORIGINAL
					selector1xAntiguo = 0;
					selector1yAntiguo = 0;
				}else if (selector1xAntiguo == 1 && selector1yAntiguo == 2){//SI LA CASILLA ANTERIOR EN LA QUE ESTABA EL SELECTOR ERA LA (1,2)
					LCD_Bitmap(104, 127, 45, 45, selector);					//REGRESARLA A SU COLOR ORIGINAL
					selector1xAntiguo = 0;
					selector1yAntiguo = 0;
				}
				if (chselect1 == 1){
					LCD_Bitmap(104, 59, 45, 45, selectorS);
					ch1 = 1;										//J2 SELECCIONÓ A MEGAMAN
					change1 = 0;
				}else{
					LCD_Bitmap(104, 59, 45, 45, selectorJ1);
					change1 = 0;
				}
			//CASILLA ROLL (1,2) J1
			}else if(selector1x == 1 && selector1y == 2 && change1 == 1){
				if (selector1xAntiguo == 1 && selector1yAntiguo == 1){		//SI LA CASILLA ANTERIOR EN LA QUE ESTABA EL SELECTOR ERA LA (1,1)
					LCD_Bitmap(104, 59, 45, 45, selector);					//REGRESARLA A SU COLOR ORIGINAL
					selector1xAntiguo = 0;
					selector1yAntiguo = 0;
				}else if (selector1xAntiguo == 2 && selector1yAntiguo == 2){//SI LA CASILLA ANTERIOR EN LA QUE ESTABA EL SELECTOR ERA LA (2,2)
					LCD_Bitmap(172, 127, 45, 45, selector);					//REGRESARLA A SU COLOR ORIGINAL
					selector1xAntiguo = 0;
					selector1yAntiguo = 0;
				}
				if (chselect1 == 1){
					LCD_Bitmap(104, 127, 45, 45, selectorS);
					ch1 = 8;										//J2 SELECCIONÓ A ELECMAN
					change1 = 0;
				}else{
					LCD_Bitmap(104, 127, 45, 45, selectorJ1);
					change1 = 0;
				}
			//CASILLA MARIO (2,1) J1
			}else if(selector1x == 2 && selector1y == 1 && change1 == 1){
				if (selector1xAntiguo == 1 && selector1yAntiguo == 1){		//SI LA CASILLA ANTERIOR EN LA QUE ESTABA EL SELECTOR ERA LA (1,1)
					LCD_Bitmap(104, 59, 45, 45, selector);					//REGRESARLA A SU COLOR ORIGINAL
					selector1xAntiguo = 0;
					selector1yAntiguo = 0;
				}else if (selector1xAntiguo == 2 && selector1yAntiguo == 2){//SI LA CASILLA ANTERIOR EN LA QUE ESTABA EL SELECTOR ERA LA (2,2)
					LCD_Bitmap(172, 127, 45, 45, selector);					//REGRESARLA A SU COLOR ORIGINAL
					selector1xAntiguo = 0;
					selector1yAntiguo = 0;
				}
				if (chselect1 == 1){
					LCD_Bitmap(172, 59, 45, 45, selectorS);
					ch1 = 9;										//J2 SELECCIONÓ A ELECMAN
					change1 = 0;
				}else{
					LCD_Bitmap(172, 59, 45, 45, selectorJ1);
					change1 = 0;
				}
			//CASILLA ICEMAN (2,2) J1
			}else if(selector1x == 2 && selector1y == 2 && change1 == 1){
				if (selector1xAntiguo == 2 && selector1yAntiguo == 1){		//SI LA CASILLA ANTERIOR EN LA QUE ESTABA EL SELECTOR ERA LA (1,1)
					LCD_Bitmap(172, 59, 45, 45, selector);					//REGRESARLA A SU COLOR ORIGINAL
					selector1xAntiguo = 0;
					selector1yAntiguo = 0;
				}else if (selector1xAntiguo == 1 && selector1yAntiguo == 2){//SI LA CASILLA ANTERIOR EN LA QUE ESTABA EL SELECTOR ERA LA (2,2)
					LCD_Bitmap(104, 127, 45, 45, selector);					//REGRESARLA A SU COLOR ORIGINAL
					selector1xAntiguo = 0;
					selector1yAntiguo = 0;
				}
				if (chselect1 == 1){
					LCD_Bitmap(172, 127, 45, 45, selectorS);
					ch1 = 5;										//J2 SELECCIONÓ A ELECMAN
					change1 = 0;
				}else{
					LCD_Bitmap(172, 127, 45, 45, selectorJ1);
					change1 = 0;
				}
			}
			//CASILLA MEGAMAN (1,1) J2
			if(selector2x == 1 && selector2y == 1 && change2 == 1){
				if (selector2xAntiguo == 2 && selector2yAntiguo == 1){		//SI LA CASILLA ANTERIOR EN LA QUE ESTABA EL SELECTOR ERA LA (2,1)
					LCD_Bitmap(172, 59, 45, 45, selector);					//REGRESARLA A SU COLOR ORIGINAL
					selector2xAntiguo = 0;
					selector2yAntiguo = 0;
				}else if (selector2xAntiguo == 1 && selector2yAntiguo == 2){//SI LA CASILLA ANTERIOR EN LA QUE ESTABA EL SELECTOR ERA LA (1,2)
					LCD_Bitmap(104, 127, 45, 45, selector);					//REGRESARLA A SU COLOR ORIGINAL
					selector2xAntiguo = 0;
					selector2yAntiguo = 0;
				}
				if (chselect2 == 1){
					LCD_Bitmap(104, 59, 45, 45, selectorS);
					ch2 = 1;										//J2 SELECCIONÓ A MEGAMAN
					change2 = 0;
				}else{
					LCD_Bitmap(104, 59, 45, 45, selectorJ2);
					change2 = 0;
				}
				//CASILLA ROLL (1,2) J2
				}else if(selector2x == 1 && selector2y == 2 && change2 == 1){
					if (selector2xAntiguo == 1 && selector2yAntiguo == 1){		//SI LA CASILLA ANTERIOR EN LA QUE ESTABA EL SELECTOR ERA LA (1,1)
						LCD_Bitmap(104, 59, 45, 45, selector);					//REGRESARLA A SU COLOR ORIGINAL
						selector2xAntiguo = 0;
						selector2yAntiguo = 0;
					}else if (selector2xAntiguo == 2 && selector2yAntiguo == 2){//SI LA CASILLA ANTERIOR EN LA QUE ESTABA EL SELECTOR ERA LA (2,2)
						LCD_Bitmap(172, 127, 45, 45, selector);					//REGRESARLA A SU COLOR ORIGINAL
						selector2xAntiguo = 0;
						selector2yAntiguo = 0;
					}
					if (chselect2 == 1){
						LCD_Bitmap(104, 127, 45, 45, selectorS);
						ch2 = 8;										//J2 SELECCIONÓ A ELECMAN
						change2 = 0;
					}else{
						LCD_Bitmap(104, 127, 45, 45, selectorJ2);
						change2 = 0;
					}
				//CASILLA MARIO (2,1) J2
				}else if(selector2x == 2 && selector2y == 1 && change2 == 1){
					if (selector2xAntiguo == 1 && selector2yAntiguo == 1){		//SI LA CASILLA ANTERIOR EN LA QUE ESTABA EL SELECTOR ERA LA (1,1)
						LCD_Bitmap(104, 59, 45, 45, selector);					//REGRESARLA A SU COLOR ORIGINAL
						selector2xAntiguo = 0;
						selector2yAntiguo = 0;
					}else if (selector2xAntiguo == 2 && selector2yAntiguo == 2){//SI LA CASILLA ANTERIOR EN LA QUE ESTABA EL SELECTOR ERA LA (2,2)
						LCD_Bitmap(172, 127, 45, 45, selector);					//REGRESARLA A SU COLOR ORIGINAL
						selector2xAntiguo = 0;
						selector2yAntiguo = 0;
					}
					if (chselect2 == 1){
						LCD_Bitmap(172, 59, 45, 45, selectorS);
						ch2 = 9;										//J2 SELECCIONÓ A ELECMAN
						change2 = 0;
					}else{
						LCD_Bitmap(172, 59, 45, 45, selectorJ2);
						change2 = 0;
					}
				//CASILLA ICEMAN (2,2) J2
				}else if(selector2x == 2 && selector2y == 2 && change2 == 1){
					if (selector2xAntiguo == 2 && selector2yAntiguo == 1){		//SI LA CASILLA ANTERIOR EN LA QUE ESTABA EL SELECTOR ERA LA (1,1)
						LCD_Bitmap(172, 59, 45, 45, selector);					//REGRESARLA A SU COLOR ORIGINAL
						selector2xAntiguo = 0;
						selector2yAntiguo = 0;
					}else if (selector2xAntiguo == 1 && selector2yAntiguo == 2){//SI LA CASILLA ANTERIOR EN LA QUE ESTABA EL SELECTOR ERA LA (2,2)
						LCD_Bitmap(104, 127, 45, 45, selector);					//REGRESARLA A SU COLOR ORIGINAL
						selector2xAntiguo = 0;
						selector2yAntiguo = 0;
					}
					if (chselect2 == 1){
						LCD_Bitmap(172, 127, 45, 45, selectorS);
						ch2 = 5;										//J2 SELECCIONÓ A ELECMAN
						change2 = 0;
					}else{
						LCD_Bitmap(172, 127, 45, 45, selectorJ2);
						change2 = 0;
					}
				}
		}
		else if(modo==3){
					FillRect(0, 0, 320, 81, 0x039D);
					//FillRect(0, 81, 320, 80, 0xF5E7);
					FillRect(0, 81, 320, 80, 0x19EB);
					LCD_Print("VS.", 138, 111, 2, 0xFFFF, 0x19EB);		//LETRAS QUE DICEN "VS"
					//LCD_Print("VS.", 140, 111, 2, 0x9FFE, 0x039D);	//LETRAS QUE DICEN "VS"
					FillRect(0, 161, 320, 80, 0x039D);
					modo = 4;
		}
		else if(modo==4){
			if(ch1 == 1){
				LCD_Sprite(80, 110, 25, 28, megamanB, 1, 1, 0, 0);	//1
				//PARAMETROS DE MEGAMAN J1
				ch1 = 1;
				x1 = 20;
				y1 = 176;
				y1Estandar = 176;
				w1 = 32;
				h1 = 32;
				column1 = 11;
				frame1 = 0;
				flip1 = 1;
				bulleth1 = 15;
				bulletskin1 = 0;
				daño1 = 1;
			}else if (ch1 == 5){
				LCD_Sprite(80, 110, 28, 28, icemanB, 1, 1, 1, 0);	//5
				//PARAMETROS DE ICEMAN
				ch1 = 5;
				x1 = 20;
				y1 = 179;
				y1Estandar = 179;
				w1 = 34;
				h1 = 29;
				column1 = 11;
				frame1 = 0;
				flip1 = 1;
				bulleth1 = 10;
				bulletskin1 = 1;
				daño1 = 2;
			}else if (ch1 == 8){
				LCD_Sprite(80, 110, 21, 28, rollB, 1, 1, 1, 0);		//8
				//PARAMETROS DE ROLL J1
				ch1 = 8;
				x1 = 20;
				y1 = 177;
				y1Estandar = 177;
				w1 = 31;
				h1 = 30;
				column1 = 11;
				frame1 = 0;
				flip1 = 1;
				bulleth1 = 15;
				bulletskin1 = 0;
				daño1 = 1;
			}else if (ch1 == 9){
				LCD_Sprite(80, 110, 20, 27, marioB, 1, 1, 1, 0);	//9
				//PARAMETROS DE MARIO J1
				ch1 = 9;
				x1 = 20;
				y1 = 182;
				y1Estandar = 182;
				w1 = 26;
				h1 = 26;
				column1 = 11;
				frame1 = 0;
				flip1 = 1;
				bulleth1 = 12;
				bulletskin1 = 2;
				daño1 = 1;
			}
			if(ch2 == 1){
				LCD_Sprite(214, 110, 25, 28, megamanB, 1, 1, 1, 2);	//1
				//PARAMETROS DE MEGAMAN J2
				ch2 = 1;
				x2 = 275;
				y2 = 176;
				y2Estandar = 176;
				w2 = 32;
				h2 = 32;
				column2 = 11;
				frame2 = 0;
				flip22 = 0;
				bulleth2 = 15;
				bulletskin2 = 0;
				daño2 = 1;
			}else if (ch2 == 5){
				LCD_Sprite(214, 110, 28, 28, icemanB, 1, 1, 0, 0);	//5
				//PARAMETROS DE ICEMAN J2
				ch2 = 5;
				x2 = 275;
				y2 = 179;
				y2Estandar = 179;
				w2 = 34;
				h2 = 29;
				column2 = 11;
				frame2 = 0;
				flip22 = 0;
				bulleth2 = 10;
				bulletskin2 = 1;
				daño2 = 2;
			}else if (ch2 == 8){
				LCD_Sprite(214, 110, 21, 28, rollB, 1, 1, 0, 0);	//8
				//PARAMETROS DE ROLL J2
				ch2 = 8;
				x2 = 275;
				y2 = 177;
				y2Estandar = 177;
				w2 = 31;
				h2 = 30;
				column2 = 11;
				frame2 = 0;
				flip22 = 0;
				bulleth2 = 15;
				bulletskin2 = 0;
				daño2 = 1;
			}else if (ch2 == 9){
				LCD_Sprite(214, 110, 20, 27, marioB, 1, 1, 0, 0);	//9
				//PARAMETROS DE MARIO J2
				ch2 = 9;
				x2 = 275;
				y2 = 182;
				y2Estandar = 182;
				w2 = 26;
				h2 = 26;
				column2 = 11;
				frame2 = 0;
				flip22 = 0;
				bulleth2 = 12;
				bulletskin2 = 2;
				daño2 = 1;
			}
			FillRect(0, 135, 320, 5, 0x19EB);
			transmit_uart3("2");
			transmit_uart5("2");
			HAL_Delay(6000);
			transmit_uart5("8");
			modo = 5;
		}
		else if(modo==5){
			LCD_Clear(0x2104);					//PINTAR TODA LA PANTALLA DE UN COLOR (EN 5R6G5B)
			LCD_Bitmap(0, 208, 64, 32, plataforma);
			LCD_Bitmap(64, 208, 64, 32, plataforma);
			LCD_Bitmap(128, 208, 64, 32, plataforma);
			LCD_Bitmap(192, 208, 64, 32, plataforma);
			LCD_Bitmap(256, 208, 64, 32, plataforma);
			//PARAMETROS DE ROLL J1
			/*ch1 = 8;
			x1 = 20;
			y1 = 178;
			y1Estandar = 178;
			w1 = 32;
			h1 = 30;
			column1 = 11;
			frame1 = 0;*/

			modo=6;
		}else if(modo==6){
			transmit_uart3("3");
			transmit_uart5("3");
			Jugador1();
			mover_balaJ1();
			Jugador2();
			mover_balaJ2();
			//check_konami_code(option[0]);
			if(konami1 == 1 || konami2 == 1){
				LCD_Print("Pablo ponganos", 50, 100, 2, 0xFF0000, 0x2104);
				LCD_Print("100", 115, 130, 2, 0xFF0000, 0x2104);
				FillRect(x1, y1, w1, h1, 0x2104);
				FillRect(x2, y2, w2, h2, 0x2104);
				LCD_Bitmap(94, 149, 132, 58, PABLOEASTEREGG);
				HAL_Delay(10000);
				LCD_Print("              ", 50, 100, 2, 0xFF0000, 0x2104);		//BORRAR LETRAS
				LCD_Print("   ", 115, 130, 3, 0xFF0000, 0x2104);				//BORRAR LETRAS
				FillRect(94, 149, 132, 58, 0x2104);
				konami1 = 0;
				konami2 = 0;
				modo = 6;
				current_index1 = 0;  // Reiniciar el índice
				current_index2 = 0;  // Reiniciar el índice
			}
		}else if(modo==7){
			if (winner1 == 1 && winner2 == 0){
				transmit_uart3("4");
				LCD_Print("PLAYER 1 WINS!", 55, 100, 2, 0xFFFF, 0xF000); // Mensaje en rojo

			}else if (winner1 == 0 && winner2 == 1){
				transmit_uart3("4");
				LCD_Print("PLAYER 2 WINS!", 55, 100, 2, 0xFFFF, 0x0015); // Mensaje en rojo
			}
			HAL_Delay(3000);
			modo = 8;
		}else if(modo==8){
			LCD_Print("PRESIONA START", 55, 100, 2, 0xFFFF, 0x039D); // Mensaje en rojo
			LCD_Print("PARA REINICIAR", 55, 125, 2, 0xFFFF, 0x039D); // Mensaje en rojo
			if (start == 1){
				caminarD = 0;
				caminarI = 0;
				caminarD2 = 0;
				caminarI2 = 0;
				start = 0;
				startcounter = 0;
				//********SELECCIÓN DE PERSONAJES********
				//JUGADOR 1
				selector1x = 1;
				selector1y = 1;
				selector1xAntiguo = 0;
				selector1yAntiguo = 0;
				change1 = 1;
				chselect1 = 0;
				ch1 = 0;
				//JUGADOR 2
				selector2x = 2;
				selector2y = 1;
				selector2xAntiguo = 0;
				selector2yAntiguo = 0;
				change2 = 1;
				chselect2 = 0;
				ch2 = 0;
				//****************PARAMETROS**************
				//JUGADOR 1
				x1 = 0;
				y1Estandar = 183;
				y1 = 183;
				w1 = 0;
				h1 = 0;
				column1 = 0;
				frame1 = 1;
				flip1 = 0;
				vY1 = 0;
				jump1 = 0;
				jumpcount1 = 0;
				falling1 = 1;
				running1 = 0;
				shooting1 = 0;
				//
				bulletskin1=0;
				bulleth1=0;
				daño1 =0;
				vidas1 = 5; // Inicializa las vidas
				winner1 = 0;
				//BALAS J1
				bala = 0;
				bala_x = -1;  // Posición inicial de la bala fuera de la pantalla
				bala_y = 180; // Altura inicial de la bala
				//JUGADOR 2
				x2 = 290;
				y2Estandar = 183;
				y2 = 183;
				w2 = 0;
				column2 = 0;
				frame2 = 1;
				flip22 = 0;
				h2 = 0;
				vY2 = 0;
				jump2 = 0;
				jumpcount2 = 0;
				falling2 = 1;
				running2 = 0;
				shooting2 = 0;
				//
				bulletskin2=0;
				bulleth2=0;
				daño2 = 0;
				vidas2 =5;
				winner2 = 0;
				//BALAS J2
				bala2 = 0;
				bala_x2 = -1;  // Posición inicial de la bala fuera de la pantalla
				bala_y2 = 180; // Altura inicial de la bala
				modo = 1;
			}
		}else if(modo==9){
			LCD_Clear(0x0000);	//PINTAR TODA LA PANTALLA DE NEGRO
			LCD_Bitmap(69, 35, 182, 75, Titulo);
			LCD_Bitmap(38, 199, 243, 39, Referencias);
			/*if (load_image_from_sd_to_play("referencias.bin")) {
				LCD_Bitmap(38, 199, 243, 39, image);
			}*/
			HAL_Delay(500);
			start = 0;
			startcounter = 0;
			modo = 0;
		}
		//for (int x = 0; x < 320-23 ; x++){
		//HAL_Delay(15);
		//int anim2 = (x/35)%2;
		//LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[], int columns, int index, char flip, char offset);
		//LCD_Sprite(46, 182, 23, 26, MegamanIDLE, 2, 1, 0, 0);
		//}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
	//void PLAYER1CONFIG(uint8_t character){
		//if (character == 1){
			//w1 = 23;
			//h1 = 26;
			//ch1 = MegamanIDLE;
		//}
	//}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */
  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */
  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */
  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief UART5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART5_Init(void)
{

  /* USER CODE BEGIN UART5_Init 0 */
  /* USER CODE END UART5_Init 0 */

  /* USER CODE BEGIN UART5_Init 1 */
  /* USER CODE END UART5_Init 1 */
  huart5.Instance = UART5;
  huart5.Init.BaudRate = 9600;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART5_Init 2 */
  /* USER CODE END UART5_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */
  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */
  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */
  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */
  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */
  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */
  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LCD_RST_Pin|LCD_D1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD_RD_Pin|LCD_WR_Pin|LCD_RS_Pin|LCD_D7_Pin
                          |LCD_D0_Pin|LCD_D2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin|LCD_D6_Pin|LCD_D3_Pin|LCD_D5_Pin
                          |LCD_D4_Pin|SD_SS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LCD_RST_Pin LCD_D1_Pin */
  GPIO_InitStruct.Pin = LCD_RST_Pin|LCD_D1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_RD_Pin LCD_WR_Pin LCD_RS_Pin LCD_D7_Pin
                           LCD_D0_Pin LCD_D2_Pin */
  GPIO_InitStruct.Pin = LCD_RD_Pin|LCD_WR_Pin|LCD_RS_Pin|LCD_D7_Pin
                          |LCD_D0_Pin|LCD_D2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_CS_Pin LCD_D6_Pin LCD_D3_Pin LCD_D5_Pin
                           LCD_D4_Pin SD_SS_Pin */
  GPIO_InitStruct.Pin = LCD_CS_Pin|LCD_D6_Pin|LCD_D3_Pin|LCD_D5_Pin
                          |LCD_D4_Pin|SD_SS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

int load_image_from_sd_to_play(const char* filename) {
    FIL fil;
    UINT bytes_read;
    FRESULT fres;

    // Abrir el archivo desde la SD
    fres = f_open(&fil, filename, FA_READ);
    if (fres != FR_OK) {
      //  transmit_uart("Error al abrir el archivo en la SD\n");
        return 0;  // Error al abrir el archivo
    }

    // Leer los datos del archivo y almacenarlos en la variable play
    fres = f_read(&fil, image, IMAGE_SIZE, &bytes_read);
    if (fres != FR_OK || bytes_read == 0) {
      //  transmit_uart("Error al leer la imagen desde la SD\n");
        f_close(&fil);
        return 0;  // Error al leer el archivo
    }

    // Cerrar el archivo
    f_close(&fil);
   // transmit_uart("Imagen cargada correctamente desde la SD a la variable play\n");
    return 1;  // Éxito
}

void transmit_uart2(char *message) {
   HAL_UART_Transmit(&huart2, (uint8_t*)message, strlen(message), HAL_MAX_DELAY);
}
void transmit_uart3(char *message) {
   HAL_UART_Transmit(&huart3, (uint8_t*)message, strlen(message), HAL_MAX_DELAY);
}
void transmit_uart5(char *message) {
   HAL_UART_Transmit(&huart5, (uint8_t*)message, strlen(message), HAL_MAX_DELAY);
}
/*______Código Konami_________________________*/
void check_konami_code1() {
   // Verificar si el buffer coincide con el código Konami
   int match = 1;  // Asumimos que hay coincidencia
   for (int i = 0; i < KONAMI_LENGTH; i++) {
       if (input_buffer1[i] != konami_code1[i]) {
           match = 0;  // Si no coinciden, desactivamos la coincidencia
           break;
       }
   }
   // Si coincide, activamos la escena
   if (match) {
       //transmit_uart2("Código Konami completado \r\n");
       modo = 99;
       konami1 =1;
   }
}
void check_konami_code2() {
   // Verificar si el buffer coincide con el código Konami
   int match = 1;  // Asumimos que hay coincidencia
   for (int i = 0; i < KONAMI_LENGTH; i++) {
       if (input_buffer2[i] != konami_code2[i]) {
           match = 0;  // Si no coinciden, desactivamos la coincidencia
           break;
       }
   }
   // Si coincide, activamos la escena
   if (match) {
       //transmit_uart2("Código Konami completado \r\n");
       modo = 99;
       konami2 =1;
   }
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART3){
			if (modo == 0){
				switch (option[0]){
						case 'd':
							strcpy(tx_buffer, "d");
							break;
						case 'a':
							strcpy(tx_buffer, "a");
							break;
						case 'e':
							strcpy(tx_buffer, "e");
							break;
						case 'x':
							strcpy(tx_buffer, "x");
							start = 1;
							break;
						default:
							break;
						}
			}if (modo == 2){
				switch (option[0]){
						case 'w':
							strcpy(tx_buffer, "w");
							if (chselect1 != 1){
								selector1xAntiguo = selector1x;
								selector1yAntiguo = selector1y;
								selector1y--;
								if (selector1x == selector2x && selector1y == selector2y){
									selector1y++;
								}else{
									change1=1;
								}
								if (selector1y <= 0){
									selector1y = 1;
								}
							}
							break;
						case 'a':
							strcpy(tx_buffer, "a");
							if (chselect1 != 1){
								selector1xAntiguo = selector1x;
								selector1yAntiguo = selector1y;
								selector1x--;
								if (selector1x == selector2x && selector1y == selector2y){
									selector1x++;
								}else{
									change1=1;
								}
								if (selector1x <= 0){
									selector1x = 1;
								}
							}
							break;
						case 's':
							if (chselect1 != 1){
								selector1xAntiguo = selector1x;
								selector1yAntiguo = selector1y;
								selector1y++;
								if (selector1x == selector2x && selector1y == selector2y){
									selector1y--;
								}else{
									change1=1;
								}
								change1=1;
								if (selector1y >= 3){
									selector1y = 2;
								}
							}
							break;
						case 'd':
							strcpy(tx_buffer, "d");
							if (chselect1 != 1){
								selector1xAntiguo = selector1x;
								selector1yAntiguo = selector1y;
								selector1x++;
								if (selector1x == selector2x && selector1y == selector2y){
									selector1x--;
								}else{
									change1=1;
								}
								if (selector1x >= 3){
									selector1x = 2;
								}
							}
							break;
						case 'e':
							strcpy(tx_buffer, "e");
							change1 = 1;				//CAMBIO 1 ES VERDADERO
							chselect1 = 1;				//SE HA SELECCIONADO PERSONAJE
							break;
						case 'q':
							strcpy(tx_buffer, "q");
							change1 = 1;				//CAMBIO 1 ES VERDADERO
							chselect1 = 0;				//NO SE HA SELECCIONADO PERSONAJE
							ch1 = 0;					//REGRESAR VALOR DEL PERSONAJE 0
							break;
						case 'x':
							strcpy(tx_buffer, "x");
							start = 0;
							modo = 9;
							break;
						default:
							break;
						}
			}else if (modo == 6){
				if(option[0] != '\r' && option[0] != '\n'){
					// Almacenar la entrada en el buffer
					if (current_index1 < KONAMI_LENGTH) {
						input_buffer1[current_index1++] = option[0];
					} else {
						// Mover el buffer si ya está lleno
						for (int i = 1; i < KONAMI_LENGTH; i++) {
							input_buffer1[i - 1] = input_buffer1[i];
						}
						input_buffer1[KONAMI_LENGTH - 1] = option[0];  // Añadir nueva entrada al final
					}
					// Verificar el código Konami solo después de agregar la nueva entrada
					check_konami_code1();
				}
				switch (option[0]){
						case 'd':
							//strcpy(tx_buffer, "d\r\n");
							strcpy(tx_buffer, "d");
							if (ch1 == 1){
								if (shooting1 == 1){
									x1 = x1+4;
									flip1 = 1;
									caminarD = 1;
									if (caminarD == 1){
										running1++;
										if(running1 == 4){
											frame1=6;
										}else if (running1 == 8){
											frame1=7;
										}else if (running1 == 12){
											frame1=8;
										}else if (running1 >= 16){
											frame1=7;
											running1=0;
										}
									}
								}else if (shooting1 == 0){
									x1 = x1+4;
									flip1 = 1;
									caminarD = 1;
									//FillRect(x1+1, y1, 1, 25, 0xF800);
									if(caminarD == 1){
										running1++;
										if (running1 == 4){
											frame1=1;
										}else if (running1 == 8){
											frame1=2;
										}else if (running1 == 12){
											frame1=3;
										}else if (running1 >= 16){
											frame1=2;
											running1=0;
										}
									}
								}
							}if (ch1 == 5){
								if (shooting1 == 1 || shooting1 == 2){
									flip1 = 1;
								}else if (shooting1 == 0){
									x1 = x1+4;
									flip1 = 1;
									caminarD = 1;
									//FillRect(x1+1, y1, 1, 25, 0xF800);
									if(caminarD == 1){
										running1++;
										if (running1 == 4){
											frame1=1;
										}else if (running1 == 8){
											frame1=2;
										}else if (running1 == 12){
											frame1=3;
										}else if (running1 >= 16){
											frame1=2;
											running1=0;
										}
									}
								}
							}if (ch1 == 8){
								if (shooting1 == 1){
									x1 = x1+4;
									flip1 = 1;
									caminarD = 1;
									if (caminarD == 1){
										running1++;
										if(running1 == 4){
											frame1=6;
										}else if (running1 == 8){
											frame1=7;
										}else if (running1 == 12){
											frame1=8;
										}else if (running1 >= 16){
											frame1=7;
											running1=0;
										}
									}
								}else if (shooting1 == 0){
									x1 = x1+4;
									flip1 = 1;
									caminarD = 1;
									//FillRect(x1+1, y1, 1, 25, 0xF800);
									if(caminarD == 1){
										running1++;
										if (running1 == 4){
											frame1=1;
										}else if (running1 == 8){
											frame1=2;
										}else if (running1 == 12){
											frame1=3;
										}else if (running1 >= 16){
											frame1=2;
											running1=0;
										}
									}
								}
							}if (ch1 == 9){
								if (shooting1 == 1){
									x1 = x1+4;
									flip1 = 1;
									caminarD = 1;
									if (caminarD == 1){
										running1++;
										if(running1 == 4){
											frame1=6;
										}else if (running1 == 8){
											frame1=7;
										}else if (running1 == 12){
											frame1=8;
										}else if (running1 >= 16){
											frame1=7;
											running1=0;
										}
									}
								}else if (shooting1 == 0){
									x1 = x1+4;
									flip1 = 1;
									caminarD = 1;
									//FillRect(x1+1, y1, 1, 25, 0xF800);
									if(caminarD == 1){
										running1++;
										if (running1 == 4){
											frame1=1;
										}else if (running1 == 8){
											frame1=2;
										}else if (running1 == 12){
											frame1=3;
										}else if (running1 >= 16){
											frame1=2;
											running1=0;
										}
									}
								}
							}
									if(x1 >= 281){
										x1 = 280;
									}
							break;
						case 'a':
							//strcpy(tx_buffer, "a\r\n");
							strcpy(tx_buffer, "a");
							if (ch1 == 1){
								if (shooting1 == 1){
									x1 = x1-4;
									flip1 = 0;				//AHORA FLIP ES 0
									caminarI = 1;
									//FillRect(x1-1, y1, 1, 25, 0xF800);
									if(caminarI == 1){
										running1++;
										if (running1 == 4){
											frame1=6;
										}else if (running1 == 8){
											frame1=7;
										}else if (running1 == 12){
											frame1=8;
										}else if (running1 >= 16){
											frame1=7;
											running1=0;
										}
									}
								}else if (shooting1 == 0){
									x1 = x1-4;
									flip1 = 0;
									caminarI = 1;
									//FillRect(x1-1, y1, 1, 25, 0xF800);
									if(caminarI == 1){
										running1++;
										if (running1 == 4){
											frame1=1;
										}else if (running1 == 8){
											frame1=2;
										}else if (running1 == 12){
											frame1=3;
										}else if (running1 >= 16){
											frame1=2;
											running1=0;
										}
									}
								}
							}if (ch1 == 5){
								if (shooting1 == 1 || shooting1 == 2){
									flip1 = 0;
								}else if (shooting1 == 0){
									x1 = x1-4;
									flip1 = 0;
									caminarI = 1;
									//FillRect(x1-1, y1, 1, 25, 0xF800);
									if(caminarI == 1){
										running1++;
										if (running1 == 4){
											frame1=1;
										}else if (running1 == 8){
											frame1=2;
										}else if (running1 == 12){
											frame1=3;
										}else if (running1 >= 16){
											frame1=2;
											running1=0;
										}
									}
								}
							}if (ch1 == 8){
								if (shooting1 == 1){
									x1 = x1-4;
									flip1 = 0;
									caminarI = 1;
									//FillRect(x1-1, y1, 1, 25, 0xF800);
									if(caminarI == 1){
										running1++;
										if (running1 == 4){
											frame1=6;
										}else if (running1 == 8){
											frame1=7;
										}else if (running1 == 12){
											frame1=8;
										}else if (running1 >= 16){
											frame1=7;
											running1=0;
										}
									}
								}else if (shooting1 == 0){
									x1 = x1-4;
									flip1 = 0;
									caminarI = 1;
									//FillRect(x1-1, y1, 1, 25, 0xF800);
									if(caminarI == 1){
										running1++;
										if (running1 == 4){
											frame1=1;
										}else if (running1 == 8){
											frame1=2;
										}else if (running1 == 12){
											frame1=3;
										}else if (running1 >= 16){
											frame1=2;
											running1=0;
										}
									}
								}
							}if (ch1 == 9){
								if (shooting1 == 1){
									x1 = x1-4;
									flip1 = 0;
									caminarI = 1;
									//FillRect(x1-1, y1, 1, 25, 0xF800);
									if(caminarI == 1){
										running1++;
										if (running1 == 4){
											frame1=6;
										}else if (running1 == 8){
											frame1=7;
										}else if (running1 == 12){
											frame1=8;
										}else if (running1 >= 16){
											frame1=7;
											running1=0;
										}
									}
								}else if (shooting1 == 0){
									x1 = x1-4;
									flip1 = 0;
									caminarI = 1;
									//FillRect(x1-1, y1, 1, 25, 0xF800);
									if(caminarI == 1){
										running1++;
										if (running1 == 4){
											frame1=1;
										}else if (running1 == 8){
											frame1=2;
										}else if (running1 == 12){
											frame1=3;
										}else if (running1 >= 16){
											frame1=2;
											running1=0;
										}
									}
								}
							}
							if(x1 <= 2){
								x1 = 2;
							}
							break;
						case 'e':
							//strcpy(tx_buffer, "d\r\n");
							strcpy(tx_buffer, "e");
							transmit_uart3("z");
							if (ch1 == 1){
								if (jumpcount1 != 2){
									vY1 = -8;
									jump1 = 1;
									jumpcount1++;
									falling1 = 0;
									if (shooting1 == 0){
										frame1 = 4;
									}else if (shooting1 == 1){
										frame1 = 9;
									}
								}
							}else if (ch1 == 5){
								if (jumpcount1 != 2){
									vY1 = -8;
									jump1 = 1;
									jumpcount1++;
									falling1 = 0;
									if (shooting1 == 0){
										frame1 = 4;
									}else if (shooting1 == 1){
										frame1 = 4;
									}else if (shooting1 == 2){
										frame1 = 8;
									}
								}
							}else if (ch1 == 8){
								if (jumpcount1 != 2){
									vY1 = -8;
									jump1 = 1;
									jumpcount1++;
									falling1 = 0;
									if (shooting1 == 0){
										frame1 = 4;
									}else if (shooting1 == 1){
										frame1 = 9;
									}
								}
							}else if (ch1 == 9){
								if (jumpcount1 != 2){
									vY1 = -8;
									jump1 = 1;
									jumpcount1++;
									falling1 = 0;
									if (shooting1 == 0){
										frame1 = 4;
									}else if (shooting1 == 1){
										frame1 = 9;
									}
								}
							}
							break;
						case 'q':
							strcpy(tx_buffer, "q");
							transmit_uart3("s");
							if (ch1==1){
								shooting1 = 1;
								frame1 = 5;
								bala = 1;
							}else if (ch1 == 5){
								shooting1++;
								if (jump1 == 1 && shooting1 == 3){
									frame1 = 9;
									bala = 1;
									shooting1 = 0;
								}
								if (shooting1==1){
									frame1 = 5;
								}else if (shooting1==2){
									frame1 = 6;
								}else if (shooting1 == 3){
									frame1 = 7;
									bala = 1;
									shooting1 = 0;
								}
							}else if (ch1 == 8){
								shooting1 = 1;
								frame1 = 5;
								bala = 1;
							}else if (ch1 == 9){
								shooting1 = 1;
								frame1 = 5;
								bala = 1;
							}
							break;
						case 'x':
							strcpy(tx_buffer, "x");
							break;
						default:
							break;
						}
			}else if (modo == 8){
				switch (option[0]){
				case 'x':
					strcpy(tx_buffer, "x");
					start = 1;
					break;
					default:
					break;
				}
			}
			//HAL_UART_Transmit(&huart2, tx_buffer, strlen(tx_buffer), 10);
			HAL_UART_Receive_IT(&huart3, option, 1);  // EMPEZAR RECEPCIÓN
		}		//SI LA INTERRUPCIÓN VIENE DEL UART5
	if(huart->Instance == UART5){
			if (modo == 0){
				switch (option2[0]){
						case 'm':
							strcpy(tx_buffer, "m");
							start = 1;
							break;
						default:
							break;
						}
			}if (modo == 2){
				switch (option2[0]){
						case 'i':
							strcpy(tx_buffer, "i");
							if (chselect2 != 1){
								selector2xAntiguo = selector2x;
								selector2yAntiguo = selector2y;
								selector2y--;
								if (selector1x == selector2x && selector1y == selector2y){
									selector2y++;
								}else{
									change2=1;
								}
								if (selector2y <= 0){
									selector2y = 1;
								}
							}
							break;
						case 'j':
							strcpy(tx_buffer, "j");
							if (chselect2 != 1){
								selector2xAntiguo = selector2x;
								selector2yAntiguo = selector2y;
								selector2x--;
								if (selector1x == selector2x && selector1y == selector2y){
									selector2x++;
								}else{
									change2=1;
								}
								if (selector2x <= 0){
									selector2x = 1;
								}
							}
							break;
						case 'k':
							strcpy(tx_buffer, "k");
							if (chselect2 != 1){
								selector2xAntiguo = selector2x;
								selector2yAntiguo = selector2y;
								selector2y++;
								if (selector1x == selector2x && selector1y == selector2y){
									selector2y--;
								}else{
									change2=1;
								}
								if (selector2y >= 3){
									selector2y = 2;
								}
							}
							break;
						case 'l':
							strcpy(tx_buffer, "l");
							if (chselect2 != 1){
								selector2xAntiguo = selector2x;
								selector2yAntiguo = selector2y;
								selector2x++;
								if (selector1x == selector2x && selector1y == selector2y){
									selector2x++;
								}else{
									change2=1;
								}
								if (selector2x >= 3){
									selector2x = 2;
								}
							}
							break;
						case 'o':
							strcpy(tx_buffer, "o");
							change2 = 1;				//CAMBIO 2 ES VERDADERO
							chselect2 = 1;				//SE HA SELECCIONADO PERSONAJE
							break;
						case 'u':
							strcpy(tx_buffer, "u");
							change2 = 1;				//CAMBIO 2 ES VERDADERO
							chselect2 = 0;				//NO SE HA SELECCIONADO PERSONAJE
							ch1 = 0;					//REGRESAR VALOR DEL PERSONAJE 0
							break;
						case 'm':
							strcpy(tx_buffer, "m");
							start = 0;
							modo = 9;
							break;
						default:
							break;
						}
			}else if (modo == 6){
				if(option2[0] != '\r' && option2[0] != '\n'){
					// Almacenar la entrada en el buffer
					if (current_index2 < KONAMI_LENGTH) {
						input_buffer2[current_index2++] = option2[0];
					} else {
						// Mover el buffer si ya está lleno
						for (int i = 1; i < KONAMI_LENGTH; i++) {
							input_buffer2[i - 1] = input_buffer2[i];
						}
						input_buffer2[KONAMI_LENGTH - 1] = option2[0];  // Añadir nueva entrada al final
					}
					// Verificar el código Konami solo después de agregar la nueva entrada
					check_konami_code2();
				}
				switch (option2[0]){
						case 'j':
							strcpy(tx_buffer, "j");
							if (ch2 == 1){
								if (shooting2 == 1){
									x2 = x2-4;
									flip22 = 0;				//AHORA FLIP ES 0
									caminarI2 = 1;
									//FillRect(x1-1, y1, 1, 25, 0xF800);
									if(caminarI2 == 1){
										running2++;
										if (running2 == 4){
											frame2=6;
										}else if (running2 == 8){
											frame2=7;
										}else if (running2 == 12){
											frame2=8;
										}else if (running2 >= 16){
											frame2=7;
											running2=0;
										}
									}
								}else if (shooting2 == 0){
									x2 = x2-4;
									flip22 = 0;
									caminarI2 = 1;
									//FillRect(x1-1, y1, 1, 25, 0xF800);
									if(caminarI2 == 1){
										running2++;
										if (running2 == 4){
											frame2=1;
										}else if (running2 == 8){
											frame2=2;
										}else if (running2 == 12){
											frame2=3;
										}else if (running2 >= 16){
											frame2=2;
											running2=0;
										}
									}
								}
							}if (ch2 == 5){
								if (shooting2 == 1 || shooting2 == 2){
									flip22 = 0;
								}else if (shooting2 == 0){
									x2 = x2-4;
									flip22 = 0;
									caminarI2 = 1;
									//FillRect(x1-1, y1, 1, 25, 0xF800);
									if(caminarI2 == 1){
										running2++;
										if (running2 == 4){
											frame2=1;
										}else if (running2 == 8){
											frame2=2;
										}else if (running2 == 12){
											frame2=3;
										}else if (running2 >= 16){
											frame2=2;
											running2=0;
										}
									}
								}
							}if (ch2 == 8){
								if (shooting2 == 1){
									x2 = x2-4;
									flip22 = 0;
									caminarI2 = 1;
									//FillRect(x1-1, y1, 1, 25, 0xF800);
									if(caminarI2 == 1){
										running2++;
										if (running2 == 4){
											frame2=6;
										}else if (running2 == 8){
											frame2=7;
										}else if (running2 == 12){
											frame2=8;
										}else if (running2 >= 16){
											frame2=7;
											running2=0;
										}
									}
								}else if (shooting2 == 0){
									x2 = x2-4;
									flip22 = 0;
									caminarI2 = 1;
									//FillRect(x1-1, y1, 1, 25, 0xF800);
									if(caminarI2 == 1){
										running2++;
										if (running2 == 4){
											frame2=1;
										}else if (running2 == 8){
											frame2=2;
										}else if (running2 == 12){
											frame2=3;
										}else if (running2 >= 16){
											frame2=2;
											running2=0;
										}
									}
								}
							}if (ch2 == 9){
								if (shooting2 == 1){
									x2 = x2-4;
									flip22 = 0;
									caminarI2 = 1;
									//FillRect(x1-1, y1, 1, 25, 0xF800);
									if(caminarI2 == 1){
										running2++;
										if (running2 == 4){
											frame2=6;
										}else if (running2 == 8){
											frame2=7;
										}else if (running2 == 12){
											frame2=8;
										}else if (running2 >= 16){
											frame2=7;
											running2=0;
										}
									}
								}else if (shooting2 == 0){
									x2 = x2-4;
									flip22 = 0;
									caminarI2 = 1;
									//FillRect(x1-1, y1, 1, 25, 0xF800);
									if(caminarI2 == 1){
										running2++;
										if (running2 == 4){
											frame2=1;
										}else if (running2 == 8){
											frame2=2;
										}else if (running2 == 12){
											frame2=3;
										}else if (running2 >= 16){
											frame2=2;
											running2=0;
										}
									}
								}
							}
							if(x2 <= 2){
								x2 = 2;
							}
							break;
						case 'l':
							strcpy(tx_buffer, "l");
							if (ch2 == 1){
							if (shooting2 == 1){
								x2 = x2+4;
								flip22 = 1;				//AHORA FLIP ES 0
								caminarD2 = 1;
								//FillRect(x1-1, y1, 1, 25, 0xF800);
								if(caminarD2 == 1){
									running2++;
									if (running2 == 4){
										frame2=6;
									}else if (running2 == 8){
										frame2=7;
									}else if (running2 == 12){
										frame2=8;
									}else if (running2 >= 16){
										frame2=7;
										running2=0;
									}
								}
							}else if (shooting2 == 0){
								x2 = x2+4;
								flip22 = 1;
								caminarD2 = 1;
								//FillRect(x1-1, y1, 1, 25, 0xF800);
								if(caminarD2 == 1){
									running2++;
									if (running2 == 4){
										frame2=1;
									}else if (running2 == 8){
										frame2=2;
									}else if (running2 == 12){
										frame2=3;
									}else if (running2 >= 16){
										frame2=2;
										running2=0;
									}
								}
							}
						}if (ch2 == 5){
							if (shooting2 == 1 || shooting2 == 2){
								flip22 = 1;
							}else if (shooting2 == 0){
								x2 = x2+4;
								flip22 = 1;
								caminarD2 = 1;
								//FillRect(x1-1, y1, 1, 25, 0xF800);
								if(caminarD2 == 1){
									running2++;
									if (running2 == 4){
										frame2=1;
									}else if (running2 == 8){
										frame2=2;
									}else if (running2 == 12){
										frame2=3;
									}else if (running2 >= 16){
										frame2=2;
										running2=0;
									}
								}
							}
						}if (ch2 == 8){
							if (shooting2 == 1){
								x2 = x2+4;
								flip22 = 1;
								caminarD2 = 1;
								//FillRect(x1-1, y1, 1, 25, 0xF800);
								if(caminarD2 == 1){
									running2++;
									if (running2 == 4){
										frame2=6;
									}else if (running2 == 8){
										frame2=7;
									}else if (running2 == 12){
										frame2=8;
									}else if (running2 >= 16){
										frame2=7;
										running2=0;
									}
								}
							}else if (shooting2 == 0){
								x2 = x2+4;
								flip22 = 1;
								caminarD2 = 1;
								//FillRect(x1-1, y1, 1, 25, 0xF800);
								if(caminarD2 == 1){
									running2++;
									if (running2 == 4){
										frame2=1;
									}else if (running2 == 8){
										frame2=2;
									}else if (running2 == 12){
										frame2=3;
									}else if (running2 >= 16){
										frame2=2;
										running2=0;
									}
								}
							}
						}if (ch2 == 9){
							if (shooting2 == 1){
								x2 = x2+4;
								flip22 = 1;
								caminarD2 = 1;
								//FillRect(x1-1, y1, 1, 25, 0xF800);
								if(caminarD2 == 1){
									running2++;
									if (running2 == 4){
										frame2=6;
									}else if (running2 == 8){
										frame2=7;
									}else if (running2 == 12){
										frame2=8;
									}else if (running2 >= 16){
										frame2=7;
										running2=0;
									}
								}
							}else if (shooting2 == 0){
								x2 = x2+4;
								flip22 = 1;
								caminarD2 = 1;
								//FillRect(x1-1, y1, 1, 25, 0xF800);
								if(caminarD2 == 1){
									running2++;
									if (running2 == 4){
										frame2=1;
									}else if (running2 == 8){
										frame2=2;
									}else if (running2 == 12){
										frame2=3;
									}else if (running2 >= 16){
										frame2=2;
										running2=0;
									}
								}
							}
						}
						if(x2 >= 281){
							x2 = 280;
						}
							break;
						case 'o':
							strcpy(tx_buffer, "o");
							transmit_uart3("z");
							if (ch2 == 1){
								if (jumpcount2 != 2){
									vY2 = -8;
									jump2 = 1;
									jumpcount2++;
									falling2 = 0;
									if (shooting2 == 0){
										frame2 = 4;
									}else if (shooting2 == 1){
										frame2 = 9;
									}
								}
							}else if (ch2 == 5){
								if (jumpcount2 != 2){
									vY2 = -8;
									jump2 = 1;
									jumpcount2++;
									falling2 = 0;
									if (shooting2 == 0){
										frame2 = 4;
									}else if (shooting2 == 1){
										frame2 = 4;
									}else if (shooting2 == 2){
										frame2 = 8;
									}
								}
							}else if (ch2 == 8){
								if (jumpcount2 != 2){
									vY2 = -8;
									jump2 = 1;
									jumpcount2++;
									falling2 = 0;
									if (shooting2 == 0){
										frame2 = 4;
									}else if (shooting2 == 1){
										frame2 = 9;
									}
								}
							}else if (ch2 == 9){
								if (jumpcount2 != 2){
									vY2 = -8;
									jump2 = 1;
									jumpcount2++;
									falling2 = 0;
									if (shooting2 == 0){
										frame2 = 4;
									}else if (shooting2 == 1){
										frame2 = 9;
									}
								}
							}
							break;
						case 'u':
							strcpy(tx_buffer, "u");
							transmit_uart3("s");
							if (ch2==1){
								shooting2 = 1;
								frame2 = 5;
								bala2 = 1;
							}else if (ch2 == 5){
								shooting2++;
								if (jump2 == 1 && shooting2 == 3){
									frame2 = 9;
									bala2 = 1;
									shooting2 = 0;
								}
								if (shooting2==1){
									frame2 = 5;
								}else if (shooting2==2){
									frame2 = 6;
								}else if (shooting2 == 3){
									frame2 = 7;
									bala2 = 1;
									shooting2 = 0;
								}
							}else if (ch2 == 8){
								shooting2 = 1;
								frame2 = 5;
								bala2 = 1;
							}else if (ch2 == 9){
								shooting2 = 1;
								frame2 = 5;
								bala2 = 1;
							}
							break;
						default:
							break;
						}
			}else if (modo == 8){
				switch (option2[0]){
				case 'm':
					strcpy(tx_buffer, "m");
					start = 1;
					break;
					default:
					break;
				}
			}
			//transmit_uart2(option2);
			HAL_UART_Receive_IT(&huart5, option2, 1);  // EMPEZAR RECEPCIÓN
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
 /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
