// Send:   02 04 00 03 00 01 00 01
// Return: 02 04 00 03 00 01 00 01 C1 F9 // Now with 16-bit CRC added
 
void setup() {
  Serial.begin(115200);
}
 
void loop() {
  char message[] = {0x02, 0x04, 0x00, 0x03, 0x00, 0x01};
  int len = 6;
  uint16_t temp1 = CRC16_modbus(message, len);   // Calculate CRC
  uint16_t result;
  result = lowByte(temp1)*256 + highByte(temp1); // result needs to be little Endian in MODBUS
  Serial.println(result,HEX);                    // print MODBUS CRC
  delay(10000);
}
 
uint16_t CRC16_modbus(char* message, int len) {
  const uint16_t generator = 0xA001;
  uint16_t crc = 0xFFFF;
  for (int i = 0; i < len; ++i) {
    crc ^= (uint16_t)message[i];
    for (int b = 0; b < 8; ++b)
    {
      if ((crc & 1) != 0)
      {
        crc >>= 1;
        crc ^= generator;
      }
      else
        crc >>= 1;
     }
  }
  return crc;
}
