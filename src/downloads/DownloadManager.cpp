#include "codebrowser/downloads/DownloadManager.h"
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

namespace codebrowser {

DownloadManager& DownloadManager::instance() {
    static DownloadManager instance;
    return instance;
}

#ifdef CODEBROWSER_HAS_WEBENGINE
void DownloadManager::manageDownload(QWebEngineDownloadRequest* download) {
    if (!download) return;

    QString defaultDir = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    QString targetPath = QDir(defaultDir).filePath(download->downloadFileName());
    download->setDownloadDirectory(defaultDir);

    DownloadItem item;
    item.id = m_downloads.size() + 1;
    item.fileName = download->downloadFileName();
    item.fullPath = targetPath;
    item.url = download->url();
    item.totalBytes = download->totalBytes();
    item.receivedBytes = download->receivedBytes();
    item.startTime = QDateTime::currentDateTime();

    m_downloads.append(item);
    emit downloadStarted(item);

    connect(download, &QWebEngineDownloadRequest::receivedBytesChanged, this, [this, download, item]() mutable {
        item.receivedBytes = download->receivedBytes();
        item.totalBytes = download->totalBytes();
        emit downloadUpdated(item);
    });

    connect(download, &QWebEngineDownloadRequest::stateChanged, this, [this, download, item]() mutable {
        if (download->state() == QWebEngineDownloadRequest::DownloadCompleted) {
            item.state = "Completed";
            emit downloadFinished(item);
        } else if (download->state() == QWebEngineDownloadRequest::DownloadCancelled) {
            item.state = "Cancelled";
            emit downloadFinished(item);
        } else if (download->state() == QWebEngineDownloadRequest::DownloadInterrupted) {
            item.state = "Interrupted";
            emit downloadFinished(item);
        }
    });

    download->accept();
}
#endif

QList<DownloadItem> DownloadManager::activeDownloads() const {
    return m_downloads;
}

} // namespace codebrowser
