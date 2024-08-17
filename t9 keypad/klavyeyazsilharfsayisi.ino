 #include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char lastKey = '\0';
int keyCount = 0;
unsigned long lastKeyPressTime = 0;
unsigned long debounceDelay = 500; // Tuş aralığı kontrolü için süre (yarım saniye)
String currentWord = ""; // Şu anki kelime
String outputText = ""; // Girişten çıkan metin

void setup() {
  Serial.begin(57600);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    unsigned long currentTime = millis();

    if (key == lastKey && (currentTime - lastKeyPressTime) < debounceDelay) {
      // Aynı tuşa hızlı bir şekilde basıldı, beklenilen tuş aralığından kısa
      keyCount=1;
    } else {
      keyCount++;
      lastKey = key;
      lastKeyPressTime = currentTime;
    }

    if (keyCount == 1) {    
      currentWord = ""; // Her yeni tuş basımında kelimeyi sıfırlayın
      if (key == '1') {
         currentWord=",";
      } else if (key == '2') {
         currentWord="a";
      } else if (key == '3') {
        currentWord="d";
      } else if (key == '4') {
         currentWord="g";
      } else if (key == '5') {
         currentWord="k";
      } else if (key == '6') {
         currentWord="m";
      } else if (key == '7') {
         currentWord="p";
      } else if (key == '8') {
         currentWord="t";
      } else if (key == '9') {
         currentWord="y";
      } else if (key == '0') {
         currentWord=" ";
      } 
    } 
    
    else if (keyCount == 2) { 
      if(key == '1'){
         currentWord=".";
      } else if (key == '2') {
         currentWord="b";
      } else if (key == '3') {
         currentWord="e";
      } else if (key == '4') {
         currentWord="h";
      } else if (key == '5') {
         currentWord="l";
      } else if (key == '6') {
         currentWord="n";
      } else if (key == '7') {
        currentWord="r";
      } else if (key == '8') {
         currentWord="u";
      } else if (key == '9') {
        currentWord="x";
      } 
    }
    
     else if (keyCount == 3) {
      if (key=='1'){
         currentWord="?";
      }else if (key == '2') {
         currentWord="c";
      } else if (key == '3') {
         currentWord="f";
      } else if (key == '4') {
         currentWord="ı";
      } else if (key == '5') {
        currentWord="j";
      } else if (key == '6') {
         currentWord="o";
      } else if (key == '7') {
         currentWord="s";
      } else if (key == '8') {
         currentWord="v";
      } else if (key == '9') {
         currentWord="z";
      } 
 
   if (keyCount > 3) {
      keyCount = 1;
    }
   } 
    // Metni seri monitöre yazdırın
  Serial.print(currentWord);

  // Eğer * tuşuna basılırsa, şu anki kelimeyi tamamla ve seri monitöre yazdır
  if (key == '*') {
    outputText += currentWord;
    Serial.println(" -> " + outputText);
    currentWord = "";
  }
  else if (key == '#') {
      if (outputText.length() > 0) {
        // Çıktı metninde en az bir karakter varsa, son karakteri sil
        outputText.remove(outputText.length() - 1);
        Serial.println("Son karakter silindi -> " + outputText);
      }
    }
    else if (key=='A'){
      int karaktersayisi = outputText.length(); //karakter sayisi için
      int harfsayisi = 0;  //harf sayısı
      for (int i = 0; i < karaktersayisi; i++) {
        if (isAlpha(outputText[i])) {  //isAlpha() işlevi, verilen karakterin bir harf olup olmadığını kontrol eder.
          harfsayisi++;
        }
      }
      Serial.println("Karakter Sayısı: " + String(karaktersayisi) + ", Harf Sayısı: " + String(harfsayisi));
    
    }
  }
}

