#pragma once

#include <QString>
#include <QVariant>
#include <unordered_map>

namespace ktbrowser {

class SettingsRepository {
public:
    SettingsRepository() = default;

    bool setSetting(const QString& key, const QString& value);
    QString setting(const QString& key, const QString& defaultValue = QString()) const;
    
    // Quick helpers
    QString defaultSearchEngine() const;
    void setDefaultSearchEngine(const QString& engineName);
    
    QString customSearchEngineUrl() const;
    void setCustomSearchEngineUrl(const QString& url);

    bool isAdBlockEnabled() const;
    void setAdBlockEnabled(bool enabled);

    bool isTrackerProtectionEnabled() const;
    void setTrackerProtectionEnabled(bool enabled);

    QString theme() const;
    void setTheme(const QString& theme);
};

} // namespace ktbrowser
