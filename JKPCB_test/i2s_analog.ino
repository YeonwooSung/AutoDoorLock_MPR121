#include <driver/i2s.h>

//#define I2S_SAMPLE_RATE 78125
#define I2S_SAMPLE_RATE 16000
//#define ADC_INPUT ADC1_CHANNEL_4 //pin 32
#define ADC_INPUT ADC1_CHANNEL_5 //pin 33
#define OUTPUT_PIN 27
#define OUTPUT_VALUE 3800
#define READ_DELAY 9000 //microseconds

#define BUFFER_SIZE       512    // Audio buffer size

uint16_t adc_reading;

void i2sInit() {
    esp_err_t err;

   i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_ADC_BUILT_IN),
    .sample_rate =  I2S_SAMPLE_RATE,              // The format of the signal using ADC_BUILT_IN
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT, // is fixed at 12bit, stereo, MSB
    //.channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    //.channel_format = I2S_CHANNEL_FMT_ALL_LEFT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    //.communication_format = I2S_COMM_FORMAT_I2S_MSB,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 2,
    .dma_buf_len = BUFFER_SIZE,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
   };
   // ADC channel 0 with 11db (divide by input 3.6)
  //adc1_config_channel_atten(ADC_INPUT, ADC_ATTEN_11db);
  // 12 bit ADC
  adc1_config_width(ADC_WIDTH_12Bit);
   err = i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
   if (err != ESP_OK) {
    Serial.printf("Failed installing driver: %d\n", err);
    while (true);
   }
   err = i2s_set_adc_mode(ADC_UNIT_1, ADC_INPUT);
   if (err != ESP_OK) {
    Serial.printf("Failed setting adc mode: %d\n", err);
    while (true);
   }
   err = i2s_adc_enable(I2S_NUM_0);
   if (err != ESP_OK) {
    Serial.printf("Failed anabling ADC: %d\n", err);
    while (true);
   }
   Serial.println("I2S Initialised.");
}

void reader(void *pvParameters) {
  uint32_t read_counter = 0;
  uint64_t read_sum = 0;
// The 4 high bits are the channel, and the data is inverted
  uint16_t offset = (int)ADC_INPUT * 0x1000 + 0xFFF;
  size_t bytes_read;
  while(1){
    uint16_t buffer[2] = {0};
    i2s_read(I2S_NUM_0, &buffer, sizeof(buffer), &bytes_read, 15);
    Serial.println(offset - buffer[0]);
    //Serial.println(offset - buffer[1]);
    //Serial.printf("%d  %d\n", offset - buffer[0], offset - buffer[1]);
    /*
    if (bytes_read == sizeof(buffer)) {
      read_sum += offset - buffer[0];
      read_sum += offset - buffer[1];
      read_counter++;
    } else {
      Serial.println("buffer empty");
    }
    if (read_counter == I2S_SAMPLE_RATE) {
      adc_reading = read_sum / I2S_SAMPLE_RATE / 2;
      //Serial.printf("avg: %d millis: ", adc_reading);
      //Serial.println(millis());
      read_counter = 0;
      read_sum = 0;
      i2s_adc_disable(I2S_NUM_0);
      delay(READ_DELAY);
      i2s_adc_enable(I2S_NUM_0);
    }
    */
  }
}


void i2s_analog_setup() {
  // Serial.begin(115200);
  // Put a signal out on pin 
  //uint32_t freq = ledcSetup(0, I2S_SAMPLE_RATE, 10);
  //Serial.printf("Output frequency: %d\n", freq);
  //ledcWrite(0, OUTPUT_VALUE/4);
  //ledcAttachPin(OUTPUT_PIN, 0);
  
  // Initialize the I2S peripheral
  i2sInit();
  // Create a task that will read the data
  //xTaskCreatePinnedToCore(reader, "ADC_reader", 2048, NULL, 1, NULL, 1);
}

void i2s_analog_main() {
  size_t bytesLength = 0;
  float buffer[BUFFER_SIZE] = {0};
  uint16_t ibuffer[BUFFER_SIZE] = {0}; 
  uint16_t tVal;
  float aVal;
  uint16_t offset = (int)ADC_INPUT * 0x1000 + 0xFFF;
    
  i2s_read(I2S_NUM_0, ibuffer, BUFFER_SIZE * sizeof(uint16_t), &bytesLength, portMAX_DELAY);
  //Serial.print("read : ");
  //Serial.println(bytesLength);
    if (bytesLength)
    {
      for (int i = 0; i < bytesLength / 2; i++)
      {
        //tVal = offset - ibuffer[i];
        //Serial.println(tVal);
        //aVal = (float) tVal - 1800,0;
        //buffer[i] = aVal;
        buffer[i] = (float)(offset - ibuffer[i]) - 1800.0;
        Serial.println(buffer[i]);
      }
    }
}

void old_i2s_analog_main() {

  //delay(1020);
  //Serial.printf("ADC reading: %d\n", adc_reading);
  //delay(READ_DELAY);
  //int32_t sample = 0;
  //int bytes_read = i2s_pop_sample(I2S_NUM_0, (char *)&sample, portMAX_DELAY); // no timeout
  //if (bytes_read > 0) {
    //Serial.println(sample);
  //}
    uint16_t offset = (int)ADC_INPUT * 0x1000 + 0xFFF;
    size_t bytes_read;
    //uint16_t buffer[2] = {0};
    uint16_t buffer = 0;
    float aval = 0.0;
    i2s_read(I2S_NUM_0, &buffer, sizeof(buffer), &bytes_read, 15);
    if (bytes_read > 0) {
      //Serial.println(offset - buffer[0]);
      //Serial.println(offset - buffer[1]);
      aval = (offset-buffer) - 1800.00;
      Serial.println(aval);
      //Serial.println(buffer[0]);
      //Serial.println(buffer[1]);
    }
}
