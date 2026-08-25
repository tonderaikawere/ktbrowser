#include "codebrowser/database/HistoryRepository.h"
#include "codebrowser/database/Database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

namespace codebrowser {

bool HistoryRepository::addOrUpdateHistory(const QString& url, const QString& title) {
    if (url.isEmpty() || url == "about:blank" || url.startsWith("chrome://") || url.startsWith("qrc://")) {
        return false;
    }

    QSqlDatabase& db = Database::instance().database();
    
    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT id, visit_count FROM history WHERE url = :url ORDER BY visit_time DESC LIMIT 1;");
    checkQuery.bindValue(":url", url);

    if (checkQuery.exec() && checkQuery.next()) {
        int64_t id = checkQuery.value(0).toLongLong();
        int visitCount = checkQuery.value(1).toInt() + 1;

        QSqlQuery updateQuery(db);
        updateQuery.prepare("UPDATE history SET title = :title, visit_time = CURRENT_TIMESTAMP, visit_count = :count WHERE id = :id;");
        updateQuery.bindValue(":title", title);
        updateQuery.bindValue(":count", visitCount);
        updateQuery.bindValue(":id", id);
        return updateQuery.exec();
    } else {
        QSqlQuery insertQuery(db);
        insertQuery.prepare("INSERT INTO history (url, title, visit_time, visit_count) VALUES (:url, :title, CURRENT_TIMESTAMP, 1);");
        insertQuery.bindValue(":url", url);
        insertQuery.bindValue(":title", title);
        return insertQuery.exec();
    }
}

QList<HistoryItem> HistoryRepository::getRecentHistory(int limit) {
    QList<HistoryItem> items;
    QSqlDatabase& db = Database::instance().database();

    QSqlQuery query(db);
    query.prepare("SELECT id, url, title, visit_time, visit_count FROM history ORDER BY visit_time DESC LIMIT :limit;");
    query.bindValue(":limit", limit);

    if (query.exec()) {
        while (query.next()) {
            HistoryItem item;
            item.id = query.value(0).toLongLong();
            item.url = query.value(1).toString();
            item.title = query.value(2).toString();
            item.visitTime = query.value(3).toDateTime();
            item.visitCount = query.value(4).toInt();
            items.append(item);
        }
    }
    return items;
}

QList<HistoryItem> HistoryRepository::searchHistory(const QString& searchQuery, int limit) {
    QList<HistoryItem> items;
    QSqlDatabase& db = Database::instance().database();

    QSqlQuery query(db);
    query.prepare("SELECT id, url, title, visit_time, visit_count FROM history WHERE url LIKE :q OR title LIKE :q ORDER BY visit_time DESC LIMIT :limit;");
    query.bindValue(":q", QString("%%1%").arg(searchQuery));
    query.bindValue(":limit", limit);

    if (query.exec()) {
        while (query.next()) {
            HistoryItem item;
            item.id = query.value(0).toLongLong();
            item.url = query.value(1).toString();
            item.title = query.value(2).toString();
            item.visitTime = query.value(3).toDateTime();
            item.visitCount = query.value(4).toInt();
            items.append(item);
        }
    }
    return items;
}

bool HistoryRepository::deleteItem(int64_t id) {
    QSqlDatabase& db = Database::instance().database();
    QSqlQuery query(db);
    query.prepare("DELETE FROM history WHERE id = :id;");
    query.bindValue(":id", id);
    return query.exec();
}

bool HistoryRepository::clearAllHistory() {
    QSqlDatabase& db = Database::instance().database();
    QSqlQuery query(db);
    return query.exec("DELETE FROM history;");
}

bool HistoryRepository::clearHistoryTimeRange(const QDateTime& start, const QDateTime& end) {
    QSqlDatabase& db = Database::instance().database();
    QSqlQuery query(db);
    query.prepare("DELETE FROM history WHERE visit_time >= :start AND visit_time <= :end;");
    query.bindValue(":start", start);
    query.bindValue(":end", end);
    return query.exec();
}

} // namespace codebrowser
