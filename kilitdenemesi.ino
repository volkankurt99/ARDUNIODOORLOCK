
#include <EEPROM.h>//Sifrem ve yeni kaydı icin tutulacak adresler

int bir_address = 50;
int iki_address = 51;
int uc_address = 52;
int dort_address = 53;


#include<Keypad.h>  //Keypad kütüphanesi
#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8,7);


int bir_;
int iki_;
int uc_;
int dort_;

int bir_sifre ;
int iki_sifre ;
int uc_sifre ;
int dort_sifre ;

const byte satir = 4;  //Satir
const byte sutun = 3;  //Sutun
char tus;
String gelen_tus;


int i = 0;

bool dogru = false;
//Keypad icin yazılan kod
char tus_takimi[4][3] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte satir_pins[4] = {3, 2, 1, 0};
byte sutun_pins[3] = {4, 5, 6};

Keypad tuss_takimi = Keypad(makeKeymap(tus_takimi), satir_pins, sutun_pins, 4, 3);

byte customChar9[8] = {  //Animasyomlu yukleme efekti için hazirlanan custom chars
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
byte customChar8[8] = {
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110
};
byte customChar7[8] = {
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100
};
byte customChar6[8] = {
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000
};
byte customChar5[8] = {
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000
};
byte customChar4[8] = {
  0b00001,
  0b00011,
  0b00011,
  0b00111,
  0b00111,
  0b01111,
  0b01111,
  0b11111
};
byte customChar3[8] = {
  0b00000,
  0b00010,
  0b00010,
  0b00110,
  0b00110,
  0b01110,
  0b01110,
  0b11110
};
byte customChar2[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b00100,
  0b01100,
  0b01100,
  0b11100
};
byte customChar1[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b01000,
  0b01000,
  0b11000
};

byte customChar0[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10000
};
//============================================================================================================================================================================================================
void setup() {

  //Animasyonlu yukleme ekrani aktiflestirmek icin kod
  lcd.createChar(0, customChar0);
  lcd.createChar(1, customChar1);
  lcd.createChar(2, customChar2);
  lcd.createChar(3, customChar3);
  lcd.createChar(4, customChar4);
  lcd.createChar(5, customChar5);
  lcd.createChar(6, customChar6);
  lcd.createChar(7, customChar7);
  lcd.createChar(8, customChar8);
  lcd.createChar(9, customChar9);
  lcd.begin(16, 2);
  lcd.clear();
  
//Sifremi en basta kaydetmis oldugum adreslerde tutması icin eerprom kodu

  bir_sifre = EEPROM.read(bir_address);                // Adresten degeri oku
  iki_sifre = EEPROM.read(iki_address);                // Adresten degeri oku
  uc_sifre = EEPROM.read(uc_address);                  // Adresten degeri oku
  dort_sifre = EEPROM.read(dort_address);              // Adresten degeri oku

  lcd.setCursor(0, 0);
  lcd.print("SISTEM  ACILIYOR");
  for (int i = 0; i <= 16; i++)  // Animasyonlu giriş ekranının yükleniyor efekti icin döngü
  {
    for (int k = 5; k <= 8; k++)
    {
      lcd.setCursor(i, 1); lcd.write((uint8_t)k);
      delay(50);

    }
  }
}
//============================================================================================================================================================================================================
void loop() {
  
  lcd.setCursor(0, 0);
  lcd.print("  HOSGELDINIZ   ");
  lcd.setCursor(0, 1);
  lcd.print("  SIFRELI KAPI  ");

  tus = tuss_takimi.getKey();//getKey metodu ile tus takimindan basilan tusu alıyorum
  gelen_tus = tus;
  int gelen = gelen_tus.toInt();

  if (bir_sifre == 255)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SIFRE           ");
    lcd.setCursor(0, 1);
    lcd.print("   BELIRLEYINIZ ");
    delay(1000);
    sifre_belirle();
   }

  if (gelen_tus.length() > 0) {

    delay(100);
    
    if (gelen_tus == "#")
    {
      lcd.setCursor(0, 0);
      lcd.print("LUTFEN SIFRENIZI");
      lcd.setCursor(0, 1);
      lcd.print("     GIRINIZ    ");
      gelen_tus == "";
      delay(1000);

      lcd.clear();
      sifre_gir();
      
    }  
    //Tusların atanması
    else if (gelen_tus == "*")
    {

     
      lcd.setCursor(0, 0);
      lcd.print("SIFRE           ");
      lcd.setCursor(0, 1);
      lcd.print("  DEGISTIRILECEK");   
      gelen_tus == "";
      delay(1000);

      lcd.clear();
      sifre_sorgula();
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.print("SIFRE GIR      #");
      lcd.setCursor(0, 1);
      lcd.print("SIFRE DEGISTIR *");  
      gelen_tus == "";
      delay(1000);
    }
  }
}
//============================================================================================================================================================================================================
void sifre_sorgula()
{
  lcd.setCursor(0, 0);
  lcd.print("ESKI SIFREYI GIR");
  while (i < 4) {
    tus = tuss_takimi.getKey();  //getKey metodu ile tus takimindan basilan tusu alıyorum

    if (tus)
    {
      lcd.setCursor(i, 1);
      lcd.print("*");
      i++;
      delay(100);
      
      gelen_tus = tus;
      if (i == 1)
        bir_ = gelen_tus.toInt();

      if (i == 2)
        iki_ = gelen_tus.toInt();

      if (i == 3)
        uc_ = gelen_tus.toInt();

      if (i == 4)
        dort_ = gelen_tus.toInt();
    }
    if (i == 4)
    {
      delay(200);
      if (bir_ == bir_sifre)
      {
        if (iki_ == iki_sifre)
        {
          if (uc_ == uc_sifre)
          {
            if (dort_ == dort_sifre)
            {
                
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("SIFRE DOGRU!"); //Sifre dogru ise
              delay(1300);


              sifre_degistir();
              i = 5;
            }
          }
        }
      }
      
      else
      { 
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SIFRE YANLIS!!!");  //Sifre yanlis ise
        delay(2000);

      }
    }
  }
  i = 0;
}
//============================================================================================================================================================================================================
  void sifre_degistir()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("YENI SIFREYI GIR");  
  i = 0;

  while (i < 4)
  {
    tus = tuss_takimi.getKey();

    if (tus)
    {
      gelen_tus = tus;

      if (i == 0)
        bir_sifre = gelen_tus.toInt();

      if (i == 1)
        iki_sifre = gelen_tus.toInt();

      if (i == 2)
        uc_sifre = gelen_tus.toInt();

      if (i == 3)
        dort_sifre = gelen_tus.toInt();



      EEPROM.write(bir_address, (bir_sifre));
      EEPROM.write(iki_address, (iki_sifre));
      EEPROM.write(uc_address, (uc_sifre));
      EEPROM.write(dort_address, (dort_sifre));
      lcd.setCursor(i, 1);
      lcd.print("*");   // Yazmis oldugum sifreyi gizlemek icin '*' kullan
      i++;
      delay(100);
      

    }

    if (i == 4) //Eğer sifrem 4 karakter uznuluğunda ise
    {
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SIFRE           ");  
      lcd.setCursor(0, 1);
      lcd.print("    DEGISTIRILDI");  
      delay(1000);

      gelen_tus == "";
    }
  }
  i = 0;
}
//============================================================================================================================================================================================================
  void sifre_gir()
{

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SIFREYI  GIRINIZ");

  
  while (i < 4)
  {
    tus = tuss_takimi.getKey();

    if (tus)
    {
      lcd.setCursor(i, 1);
      lcd.print("*");// Yazmis oldugum sifreyi gizlemek icin '*' kullanilir
      delay(300);
      i++;
      gelen_tus = tus;


      if (i == 1)
        bir_ = gelen_tus.toInt();

      if (i == 2)
        iki_ = gelen_tus.toInt();

      if (i == 3)
        uc_ = gelen_tus.toInt();

      if (i == 4)
        dort_ = gelen_tus.toInt();


    }

    if (i == 4)
    {
      delay(200);
      dogru = false;
      if (bir_ == bir_sifre)
      {
        if (iki_ == iki_sifre)
        {
          if (uc_ == uc_sifre)
          {
            if (dort_ == dort_sifre)
            {
              dogru = true;
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("SIFRE DOGRU!"); //Sifre dogru ise
              delay(3300);
            }
          }
        }
      }


      if (dogru == false)
      {
        
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SIFRE YANLIS!!!");  //Sifre yanlis ise

        delay(2000);

      }
    }
  }
  i = 0;
}
//============================================================================================================================================================================================================
  void sifre_belirle()
{ lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GIRILEN SIFRE   ");
  while (i < 4)
  {
    int sifre;

    tus = tuss_takimi.getKey();

    if (tus)
    {
      delay(300);

      gelen_tus = tus;

      if (i == 0)
      { bir_sifre = gelen_tus.toInt();
        sifre = bir_sifre;
      }
      if (i == 1)
      { iki_sifre = gelen_tus.toInt();
        sifre = iki_sifre;
      }
      if (i == 2)
      { uc_sifre = gelen_tus.toInt();
        sifre = uc_sifre;
      }
      if (i == 3)
      { dort_sifre = gelen_tus.toInt();
        sifre = dort_sifre;
      }

      lcd.setCursor(i, 1);
      lcd.print(sifre);
      i++;
    }
  }
  delay(1000);

  lcd.setCursor(0, 0);
  lcd.print("SIFRE           ");
  lcd.setCursor(0, 1);
  lcd.print("   KAYIT EDILDI ");



  EEPROM.write(bir_address, (bir_sifre));
  EEPROM.write(iki_address, (iki_sifre));
  EEPROM.write(uc_address, (uc_sifre));
  EEPROM.write(dort_address, (dort_sifre));

  delay(1000);
  lcd.clear();
}
//============================================================================================================================================================================================================
void sifre_uzuznluk(){
  int sifre;
  if(sifre<4){
    lcd.setCursor(0,0);
    lcd.print("SIFRE COK KISA");
    }
    else if (sifre>8){
      lcd.setCursor(0,0);
      lcd.print("SIFRE COK UZUN ");
     }
     else{
      lcd.print( "sifre normal");
      }
  
  }
