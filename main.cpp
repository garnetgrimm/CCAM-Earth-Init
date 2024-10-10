#include "board.h"
#include "daisysp.h"
#include <array>

json2daisy::DaisyEarth earth;
daisysp::Oscillator osc;

static void EarthCallback(daisy::AudioHandle::InputBuffer in, 
            daisy::AudioHandle::OutputBuffer out, 
            size_t size) {
    earth.ProcessAllControls();
    earth.PostProcess();

    for (size_t i = 0; i < size; i++)
    {
        float value = osc.Process();
        out[0][i] = value;
        out[1][i] = value;
    }
}

int main(void)
{
    earth.Init();
    earth.StartAudio(EarthCallback);

    osc.Init(earth.som.AudioSampleRate());

    earth.som.StartLog();
    earth.som.PrintLine("Hello world");

    std::array<daisy::Led*, 8> leds = {
        &earth.led1,
        &earth.led2,
        &earth.led3,
        &earth.led4,
        &earth.led5,
        &earth.led6,
        &earth.led7,
        &earth.led8
    };

    std::array<daisy::Switch*, 8> buttons = {
        &earth.button1,
        &earth.button2,
        &earth.button3,
        &earth.button4,
        &earth.button5,
        &earth.button6,
        &earth.button7,
        &earth.button8,
    };

    std::array<daisy::AnalogControl*, 6> knobs = {
        &earth.knob1,
        &earth.knob2,
        &earth.knob3,
        &earth.knob4,
        &earth.knob5,
        &earth.knob6,
    };

    while(1) {
        for (unsigned i = 0; i < leds.size(); i++) {
            float value;
            if (buttons[i]->Pressed()) {
                value = 0.0f;
            } else if (i < knobs.size()) {
                value = knobs[i]->Value();
            } else {
                value = 1.0f;
            }
            leds[i]->Set(value);
        }
        daisy::System::Delay(1);
    }
}