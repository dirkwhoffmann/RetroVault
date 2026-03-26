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

  private:

    Q_OBJECT

    // Provide a RESET function in order to allow an item to set MyStyle.theme to undefined
    // in order to use its parent's (or global) theme after one was explicitly set on it.
    Q_PROPERTY(Theme theme READ theme WRITE setTheme RESET resetTheme NOTIFY themeChanged FINAL)

    // As the values of these properties only depend on the theme, they can all use the theme
    // property's change signal.
    Q_PROPERTY(QColor windowColor READ windowColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor windowTextColor READ windowTextColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor buttonColor READ buttonColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor buttonTextColor READ buttonTextColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor toolBarColor READ toolBarColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor popupColor READ popupColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor popupBorderColor READ popupBorderColor NOTIFY themeChanged FINAL)
    Q_PROPERTY(QColor backgroundDimColor READ backgroundDimColor NOTIFY themeChanged FINAL)

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

    QColor windowColor() const;
    QColor windowTextColor() const;
    QColor buttonColor() const;
    QColor buttonTextColor() const;
    QColor toolBarColor() const;
    QColor popupColor() const;
    QColor popupBorderColor() const;
    QColor backgroundDimColor() const;

  Q_SIGNALS:
    void themeChanged();

  protected:

    void attachedParentChange(QQuickAttachedPropertyPropagator *newParent,
                              QQuickAttachedPropertyPropagator *oldParent) override;
};
