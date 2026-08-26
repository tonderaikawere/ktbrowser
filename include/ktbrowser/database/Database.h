#pragma once

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <memory>
#include <mutex>

namespace ktbrowser {

class Database {
public:
    static Database& instance();
    
    bool initialize(const QString& dbPath = QString());
    bool isConnected() const;
    
    QSqlDatabase& database();
    
    // Transactions
    bool transaction();
    bool commit();
    bool rollback();

private:
    Database() = default;
    ~Database();
    
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;
    
    bool createTables();

    QSqlDatabase m_db;
    bool m_initialized{false};
    std::mutex m_mutex;
};

} // namespace ktbrowser
