#include <Arduino.h>
class Button{
    private:
        int pin;
        void (*CallbackHandler)() = nullptr;
        bool state;
        
    public:
        Button(int pin);
        void tick();
        void setPin(int pin);
        void setCallbackHandler( void (*handler)()) {CallbackHandler = *handler;}
        
};

Button::Button(int pin = 0){
    this->pin = pin;
    pinMode(pin, INPUT);
}

void Button::tick(){
    if (digitalRead(pin)==false && state==false){
        state = true;
    }

    if (digitalRead(pin)==true && state==true){
        state = false;
        if (*CallbackHandler) CallbackHandler();
    }
}

void Button::setPin(int pin){
    this->pin = pin;
    pinMode(pin, INPUT);
}
