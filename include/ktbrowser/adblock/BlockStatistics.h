#pragma once

#include <QObject>
#include <atomic>

namespace ktbrowser {

class BlockStatistics : public QObject {
    Q_OBJECT
public:
    explicit BlockStatistics(QObject* parent = nullptr);

    void recordAdBlocked();
    void recordTrackerBlocked();
    void recordRequestBlocked();
    void recordHttpsConnection(bool isHttps);

    uint64_t adsBlocked() const { return m_adsBlocked.load(); }
    uint64_t trackersBlocked() const { return m_trackersBlocked.load(); }
    uint64_t requestsBlocked() const { return m_requestsBlocked.load(); }
    uint64_t totalHttpsRequests() const { return m_httpsRequests.load(); }
    uint64_t totalHttpRequests() const { return m_httpRequests.load(); }

    double httpsPercentage() const;

    void resetSessionStats();

signals:
    void statisticsUpdated();

private:
    std::atomic<uint64_t> m_adsBlocked{0};
    std::atomic<uint64_t> m_trackersBlocked{0};
    std::atomic<uint64_t> m_requestsBlocked{0};
    std::atomic<uint64_t> m_httpsRequests{0};
    std::atomic<uint64_t> m_httpRequests{0};
};

} // namespace ktbrowser
