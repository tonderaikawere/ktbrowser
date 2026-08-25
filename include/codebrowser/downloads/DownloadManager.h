#pragma once

#include <QObject>
#include <QUrl>
#include <QString>
#include <QDateTime>
#include <QList>

#ifdef CODEBROWSER_HAS_WEBENGINE
#include <QWebEngineDownloadRequest>
#endif

namespace codebrowser {

struct DownloadItem {
    int id{0};
    QString fileName;
    QString fullPath;
    QUrl url;
    qint64 totalBytes{0};
    qint64 receivedBytes{0};
    QString state{"Downloading"}; // Downloading, Completed, Interrupted, Cancelled
    QDateTime startTime;
};

class DownloadManager : public QObject {
    Q_OBJECT
public:
    static DownloadManager& instance();

#ifdef CODEBROWSER_HAS_WEBENGINE
    void manageDownload(QWebEngineDownloadRequest* download);
#endif

    QList<DownloadItem> activeDownloads() const;

signals:
    void downloadStarted(const DownloadItem& item);
    void downloadUpdated(const DownloadItem& item);
    void downloadFinished(const DownloadItem& item);

private:
    DownloadManager() = default;
    ~DownloadManager() = default;

    QList<DownloadItem> m_downloads;
};

} // namespace codebrowser
