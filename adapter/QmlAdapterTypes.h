#pragma once

#include <QObject>
#include <QString>
#include <QVariantList>

class DeviceInfo : public QObject {

    Q_OBJECT

public:

    enum Format { ADF, ADZ, EADF, DMS, HDF, HDZ, IMG, ST, D64, UNKNOWN };

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
    Q_PROPERTY(int format READ format CONSTANT) // Use an Enum

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