#pragma once

#include <QString>
#include <QDateTime>
#include <QList>
#include <optional>

namespace ktbrowser {

struct HistoryItem {
    int64_t id{0};
    QString url;
    QString title;
    QDateTime visitTime;
    int visitCount{1};
};

class HistoryRepository {
public:
    HistoryRepository() = default;
    
    bool addOrUpdateHistory(const QString& url, const QString& title);
    QList<HistoryItem> getRecentHistory(int limit = 100);
    QList<HistoryItem> searchHistory(const QString& query, int limit = 50);
    
    bool deleteItem(int64_t id);
    bool clearAllHistory();
    bool clearHistoryTimeRange(const QDateTime& start, const QDateTime& end);
};

} // namespace ktbrowser
