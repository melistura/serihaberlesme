int latchPin = 5;
int clockPin = 6;
int dataPin = 4;
byte Led = 0;


void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600); //Seri haberleşme hızını belirtir. 
  while(! Serial);  // Seri portun hazır olmasını bekle anlamına gelmektedir. Hazır ise True değilse False değerini döndürecektir. 
  Serial.print("1 ile 8 arasinda bir sayi girin veya "); //Seri monitöre yazdırılması istenen yazı için kullandığımız fonksiyondur.
  Serial.println("x ile temizleyin y ile hepsini acin."); //Eğer bir satır aşağı yazdırmak istersek kullandığımız fonksiyondur. 
}

void loop() {
  if(Serial.available()) {   // Seri portta girdi değerinin olup olmadığını kontrol et eğer girdi varsa oku ve yazdır anlamındadır. 
    char ch = Serial.read();  //Burada karakter değişkeni tanımlayıp girdiğimiz değere yani Serial.read() fonksiyonu ile okunacak değere eşitledik) 
     if (ch >= '1' && ch <= '8' ) { // Eğer karakter değişkeni 1 ve 8 arasında ise (1 ve 8 dahil)
      int leds = ch - '1'; //Led dizisinin 0'dan başladığını unutmayalım. Ekrana 1'den başlayarak yazılsın istiyoruz. 
       bitSet(Led, leds); // Yukarıda Byte olarak atadığımız Led değişkenini ekrana yazılmasını istediğimiz şekilde leds değişkeni olarak atıyoruz.
       RegisterWrite(); // Kendi fonksiyonumuzu oluşturduk.
       Serial.print(leds +1); //Led dizisi 0'dan başlar. Ama biz 0. ledi 1 olarak yazdırmak istiyoruz.
       Serial.println(" numarali led yandi."); 
     }
        if (ch == 'x') { //Eğer x karakterini girersek tüm ledlerin sönmesini istiyoruz. 
            Led = 0;
            RegisterWrite();
            Serial.println("Tum ledler sonduruldu.");
        }
      if (ch == 'y') { //Eğer y karakterini girersek tüm ledlerin sönmesini istiyoruz. 
          Led = 255; //Ledlere gönderilebilecek en yüksek değeri gönderiyoruz. 
            RegisterWrite();
            Serial.println("Tum ledler yandi.");
        }
   }
}
void RegisterWrite() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, Led); //Sadece MSB kullanmamız Ledlerin en yüksek değerlikli olandan başlaması için. 
  digitalWrite(latchPin, HIGH);
}
