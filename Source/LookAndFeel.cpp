/*
  ==============================================================================

    LookAndFeel.cpp
    Created: 29 Mar 2025 4:09:27pm
    Author:  axels

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LookAndFeel.h"

//==============================================================================
RotaryKnobLookAndFeel::RotaryKnobLookAndFeel()
{
    setColour(juce::Label::textColourId, Colors::Knob::label);
    setColour(juce::Slider::textBoxTextColourId, Colors::Knob::label);
}

LookAndFeel::~LookAndFeel()
{
}

void LookAndFeel::paint (juce::Graphics& g)
{
}

void LookAndFeel::resized()
{

}

void RotaryKnobLookAndFeel::drawRotarySlider(
    juce::Graphics& g,
    int x, int y, int width, [[maybe_unused]] int height,
    float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle,
    juce::Slider& slider)
{    
    auto bounds = juce::Rectangle<int>(x, y, width, width).toFloat();
    auto knobRect = bounds.reduced(10.0f, 10.0f);
    
    auto path = juce::Path();
    path.addEllipse(knobRect);
    dropShadow.drawForPath(g, path);
    
    g.setColour(Colors::Knob::outline);
    g.fillEllipse(knobRect);

    auto innerRect = knobRect.reduced(2.0f, 2.0f);
    auto gradient = juce::ColourGradient(
        Colors::Knob::gradientTop, 0.0f, innerRect.getY(),
        Colors::Knob::gradientBottom, 0.0f, innerRect.getBottom(), false);
    g.setGradientFill(gradient);
    g.fillEllipse(innerRect);
}
