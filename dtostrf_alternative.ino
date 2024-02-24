class float2string {
public:
  const static uint8_t f_str_max_len = 20;
  inline static char f_str[f_str_max_len];

  static void make(float val, uint8_t dp = 20) {
    f2str(f_str, val, (int8_t)dp);
  }

private:
  static void f2str(char *arr, float val, int8_t dp) {
    if (isnan(val)) {
      memcpy(arr, "NAN", f_str_max_len);
      return;
    } else if (isinf(val)) {
      memcpy(arr, "INF", f_str_max_len);
      return;
    } else if (val > 4294967040.0 || val < -4294967040.0) {
      memcpy(arr, "OVF", f_str_max_len); // constant determined empirically
      return;
    }

    if (dp > 0) {
      float f = abs(val);
      long whole_num = f;          //casting float to long integer(whole number part of number)
      float frac = f - whole_num;  //get the fractional part of number

      //turning fractional part of number into an integer value
      while (dp-- > 0) {
        frac *= 10;
      }
      frac += 0.5;  //roundup
      sprintf(arr, "%ld.%ld", (long)val, (long)frac);
    } else {
      sprintf(arr, "%ld", (long)(val + (val > 0 ? 0.5 : -0.5)));
    }
  }
};

float f = 3.141592;
int cnt = 0;

void setup() {
  Serial.begin(115200);
}
void loop() {
  Serial.print("Try: ");
  Serial.print(cnt++, DEC);

  //sprintf(str,String(f, 4).c_str()); //BEWARE!'String' may slowly eating away SRAM memory

  float2string::make(f, 4);

  Serial.print(", f: ");
  Serial.println(float2string::f_str);

  //increment the float number
  f += 0.1;

  //arbitrary delay
  delay(1000);
}
