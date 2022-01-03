/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


#define WINDOW_WIDTH 260
#define WINDOW_HEIGHT 200

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    pre_gain_attch(audioProcessor.states, "pre-gain", pre_gain_slider),
    post_gain_attch(audioProcessor.states, "post-gain", post_gain_slider)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (WINDOW_WIDTH, WINDOW_HEIGHT);
    setLookAndFeel(&my_look_and_feel);

    Rectangle<int> bounds = getBounds();
    Rectangle<int> title_rect = bounds.removeFromTop(70);
    bounds.removeFromBottom(20);
    bounds.removeFromLeft(20);
    Rectangle<int> pre_gain_rect = bounds.removeFromLeft(100);
    bounds.removeFromLeft(20);
    Rectangle<int> post_gain_rect = bounds.removeFromLeft(100);
    
    title_label.setBounds(title_rect);
    title_label.setJustificationType(Justification::centred);
    title_label.setFont(18.0f);

    pre_gain_label.setBounds(pre_gain_rect.removeFromTop(15));
    pre_gain_label.setJustificationType(Justification::centred);
    pre_gain_slider.setBounds(pre_gain_rect);
    pre_gain_slider.setRange(-20, 20, 1);

    post_gain_label.setBounds(post_gain_rect.removeFromTop(15));
    post_gain_label.setJustificationType(Justification::centred);
    post_gain_slider.setBounds(post_gain_rect);
    post_gain_slider.setRange(-20, 20, 1);
    
    addAndMakeVisible(title_label);
    addAndMakeVisible(pre_gain_label);
    addAndMakeVisible(post_gain_label);
    addAndMakeVisible(pre_gain_slider);
    addAndMakeVisible(post_gain_slider);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    //g.setColour (juce::Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("FClipper By Filipe Chagas", getLocalBounds(), juce::Justification::topLeft, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
