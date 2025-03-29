/*
  ==============================================================================

    LookAndFeel.h
    Created: 29 Mar 2025 4:09:27pm
    Author:  axels

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LookAndFeel  : public juce::Component
{
public:
    LookAndFeel();
    ~LookAndFeel() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LookAndFeel)
};
