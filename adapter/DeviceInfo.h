#pragma once

#include <QObject>
#include <QString>
#include <QVariantList>

class DeviceInfo : public QObject {

    Q_OBJECT

    // Exposed to QML
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(int numBlocks READ numBlocks CONSTANT)
    Q_PROPERTY(int bsize READ bsize CONSTANT)
    Q_PROPERTY(int numCyls READ numCyls CONSTANT)
    Q_PROPERTY(int numHeads READ numHeads CONSTANT)
    Q_PROPERTY(int format READ format CONSTANT) // Use an Enum

    // Computed Properties (Helpers for QML)
    Q_PROPERTY(long long totalBytes READ totalBytes CONSTANT)

public:

    enum Format { ADF, ADZ, EADF, DMS, HDF, HDZ, IMG, ST, D64, UNKNOWN };
    Q_ENUM(Format)

    explicit DeviceInfo(QObject *parent = nullptr) : QObject(parent) {}

    // Getters
    QString name() const { return m_name; }
    int numBlocks() const { return m_numBlocks; }
    int bsize() const { return m_bsize; }
    int numCyls() const { return m_numCyls; }
    int numHeads() const { return m_numHeads; }
    int format() const { return m_format; }
    long long totalBytes() const { return (long long)m_numBlocks * m_bsize; }

    QString m_name;
    int m_numBlocks = 0;
    int m_bsize = 512;
    int m_numCyls = 0;
    int m_numHeads = 0;
    Format m_format = UNKNOWN;
};