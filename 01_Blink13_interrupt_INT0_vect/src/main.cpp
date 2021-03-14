
/*
Connectez simplement un fil (ou un interrupteur) entre D2 et la masse. 
Le pullup interne (activé dans le setup() ) force la broche HAUT normalement,
   une fois mis à la terre, il devient BAS. 
Le changement dans la broche est détecté par une interruption en mode CHANGE, 
   ce qui provoque l'appel de la routine de service d'interruption blinkIsr().
*/

#include <Arduino.h>

const uint8_t pin_led = 13;
const uint8_t pin_isr = 2;

volatile bool state = LOW;

/*
    Changement d'état uniquement dans la routine d'interruption
    digitalWrite(pin_led, state); doit être dans la boucle principale
    -------------------------------------
    Avantage:      routine trés rapide
    Inconvénient:  l'application de l'état est fonction du délai de traitement de la boucle principale
        Si nous rajoutons un delay(3000), le changement sur la LED ne se verra qu'au bout de 3 secondes max
*/
void blinkIsr_v1() {
    state = !state;
}

/*
    Changement d'état & application sur la LED dans la routine d'interruption
    //digitalWrite(pin_led, state); doit être supprimée ou passée en commentaire dans la boucle principale
    -------------------------------------
    Avantage:      n'est plus tributaire de la boucle principale, application immédiate du changement d'état sur la LED
    Inconvénient:  delai de traitement de la routine plus longue
*/
void blinkIsr_v2() {
    digitalWrite(pin_led, state = !state);
}

/*
    Changement d'état & application sur la LED dans la routine d'interruption directement par Registre & opération booléenne
    //digitalWrite(pin_led, state); doit être supprimée ou passée en commentaire dans la boucle principale
    -------------------------------------
    Avantage:      idem à la v2
                   par le registre: opération 10x plus rapide qu'avec digitalWrite()
                   avec l'opération booléenne: plus besoin de la variable state 
    Inconvénient:  routine moins lisible, necessité de commenter
*/
void blinkIsr_v3() {
    PORTB ^= B00100000; // Inversion (par XOR) du bit5 sur le PORTB correspondant à la broche 13
}

void setup() {
    pinMode(pin_led, OUTPUT);
    pinMode(pin_isr, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pin_isr), blinkIsr_v3, CHANGE); // modifier le nom de la routine ISR en fonction de l'exercice
}

void loop() {
    //digitalWrite(pin_led, state);
    delay(5000);
}


