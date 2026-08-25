#include "codebrowser/adblock/FilterListManager.h"
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

namespace codebrowser {

FilterListManager::FilterListManager() {
    loadDefaultLists();
}

QList<FilterListInfo> FilterListManager::filterLists() const {
    return m_lists;
}

void FilterListManager::addFilterList(const FilterListInfo& info) {
    m_lists.append(info);
}

void FilterListManager::removeFilterList(const QString& id) {
    m_lists.removeIf([&id](const FilterListInfo& info) { return info.id == id; });
}

void FilterListManager::setFilterListEnabled(const QString& id, bool enabled) {
    for (auto& info : m_lists) {
        if (info.id == id) {
            info.enabled = enabled;
            break;
        }
    }
}

void FilterListManager::loadDefaultLists() {
    FilterListInfo defaultEasyList;
    defaultEasyList.id = "easylist_default";
    defaultEasyList.name = "CodeBrowser Built-in Protection List";
    defaultEasyList.url = "https://easylist.to/easylist/easylist.txt";
    defaultEasyList.enabled = true;
    
    m_lists.append(defaultEasyList);
}

QStringList FilterListManager::readListRules(const QString& localPath) {
    QStringList rules;
    QFile file(localPath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            rules.append(in.readLine());
        }
    }
    return rules;
}

} // namespace codebrowser
