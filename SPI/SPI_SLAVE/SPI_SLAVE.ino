
#define SCK_PIN  4  // chân SCK
#define MOSI_PIN 5  // Chân MOSI
#define MISO_PIN 6  // Chân MISO
#define SS_PIN   7  // chân SS

//SLAVE side-------------------------------
#define SCK_INPUT   DDRD &= ~(1<< DDD4) //pinMode(SCK_PIN, INPUT);
#define MOSI_INPUT  DDRD &= ~(1<< DDD5)
#define SS_INPUT    DDRD &= ~(1<< DDD7)
#define MISO_OUTPUT DDRD |= (1<< DDD6) //pinMode(MISO_PIN, OUTPUT);

#define read_SCK()  ((PIND & (1 << PIND4)) ? HIGH:LOW)
#define read_MOSI() ((PIND & (1 << PIND5)) ? HIGH:LOW)
#define read_SS()   ((PIND & (1 << PIND7)) ? HIGH:LOW)
#define write_MISO(x) PORTD = ((x) ? (PORTD | 1<<PD6):(PORTD & (~(1<<PD6))))

void setup() {
  // put your setup code here, to run once:
SPI_setup();
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
uint8_t rev;
rev = SPI_transfer('A');// ASCII 0x41 65 0100.0001
Serial.println(rev);
Serial.println("S:" + String((char)rev));
}

void SPI_setup(void)
{
  SCK_INPUT;
  MOSI_INPUT;
  SS_INPUT;
  MISO_OUTPUT;
}
//MODE0: CPOL =0, CPHASE =0. bitOder=MSB.
uint8_t SPI_transfer(uint8_t byte_out)
{
  uint8_t byte_in = 0; //0000.0000
  uint8_t ibit, res;
  while( read_SS() == HIGH);//waiting utill SS=0(LOW), start condition
  for(ibit=0x80; ibit>0; ibit=ibit>>1) //1000.0000 -> 0100.0000 -> 0010.000 ... -> 0000.0001 -> 0000.0000(stop condition)
  {
    res = byte_out & ibit;// (1000.0000)#0(true) (0000.0000)=0(fale)
    write_MISO(res);

    while(read_SCK() == LOW);//waiting untill SCK=1

    if(read_MOSI() == HIGH)
      byte_in = byte_in | ibit; //set bit(byte_in) to 1 at bit '1'(ibit)
    else 
      byte_in = byte_in & (~ibit);
    while( read_SCK() == HIGH); //waiting utill SCK = 0
    //utill here, this is the end of 1 clock of cycle
  }
  return byte_in;
}
