#include "ofApp.h"
#define PIN_IF 0
#define PIN_LED 3
#define MAX_DISTANCE 500
#define MAX_LED 255
#define MIN_LED 0

void ofApp::setup(){
    ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
    arduino.connect("/dev/cu.usbmodem641");
    arduino.sendFirmwareVersionRequest();
}

void ofApp::update(){
    arduino.update();
    
}

void ofApp::draw(){
    
}

void ofApp::setupArduino(const int&version){
    ofLogNotice() << "arduino init" << endl;
    ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);
    
    //arduino.sendAnalogPinMode(PIN_IF, ARD_INPUT);
    arduino.sendAnalogPinReporting(PIN_IF, ARD_ANALOG);
    arduino.sendDigitalPinMode(PIN_LED, ARD_PWM);
    
    ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
    ofAddListener(arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);
    
}

void ofApp::updateArduino(const int&version){
    
}

void ofApp::digitalPinChanged(const int&pin){
    ofLog() << "value of pin" << pin << "is now" << arduino.getPwm(pin) << endl;
    
}

void ofApp::analogPinChanged(const int&pin){
    ofLog() << "analog pin" << pin << "changed to" <<arduino.getAnalog(pin) << endl;
    int distance = arduino.getAnalog(pin);
    
    int ledwaarde = ofMap(distance, 0, MAX_DISTANCE, MIN_LED, MAX_LED);
    arduino.sendPwm(PIN_LED, ledwaarde);
}
