#pragma once

#include "daisy_seed.h"
#include <array>

using namespace daisy;

struct EarthModule {
    DaisySeed seed;
    std::array<daisy::Led, 8> leds;
    std::array<daisy::AdcChannelConfig, 6> knobs;
    std::array<daisy::Switch, 8> buttons;

    void Init();
    void SetLed(unsigned idx, float val);
    float GetKnob(unsigned idx);
    bool GetButton(unsigned idx);
    void Update();
};