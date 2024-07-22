#include "mbed.h"
#include "sMotor.h"
#include "ssd1306.h"
//-----------------------------------------------------------------------------------------------
Serial pc(USBTX, USBRX);
//-----------------------------------------------------------------------------------------------

Ticker t_temp;						// Ticker para la temperatura
Ticker t_pot;						// Ticker para el potenciometro
Ticker t_pap;						// Ticker para el motor paso a paso
Ticker t_oled;						// Ticker para el display



//-----------------------------------------------------------------------------------------------

void rutina_barrido(void);			// Rutina que realiza el barrido del servo

//-----------------------------------------------------------------------------------------------
AnalogIn stemp (A0);
AnalogIn pot (A1);
PwmOut pwm (D9);
DigitalOut IN1(D3), IN2(D4), IN3(D5), IN4(D6);
SSD1306 oled (I2C_SDA, I2C_SCL, 0x78);


//-----------------------------------------------------------------------------------------------

char trama [4];
char trama_rx [4];

//------------------------------------VARIBLES DEL MAIN------------------------------------//

// Variables de la temperatura
float temp;
float t_act;					// Tiempo de actualizacion

// Variables del servo
float vpot, grados=0;
int anchopulso_servo;			// Tiempo en alto de la senyal pwm
int espera, vel_barrido;		// Variables espera y velocidad para el abre cierra del servo
int Estado_servo=0;				// Estados del servo. 1=Estado Inicial, 2=Abriendo, 3=Pausa, 4=Cerrando
float intervalo = 0.05;			//


// Variables para el motor paso a paso
int dir=0;
int time_pap;					// Tiempo entrepasos
int vel_motor;


// Variables banderas (Enables)
int enable_pot_servo=0;						// V.Bandera mover servo con potenciometro
int enable_servo=0;							// V.Bandera servo
int enable_temp=0;							// V.Bandera sensor de temperatura
int enable_AC=0;							// V.Bandera abre/cierra del servo


//------------------------------------RUTINA GENERAL SERVO------------------------------------//
void rutina_servo(){


	vpot= pot.read();									// Leer potenciometro

	// Mover servo con potenciometro
	if (enable_pot_servo==1){

		grados = vpot*90;								// Calcular los grados
		anchopulso_servo = (grados*1000/90+1000);		// Calcular ancho de pulso del servo
		pwm.pulsewidth_us(anchopulso_servo);			// Mover el servo
		trama[0]= 0x20;
		trama[1]= (char) grados;
		trama[2]= 0xFF;
		trama[3]= 0xE0;
		pc.printf(trama);
	}

	// Mover servo
	if (enable_servo==1){

		anchopulso_servo = (grados*1000/90+1000);
		pwm.pulsewidth_us(anchopulso_servo);
		trama[0]= 0x20;
		trama[1]= (char) grados;
		trama[2]= 0xFF;
		trama[3]= 0xE0;
		pc.printf(trama);
	}

	// Abre Cierra Servo
	if(enable_AC==1){

		rutina_barrido();			// Llamada a la rutina del barrido del servo

	}


}
//------------------------------------RUTINA TEMPERATURA------------------------------------//
void rutina_temp()
{
	if(enable_temp==1){

		temp = stemp.read()*330;	// Leer temperatura

		trama[0]=   0x30;
		trama[1]=  (char) temp;			 			// Parte entera de la temperatura
		trama[2]=  (char)((temp-trama[1])*100.0); 	// Parte decimal, solo dos decimales.
		trama[3]=   0xE0;
		pc.printf(trama);
	}
}
//------------------------------------RUTINA ABRIR CERRAR SERVO------------------------------------//
void rutina_barrido(){

	static int i;

	// Estado Inicial, servo a 0 grados
	if(Estado_servo==1){

		// Si empezamos el servo con 0 grados, estamos en el inicio por tanto me paso al estado 2
		if(grados == 0){

			i=0;
			Estado_servo=2;						// Siguiente estado Abriendo

		// Si el servo se encuentra en X grados me vuelvo a inicio, servo 0 grados
		}else{

			grados = 0;
			anchopulso_servo = (grados*1000/90+1000);
			pwm.pulsewidth_us(anchopulso_servo);

			// Envio de tramas
			trama[0]= 0x20;
			trama[1]= (char) grados;
			trama[2]= 0xFF;
			trama[3]= 0xE0;
			pc.printf(trama);

		}


	}
	// Estado Abriendo
	else if(Estado_servo==2){

		// Si el servo es menor que 90 grados, calculo los grados correspondiente al movimiento
		if(grados<90){

			grados=i*vel_barrido*intervalo; 				// Espacio = velocidad*tiempo
			anchopulso_servo = (grados*1000/90+1000);
			pwm.pulsewidth_us(anchopulso_servo);
			i++;

			// Envio de tramas
			trama[0]= 0x20;
			trama[1]= (char) grados;
			trama[2]= 0xFF;
			trama[3]= 0xE0;
			pc.printf(trama);

		}else{					// En otro caso, los grados son 90 grados. Siguiente estado es Pausa


			Estado_servo=3;
			i=espera/intervalo;	// Tiempo que salta a la rutina sin realizar nada
		}


	}
	// Estado de Pausa
	else if(Estado_servo==3){

		if(i==0){

			Estado_servo=4;			// i es 0, siguiente estado Cerrando

		}else{

			i--;					// Mientra i no sea 0 seguimos en Pausa

		}

	}
	// Estado Cerrando
	else if(Estado_servo==4){


		if(grados>0){				// Si grados es mayor que 0, calculo los grados correspondiente al movimiento

			grados=90-i*vel_barrido*intervalo;					// i restanndo para ir hacia atras
			anchopulso_servo = (grados*1000/90+1000);
			pwm.pulsewidth_us(anchopulso_servo);
			i++;

			// Envio de tramas
			trama[0]= 0x20;
			trama[1]= (char) grados;
			trama[2]= 0xFF;
			trama[3]= 0xE0;
			pc.printf(trama);

		}else{						// En otro caso grados es 0, Estado Inicial

			Estado_servo=1;			// Estado inicial

			enable_AC=0;			// Desactivo V.Bandera

		}


	}

}
//------------------------------------RUTINA MOTOR PASO A PASO------------------------------------//
void rutina_mpap(){


	static char numfase = 1;


		if(dir==0){				// Sentido horario

			numfase++;

			if(numfase>=5){		// Si numfase se pasa de 5, lo pongo a 1
				numfase = 1;
			}

		}
		else if(dir==1){		// Sentido antihorario

			numfase--;

			if(numfase<=0){		// Si llega a 0, numfase lo pongo a 4

				numfase = 4;

			}
		}
		switch(numfase){

		case 1:
			IN1=1;
			IN2=1;
			IN3=0;
			IN4=0;
			break;
		case 2:
			IN1=0;
			IN2=1;
			IN3=1;
			IN4=0;
			break;
		case 3:
			IN1=0;
			IN2=0;
			IN3=1;
			IN4=1;
			break;
		case 4:
			IN1=1;
			IN2=0;
			IN3=0;
			IN4=1;
			break;

		}



}


