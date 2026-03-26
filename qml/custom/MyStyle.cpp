// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include "MyStyle.h"
#include <QGuiApplication>
#include <QStyleHints>

// Default theme (if no theme is inherited or explicitely set)
static MyStyle::Theme globalTheme = MyStyle::AppDefault;

bool MyStyle::darkMode = false;

MyStyle::MyStyle(QObject *parent) : QQuickAttachedPropertyPropagator(parent), m_theme(globalTheme)
{
    static bool inited = false;

    if (!inited) {
        inited = true;

        // 1. Get the system default
        auto *hints = QGuiApplication::styleHints();
        darkMode    = hints->colorScheme() == Qt::ColorScheme::Dark;
        printf("Dark mode = %d\n", darkMode);

        connect(hints, &QStyleHints::colorSchemeChanged, this, [this](Qt::ColorScheme scheme) {
            darkMode = scheme == Qt::ColorScheme::Dark;
            printf("colorSchemeChanged %d\n", darkMode);
            this->themeChange();
        });
    }

    // A static function could be called here that reads globalTheme from a
    // settings file once at startup. That value would override the global
    // value. This is similar to what the Imagine and Material styles do, for
    // example.

    initialize();
}

MyStyle *
MyStyle::qmlAttachedProperties(QObject *object)
{
    return new MyStyle(object);
}

MyStyle::Theme
MyStyle::theme() const
{
    return m_theme;
}

void
MyStyle::setTheme(Theme theme)
{
    printf("setTheme %d\n", theme);
    m_explicitTheme = true;

    if (m_theme != theme) {

        m_theme = theme;
        propagateTheme();
        themeChange();
    }
}

void
MyStyle::inheritTheme(Theme theme)
{
    if (!m_explicitTheme && m_theme != theme) {

        m_theme = theme;
        propagateTheme();
        themeChange();
    }
}

void
MyStyle::propagateTheme()
{
    const auto styles = attachedChildren();

    for (QQuickAttachedPropertyPropagator *child : styles) {

        if (auto *myStyle = qobject_cast<MyStyle *>(child)) {
            myStyle->inheritTheme(m_theme);
        }
    }
}

void
MyStyle::resetTheme()
{
    if (m_explicitTheme) {

        m_explicitTheme  = false;
        MyStyle *myStyle = qobject_cast<MyStyle *>(attachedParent());
        inheritTheme(myStyle ? myStyle->theme() : globalTheme);
    }
}

void
MyStyle::themeChange()
{
    emit themeChanged();

    // Emit other change signals for theme-dependent properties
    // ...
}

/*
QColor
MyStyle::windowColor() const
{
    if (m_theme == AppDebug) return QColor::fromRgb(0xFF0000);
    return darkMode ? QColor::fromRgb(0x303030) : QColor::fromRgb(0xf0f0f0);
}

QColor
MyStyle::windowTextColor() const
{
    return darkMode ? QColor::fromRgb(0xe0e0e0) : QColor::fromRgb(0x5c5c5c);
}

QColor
MyStyle::buttonColor() const
{
    return darkMode ? QColor::fromRgb(0x74bbff) : QColor::fromRgb(0xc2e1ff);
}

QColor
MyStyle::buttonTextColor() const
{
    return darkMode ? QColor::fromRgb(0xffffff) : QColor::fromRgb(0x5c5c5c);
}

QColor
MyStyle::toolBarColor() const
{
    return darkMode ? QColor::fromRgb(0x0066cc) : QColor::fromRgb(0x4da6ff);
}

QColor
MyStyle::popupColor() const
{
    return windowColor().lighter(120);
}

QColor
MyStyle::popupBorderColor() const
{
    const QColor winColor = windowColor();
    return darkMode ? winColor.lighter(140) : winColor.darker(140);
}

QColor
MyStyle::backgroundDimColor() const
{
    const QColor winColor = windowColor().darker();
    return QColor::fromRgb(winColor.red(), winColor.green(), winColor.blue(), 100);
}
*/

