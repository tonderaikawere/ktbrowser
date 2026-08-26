#include "ktbrowser/privacy/PrivacyManager.h"
#include "ktbrowser/database/Database.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

namespace ktbrowser {

PrivacyManager& PrivacyManager::instance() {
    static PrivacyManager instance;
    return instance;
}

PermissionState PrivacyManager::getPermission(const QString& origin, PermissionType type) {
    if (m_permissions.contains(origin) && m_permissions[origin].contains(type)) {
        return m_permissions[origin][type];
    }
    return PermissionState::Ask;
}

void PrivacyManager::setPermission(const QString& origin, PermissionType type, PermissionState state) {
    m_permissions[origin][type] = state;

    QSqlDatabase& db = Database::instance().database();
    QSqlQuery query(db);
    query.prepare("INSERT OR REPLACE INTO permissions (origin, permission_type, permission_state) VALUES (:origin, :type, :state);");
    query.bindValue(":origin", origin);
    query.bindValue(":type", static_cast<int>(type));
    query.bindValue(":state", static_cast<int>(state));
    query.exec();
}

} // namespace ktbrowser