//------------------------------------RUTINA DISPLAY------------------------------------//
void rutina_display(){



		oled.locate(3,0);
		oled.printf("Temp: %4.1f", temp);
		oled.locate(4,0);
		oled.printf("Pos: %4.1f", grados);
		oled.locate(5,0);
		oled.printf("Vel: %4.1f", vel_motor);



		oled.redraw();


}

//------------------------------------RUTINA SERIE------------------------------------//
void leer_serie()   
{
	trama_rx[0]=trama_rx[1];
	trama_rx[1]=trama_rx[2];
	trama_rx[2]=trama_rx[3];
	trama_rx[3]=pc.getc();

	if(trama_rx[3]== 0xE0){							// TRAMA OK

		if(trama_rx[0]==0x54){						// "T" Lectura de la temperatura

			enable_temp=1;
			t_act=(float)trama_rx[1];
			t_temp.detach();
			t_temp.attach(rutina_temp,t_act*0.01);

		}else if(trama_rx[0]==0x50){				// "P" Activar control del servo por potenci�metro

			enable_servo=0;
			enable_pot_servo=1;

		}else if(trama_rx[0]==0x53){				// "S" Posicionar el servo

			enable_pot_servo=0;
			enable_servo=1;

			grados=trama_rx[1];

			if(grados<=0){
				grados=0;
			}if(grados>=90){
				grados=90;
			}

		}else if(trama_rx[0]==0x41){				// "A" Movimiento de apertura y cierre del servo

			enable_servo=0;							// Desactivar control del servo-pot y servo
			enable_pot_servo=0;
			enable_AC = 1;							// Activar abre cierra
			espera=trama_rx[1];
			vel_barrido=trama_rx[2];
			Estado_servo=1;							// Maquina de estado. Estado inicial

		}
		else if(trama_rx[0]==0x4D){					// "M" Girar el motor paso a paso a la velocidad indicada

			vel_motor=trama_rx[1];
			// Anotacion: con rpm superior a 10, el motor paso a paso no se observa movimiento
			time_pap = (60.0/(vel_motor*4096))*1000000;
			t_pap.detach();
			t_pap.attach_us(&rutina_mpap, time_pap);

			// Envio de tramas
			trama[0]= 0x40;
			trama[1]= (char) vel_motor;
			trama[2]= 0xFF;
			trama[3]= 0xE0;
			pc.printf(trama);

		}else if(trama_rx[0]==0x44){				// "D" Girar el motor paso a paso a la derecha (horario)

			dir=0;

		}else if(trama_rx[0]==0x49){				// "I" Girar el motor paso a paso a la izquierda (antihorario)

			dir=1;

		}else if(trama_rx[0]==0x58){				// "X" Visualizar el estado de sistema en el display

			t_oled.attach_us(rutina_display,1000000);

		}else if(trama_rx[0]==0x43){				// "C" Cancelar todos los comandos

			enable_pot_servo=0;
			enable_servo=0;
			enable_temp=0;
			enable_AC=0;
			t_pap.detach();
			t_temp.detach();
			t_oled.detach();
			oled.redraw();
			oled.cls();

		}
	}

}


int main()
{
	pc.attach(&leer_serie,Serial::RxIrq);
	pwm.period_ms(20);
	t_pot.attach_us(rutina_servo,50000); 					// Cada 50ms
	oled.speed(SSD1306::Medium);
	oled.init();
	oled.cls();
	while(1){}

}
