#include "ktbrowser/adblock/AdBlockEngine.h"
#include "ktbrowser/adblock/FilterParser.h"
#include <mutex>
#include <QDebug>

namespace ktbrowser {

AdBlockEngine& AdBlockEngine::instance() {
    static AdBlockEngine instance;
    return instance;
}

bool AdBlockEngine::initialize() {
    std::unique_lock<std::shared_mutex> lock(m_mutex);
    
    // Seed known tracker and ad domains for instant high-performance network blocking
    m_knownTrackerDomains = {
        "google-analytics.com", "analytics.google.com", "googletagmanager.com",
        "doubleclick.net", "adservice.google.com", "connect.facebook.net",
        "pixel.facebook.com", "analytics.tiktok.com", "hotjar.com",
        "mixpanel.com", "segment.io", "quantserve.com", "scorecardresearch.com",
        "yandex.ru/metrika", "crazyegg.com", "fullstory.com", "clarity.ms"
    };

    m_knownAdDomains = {
        "adnxs.com", "rubiconproject.com", "pubmatic.com", "openx.net",
        "criteo.com", "criteo.net", "outbrain.com", "taboola.com",
        "zedo.com", "amazon-adsystem.com", "adroll.com", "popads.net",
        "propellerads.com", "exoclick.com", "adblade.com", "buy-ads.com"
    };

    // Built-in rule seeds
    QStringList seedRules = {
        "||google-analytics.com^",
        "||doubleclick.net^",
        "||adservice.google.com^",
        "||googletagmanager.com^",
        "||connect.facebook.net^",
        "||adnxs.com^",
        "||rubiconproject.com^",
        "||pubmatic.com^",
        "||openx.net^",
        "||criteo.com^",
        "||outbrain.com^",
        "||taboola.com^"
    };

    auto parsedRules = FilterParser::parseLines(seedRules);
    for (auto& rule : parsedRules) {
        if (rule->isException()) {
            m_allowRules.append(rule);
        } else {
            m_blockRules.append(rule);
        }
    }

    qDebug() << "AdBlockEngine initialized with" << m_blockRules.size() << "rules and"
             << m_knownTrackerDomains.size() << "tracker domains.";
    return true;
}

bool AdBlockEngine::shouldBlockRequest(const QUrl& requestUrl, const QUrl& firstPartyUrl, QString* outReason) {
    if (!m_enabled) return false;

    QString host = requestUrl.host().toLower();
    if (host.isEmpty()) return false;

    // Check Whitelist
    if (isWhitelisted(host) || isWhitelisted(firstPartyUrl.host().toLower())) {
        return false;
    }

    auto recordBlock = [this, &requestUrl](const QString& reason) {
        std::unique_lock<std::shared_mutex> lock(m_mutex);
        BlockedRequestLog log;
        log.url = requestUrl.toString();
        log.reason = reason;
        log.timestamp = QDateTime::currentDateTime();
        
        m_recentLogs.prepend(log);
        if (m_recentLogs.size() > 50) {
            m_recentLogs.removeLast();
        }
        emit requestBlocked(log.url, reason);
    };

    // High performance domain lookup
    for (const auto& trackerDomain : m_knownTrackerDomains) {
        if (host == trackerDomain || host.endsWith("." + trackerDomain)) {
            m_stats.recordTrackerBlocked();
            QString reason = "Tracker Domain: " + trackerDomain;
            if (outReason) *outReason = reason;
            recordBlock(reason);
            return true;
        }
    }

    for (const auto& adDomain : m_knownAdDomains) {
        if (host == adDomain || host.endsWith("." + adDomain)) {
            m_stats.recordAdBlocked();
            QString reason = "Ad Network: " + adDomain;
            if (outReason) *outReason = reason;
            recordBlock(reason);
            return true;
        }
    }

    // Shared read lock for rule iteration
    std::shared_lock<std::shared_mutex> lock(m_mutex);

    // Check Allow rules first
    for (const auto& rule : m_allowRules) {
        if (rule->matches(requestUrl, firstPartyUrl)) {
            return false;
        }
    }

    // Check Block rules
    for (const auto& rule : m_blockRules) {
        if (rule->matches(requestUrl, firstPartyUrl)) {
            m_stats.recordAdBlocked();
            QString reason = "Filter Rule: " + rule->rawPattern();
            if (outReason) *outReason = reason;
            recordBlock(reason);
            return true;
        }
    }

    // Third-party tracker check
    if (!firstPartyUrl.isEmpty() && firstPartyUrl.host().toLower() != host) {
        if (host.contains("tracker") || host.contains("telemetry") || host.contains("analytics")) {
            m_stats.recordTrackerBlocked();
            QString reason = "Third-Party Tracking Request";
            if (outReason) *outReason = reason;
            recordBlock(reason);
            return true;
        }
    }

    return false;
}

void AdBlockEngine::addWhitelistDomain(const QString& domain) {
    std::unique_lock<std::shared_mutex> lock(m_mutex);
    m_whitelistedDomains.insert(domain.toLower());
}

void AdBlockEngine::removeWhitelistDomain(const QString& domain) {
    std::unique_lock<std::shared_mutex> lock(m_mutex);
    m_whitelistedDomains.remove(domain.toLower());
}

bool AdBlockEngine::isWhitelisted(const QString& domain) const {
    std::shared_lock<std::shared_mutex> lock(m_mutex);
    QString lower = domain.toLower();
    for (const auto& d : m_whitelistedDomains) {
        if (lower == d || lower.endsWith("." + d)) {
            return true;
        }
    }
    return false;
}

QList<BlockedRequestLog> AdBlockEngine::recentBlockedLogs() const {
    std::shared_lock<std::shared_mutex> lock(m_mutex);
    return m_recentLogs;
}

void AdBlockEngine::setEnabled(bool enabled) {
    m_enabled = enabled;
}

void AdBlockEngine::reloadRules() {
    // Reload rules logic
}

} // namespace ktbrowser
