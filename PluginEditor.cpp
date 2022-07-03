/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WDFsPluginAudioProcessorEditor::WDFsPluginAudioProcessorEditor (WDFsPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //GAIN

    addAndMakeVisible(gainKnob = new juce::Slider("Gain"));
    gainKnob->setLookAndFeel(&myLookAndFeel);
    gainKnob->setSliderStyle(juce::Slider::RotaryVerticalDrag);
    gainKnob->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);


    //TREBLE

    addAndMakeVisible(trebleKnob = new juce::Slider("Treble"));
    trebleKnob->setLookAndFeel(&myLookAndFeel);
    trebleKnob->setSliderStyle(juce::Slider::RotaryVerticalDrag);
    trebleKnob->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);


    //OUT

    addAndMakeVisible(outKnob = new juce::Slider("Out"));
    outKnob->setLookAndFeel(&myLookAndFeel);
    outKnob->setSliderStyle(juce::Slider::RotaryVerticalDrag);
    outKnob->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);



    //GAIN, TREBLE, OUT ATTACHMENTS

    gainAttach = new juce::AudioProcessorValueTreeState::SliderAttachment(p.getState(), "gain", *gainKnob);
    trebleAttach = new juce::AudioProcessorValueTreeState::SliderAttachment(p.getState(), "treble", *trebleKnob);
    outAttach = new juce::AudioProcessorValueTreeState::SliderAttachment(p.getState(), "out", *outKnob);




    setSize(485, 381);
}

WDFsPluginAudioProcessorEditor::~WDFsPluginAudioProcessorEditor()
{
}

//==============================================================================
void WDFsPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    g.drawImageAt(juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize), 0, 0);
}

void WDFsPluginAudioProcessorEditor::resized()
{

    gainKnob->setBounds(((getWidth() / 5) * 1) - 30, (getHeight() / 6) - 18, 70, 70);
    trebleKnob->setBounds(((getWidth() / 5) * 2) + 27, (getHeight() / 6) - 18, 70, 70);
    outKnob->setBounds(((getWidth() / 5) * 4) - 20, (getHeight() / 6) - 18, 70, 70);


}
