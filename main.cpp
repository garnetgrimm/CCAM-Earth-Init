#include "daisy_seed.h"
#include "daisysp.h"

#include <tuple>

using namespace daisy;

struct EarthModule {

    DaisySeed seed;
    std::array<daisy::Led, 8> led;
    AdcChannelConfig knob[4];

    daisysp::Oscillator osc;

    void Init() {
        seed.Init();

        for(unsigned i = 0; i < led.size(); i++)
        {
            led[i].Init(seed.GetPin(i + 7), false);
            led[i].Set(0.0f);
            led[i].SetSampleRate(seed.AudioCallbackRate());
        }

        // We initialize the oscillator with the sample rate of the hardware
        // this ensures that the frequency of the Oscillator will be accurate.
        osc.Init(seed.AudioSampleRate());

        knob[0].InitSingle(seed.GetPin(18));
        knob[1].InitSingle(seed.GetPin(19));
        knob[2].InitSingle(seed.GetPin(21));
        knob[3].InitSingle(seed.GetPin(24));
        seed.adc.Init(&knob[0], 4);

        seed.adc.Start();
    }

    void SetLed(unsigned idx, float val) {
        if (idx >= led.size() || idx < 0) {
            return;
        }
        
        // LED's support dimming via PWM, but requires
        // function handlers I don't care to set up
        led[idx].Set(val);
    }

    void Update() {
        for(unsigned i = 0; i < led.size(); i++) {
            led[i].Update();
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

    int blinkIndex = 0;
    float ledAmount = 0.0f;
    while(1) {
        earth.SetLed(blinkIndex, ledAmount);
        blinkIndex++;
        if (blinkIndex == 8) {
            ledAmount += 0.1f;
            blinkIndex = 0;
        }
        if (ledAmount >= 1.0f) {
            ledAmount = 0.0f;
        }
        System::Delay(500);
        earth.seed.PrintLine("Toggle %d %d", blinkIndex, ledAmount);
    }
}
