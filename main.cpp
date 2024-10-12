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

    while(1) {
        for (unsigned i = 0; i < earth.leds.size(); i++) {
            float value;
            if (earth.buttons[i]->Pressed()) {
                value = 0.0f;
            } else if (i < earth.knobs.size()) {
                value = earth.knobs[i]->Value() - 0.05;
            } else {
                value = 1.0f;
            }
            earth.leds[i]->Set(value);
        }
        daisy::System::Delay(1);
    }
}