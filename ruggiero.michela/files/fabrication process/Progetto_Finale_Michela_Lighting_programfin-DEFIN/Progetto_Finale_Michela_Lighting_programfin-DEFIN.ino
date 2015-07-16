
#include <Encoder.h>
/* L'encoder rotativo è un componente elettronico in grado di misurare la rotazione di un asse, nel nostro caso del servo
essendo infatti il servo rotto, non possiede più capacità di controllo, e pertanto dobbiamo "misurare" la sua rotazione con questo hardware
e la libreria apposita
*/
Encoder myEnc(3, 2);
/* L'encoder si può usare solo su determinati pin di arduino, non è come tutti i componenti, ma per avere una massima precisione bisogna
necessariamente usare i pin di "interrupt" , nel nostro caso i pin 5 e 6 */

int IN1 = 8; // pin di comando del ponte H
int IN2 = 9; // pin2 di comando del ponte H

long newPosition;  // questa variabile serve alla libreria encoder per registrare quanti step ha fatto l'encoder, e quindi quanti giri ha fatto l'albero del servo

int guida; // guida rappresenta il valore del sensore, nel nostro caso un sensore di luminosità
int vel = 255; // velocità e potenza del motore
int errorRate =3; // essendo il servo un servo modificato possiede un errore di precisione, se si abbassasse questo valore il servo potrebbe iniziare a dondolare facendo destra e sinistra
long previousMillis = 0;        // will store last time LED was updated
long interval = 100;           // interval at which to refresh (milliseconds)



void setup() {
  setupsmooth();  // la funzione smooth può essere trovata nel secondo tab, questa permette di prendere i valori del sensore e fare una media , avendo quindi un valore molto più preciso, qui chiamiamo il setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
    Serial.begin(9600);

}


void loop() {
  unsigned long currentMillis = millis();

    newPosition = myEnc.read(); // questa dicitua significa "assegna a newPosition" il valore dell'encoder rotativo

//  if (currentMillis - previousMillis > interval) {
//   previousMillis = currentMillis;

    loopsmooth(); // qui chiamiamo il loop della funzione smooth

    //
    Serial.print("guida   "); Serial.println(guida);
    Serial.print("newPosition   ");  Serial.println(newPosition);


if (newPosition<guida-errorRate){
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
Serial.println("Av");
}

if (newPosition>guida+errorRate){
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
Serial.println("ind");
}

if (newPosition>=guida-errorRate && newPosition<=guida+errorRate){
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
Serial.println("st");
}

    delay(1);

//}


//
//
//  }
}
