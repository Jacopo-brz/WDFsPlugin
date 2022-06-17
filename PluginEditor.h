/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"
#include "myLookAndFeel.h"


//==============================================================================
/**
*/
class WDFsPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    WDFsPluginAudioProcessorEditor (WDFsPluginAudioProcessor&);
    ~WDFsPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

    //LOOK AND FEEL

    myLookAndFeelV1 myLookAndFeel;




    juce::ScopedPointer<juce::Slider> gainKnob;
    juce::ScopedPointer<juce::Slider> trebleKnob;
    juce::ScopedPointer<juce::Slider> outKnob;


    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttach;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> trebleAttach;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> outAttach;








    WDFsPluginAudioProcessor& audioProcessor;




    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WDFsPluginAudioProcessorEditor)
};
