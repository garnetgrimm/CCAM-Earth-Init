#include "daisy_seed.h"
#include "daisysp.h"

#include <tuple>

using namespace daisy;

struct EarthModule {

    DaisySeed seed;
    std::array<daisy::Led, 8> leds;
    std::array<AdcChannelConfig, 6> knobs;

    daisysp::Oscillator osc;

    void Init() {
        seed.Init();

        for(unsigned i = 0; i < leds.size(); i++)
        {
            leds[i].Init(seed.GetPin(i + 7), false);
            leds[i].Set(0.0f);
            leds[i].SetSampleRate(seed.AudioCallbackRate());
        }

        // We initialize the oscillator with the sample rate of the hardware
        // this ensures that the frequency of the Oscillator will be accurate.
        osc.Init(seed.AudioSampleRate());

        std::array knobsPin = {
            17, 18, 19, 20, 21, 24,
        };

        for (unsigned i = 0; i < knobs.size(); i++) {
            knobs[i].InitSingle(seed.GetPin(knobsPin[i]));
        }
        seed.adc.Init(&knobs[0], knobs.size());

        seed.adc.Start();
    }

    void SetLed(unsigned idx, float val) {
        if (idx >= leds.size() || idx < 0) {
            return;
        }
        
        leds[idx].Set(val);
    }

    float GetKnob(unsigned idx) {
        if (idx >= knobs.size() || idx < 0) {
            return 0.0f;
        }

        // max out at 95% so that we can actually go all the way down to zero
        return 0.95f - seed.adc.GetFloat(idx);
    }

    void Update() {
        for(unsigned i = 0; i < leds.size(); i++) {
            leds[i].Update();
        }
    }

    std::tuple<float, float> Process() {
        float right = osc.Process();
        float left = right;
        return std::make_tuple(left, right);
    }
};

EarthModule earth;

static void EarthCallback(AudioHandle::InputBuffer in, 
            AudioHandle::OutputBuffer out, 
            size_t size) 
{
    earth.Update();

    for (size_t i = 0; i < size; i++)
    {
        // The oscillator's Process function synthesizes, and
        // returns the next sample.
        auto [left, right] = earth.Process();
        out[0][i] = left;
        out[1][i] = right;
    }
}

int main(void)
{
    earth.Init();
    earth.seed.StartAudio(EarthCallback);

    // NOTE: If you do not plan to connect to the serial monitor,
    // you MUST remove this line. Otherwise the program will not run
    // earth.seed.StartLog(true);

    earth.seed.PrintLine("Hello world");

    while(1) {
        for (unsigned i = 0; i < earth.knobs.size(); i++) {
            earth.SetLed(i, earth.GetKnob(i));
        }
        System::Delay(1);
    }
}
