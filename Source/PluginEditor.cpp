/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AxelDelayPluginAudioProcessorEditor::AxelDelayPluginAudioProcessorEditor (AxelDelayPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 16);
    slider.setBounds(0, 0, 70, 86);
	addAndMakeVisible(slider);

    label.setText("Gain", juce::NotificationType::dontSendNotification);
    label.setJustificationType(juce::Justification::horizontallyCentred);
    label.setBorderSize(juce::BorderSize<int>{0, 0, 2, 0});
    label.attachToComponent(&slider, false);
    addAndMakeVisible(label);

    setSize(500, 330);
}

AxelDelayPluginAudioProcessorEditor::~AxelDelayPluginAudioProcessorEditor()
{
}

//==============================================================================

// Paint
void AxelDelayPluginAudioProcessorEditor::paint (juce::Graphics& g){
    g.fillAll(juce::Colours::grey);
}

void AxelDelayPluginAudioProcessorEditor::resized(){
    slider.setTopLeftPosition(215, 120);
}
