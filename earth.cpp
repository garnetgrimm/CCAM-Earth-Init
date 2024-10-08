#include "earth.h"

using namespace daisy;

void EarthModule::Init() {
    seed.Init();

    // init LEDs
    for(unsigned i = 0; i < leds.size(); i++)
    {
        leds[i].Init(seed.GetPin(i + 7), false);
        leds[i].Set(0.0f);
        leds[i].SetSampleRate(seed.AudioCallbackRate());
    }

    // init knobs
    std::array knobsPin = { 17, 18, 19, 20, 21, 24 };
    for (unsigned i = 0; i < knobs.size(); i++) {
        knobs[i].InitSingle(seed.GetPin(knobsPin[i]));
    }
    seed.adc.Init(&knobs[0], knobs.size());
    seed.adc.Start();

    // init buttons
    std::array buttonPin = { 0, 1, 2, 3, 4, 5, 6, 25 };
    for (unsigned i = 0; i < buttons.size(); i++) {
        buttons[i].Init(seed.GetPin(buttonPin[i]));
    }

}

void EarthModule::SetLed(unsigned idx, float val) {
    if (idx >= leds.size() || idx < 0) {
        return;
    }
    
    leds[idx].Set(val);
}

float EarthModule::GetKnob(unsigned idx) {
    if (idx >= knobs.size() || idx < 0) {
        return 0.0f;
    }

    // max out at 95% so that we can actually go all the way down to zero
    return 0.95f - seed.adc.GetFloat(idx);
}

bool EarthModule::GetButton(unsigned idx) {
    if (idx >= buttons.size() || idx < 0) {
        return false;
    }

    return buttons[idx].Pressed();
}

void EarthModule::Update() {
    for (unsigned i = 0; i < leds.size(); i++) {
        leds[i].Update();
    }
    for (unsigned i = 0; i < buttons.size(); i++) {
        buttons[i].Debounce();
    }
}