#include "ktbrowser/database/BookmarkRepository.h"
#include "ktbrowser/database/Database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

namespace ktbrowser {

int64_t BookmarkRepository::addFolder(const QString& name, int64_t parentId) {
    QSqlDatabase& db = Database::instance().database();
    QSqlQuery query(db);
    query.prepare("INSERT INTO bookmark_folders (name, parent_id) VALUES (:name, :parent);");
    query.bindValue(":name", name);
    query.bindValue(":parent", parentId);
    if (query.exec()) {
        return query.lastInsertId().toLongLong();
    }
    return 0;
}

QList<BookmarkFolder> BookmarkRepository::getFolders(int64_t parentId) {
    QList<BookmarkFolder> folders;
    QSqlDatabase& db = Database::instance().database();
    QSqlQuery query(db);
    query.prepare("SELECT id, name, parent_id FROM bookmark_folders WHERE parent_id = :parent ORDER BY name ASC;");
    query.bindValue(":parent", parentId);
    if (query.exec()) {
        while (query.next()) {
            BookmarkFolder f;
            f.id = query.value(0).toLongLong();
            f.name = query.value(1).toString();
            f.parentId = query.value(2).toLongLong();
            folders.append(f);
        }
    }
    return folders;
}

bool BookmarkRepository::deleteFolder(int64_t folderId) {
    QSqlDatabase& db = Database::instance().database();
    QSqlQuery query(db);
    query.prepare("DELETE FROM bookmark_folders WHERE id = :id;");
    query.bindValue(":id", folderId);
    return query.exec();
}

int64_t BookmarkRepository::addBookmark(const QString& title, const QString& url, int64_t folderId) {
    QSqlDatabase& db = Database::instance().database();
    QSqlQuery query(db);
    query.prepare("INSERT INTO bookmarks (folder_id, title, url, created_at) VALUES (:folder, :title, :url, CURRENT_TIMESTAMP);");
    query.bindValue(":folder", folderId);
    query.bindValue(":title", title);
    query.bindValue(":url", url);
    if (query.exec()) {
        return query.lastInsertId().toLongLong();
    }
    return 0;
}

bool BookmarkRepository::updateBookmark(int64_t id, const QString& title, const QString& url, int64_t folderId) {
    QSqlDatabase& db = Database::instance().database();
    QSqlQuery query(db);
    query.prepare("UPDATE bookmarks SET title = :title, url = :url, folder_id = :folder WHERE id = :id;");
    query.bindValue(":title", title);
    query.bindValue(":url", url);
    query.bindValue(":folder", folderId);
    query.bindValue(":id", id);
    return query.exec();
}

bool BookmarkRepository::deleteBookmark(int64_t id) {
    QSqlDatabase& db = Database::instance().database();
    QSqlQuery query(db);
    query.prepare("DELETE FROM bookmarks WHERE id = :id;");
    query.bindValue(":id", id);
    return query.exec();
}

bool BookmarkRepository::isBookmarked(const QString& url) {
    QSqlDatabase& db = Database::instance().database();
    QSqlQuery query(db);
    query.prepare("SELECT 1 FROM bookmarks WHERE url = :url LIMIT 1;");
    query.bindValue(":url", url);
    return query.exec() && query.next();
}

QList<BookmarkItem> BookmarkRepository::getBookmarks(int64_t folderId) {
    QList<BookmarkItem> items;
    QSqlDatabase& db = Database::instance().database();
    QSqlQuery query(db);
    query.prepare("SELECT id, folder_id, title, url, created_at FROM bookmarks WHERE folder_id = :folder ORDER BY title ASC;");
    query.bindValue(":folder", folderId);
    if (query.exec()) {
        while (query.next()) {
            BookmarkItem item;
            item.id = query.value(0).toLongLong();
            item.folderId = query.value(1).toLongLong();
            item.title = query.value(2).toString();
            item.url = query.value(3).toString();
            item.createdAt = query.value(4).toDateTime();
            items.append(item);
        }
    }
    return items;
}

QList<BookmarkItem> BookmarkRepository::getAllBookmarks() {
    QList<BookmarkItem> items;
    QSqlDatabase& db = Database::instance().database();
    QSqlQuery query(db);
    if (query.exec("SELECT id, folder_id, title, url, created_at FROM bookmarks ORDER BY title ASC;")) {
        while (query.next()) {
            BookmarkItem item;
            item.id = query.value(0).toLongLong();
            item.folderId = query.value(1).toLongLong();
            item.title = query.value(2).toString();
            item.url = query.value(3).toString();
            item.createdAt = query.value(4).toDateTime();
            items.append(item);
        }
    }
    return items;
}

QList<BookmarkItem> BookmarkRepository::searchBookmarks(const QString& searchQuery) {
    QList<BookmarkItem> items;
    QSqlDatabase& db = Database::instance().database();
    QSqlQuery query(db);
    query.prepare("SELECT id, folder_id, title, url, created_at FROM bookmarks WHERE title LIKE :q OR url LIKE :q ORDER BY title ASC;");
    query.bindValue(":q", QString("%%1%").arg(searchQuery));
    if (query.exec()) {
        while (query.next()) {
            BookmarkItem item;
            item.id = query.value(0).toLongLong();
            item.folderId = query.value(1).toLongLong();
            item.title = query.value(2).toString();
            item.url = query.value(3).toString();
            item.createdAt = query.value(4).toDateTime();
            items.append(item);
        }
    }
    return items;
}

} // namespace ktbrowser
