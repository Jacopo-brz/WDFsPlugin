/*
  ==============================================================================

    myLookAndFeel.cpp
    Created: 16 Apr 2021 5:41:46pm
    Author:  franc

  ==============================================================================
*/
#include "myLookAndFeel.h"
//==============================================================================
myLookAndFeelV1::myLookAndFeelV1()
{

    img1 = juce::ImageCache::getFromMemory(BinaryData::knob1_png, BinaryData::knob1_pngSize);

}

//==============================================================================
void myLookAndFeelV1::drawRotarySlider(juce::Graphics& g,
    int x, int y, int width, int height, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{

    if (img1.isValid())
    {
        const double rotation = (slider.getValue()
            - slider.getMinimum())
            / (slider.getMaximum()
                - slider.getMinimum());

        const int frames = img1.getHeight() / img1.getWidth();
        const int frameId = (int)ceil(rotation * ((double)frames - 1.0));
        const float radius = juce::jmin(width / 2.0f, height / 2.0f);
        const float centerX = x + width * 0.5f;
        const float centerY = y + height * 0.5f;
        const float rx = centerX - radius - 1.0f;
        const float ry = centerY - radius;

        g.drawImage(img1,
            (int)rx,
            (int)ry,
            2 * (int)radius,
            2 * (int)radius,
            0,
            frameId * img1.getWidth(),
            img1.getWidth(),
            img1.getWidth());
    }
    else
    {
        static const float textPpercent = 0.35f;
        juce::Rectangle<float> text_bounds(1.0f + width * (1.0f - textPpercent) / 2.0f,
            0.5f * height, width * textPpercent, 0.5f * height);

        g.setColour(juce::Colours::white);

        g.drawFittedText(juce::String("No Image"), text_bounds.getSmallestIntegerContainer(),
            juce::Justification::horizontallyCentred | juce::Justification::centred, 1);
    }
}


