/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <iostream>

#define WINDOW_WIDTH (464)
#define WINDOW_HEIGHT (180)

//==============================================================================
FClipperAudioProcessorEditor::FClipperAudioProcessorEditor(FClipperAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p),
    pre_gain_attch(audioProcessor.states, "pre-gain", pre_gain_slider),
    post_gain_attch(audioProcessor.states, "post-gain", post_gain_slider),
    offset_attch(audioProcessor.states, "offset", offset_slider),
    hard_soft_attch(audioProcessor.states, "hard_soft", hard_soft_switch)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (WINDOW_WIDTH, WINDOW_HEIGHT);
    setLookAndFeel(&gray_knob_slider_lnf);

    // -- Rectangles --
    Rectangle<int> bounds = getBounds();
    bounds.removeFromTop(10);
    bounds.removeFromBottom(20);
    bounds.removeFromLeft(10);
    Rectangle<int> title_rect = bounds.removeFromTop(30);
    title_rect.removeFromRight(10);
    Rectangle<int> version_rect = title_rect.removeFromRight(150);
    bounds.removeFromLeft(10);
    Rectangle<int> pre_gain_rect = bounds.removeFromLeft(100);
    bounds.removeFromLeft(20);
    Rectangle<int> offset_rect = bounds.removeFromLeft(100);
    bounds.removeFromLeft(20);
    Rectangle<int> hard_soft_switch_rect = bounds.removeFromLeft(64);
    bounds.removeFromLeft(20);
    Rectangle<int> post_gain_rect = bounds.removeFromLeft(100);
    
    // -- Title and version label --
    title_label.setBounds(title_rect);
    title_label.setJustificationType(Justification::topLeft);
    title_label.setFont(15.0f);
    title_label.setColour(Label::ColourIds::textColourId, Colour(150, 150, 150));

    version_label.setBounds(version_rect);
    version_label.setJustificationType(Justification::topRight);
    version_label.setFont(15.0f);
    version_label.setColour(Label::ColourIds::textColourId, Colour(150, 150, 150));

    // -- Input control --
    pre_gain_label.setBounds(pre_gain_rect.removeFromTop(15));
    pre_gain_label.setJustificationType(Justification::centred);
    pre_gain_slider.setBounds(pre_gain_rect);
    pre_gain_slider.setRange(-20, 20, 1);
    
    // -- Offset control ---
    offset_label.setBounds(offset_rect.removeFromTop(15));
    offset_label.setJustificationType(Justification::centred);
    offset_slider.setBounds(offset_rect);
    offset_slider.setRange(-0.1, 0.1, 0.001);

    // -- Hard/Soft control ---
    hard_soft_switch_rect.removeFromTop(10);
    hard_soft_switch_rect.removeFromBottom(10);
    hard_label.setBounds(hard_soft_switch_rect.removeFromTop(20));
    hard_label.setJustificationType(Justification::centredBottom);
    soft_label.setBounds(hard_soft_switch_rect.removeFromBottom(20));
    soft_label.setJustificationType(Justification::centredTop);
    hard_soft_switch.setBounds(hard_soft_switch_rect);
    hard_soft_switch.setLookAndFeel(&toggle_button_lnf);

    // -- Output control --
    post_gain_label.setBounds(post_gain_rect.removeFromTop(15));
    post_gain_label.setJustificationType(Justification::centred);
    post_gain_slider.setBounds(post_gain_rect);
    post_gain_slider.setRange(-20, 20, 1);
    
    addAndMakeVisible(title_label);
    addAndMakeVisible(version_label);
    addAndMakeVisible(pre_gain_label);
    addAndMakeVisible(post_gain_label);
    addAndMakeVisible(offset_label);
    addAndMakeVisible(hard_label);
    addAndMakeVisible(soft_label);

    addAndMakeVisible(pre_gain_slider);
    addAndMakeVisible(post_gain_slider);
    addAndMakeVisible(offset_slider);

    addAndMakeVisible(hard_soft_switch);
}

FClipperAudioProcessorEditor::~FClipperAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
    hard_soft_switch.setLookAndFeel(nullptr);
}

//==============================================================================

void FClipperAudioProcessorEditor::paint (juce::Graphics& g)
{
    //Image background_img = ImageCache::getFromFile(background_path);
    Image background_img = ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    g.drawImage(background_img, 
        0, 0,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        0, 0,
        380, 180
    );
}

void FClipperAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
