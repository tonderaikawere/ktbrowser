#pragma once

#include <QString>
#include <QSet>
#include <QUrl>

namespace ktbrowser {

enum class TrackerCategory {
    Analytics,
    TrackingPixel,
    Fingerprinting,
    SocialTracking,
    AdNetwork,
    Unknown
};

class TrackerProtection {
public:
    TrackerProtection();

    bool isTrackerDomain(const QString& domain, TrackerCategory* outCategory = nullptr) const;
    TrackerCategory classifyUrl(const QUrl& url) const;

private:
    void loadCategoryData();

    QSet<QString> m_analyticsDomains;
    QSet<QString> m_pixelDomains;
    QSet<QString> m_fingerprintingDomains;
    QSet<QString> m_socialDomains;
    QSet<QString> m_adDomains;
};

} // namespace ktbrowser