void
MyStyle::attachedParentChange(QQuickAttachedPropertyPropagator *newParent,
                              QQuickAttachedPropertyPropagator *oldParent)
{
    Q_UNUSED(oldParent);
    MyStyle *attachedParentStyle = qobject_cast<MyStyle *>(newParent);

    if (attachedParentStyle) {

        inheritTheme(attachedParentStyle->theme());
        // Do any other inheriting here...
    }
}

QColor
MyStyle::getColor(Color c) const
{
    switch (m_theme) {

        case AppDefault:
            return getDefaultColor(c);
        case AppDebug:
            return getDebugColor(c);
        default:
            return getDefaultColor(c);
    }
}

QColor
MyStyle::getDefaultColor(Color c) const
{
    switch (c) {
        case Color::Accent:
            return darkMode ? QColor("#0a84ff") : QColor("#0a84ff");
        case Color::AlternateBase:
            return darkMode ? QColor("#2c2c2e") : QColor("#f2f2f7");
        case Color::Base:
            return darkMode ? QColor("#1c1c1e") : QColor("#ffffff");
        case Color::Button:
            return darkMode ? QColor("#2c2c2e") : QColor("#f2f2f7");
        case Color::ButtonText:
            return darkMode ? QColor("#ffffff") : QColor("#000000");
        case Color::Dark:
            return darkMode ? QColor("#3a3a3c") : QColor("#d1d1d6");
        case Color::Highlight:
            return darkMode ? QColor("#0a84ff") : QColor("#0a84ff");
        case Color::HighlightedText:
            return darkMode ? QColor("#ffffff") : QColor("#ffffff");
        case Color::Light:
            return darkMode ? QColor("#3a3a3c") : QColor("#ffffff");
        case Color::Mid:
            return darkMode ? QColor("#48484a") : QColor("#c7c7cc");
        case Color::Midlight:
            return darkMode ? QColor("#636366") : QColor("#e5e5ea");
        case Color::PlaceholderText:
            return darkMode ? QColor("#8e8e93") : QColor("#8e8e93");
        case Color::Shadow:
            return darkMode ? QColor("#00000066") : QColor("#00000022");
        case Color::Text:
            return darkMode ? QColor("#ffffff") : QColor("#000000");
        case Color::Window:
            return darkMode ? QColor("#2c2c2e") : QColor("#f5f5f7");
        case Color::WindowText:
            return darkMode ? QColor("#ffffff") : QColor("#000000");

        // Extensions
        case Color::Ok:
            return darkMode ? QColor("#66ff66") : QColor("#00aa00");
        case Color::Warning:
            return darkMode ? QColor("#ffff66") : QColor("#cccc00");
        case Color::Error:
            return darkMode ? QColor("#ff6666") : QColor("#ff0000");

            // Derived colors
        case Color::Primary: {
            auto base = getColor(Color::WindowText);
            return QColor(base.red(), base.green(), base.blue(), 255);
        }
        case Color::Secondary: {
            auto base = getColor(Color::WindowText);
            return QColor(base.red(), base.green(), base.blue(), 192);
        }
        case Color::Tertiary: {
            auto base = getColor(Color::WindowText);
            return QColor(base.red(), base.green(), base.blue(), 128);
        }
        case Color::PrimaryBg: {
            auto base = getColor(Color::WindowText);
            return darkMode ? base.lighter(125) : base.darker(125);
        }
        case Color::SecondaryBg: {
            auto base = getColor(Color::WindowText);
            return darkMode ? base.lighter(150) : base.darker(150);
        }
        case Color::TertiaryBg: {
            auto base = getColor(Color::WindowText);
            return darkMode ? base.lighter(200) : base.darker(200);
        }
        case Color::Separator:
            return darkMode ? QColor("#3c3c4355") : QColor("#3c3c4349");

        case Color::AccentHover: {
            auto base = getColor(Color::Accent);
            return darkMode ? base.lighter(200) : base.lighter(200);
        }
        case Color::AccentPressed: {
            auto base = getColor(Color::Accent);
            return darkMode ? base.darker(200) : base.darker(200);
        }
        case Color::Border: {
            auto base = getColor(Color::WindowText);
            return QColor(base.red(), base.green(), base.blue(), 48);
        }
    }

    return QColor("#ff0000");
}

QColor
MyStyle::getDebugColor(Color c) const
{
    return getDefaultColor(c);
}