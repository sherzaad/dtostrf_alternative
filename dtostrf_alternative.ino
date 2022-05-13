void float2string(char *arr, float val, unsigned char dp = 20) {
  float i = dp;
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

  
  if (i > 0) {
    long whole_num = (long)val; //casting float to long integer(whole number part of number)
    float frac = abs(val - whole_num); //get the fractional part of number
                                       //using abs() to take care of potential negative float value
    
    //turning fractional part of number into an integer value
    while (i > 0) {
      frac *= 10;
      if (dp < 20) i = --dp; //number of decimal places was specfied
      else i = fmod(frac, 1);
    }
    frac += 0.5; //roundup
    sprintf(arr, "%ld.%ld", whole_num, (long)frac);
  }
  else {
    //round up to nearest whole number
    sprintf(arr, "%ld", (long)(val + ((val < 0) ? -0.5 : 0.5)));
  }
}


char str[20]; //maximum number of characters in c-string + 2 (for decimal point and null terminator)
float f = 3.141592;
int cnt = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  str[0] = '\0'; //clear string

  Serial.print("Try: ");
  Serial.print(cnt++, DEC);

  //sprintf(str,String(f, 4).c_str()); //BEWARE!'String' may slowly eating away SRAM memory

  float2string(str, f, 4);

  Serial.print(", f: ");
  Serial.println(str);

  //increment the float number
  f += 0.1;

  //arbitrary delay
  delay(1000);
}
