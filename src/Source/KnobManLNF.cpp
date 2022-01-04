/**
 * @file KnobManLNF.cpp
 * @author Filipe Chagas (github.com/FilipeChagasDev)
 * @brief 
 * @version 0.1
 * @date 2022-01-03
 * 
 * based on: https://github.com/remberg/juceCustomSliderSample/blob/master/Source/myLookAndFeel.cpp
 * 
 */

#include "KnobManLNF.h"
#include <assert.h>
#include <iostream>

// === Slider ===

KnobManSliderLNF::KnobManSliderLNF(Image _img, int _frameWidth, int _frameHeight)
{
    this->img = _img;
    this->frameWidth = _frameWidth;
    this->frameHeight = _frameHeight;
}

void KnobManSliderLNF::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    if (img.isValid())
    {
        const double rotation = (slider.getValue()
            - slider.getMinimum())
            / (slider.getMaximum()
                - slider.getMinimum());

        const int frames = img.getHeight() / frameHeight;
        const int frameId = (int)ceil(rotation * ((double)frames - 1.0));
        const float radius = jmin(width / 2.0f, height / 2.0f);
        const float centerX = x + width * 0.5f;
        const float centerY = y + height * 0.5f;
        const float rx = centerX - radius - 1.0f;
        const float ry = centerY - radius;

        g.drawImage(img,
            (int)rx, (int)ry, /*dest x & y*/
            2 * (int)radius, 2 * (int)radius, /*dest w & h*/
            0, frameId*frameHeight, /*source x & y*/
            frameWidth, frameHeight /*source w & h*/
            );
    }
    else
    {
        static const float textPpercent = 0.35f;
        Rectangle<float> text_bounds(1.0f + width * (1.0f - textPpercent) / 2.0f,
            0.5f * height, width * textPpercent, 0.5f * height);

        g.setColour(Colour(255,0,0));

        g.drawFittedText(String("No Image"), text_bounds.getSmallestIntegerContainer(),
            Justification::horizontallyCentred | Justification::centred, 1);
    }
}

// === Toggle Button ===

KnobManToggleButtonLNF::KnobManToggleButtonLNF(Image _img, int _width, int _height, int _frameWidth, int _frameHeight)
{
    this->img = _img;
    this->frameWidth = _frameWidth;
    this->frameHeight = _frameHeight;
    this->width = _width;
    this->height = _height;
}

void KnobManToggleButtonLNF::drawToggleButton(Graphics& g, ToggleButton& tg,
        bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    if (img.isValid())
    {
        const int frames = img.getHeight() / frameHeight;
        const int frameId = tg.getToggleState() ? 1 : 0;
        
        g.drawImage(img,
            0, 0, /*dest x & y*/
            width, height, /*dest w & h*/
            0, frameId*frameHeight, /*source x & y*/
            frameWidth, frameHeight /*source w & h*/
            );
    }
    else
    {
        static const float textPpercent = 0.35f;
        Rectangle<float> text_bounds(1.0f + width * (1.0f - textPpercent) / 2.0f,
            0.5f * height, width * textPpercent, 0.5f * height);

        g.setColour(Colour(255,0,0));

        g.drawFittedText(String("No Image"), text_bounds.getSmallestIntegerContainer(),
            Justification::horizontallyCentred | Justification::centred, 1);
    }
}