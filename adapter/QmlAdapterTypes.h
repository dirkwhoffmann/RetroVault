#pragma once

#include <qqml.h>
#include <QObject>
#include <QString>
#include <QAbstractTableModel>
#include <QVariantList>

#include "ImageTypes.h"


class DeviceInfo : public QObject {

    Q_OBJECT

public:

    enum Format
    {
        UNKNOWN = static_cast<int>(retro::vault::ImageFormat::UNKNOWN),
        ADF = static_cast<int>(retro::vault::ImageFormat::ADF),
        ADZ = static_cast<int>(retro::vault::ImageFormat::ADZ),
        EADF = static_cast<int>(retro::vault::ImageFormat::EADF),
        HDF = static_cast<int>(retro::vault::ImageFormat::HDF),
        HDZ = static_cast<int>(retro::vault::ImageFormat::HDZ),
        IMG = static_cast<int>(retro::vault::ImageFormat::IMG),
        ST = static_cast<int>(retro::vault::ImageFormat::ST),
        DMS = static_cast<int>(retro::vault::ImageFormat::DMS),
        EXE = static_cast<int>(retro::vault::ImageFormat::EXE),
        D64 = static_cast<int>(retro::vault::ImageFormat::D64)
    };

    // Members
    QString m_name;
    int m_numBlocks = 0;
    int m_bsize = 512;
    int m_numCyls = 0;
    int m_numHeads = 0;
    Format m_format = UNKNOWN;

    // QML Properties
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(int numBlocks READ numBlocks CONSTANT)
    Q_PROPERTY(int bsize READ bsize CONSTANT)
    Q_PROPERTY(int numCyls READ numCyls CONSTANT)
    Q_PROPERTY(int numHeads READ numHeads CONSTANT)
    Q_PROPERTY(int format READ format CONSTANT)

    // Computed QML Properties
    Q_PROPERTY(long long totalBytes READ totalBytes CONSTANT)

    Q_ENUM(Format)

public:

    explicit DeviceInfo(QObject *parent = nullptr) : QObject(parent) {}

    // Getters
    QString name() const { return m_name; }
    int numBlocks() const { return m_numBlocks; }
    int bsize() const { return m_bsize; }
    int numCyls() const { return m_numCyls; }
    int numHeads() const { return m_numHeads; }
    int format() const { return m_format; }
    long long totalBytes() const { return (long long)m_numBlocks * m_bsize; }
};


