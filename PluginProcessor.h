/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include "InputStage.h"
#include "Gain_Stage.h"
#include "Summing_Stage.h"
#include "ToneControlStage.h"
#include "OutputStage.h"
//==============================================================================
/**
*/
class WDFsPluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    WDFsPluginAudioProcessor();
    ~WDFsPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState& getState();


private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WDFsPluginAudioProcessor)

    //STATE
    juce::ScopedPointer<juce::AudioProcessorValueTreeState> state;


    //input stage
    Input_Data I_data;
    MyMat_IN S_in;

    //Gain stage;
    Gain_Data G_data;
    MyMat_G S_g;

    //Summing stage
    Summing_Data S_data;
    MyMat_SS S_ss;

    //Tone control stage
    TC_Data TC_data;
    MyMat_TC S_tc;

    //Output stage
    Output_Data O_data;

    //read and write on file
    juce::AudioFormatManager formatManager;
    juce::AudioBuffer<float> GetAudioBufferFromFile(juce::File file);
    juce::AudioBuffer<float> exp_sweep_buffer;
    juce::AudioBuffer<float> vst_output_buffer;
    double sample_rate = 192000;

    float current_gain_value = 0.5;
    float current_treble_value = 0.5;
    float current_out_value = 0.5;


};
