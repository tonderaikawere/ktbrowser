#pragma once

#include "ktbrowser/adblock/FilterRule.h"
#include "ktbrowser/adblock/BlockStatistics.h"
#include "ktbrowser/adblock/FilterListManager.h"
#include <QObject>
#include <QUrl>
#include <QSet>
#include <QDateTime>
#include <shared_mutex>
#include <memory>

namespace ktbrowser {

struct BlockedRequestLog {
    QString url;
    QString reason;
    QDateTime timestamp;
};

class AdBlockEngine : public QObject {
    Q_OBJECT
public:
    static AdBlockEngine& instance();

    bool initialize();
    bool shouldBlockRequest(const QUrl& requestUrl, const QUrl& firstPartyUrl, QString* outReason = nullptr);

    void addWhitelistDomain(const QString& domain);
    void removeWhitelistDomain(const QString& domain);
    bool isWhitelisted(const QString& domain) const;
    
    void setEnabled(bool enabled);
    bool isEnabled() const { return m_enabled; }

    BlockStatistics& statistics() { return m_stats; }
    FilterListManager& listManager() { return m_listManager; }
    
    QList<BlockedRequestLog> recentBlockedLogs() const;

    void reloadRules();

signals:
    void requestBlocked(const QString& url, const QString& reason);

private:
    AdBlockEngine() = default;
    ~AdBlockEngine() = default;

    AdBlockEngine(const AdBlockEngine&) = delete;
    AdBlockEngine& operator=(const AdBlockEngine&) = delete;

    bool m_enabled{true};
    QList<std::shared_ptr<FilterRule>> m_blockRules;
    QList<std::shared_ptr<FilterRule>> m_allowRules;
    QSet<QString> m_whitelistedDomains;
    QSet<QString> m_knownTrackerDomains;
    QSet<QString> m_knownAdDomains;
    QList<BlockedRequestLog> m_recentLogs;

    BlockStatistics m_stats;
    FilterListManager m_listManager;
    mutable std::shared_mutex m_mutex;
};

} // namespace ktbrowser
