#include "json/earth.h"
#include "daisysp.h"
#include <array>

json2daisy::DaisyEarth earth;
daisysp::Oscillator vco;
daisysp::Oscillator lfo;

static constexpr float MAX_U16_FLOAT = static_cast<float>(0xFFFF);

static void EarthCallback(daisy::AudioHandle::InputBuffer in, 
            daisy::AudioHandle::OutputBuffer out, 
            size_t size) {
    earth.ProcessAllControls();
    earth.PostProcess();

    for (size_t i = 0; i < size; i++)
    {
        float value = vco.Process();
        out[0][i] = value;
        out[1][i] = value;
    }
}

static void CVOutCallback(uint16_t **out, size_t size)
{
    for(size_t i = 0; i < size; i++)
    {
        // the outputs are switched, do not know why.
        out[1][i] = static_cast<uint16_t>(earth.knob1.Value() * MAX_U16_FLOAT) >> 4;
        out[0][i] = static_cast<uint16_t>(earth.knob2.Value() * lfo.Process()) >> 4;
    }
}

int main(void)
{
    earth.Init();
    earth.StartAudio(EarthCallback);
    earth.StartCV(CVOutCallback);

    vco.Init(earth.som.AudioSampleRate());
    lfo.Init(earth.CvOutSampleRate());
    
    lfo.SetFreq(220.0f);
    lfo.SetAmp(MAX_U16_FLOAT);

    vco.SetFreq(440.0f);

    earth.som.StartLog(false);
    earth.som.PrintLine("Hello world");

    while(1) {
        for (unsigned i = 0; i < earth.knobs.size(); i++) {
            earth.leds[i]->Set(earth.knobs[i]->Value() - 0.05);
        }
        earth.led7.Set(earth.cvin1.Value() - 0.05);
        earth.led8.Set(earth.cvin2.Value() - 0.05);

        for (unsigned i = 0; i < earth.leds.size(); i++) {
            if (earth.buttons[i]->Pressed()) {
                earth.leds[i]->Set(0.0f);
            }
        }

        daisy::System::Delay(1);
    }
}