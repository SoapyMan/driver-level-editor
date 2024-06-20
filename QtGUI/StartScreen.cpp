#include "StartScreen.hpp"

StartScreen::StartScreen(QWidget* parent) : QWidget(parent)
{
    QPalette pal = palette();
    pal.setBrush(QPalette::Base, QColor(255,255,255));
    setAutoFillBackground(true);
    setPalette(pal);
};
