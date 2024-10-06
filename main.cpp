#include "daisy_seed.h"
#include "daisysp.h"

#include <tuple>

using namespace daisy;

struct EarthModule {
    daisysp::Oscillator osc;
    std::array<daisy::Led, 8> led;
    DaisySeed seed;

    void Init() {
        seed.Init();

        for(int i = 0; i < 8; i++)
        {
            led[i].Init(seed.GetPin(i + 7), false);
            led[i].Set(0.0f);
        }

        // We initialize the oscillator with the sample rate of the hardware
        // this ensures that the frequency of the Oscillator will be accurate.
        osc.Init(seed.AudioSampleRate());
    }

    void SetLed(unsigned idx, bool state) {
        if (idx >= led.size() || idx < 0) {
            return;
        }
        
        // LED's support dimming via PWM, but requires
        // function handlers I don't care to set up
        led[idx].Set(state ? 1.0f : 0.0f);
        led[idx].Update();
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
    //earth.seed.StartAudio(EarthCallback);

    // NOTE: If you do not plan to connect to the serial monitor,
    // you MUST remove this line. Otherwise the program will not run
    earth.seed.StartLog(true);

    int blinkIndex = 0;
    bool ledState = true;
    while(1) {
        earth.SetLed(blinkIndex, ledState);
        blinkIndex++;
        if (blinkIndex == 8) {
            ledState = !ledState;
            blinkIndex = 0;
        }
        System::Delay(500);
        earth.seed.PrintLine("Toggle %d %d", blinkIndex, ledState);
    }
}
