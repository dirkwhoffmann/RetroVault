#include "BaseScanner.h"
#include <qtconcurrentrun.h>

BaseScanner::BaseScanner(QObject* parent) : QObject(parent)
{
    /*
    connect(&m_watcher, &QFutureWatcher<QByteArray>::finished, this, [this]
    {
        m_cachedImage = m_watcher.result();
        emit isProcessingChanged();
        update();
    });
    */
    connect(&m_watcher, &QFutureWatcher<QByteArray>::finished, this, &BaseScanner::onScanFinished);
}

void
BaseScanner::runTask(std::function<QByteArray()> task)
{
    if (m_watcher.isRunning()) m_watcher.cancel();
    emit isScanningChanged();

    // Wrap the original task in a timing wrapper
    auto timedTask = [task]() {
        auto start = std::chrono::steady_clock::now();

        printf("heavy task started\n");
        // Execute the actual heavy work
        QByteArray result = task();

        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        // If it took less than 2000ms, wait the difference
        if (elapsed.count() < 2000) {
            std::this_thread::sleep_for(std::chrono::milliseconds(2000 - elapsed.count()));
        }
        printf("heavy task finished\n");

        return result;
    };

    m_watcher.setFuture(QtConcurrent::run(timedTask));
    emit isScanningChanged();
}

void
BaseScanner::onScanFinished()
{
    m_buffer = m_watcher.result();
    emit bufferChanged();
    emit isScanningChanged();
}