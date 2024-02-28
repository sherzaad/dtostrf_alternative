class float2string {
  public:
    const static uint8_t f_str_max_len = 16;
    inline static char f_str[f_str_max_len];

    static void make(float val, uint8_t dp) {
      f2str(f_str, val, dp);
    }

  private:
    static void f2str(char *arr, float val, uint8_t dp) {
      if (isnan(val)) {
        memcpy(arr, "NAN", f_str_max_len);
        return;
      } else if (isinf(val)) {
        memcpy(arr, "INF", f_str_max_len);
        return;
      } else if (val > 4294967040.0 || val < -4294967040.0) {
        memcpy(arr, "OVF", f_str_max_len);  // constant determined empirically
        return;
      }

      float f = abs(val);
      uint8_t index = 0;

      if (val < 0) {
        memcpy(&arr[index], "-", f_str_max_len);
        index = 1;
      }

      if (f < 1) {
        memcpy(&arr[index], "0.", f_str_max_len);
        index += 2;
      }

      for (uint8_t i = 0; i < dp; ++i) {
        f *= 10;
        if (f < 1) {
          if(!((i+1 == dp) && (f + 0.5 > 1))) arr[index++] = '0';
        }
      }

      f += 0.5;  //roundup

      sprintf(&arr[index], "%ld", (uint32_t)f);

      if (index < 2) {
        index = strlen(arr) - dp;
        memmove(&arr[index + 1], &arr[index], dp);
        arr[index] = '.';
      }
    }
};

float f = 0.141592;
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
