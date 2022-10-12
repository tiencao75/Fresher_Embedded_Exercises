
//SPI speed
//Slow_01: f=20kHz => T=50us
//Slow_21: f=1kHz => T=1000us
#define TFull 50
#define THalf TFull/2

#define SCK_PIN  4  // chân SCK
#define MOSI_PIN 5  // Chân MOSI
#define MISO_PIN 6  // Chân MISO
#define SS_PIN   7  // chân SS

#define SCK_OUTPUT  DDRD |= (1<< DDD4) //pinMode(SCK_PIN, OUTPUT);
#define MOSI_OUTPUT DDRD |= (1<< DDD5)
#define SS_OUTPUT   DDRD |= (1<< DDD7)
#define MISO_INPUT  DDRD &= ~(1<< DDD6) //pinMode(MISO_PIN, INPUT);

//#define MOSI_HIGH PORTD |= (1<<5) //digitalWrite(MOSI_PIN, HIGHT);
//#define MOSI_LOW PORTD &= ~(1<<5) //digitalWrite(MOSI_PIN, LOW);
#define write_MOSI(x) PORTD = ((x) ? (PORTD | 1<<PD5):(PORTD & (~(1<<PD5))))

#define write_SS(x)   PORTD = ((x) ? (PORTD | 1<<PD7):(PORTD & (~(1<<PD7))))

#define write_SCK(x)  PORTD = ((x) ? (PORTD | 1<<PD4):(PORTD & (~(1<<PD4))))

#define read_MISO() ((PIND & ( 1<< PIND6)) ? HIGH:LOW) // digitalRead(MISO_PIN)



void setup() {                
SPI_setup();
Serial.begin(9600);
}

void loop() {
uint8_t rev;
SPI_begin();
rev = SPI_transfer('a');//ASCII: 0x61 97 0110.0001
SPI_end();
Serial.println(rev);
Serial.println("M:" + String((char)rev));
delay(1000);
}

void SPI_setup()
{
  MOSI_OUTPUT;
  MISO_INPUT;
  write_SCK(LOW);
  SCK_OUTPUT;
  write_SS(HIGH);
  SS_OUTPUT;
  delay(1);
}

void SPI_begin(void)
{
write_SS(LOW);//  write_SS(LOW)// 1MASTER- 1 SLAVE
}

void SPI_end(void)
{
  write_SCK(LOW);
  write_SS(HIGH);
}
//MODE0: CPOL =0, CPHASE =0. bitOder=MSB.
uint8_t SPI_transfer(uint8_t byte_out)
{
  uint8_t byte_in = 0; //0000.0000
  uint8_t ibit, res;
  //1000.0000 -> 0100.0000 -> 0010.000 ... -> 0000.0001 -> 0000.0000(stop condition)
  for(ibit=0x80; ibit>0; ibit = ibit>>1)
  {
    res = byte_out & ibit; //(#0=true), (=0=false)
    write_MOSI(res);

    delayMicroseconds(THalf);
    write_SCK(HIGH);

    if(read_MISO() == HIGH)
      byte_in = byte_in | ibit; //0000.0000 | 1000.000 = 1000.000
    else
      byte_in = byte_in & (~ibit);

    delayMicroseconds(THalf);
    write_SCK(LOW); //end 1 clocl cycle
  }
  return byte_in;
}
