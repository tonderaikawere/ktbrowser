#include "codebrowser/ui/DownloadsWidget.h"
#include "codebrowser/downloads/DownloadManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>

namespace codebrowser {

DownloadsWidget::DownloadsWidget(QWidget* parent)
    : QDialog(parent) {
    setWindowTitle("CodeBrowser Download Manager");
    resize(600, 400);

    setupUi();
    refreshDownloads();

    connect(&DownloadManager::instance(), &DownloadManager::downloadStarted, this, &DownloadsWidget::refreshDownloads);
    connect(&DownloadManager::instance(), &DownloadManager::downloadUpdated, this, &DownloadsWidget::refreshDownloads);
    connect(&DownloadManager::instance(), &DownloadManager::downloadFinished, this, &DownloadsWidget::refreshDownloads);
}

void DownloadsWidget::setupUi() {
    auto* mainLayout = new QVBoxLayout(this);
    
    auto* header = new QLabel("<h2>Active & Completed Downloads</h2>", this);
    mainLayout->addWidget(header);

    m_listWidget = new QListWidget(this);
    mainLayout->addWidget(m_listWidget);

    auto* btnLayout = new QHBoxLayout();
    auto* closeBtn = new QPushButton("Close", this);
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);

    btnLayout->addStretch();
    btnLayout->addWidget(closeBtn);
    mainLayout->addLayout(btnLayout);
}

void DownloadsWidget::refreshDownloads() {
    m_listWidget->clear();

    auto downloads = DownloadManager::instance().activeDownloads();
    for (const auto& item : downloads) {
        double progressPct = (item.totalBytes > 0) ? (double(item.receivedBytes) / item.totalBytes) * 100.0 : 0.0;
        QString statusText = (item.state == "Completed") ? "Completed" : (item.state == "Cancelled") ? "Cancelled" : QString("%1%").arg(progressPct, 0, 'f', 1);

        auto* listItem = new QListWidgetItem(m_listWidget);
        listItem->setText(QString("%1\nURL: %2 | Status: %3 (%4 / %5 bytes)")
            .arg(item.fileName)
            .arg(item.url.toString())
            .arg(statusText)
            .arg(item.receivedBytes)
            .arg(item.totalBytes));
    }
}

} // namespace codebrowser
