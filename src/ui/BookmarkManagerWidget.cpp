#include "ktbrowser/ui/BookmarkManagerWidget.h"
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>

namespace ktbrowser {

BookmarkManagerWidget::BookmarkManagerWidget(QWidget* parent)
    : QDialog(parent) {
    setWindowTitle("Bookmark Manager");
    setMinimumSize(600, 420);
    setupUi();
    refreshBookmarks();
}

void BookmarkManagerWidget::setupUi() {
    auto* mainLayout = new QVBoxLayout(this);

    // Toolbar search & buttons
    auto* topLayout = new QHBoxLayout();
    m_searchEdit = new QLineEdit(this);
    m_searchEdit->setPlaceholderText("Search bookmarks...");
    topLayout->addWidget(m_searchEdit);

    auto* addFolderBtn = new QPushButton("New Folder", this);
    auto* addBookmarkBtn = new QPushButton("Add Bookmark", this);
    auto* editBtn = new QPushButton("Edit", this);
    auto* deleteBtn = new QPushButton("Delete", this);

    topLayout->addWidget(addFolderBtn);
    topLayout->addWidget(addBookmarkBtn);
    topLayout->addWidget(editBtn);
    topLayout->addWidget(deleteBtn);

    mainLayout->addLayout(topLayout);

    // Tree View
    m_treeWidget = new QTreeWidget(this);
    m_treeWidget->setHeaderLabels({"Title / Name", "URL", "ID"});
    m_treeWidget->setColumnWidth(0, 260);
    m_treeWidget->setColumnWidth(1, 260);
    m_treeWidget->hideColumn(2);
    mainLayout->addWidget(m_treeWidget);

    connect(m_searchEdit, &QLineEdit::textChanged, this, [this](const QString& text) {
        if (text.isEmpty()) {
            refreshBookmarks();
        } else {
            m_treeWidget->clear();
            auto results = m_repo.searchBookmarks(text);
            for (const auto& bm : results) {
                auto* item = new QTreeWidgetItem(m_treeWidget);
                item->setText(0, bm.title);
                item->setText(1, bm.url);
                item->setText(2, QString::number(bm.id));
            }
        }
    });

    connect(addFolderBtn, &QPushButton::clicked, this, &BookmarkManagerWidget::addFolderDialog);
    connect(addBookmarkBtn, &QPushButton::clicked, this, &BookmarkManagerWidget::addBookmarkDialog);
    connect(editBtn, &QPushButton::clicked, this, &BookmarkManagerWidget::editSelected);
    connect(deleteBtn, &QPushButton::clicked, this, &BookmarkManagerWidget::deleteSelected);

    connect(m_treeWidget, &QTreeWidget::itemDoubleClicked, this, [this](QTreeWidgetItem* item, int column) {
        Q_UNUSED(column);
        QString url = item->text(1);
        if (!url.isEmpty()) {
            emit openUrlRequested(url);
            accept();
        }
    });
}

void BookmarkManagerWidget::refreshBookmarks() {
    m_treeWidget->clear();

    // Top level folders
    auto folders = m_repo.getFolders(0);
    for (const auto& f : folders) {
        auto* folderItem = new QTreeWidgetItem(m_treeWidget);
        folderItem->setText(0, "[Folder] " + f.name);
        folderItem->setText(2, QString::number(f.id));

        auto bms = m_repo.getBookmarks(f.id);
        for (const auto& bm : bms) {
            auto* childItem = new QTreeWidgetItem(folderItem);
            childItem->setText(0, bm.title);
            childItem->setText(1, bm.url);
            childItem->setText(2, QString::number(bm.id));
        }
    }

    // Root bookmarks
    auto rootBms = m_repo.getBookmarks(0);
    for (const auto& bm : rootBms) {
        auto* item = new QTreeWidgetItem(m_treeWidget);
        item->setText(0, bm.title);
        item->setText(1, bm.url);
        item->setText(2, QString::number(bm.id));
    }

    m_treeWidget->expandAll();
}

void BookmarkManagerWidget::addFolderDialog() {
    bool ok;
    QString name = QInputDialog::getText(this, "New Folder", "Folder Name:", QLineEdit::Normal, "", &ok);
    if (ok && !name.isEmpty()) {
        m_repo.addFolder(name, 0);
        refreshBookmarks();
    }
}

void BookmarkManagerWidget::addBookmarkDialog() {
    bool okTitle, okUrl;
    QString title = QInputDialog::getText(this, "Add Bookmark", "Title:", QLineEdit::Normal, "", &okTitle);
    if (!okTitle || title.isEmpty()) return;

    QString url = QInputDialog::getText(this, "Add Bookmark", "URL:", QLineEdit::Normal, "https://", &okUrl);
    if (okUrl && !url.isEmpty()) {
        m_repo.addBookmark(title, url, 0);
        refreshBookmarks();
    }
}

void BookmarkManagerWidget::editSelected() {
    auto* item = m_treeWidget->currentItem();
    if (!item) return;

    int64_t id = item->text(2).toLongLong();
    QString oldTitle = item->text(0);
    QString oldUrl = item->text(1);

    bool ok;
    QString newTitle = QInputDialog::getText(this, "Edit Bookmark", "Title:", QLineEdit::Normal, oldTitle, &ok);
    if (ok && !newTitle.isEmpty()) {
        if (!oldUrl.isEmpty()) {
            QString newUrl = QInputDialog::getText(this, "Edit Bookmark", "URL:", QLineEdit::Normal, oldUrl, &ok);
            if (ok && !newUrl.isEmpty()) {
                m_repo.updateBookmark(id, newTitle, newUrl, 0);
            }
        }
        refreshBookmarks();
    }
}

void BookmarkManagerWidget::deleteSelected() {
    auto* item = m_treeWidget->currentItem();
    if (!item) return;

    int64_t id = item->text(2).toLongLong();
    if (item->text(0).startsWith("[Folder] ")) {
        m_repo.deleteFolder(id);
    } else {
        m_repo.deleteBookmark(id);
    }
    refreshBookmarks();
}

} // namespace ktbrowser
