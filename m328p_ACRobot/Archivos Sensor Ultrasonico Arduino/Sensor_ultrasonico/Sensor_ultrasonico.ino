long duracion;
long distancia; // float distancia para obtener decimales
int echo=8;
int trig=9;

void setup() 
{
  Serial.begin(9600);
  pinMode(trig,OUTPUT); // emisor
  pinMode(echo,INPUT); // Receptor
}

void loop() 
{
  //Para estabilizar nuestro módulo ultrasónico
  digitalWrite(trig,LOW);
  delayMicroseconds(4);
  //disparo de un pulso en el trigger de longitud 10us
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  //Lectura de la duración del pulso HIGH generado hasta recibir el Echo
  duracion=pulseIn(echo,HIGH);

  //Calculo distancia
  distancia=duracion/58.4;// (cm)
  Serial.print("Distancia:");
  Serial.print(distancia);
  Serial.println(" cm");
  delay(100);  
}
