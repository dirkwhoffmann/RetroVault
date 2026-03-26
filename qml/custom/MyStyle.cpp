// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include <QGuiApplication>
#include <QStyleHints>
#include "MyStyle.h"

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
        darkMode = hints->colorScheme() == Qt::ColorScheme::Dark;
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
    return darkMode ?  winColor.lighter(140) : winColor.darker(140);
}

QColor
MyStyle::backgroundDimColor() const
{
    const QColor winColor = windowColor().darker();
    return QColor::fromRgb(winColor.red(), winColor.green(), winColor.blue(), 100);
}

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
