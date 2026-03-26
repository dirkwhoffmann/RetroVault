/// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#pragma once

#include <QColor>
#include <QQmlEngine>
#include <QQuickAttachedPropertyPropagator>

class MyStyle : public QQuickAttachedPropertyPropagator {

  public:

    enum Theme { AppDefault, AppDebug };

    enum class Color {

        // Base
        Accent,
        AlternateBase,
        Base,
        Button,
        ButtonText,
        Dark,
        Highlight,
        HighlightedText,
        Light,
        Mid,
        Midlight,
        PlaceholderText,
        Shadow,
        Text,
        Window,
        WindowText,

        // Additions
        Ok,
        Warning,
        Error,

        // Derived
        Primary,
        Secondary,
        Tertiary,
        PrimaryBg,
        SecondaryBg,
        TertiaryBg,
        Separator,
        AccentHover,
        AccentPressed,
        Border
    };

  private:

    Q_OBJECT

    // Setting MyStyle.theme to undefined calls the reset function
    Q_PROPERTY(Theme theme READ theme WRITE setTheme RESET resetTheme NOTIFY themeChanged FINAL)

    // As the values of these properties only depend on the theme, they can all use the theme
    // property's change signal.

    Q_PROPERTY(QColor accentColor READ accentColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor alternateBaseColor READ alternateBaseColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor baseColor READ baseColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor buttonColor READ buttonColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor buttonTextColor READ buttonTextColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor darkColor READ darkColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor highlightColor READ highlightColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor highlightedTextColor READ highlightedTextColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor lightColor READ lightColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor midColor READ midColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor midlightColor READ midlightColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor placeholderTextColor READ placeholderTextColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor shadowColor READ shadowColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor textColor READ textColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor windowColor READ windowColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor windowTextColor READ windowTextColor NOTIFY themeChanged FINAL)

    // Additions
    Q_PROPERTY(QColor okColor READ okColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor errorColor READ errorColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor warningColor READ warningColor NOTIFY themeChanged FINAL)

    // Derived
    Q_PROPERTY(QColor primaryColor READ primaryColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor secondaryColor READ secondaryColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor tertiaryColor READ tertiaryColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor primaryBgColor READ primaryBgColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor secondaryBgColor READ secondaryBgColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor tertiaryBgColor READ tertiaryBgColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor separatorColor READ separatorColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor accentHoverColor READ accentHoverColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor accentPressedColor READ accentPressedColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor bordeColor READ borderColor NOTIFY themeChanged FINAL)

    QML_ELEMENT
    QML_ATTACHED(MyStyle)
    QML_UNCREATABLE("")
    QML_ADDED_IN_VERSION(1, 0)

    static bool darkMode;

    bool m_explicitTheme = false;
    Theme m_theme        = AppDefault;

    Q_ENUM(Theme)

    explicit MyStyle(QObject *parent = nullptr);

    static MyStyle *qmlAttachedProperties(QObject *object);

    Theme theme() const;
    void setTheme(Theme theme);
    void inheritTheme(Theme theme);
    void propagateTheme();
    void resetTheme();
    void themeChange();

    QColor accentColor() const { return getColor(Color::Accent); }
    QColor alternateBaseColor() const { return getColor(Color::AlternateBase); }
    QColor baseColor() const { return getColor(Color::Base); }
    QColor buttonColor() const { return getColor(Color::Button); }
    QColor buttonTextColor() const { return getColor(Color::ButtonText); }
    QColor darkColor() const { return getColor(Color::Dark); }
    QColor highlightColor() const { return getColor(Color::Highlight); }
    QColor highlightedTextColor() const { return getColor(Color::HighlightedText); }
    QColor lightColor() const { return getColor(Color::Light); }
    QColor midColor() const { return getColor(Color::Mid); }
    QColor midlightColor() const { return getColor(Color::Midlight); }
    QColor placeholderTextColor() const { return getColor(Color::PlaceholderText); }
    QColor shadowColor() const { return getColor(Color::Shadow); }
    QColor textColor() const { return getColor(Color::Text); }
    QColor windowColor() const { return getColor(Color::Window); }
    QColor windowTextColor() const { return getColor(Color::WindowText); }

    // Additions
    QColor okColor() const { return getColor(Color::Ok); }
    QColor errorColor() const { return getColor(Color::Error); }
    QColor warningColor() const { return getColor(Color::Warning); }

    QColor primaryColor() const { return getColor(Color::Primary); }
    QColor secondaryColor() const { return getColor(Color::Secondary); }
    QColor tertiaryColor() const { return getColor(Color::Tertiary); }
    QColor primaryBgColor() const { return getColor(Color::PrimaryBg); }
    QColor secondaryBgColor() const { return getColor(Color::SecondaryBg); }
    QColor tertiaryBgColor() const { return getColor(Color::TertiaryBg); }
    QColor separatorColor() const { return getColor(Color::Separator); }
    QColor accentHoverColor() const { return getColor(Color::AccentHover); }
    QColor accentPressedColor() const { return getColor(Color::AccentPressed); }
    QColor borderColor() const { return getColor(Color::Border); }

  Q_SIGNALS:
    void themeChanged();

  protected:

    void attachedParentChange(QQuickAttachedPropertyPropagator *newParent,
                              QQuickAttachedPropertyPropagator *oldParent) override;

  private:

    QColor getColor(Color c) const;
    QColor getDefaultColor(Color c) const;
    QColor getDebugColor(Color c) const;
};
