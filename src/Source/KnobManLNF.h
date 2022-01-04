/**
 * @file KnobManLNF.h
 * @author Filipe Chagas (github.com/FilipeChagasDev)
 * @brief 
 * @version 0.1
 * @date 2022-01-03
 * 
 */

#include <JuceHeader.h>

class KnobManSliderLNF : public LookAndFeel_V4
{
public:
    KnobManSliderLNF(Image _img, int _frameWidth, int _frameHeight);

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;

private:
    Image img;
    int frameWidth;
    int frameHeight;
};

class KnobManToggleButtonLNF : public LookAndFeel_V4
{
public:
    KnobManToggleButtonLNF(Image _img, int _width, int _height, int _frameWidth, int _frameHeight);

    void drawToggleButton(Graphics& g, ToggleButton& tg,
        bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

private:
    Image img;
    int frameWidth;
    int frameHeight;
    int width;
    int height;
};