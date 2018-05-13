// Arduino RBD Serial Manager Library v0.1 - A simple interface for serial communication.
// https://github.com/shakh13/SerialManager
// Shaxzod Saidmurodov
// MIT License

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <SerialManager.h> // https://github.com/shakh13/SerialManager

  SerialManager::SerialManager() {}

  void SerialManager::start(int pin_rx, pin_tx) {
    _pin_rx = pin_rx;
    _pin_tx = pin_tx;
    SoftwareSerial serial(pin_rx, pin_tx);
    serial.begin(115200);
  }

  bool SerialManager::onReceive() {
    if(serial.available()) {
      _char = char(serial.read());

      if(_char == _flag) {
        _value  = _buffer;
        _buffer = "";
        return true;
      }
      else {
        _buffer += _char;
        return false;
      }
    }
    else {
      return false;
    }
  }

  String SerialManager::getValue() {
    return _value;
  }

  void SerialManager::setFlag(char value) {
    _flag = value;
  }

  void SerialManager::setDelimiter(char value) {
    _delimiter = value;
  }

  String SerialManager::getCmd() {
    _position = getValue().indexOf(_delimiter);

    if(_position > -1) {
      return _value.substring(0, _position);
    }
    else {
      return getValue();
    }
  }

  String SerialManager::getParam() {
    _position = getValue().indexOf(_delimiter);

    if(_position > -1) {
      return _value.substring(_position + 1, _value.length());
    }
    else {
      return "";
    }
  }

  bool SerialManager::isCmd(String value) {
    return getCmd() == value;
  }

  bool SerialManager::isParam(String value) {
    return getParam() == value;
  }