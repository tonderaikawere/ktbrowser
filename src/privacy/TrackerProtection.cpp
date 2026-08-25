#include "codebrowser/privacy/TrackerProtection.h"

namespace codebrowser {

TrackerProtection::TrackerProtection() {
    loadCategoryData();
}

void TrackerProtection::loadCategoryData() {
    m_analyticsDomains = {
        "google-analytics.com", "analytics.google.com", "googletagmanager.com",
        "mixpanel.com", "segment.io", "hotjar.com", "crazyegg.com", "fullstory.com", "clarity.ms"
    };

    m_pixelDomains = {
        "pixel.facebook.com", "connect.facebook.net", "analytics.tiktok.com", "t.co"
    };

    m_fingerprintingDomains = {
        "fpjs.io", "fingerprintjs.com", "device-id.com", "canvas-print.net"
    };

    m_socialDomains = {
        "platform.twitter.com", "widgets.wp.com", "disqus.com", "addthis.com", "sharethis.com"
    };

    m_adDomains = {
        "adnxs.com", "rubiconproject.com", "pubmatic.com", "openx.net",
        "criteo.com", "outbrain.com", "taboola.com", "doubleclick.net"
    };
}

bool TrackerProtection::isTrackerDomain(const QString& domain, TrackerCategory* outCategory) const {
    QString host = domain.toLower();

    for (const auto& d : m_analyticsDomains) {
        if (host == d || host.endsWith("." + d)) {
            if (outCategory) *outCategory = TrackerCategory::Analytics;
            return true;
        }
    }

    for (const auto& d : m_pixelDomains) {
        if (host == d || host.endsWith("." + d)) {
            if (outCategory) *outCategory = TrackerCategory::TrackingPixel;
            return true;
        }
    }

    for (const auto& d : m_fingerprintingDomains) {
        if (host == d || host.endsWith("." + d)) {
            if (outCategory) *outCategory = TrackerCategory::Fingerprinting;
            return true;
        }
    }

    for (const auto& d : m_socialDomains) {
        if (host == d || host.endsWith("." + d)) {
            if (outCategory) *outCategory = TrackerCategory::SocialTracking;
            return true;
        }
    }

    for (const auto& d : m_adDomains) {
        if (host == d || host.endsWith("." + d)) {
            if (outCategory) *outCategory = TrackerCategory::AdNetwork;
            return true;
        }
    }

    return false;
}

TrackerCategory TrackerProtection::classifyUrl(const QUrl& url) const {
    TrackerCategory cat = TrackerCategory::Unknown;
    isTrackerDomain(url.host(), &cat);
    return cat;
}

} // namespace codebrowser
