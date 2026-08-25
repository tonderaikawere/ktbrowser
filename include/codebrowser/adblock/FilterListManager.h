#pragma once

#include <QString>
#include <QStringList>
#include <QSet>
#include <QNetworkAccessManager>

namespace codebrowser {

struct FilterListInfo {
    QString id;
    QString name;
    QString url;
    bool enabled{true};
    QString localFilePath;
};

class FilterListManager {
public:
    FilterListManager();

    QList<FilterListInfo> filterLists() const;
    void addFilterList(const FilterListInfo& info);
    void removeFilterList(const QString& id);
    void setFilterListEnabled(const QString& id, bool enabled);

    void loadDefaultLists();
    QStringList readListRules(const QString& localPath);

private:
    QList<FilterListInfo> m_lists;
    QNetworkAccessManager m_networkManager;
};

} // namespace codebrowser
