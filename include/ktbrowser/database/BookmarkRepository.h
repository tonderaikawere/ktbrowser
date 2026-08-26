#pragma once

#include <QString>
#include <QDateTime>
#include <QList>

namespace ktbrowser {

struct BookmarkFolder {
    int64_t id{0};
    QString name;
    int64_t parentId{0};
};

struct BookmarkItem {
    int64_t id{0};
    int64_t folderId{0};
    QString title;
    QString url;
    QDateTime createdAt;
};

class BookmarkRepository {
public:
    BookmarkRepository() = default;

    int64_t addFolder(const QString& name, int64_t parentId = 0);
    QList<BookmarkFolder> getFolders(int64_t parentId = 0);
    bool deleteFolder(int64_t folderId);

    int64_t addBookmark(const QString& title, const QString& url, int64_t folderId = 0);
    bool updateBookmark(int64_t id, const QString& title, const QString& url, int64_t folderId);
    bool deleteBookmark(int64_t id);
    bool isBookmarked(const QString& url);
    QList<BookmarkItem> getBookmarks(int64_t folderId = 0);
    QList<BookmarkItem> getAllBookmarks();
    QList<BookmarkItem> searchBookmarks(const QString& query);
};

} // namespace ktbrowser
