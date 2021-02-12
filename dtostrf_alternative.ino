#include <MemoryFree.h>; //https://github.com/mpflaga/Arduino-MemoryFree

#define MAX_CHARS 100 //maximum number of characters in c-string (including null terminator!)
char str[MAX_CHARS] = ""; //IMPORTANT: initialise c-string array as empty
unsigned long cnt = 0;
float f = 3.1415927;

//alternative to dtostrf().Based on the 'print_float' routine with the 'Print' library.
//With dtostrf(), once the float string is created 'unused' array elements are will with <space> character
//strcat_lf concaternates only the float string to the existing c-string
//IMPORTANT: make sure c-string array size is sufficient to accomodate your biggest float string along with the other current string contents!
void strcat_lf(char *str, unsigned int max_chars, const double lf, uint8_t digits = 2) {
  double number = lf;

  if (isnan(number)) {
    strcat(str, "NAN");
    return;
  }
  else if (isinf(number)) {
    strcat(str, "INF");
    return;
  }
  else if (number > 4294967040.0 || number < -4294967040.0) {
    strcat(str, "OVF"); // constant determined empirically
    return;
  }

  // Handle negative numbers
  if (number < 0.0)
  {
    strcat(str, "-");
    number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i = 0; i < digits; ++i) rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  char temp[12];
  sprintf(temp, "%ld", int_part);

  //check there is enough elements to contain integer part
  if (strlen(str) + strlen(temp) >= max_chars) {
    return;
  }

  strcat(str, temp);

  //check there is enough elements to contain '.' + at least one digit after decimal point
  if (strlen(str) + 3 >= max_chars) {
    return;
  }

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0) {
    strcat(str, ".");
  }

  // Extract digits from the remainder one at a time
  unsigned int len = strlen(str);
  while (digits-- > 0)
  {
    remainder *= 10.0;
    unsigned int toPrint = (unsigned int)(remainder);
    str[len++] = toPrint + 48; //convert number to ASCII character

    //check there is enough elements to continue adding remainder digits
    if (len >= max_chars) {
      str[--len] = '\0';
      return;
    }

    remainder -= toPrint;
  }

  str[len] = '\0';

}

void setup() {
  Serial.begin(115200);

  Serial.print(F("Free RAM0 = "));
  Serial.println(freeMemory(), DEC);  // print how much RAM is available.
}

void loop() {

  //String casting of float number
  //sprintf(str, "Try: %ld, Free RAM: %d, f: %s", cnt++, freeMemory(), String(f, 5).c_str()); //NOT OK!!! 'String' still slowly eats away SRAM memory

  //write the first part of your c-string
  sprintf(str, "Try: %ld, f: ", cnt++);
  //concaternate 5dp float number to str
  strcat_lf(str, MAX_CHARS, f, 5);

  //and if you want to add more to str...
  sprintf(&str[strlen(str)], ", Free RAM: %d", freeMemory()); //strcat could have been used instead

  //print to serial monitor
  Serial.println(str);

  //increment the float number
  f += 0.1;

  //arbitrary delay
  delay(1000);
}
