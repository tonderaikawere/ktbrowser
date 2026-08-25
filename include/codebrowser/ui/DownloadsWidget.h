#pragma once

#include "codebrowser/downloads/DownloadManager.h"
#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

namespace codebrowser {

class DownloadsWidget : public QDialog {
    Q_OBJECT
public:
    explicit DownloadsWidget(QWidget* parent = nullptr);

    void refreshDownloads();

private:
    void setupUi();

    QListWidget* m_listWidget{nullptr};
};

} // namespace codebrowser
