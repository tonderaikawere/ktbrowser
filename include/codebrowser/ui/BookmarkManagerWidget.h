#pragma once

#include "codebrowser/database/BookmarkRepository.h"
#include <QDialog>
#include <QTreeWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

namespace codebrowser {

class BookmarkManagerWidget : public QDialog {
    Q_OBJECT
public:
    explicit BookmarkManagerWidget(QWidget* parent = nullptr);

    void refreshBookmarks();

signals:
    void openUrlRequested(const QString& url);

private:
    void setupUi();
    void addFolderDialog();
    void addBookmarkDialog();
    void editSelected();
    void deleteSelected();

    QTreeWidget* m_treeWidget{nullptr};
    QLineEdit* m_searchEdit{nullptr};
    BookmarkRepository m_repo;
};

} // namespace codebrowser
