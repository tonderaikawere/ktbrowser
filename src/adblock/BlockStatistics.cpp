#include "codebrowser/adblock/BlockStatistics.h"

namespace codebrowser {

BlockStatistics::BlockStatistics(QObject* parent)
    : QObject(parent) {}

void BlockStatistics::recordAdBlocked() {
    m_adsBlocked.fetch_add(1, std::memory_order_relaxed);
    m_requestsBlocked.fetch_add(1, std::memory_order_relaxed);
    emit statisticsUpdated();
}

void BlockStatistics::recordTrackerBlocked() {
    m_trackersBlocked.fetch_add(1, std::memory_order_relaxed);
    m_requestsBlocked.fetch_add(1, std::memory_order_relaxed);
    emit statisticsUpdated();
}

void BlockStatistics::recordRequestBlocked() {
    m_requestsBlocked.fetch_add(1, std::memory_order_relaxed);
    emit statisticsUpdated();
}

void BlockStatistics::recordHttpsConnection(bool isHttps) {
    if (isHttps) {
        m_httpsRequests.fetch_add(1, std::memory_order_relaxed);
    } else {
        m_httpRequests.fetch_add(1, std::memory_order_relaxed);
    }
    emit statisticsUpdated();
}

double BlockStatistics::httpsPercentage() const {
    uint64_t https = m_httpsRequests.load();
    uint64_t http = m_httpRequests.load();
    uint64_t total = https + http;
    if (total == 0) return 100.0;
    return (static_cast<double>(https) / total) * 100.0;
}

void BlockStatistics::resetSessionStats() {
    m_adsBlocked.store(0);
    m_trackersBlocked.store(0);
    m_requestsBlocked.store(0);
    m_httpsRequests.store(0);
    m_httpRequests.store(0);
    emit statisticsUpdated();
}

} // namespace codebrowser
