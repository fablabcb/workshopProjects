#include "AudioTools.h"
#include "BluetoothA2DPSink.h"
#include <Arduino.h>

// Button GPIO pins
#define BUTTON_PLAY_PAUSE 18
#define BUTTON_PREVIOUS 5
#define BUTTON_NEXT 17
#define BUTTON_VOLUME_UP 4
#define BUTTON_VOLUME_DOWN 16

#define I2S_LRC 14
#define I2S_BCLK 27
#define I2S_DIN 26

// I2S and Bluetooth sink
I2SStream i2s;
BluetoothA2DPSink a2dp_sink(i2s);

// Button states
bool lastPlayPauseState = HIGH;
bool lastPreviousState = HIGH;
bool lastNextState = HIGH;
bool lastVolumeUpState = HIGH;
bool lastVolumeDownState = HIGH;

// Playback state
bool isPlaying = false;

void setup()
{
    Serial.begin(115200);

    // Configure buttons
    pinMode(BUTTON_PLAY_PAUSE, INPUT_PULLUP);
    pinMode(BUTTON_PREVIOUS, INPUT_PULLUP);
    pinMode(BUTTON_NEXT, INPUT_PULLUP);
    pinMode(BUTTON_VOLUME_UP, INPUT_PULLUP);
    pinMode(BUTTON_VOLUME_DOWN, INPUT_PULLUP);

    // Configure I2S pins
    auto cfg = i2s.defaultConfig();
    cfg.pin_bck = I2S_BCLK; // BCLK pin
    cfg.pin_ws = I2S_LRC;   // LRC pin
    cfg.pin_data = I2S_DIN; // DIN pin
    i2s.begin(cfg);

    // Start Bluetooth sink
    a2dp_sink.start("ESPEAKER");
    a2dp_sink.set_volume(64);
}

void loop()
{
    // Read button states
    bool currentPlayPauseState = digitalRead(BUTTON_PLAY_PAUSE);
    bool currentPreviousState = digitalRead(BUTTON_PREVIOUS);
    bool currentNextState = digitalRead(BUTTON_NEXT);
    bool currentVolumeUpState = digitalRead(BUTTON_VOLUME_UP);
    bool currentVolumeDownState = digitalRead(BUTTON_VOLUME_DOWN);
    Serial.println(a2dp_sink.get_volume());
    // Handle Play/Pause button
    if(currentPlayPauseState == LOW && lastPlayPauseState == HIGH)
    {
        Serial.println(" Play/Pause Button Pressed");
        if(isPlaying)
        {
            a2dp_sink.pause(); // Call pause method
            isPlaying = false;
            Serial.println(" Paused");
        }
        else
        {
            a2dp_sink.play(); // Call play method
            isPlaying = true;
            Serial.println(" Playing");
        }
    }
    lastPlayPauseState = currentPlayPauseState;

    // Handle Previous Track button
    if(currentPreviousState == LOW && lastPreviousState == HIGH)
    {
        Serial.println("Previous Track Button Pressed");
        a2dp_sink.previous(); // Go to the previous track
    }
    lastPreviousState = currentPreviousState;

    // Handle Next Track button
    if(currentNextState == LOW && lastNextState == HIGH)
    {
        Serial.println("Next Track Button Pressed");
        a2dp_sink.next(); // Go to the next track
    }
    lastNextState = currentNextState;

    // Handle Volume Up button
    if(currentVolumeUpState == LOW && lastVolumeUpState == HIGH)
    {
        int louder = a2dp_sink.get_volume();
        if(louder < 100)
        {
            louder += 1;
            a2dp_sink.set_volume(louder);
        }
        Serial.println("Volume Up Button Pressed");
    }
    lastVolumeUpState = currentVolumeUpState;

    // Handle Volume Down button
    if(currentVolumeDownState == LOW && lastVolumeDownState == HIGH)
    {
        int silenter = a2dp_sink.get_volume();
        if(silenter > 0)
        {
            silenter -= 1;
            a2dp_sink.set_volume(silenter);
        }
        Serial.println("Volume Down Button Pressed");
    }
    lastVolumeDownState = currentVolumeDownState;

    // Short delay to debounce buttons
    delay(50);
}
