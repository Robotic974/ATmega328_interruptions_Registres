/*
Exo N°2: 
--------------
Mise en pratique d'une interruption PCINT0_vect avec activation uniquement sur la broche D8
*/

#include <Arduino.h>

const uint8_t pin_led = 13;
const uint8_t pin_isr = 8; // Bit 0 du Port B => vecteur PCINT0_vect


/*
Changement d'état & application sur la LED dans la routine d'interruption directement par Registre & opération booléenne
Voir Exo 1

La broche 8 n'a pas d'interruption propre comme les broches 2 ou 3.
Pour cette broche nous n'avons que l'interruption PCINT0_vect rattachée au PORTB. Elle sera donc levée lors d'un changement
d'état sur l'une des broches du port B de D8 à D13.
Nous appliquons un masque sur le registre PCMSK0 afin de désactiver les autres broches du port.
*/


/*
Routine d'interruption identique à l'exercice 1
*/
ISR(PCINT0_vect) {
    PORTB ^= B00100000; // Inversion (par XOR) du bit5 sur le PORTB correspondant à la broche 13
}


void setup() {
    pinMode(pin_led, OUTPUT);
	// Equivalence par registre: DDRB  |= B00100000; // passage de PB5 (broche 13) à 1 donc en sortie
	
    pinMode(pin_isr, INPUT_PULLUP);
	// Equivalence par registre: DDRB  &= B11111110; // passage de PB0 (broche  8) à 0 donc en entrée
	// 							 PORTB |= B00000001; // passage de PB0 (broche  8) à 1 afin d'activer le pull-up

	// Nous n'utilisons plus la fonction attachInterrupt(), directement par registre
    PCICR  |= B00000001;  // Activation de l'interruption sur le port B par le passage à 1 du 1er bit correspondant à ce port
    PCMSK0 |= B00000001;  // Activation uniquement de la broche 8 du port B par le passage à 1 du 1er bit correspondant à cette broche
}

void loop() {
    delay(5000);
}


