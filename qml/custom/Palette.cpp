// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include "Palette.h"
#include <QGuiApplication>
#include <QStyleHints>

Palette::Palette(QObject *parent) : QQuickAttachedPropertyPropagator(parent)
{
    auto *hints = QGuiApplication::styleHints();

    darkMode = hints->colorScheme() == Qt::ColorScheme::Dark;
    m_theme  = AppDefault;

    initialize();
}

Palette *
Palette::qmlAttachedProperties(QObject *object)
{
    return new Palette(object);
}

void
Palette::setDarkMode(bool value)
{
    m_explicitDarkMode = true;

    if (darkMode != value) {

        darkMode = value;
        propagateDarkMode();
        themeChange();
    }
}

void
Palette::inheritDarkMode(bool value)
{
    if (!m_explicitDarkMode) {

        darkMode = value;
        propagateDarkMode();
        themeChange();
    }
}
void
Palette::propagateDarkMode()
{
    const auto styles = attachedChildren();

    for (QQuickAttachedPropertyPropagator *child : styles) {

        if (auto *palette = qobject_cast<Palette *>(child)) {
            palette->inheritDarkMode(darkMode);
        }
    }
}

void
Palette::resetDarkMode()
{
    if (m_explicitDarkMode) {

        m_explicitDarkMode = false;
        Palette *palette   = qobject_cast<Palette *>(attachedParent());
        inheritDarkMode(palette ? palette->getDarkMode() : false);
    }
}


void
Palette::setTheme(Theme theme)
{
    m_explicitTheme = true;

    if (m_theme != theme) {

        m_theme = theme;
        propagateTheme();
        themeChange();
    }
}

void
Palette::inheritTheme(Theme theme)
{
    if (!m_explicitTheme) {

        m_theme = theme;
        propagateTheme();
        themeChange();
    }
}

void
Palette::propagateTheme()
{
    const auto styles = attachedChildren();

    for (QQuickAttachedPropertyPropagator *child : styles) {

        if (auto *palette = qobject_cast<Palette *>(child)) {
            palette->inheritTheme(m_theme);
        }
    }
}

void
Palette::resetTheme()
{
    if (m_explicitTheme) {

        m_explicitTheme  = false;
        Palette *palette = qobject_cast<Palette *>(attachedParent());
        inheritTheme(palette ? palette->theme() : Palette::AppDefault);
    }
}

void
Palette::themeChange()
{
    emit themeChanged();

    // Emit other change signals for theme-dependent properties
    // ...
}

void
Palette::attachedParentChange(QQuickAttachedPropertyPropagator *newParent,
                              QQuickAttachedPropertyPropagator *oldParent)
{
    Q_UNUSED(oldParent);
    Palette *attachedParentStyle = qobject_cast<Palette *>(newParent);

    if (attachedParentStyle) {

        inheritTheme(attachedParentStyle->theme());
        // Do any other inheriting here...
    }
}

QColor
Palette::getColor(Color c) const
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
Palette::getDefaultColor(Color c) const
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
            return darkMode ? QColor("#262424") : QColor("#ececec");
        case Color::WindowText:
            return darkMode ? QColor("#ffffff") : QColor("#000000");

        // Additions
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
        case Color::Ok:
            return darkMode ? QColor("#66ff66") : QColor("#00aa00");
        case Color::Warning:
            return darkMode ? QColor("#ffff66") : QColor("#cccc00");
        case Color::Error:
            return darkMode ? QColor("#ff6666") : QColor("#ff0000");

        case Color::PrimaryBg:
            return darkMode ? QColor("#262424") : QColor("#ececec");
        case Color::SecondaryBg:
            return darkMode ? QColor("#2c2c2e") : QColor("#e2e2e2");
        case Color::TertiaryBg:
            return darkMode ? QColor("#3C3A3B") : QColor("#d2d2d2");
        case Color::TableBg:
            return darkMode ? QColor("#111111") : QColor("#ffffff");
        case Color::SidebarBg:
            return darkMode ? QColor("#2f2d2d") : QColor("#e2e2e2");
        case Color::PositiveBg:
            return darkMode ? QColor("#006137") : QColor("#e3fae9");
        case Color::NegativeBg:
            return darkMode ? QColor("#941100") : QColor("#e7d5d6");

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
        case Color::Border:
            return darkMode ? QColor("#6C6B6B") : QColor("#c8c8c8");
    }

    return QColor("#ff0000");
}

QColor
Palette::getDebugColor(Color c) const
{
    return getDefaultColor(c);
}