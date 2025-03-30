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
    //// Knobs:
    //addAndMakeVisible(gainKnob);
    //addAndMakeVisible(mixKnob);
    //addAndMakeVisible(delayTimeKnob);

    // Delay Group
    delayGroup.setText("Delay");
    delayGroup.setTextLabelPosition(juce::Justification::horizontallyCentred);
	// Delay Group Individual Knobs
    delayGroup.addAndMakeVisible(delayTimeKnob);
	addAndMakeVisible(delayGroup);

    // Feedback Group
    feedbackGroup.setText("Feedback");
    feedbackGroup.setTextLabelPosition(juce::Justification::horizontallyCentred);
    // Feedback Group Individual Knobs
    addAndMakeVisible(feedbackGroup);

    // Output Group
    outputGroup.setText("Output");
	outputGroup.setTextLabelPosition(juce::Justification::horizontallyCentred);
	// Output Group Individual Knobs
    outputGroup.addAndMakeVisible(gainKnob);
	outputGroup.addAndMakeVisible(mixKnob); 
	addAndMakeVisible(outputGroup);

    setSize(500, 330);
}

AxelDelayPluginAudioProcessorEditor::~AxelDelayPluginAudioProcessorEditor()
{
}

//==============================================================================

// Paint
void AxelDelayPluginAudioProcessorEditor::paint (juce::Graphics& g){
    g.fillAll(Colors::background);
}

void AxelDelayPluginAudioProcessorEditor::resized(){
	auto bounds = getLocalBounds();

    int y = 10;
    int height = bounds.getHeight() - 20;

    delayGroup.setBounds(10, y, 110, height);

    outputGroup.setBounds(bounds.getWidth() - 160, y, 150, height);

    feedbackGroup.setBounds(delayGroup.getRight() + 10, y, 
        outputGroup.getX() - delayGroup.getRight() - 20, height);

    delayTimeKnob.setTopLeftPosition(20, 20);
    mixKnob.setTopLeftPosition(20, 20);
    gainKnob.setTopLeftPosition(mixKnob.getX(), mixKnob.getBottom() + 10);
}
