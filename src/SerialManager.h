// Arduino RBD Serial Manager Library v0.1 - A simple interface for serial communication.
// https://github.com/shakh13/SerialManager
// Shaxzod Saidmurodov
// MIT License

#ifndef SERIAL_MANAGER
#define SERIAL_MANAGER

#include <Arduino.h>

  class SerialManager {
    public:
      SerialManager();
      void start(int ser);
      void setFlag(char value);
      void setDelimiter(char value);
      bool onReceive();
      String getValue();
      String getCmd();
      String getParam();
      bool isCmd(String value);
      bool isParam(String value);
      template <typename T> void print(T value){if (_serial == 0) Serial.print(value); else Serial1.print(value);}
      template <typename T> void println(T value){if (_serial == 0) Serial.println(value); else Serial1.println(value);}
    private:
      int _serial;
      int _position;
      char _char;
      char _flag      = '\n'; // you must set the serial monitor to include a newline with each command
      char _delimiter = ',';
      String _buffer  = "";
      String _value   = "";
  };

#endif
