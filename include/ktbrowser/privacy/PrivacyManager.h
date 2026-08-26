#pragma once

#include <QObject>
#include <QString>
#include <QSet>
#include <QMap>

namespace ktbrowser {

enum class PermissionType {
    Camera,
    Microphone,
    Geolocation,
    Notifications,
    Popups
};

enum class PermissionState {
    Ask,
    Allow,
    Block
};

class PrivacyManager : public QObject {
    Q_OBJECT
public:
    static PrivacyManager& instance();

    PermissionState getPermission(const QString& origin, PermissionType type);
    void setPermission(const QString& origin, PermissionType type, PermissionState state);

    bool isThirdPartyCookieBlockingEnabled() const { return m_blockThirdPartyCookies; }
    void setBlockThirdPartyCookies(bool block) { m_blockThirdPartyCookies = block; }

private:
    PrivacyManager() = default;
    
    bool m_blockThirdPartyCookies{true};
    QMap<QString, QMap<PermissionType, PermissionState>> m_permissions;
};

} // namespace ktbrowser
