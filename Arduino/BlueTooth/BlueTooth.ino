#include <SoftwareSerial.h>

// 初始化軟件串口，使用 Arduino 的 2 和 3 號引腳
SoftwareSerial BT(2, 3); // RX, TX

void setup() {
  // 啟動 Arduino 與電腦之間的硬件串口通信
  Serial.begin(9600);
  Serial.println("BT is ready!");

  // 啟動與藍牙模塊的軟件串口通信
  BT.begin(9600);
}

void loop() {
  // 從 Arduino 的硬件串口讀取數據並發送到藍牙模塊
  if (Serial.available()) {
    char val = Serial.read(); // 讀取一個字符
    BT.write(val); // 發送這個字符到藍牙模塊
    Serial.write(val); // 回顯到電腦的串口監視器
  }

  // 從藍牙模塊讀取數據並發送到 Arduino 的硬件串口
  if (BT.available()) {
    char val = BT.read(); // 讀取一個字符
    Serial.write(val); // 發送這個字符到電腦
  }
}
