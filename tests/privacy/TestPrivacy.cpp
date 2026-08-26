#include "ktbrowser/privacy/PrivacyManager.h"
#include "ktbrowser/privacy/TrackerProtection.h"
#include <QCoreApplication>
#include <iostream>
#include <cassert>

using namespace ktbrowser;

void testPrivacyPermissions() {
    PrivacyManager& pm = PrivacyManager::instance();
    
    // Default permission should be Ask
    assert(pm.getPermission("https://example.com", PermissionType::Camera) == PermissionState::Ask);
    
    // Set permission to Allow
    pm.setPermission("https://example.com", PermissionType::Camera, PermissionState::Allow);
    assert(pm.getPermission("https://example.com", PermissionType::Camera) == PermissionState::Allow);
    
    // Set permission to Block
    pm.setPermission("https://example.com", PermissionType::Geolocation, PermissionState::Block);
    assert(pm.getPermission("https://example.com", PermissionType::Geolocation) == PermissionState::Block);
    
    // Cookie blocking toggle test
    assert(pm.isThirdPartyCookieBlockingEnabled());
    pm.setBlockThirdPartyCookies(false);
    assert(!pm.isThirdPartyCookieBlockingEnabled());
    pm.setBlockThirdPartyCookies(true);
    
    std::cout << "[PASS] PrivacyManager permissions test passed.\n";
}

void testTrackerClassification() {
    TrackerProtection tracker;
    
    TrackerCategory category = TrackerCategory::Unknown;
    bool isTracker = tracker.isTrackerDomain("analytics.google.com", &category);
    assert(isTracker);
    assert(category == TrackerCategory::Analytics);
    
    bool isNotTracker = tracker.isTrackerDomain("wikipedia.org");
    assert(!isNotTracker);
    
    TrackerCategory catUrl = tracker.classifyUrl(QUrl("https://facebook.com/tr/"));
    assert(catUrl == TrackerCategory::SocialTracking);
    
    std::cout << "[PASS] TrackerProtection classification test passed.\n";
}

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    testPrivacyPermissions();
    testTrackerClassification();
    std::cout << "All Privacy Unit Tests PASSED Successfully!\n";
    return 0;
}
