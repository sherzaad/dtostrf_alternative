#include <MemoryFree.h>; //https://github.com/mpflaga/Arduino-MemoryFree

void float2string(char *arr, float val, unsigned char precision = 2) {
  if (isnan(val)) {
    strcat(arr, "NAN");
    return;
  }
  else if (isinf(val)) {
    strcat(arr, "INF");
    return;
  }
  else if (val > 4294967040.0 || val < -4294967040.0) {
    strcat(arr, "OVF"); // constant determined empirically
    return;
  }

  unsigned long multiplier = 1;
  float roundup = (val < 0) ? -0.5 : 0.5;

  for (int i = 0; i < precision; ++i) {
    multiplier *= 10;
  }

  roundup /= multiplier;

  if (precision == 0) sprintf(arr, "%ld", (long)(val + roundup));
  else if (val < 0) sprintf(arr, "%ld.%ld", (long)val, (long)(((long)val - val + roundup)*multiplier));
  else sprintf(arr, "%ld.%ld", (long)val, (long)((val - (long)val + roundup)*multiplier));

}

char str[20]; //maximum number of characters in c-string + 2 (for decimal point and null terminator)
float f = 3.141592;
int cnt = 0;
void setup() {
  Serial.begin(115200);

  Serial.print(F("Free RAM = "));
  Serial.println(freeMemory(), DEC);  // print how much RAM is available.
}

void loop() {
  str[0] = '\0'; //clear string

  Serial.print("Try: ");
  Serial.print(cnt++, DEC);

  //create a 4dp c-string from float number
  //String casting of float number
  //sprintf(str,String(f, 4).c_str()); //NOT OK!!! 'String' still slowly eats away SRAM memory

  float2string(str, f, 4);

  Serial.print(", f: ");
  Serial.print(str);

  Serial.print(", Free RAM: ");
  Serial.println(freeMemory(), DEC);

  //increment the float number
  f += 0.1;

  //arbitrary delay
  delay(1000);
}
