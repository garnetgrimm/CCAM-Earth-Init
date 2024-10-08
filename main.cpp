#include "earth.h"
#include "daisysp.h"

EarthModule earth;
daisysp::Oscillator osc;

static void EarthCallback(AudioHandle::InputBuffer in, 
            AudioHandle::OutputBuffer out, 
            size_t size) {
    earth.Update();

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
    earth.seed.StartAudio(EarthCallback);

    osc.Init(earth.seed.AudioSampleRate());

    earth.seed.StartLog();
    earth.seed.PrintLine("Hello world");

    while(1) {
        for (unsigned i = 0; i < earth.leds.size(); i++) {
            float value;
            if (earth.GetButton(i)) {
                value = 0.0f;
            } else if (i < earth.knobs.size()) {
                value = earth.GetKnob(i);
            } else {
                value = 1.0f;
            }
            earth.SetLed(i, value);
        }
        System::Delay(1);
    }
}
