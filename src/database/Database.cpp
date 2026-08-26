#include "ktbrowser/database/Database.h"
#include <QStandardPaths>
#include <QDir>
#include <QSqlError>
#include <QDebug>

namespace ktbrowser {

Database& Database::instance() {
    static Database instance;
    return instance;
}

Database::~Database() {
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool Database::initialize(const QString& dbPath) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_initialized) return true;

    QString path = dbPath;
    if (path.isEmpty()) {
        QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        QDir dir(dataDir);
        if (!dir.exists()) {
            dir.mkpath(".");
        }
        path = dir.filePath("codebrowser.sqlite");
    }

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open()) {
        qCritical() << "Failed to open SQLite database:" << m_db.lastError().text();
        return false;
    }

    if (!createTables()) {
        qCritical() << "Failed to create database tables";
        return false;
    }

    m_initialized = true;
    qDebug() << "KT Browser database initialized successfully at:" << path;
    return true;
}

bool Database::isConnected() const {
    return m_initialized && m_db.isOpen();
}

QSqlDatabase& Database::database() {
    return m_db;
}

bool Database::transaction() {
    return m_db.transaction();
}

bool Database::commit() {
    return m_db.commit();
}

bool Database::rollback() {
    return m_db.rollback();
}

bool Database::createTables() {
    QSqlQuery query(m_db);

    const QStringList schemaQueries = {
        R"(CREATE TABLE IF NOT EXISTS history (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            url TEXT NOT NULL,
            title TEXT,
            visit_time DATETIME DEFAULT CURRENT_TIMESTAMP,
            visit_count INTEGER DEFAULT 1
        );)",
        R"(CREATE TABLE IF NOT EXISTS bookmark_folders (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            parent_id INTEGER DEFAULT 0
        );)",
        R"(CREATE TABLE IF NOT EXISTS bookmarks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            folder_id INTEGER DEFAULT 0,
            title TEXT NOT NULL,
            url TEXT NOT NULL,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        );)",
        R"(CREATE TABLE IF NOT EXISTS downloads (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            file_name TEXT NOT NULL,
            full_path TEXT NOT NULL,
            url TEXT NOT NULL,
            total_bytes INTEGER DEFAULT 0,
            received_bytes INTEGER DEFAULT 0,
            state INTEGER DEFAULT 0,
            start_time DATETIME DEFAULT CURRENT_TIMESTAMP
        );)",
        R"(CREATE TABLE IF NOT EXISTS settings (
            key TEXT PRIMARY KEY,
            value TEXT NOT NULL
        );)",
        R"(CREATE TABLE IF NOT EXISTS permissions (
            origin TEXT NOT NULL,
            permission_type INTEGER NOT NULL,
            permission_state INTEGER NOT NULL,
            PRIMARY KEY (origin, permission_type)
        );)",
        R"(CREATE TABLE IF NOT EXISTS blocked_statistics (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            ads_blocked INTEGER DEFAULT 0,
            trackers_blocked INTEGER DEFAULT 0,
            requests_blocked INTEGER DEFAULT 0,
            date TEXT DEFAULT CURRENT_DATE
        );)",
        R"(CREATE TABLE IF NOT EXISTS filter_lists (
            id TEXT PRIMARY KEY,
            name TEXT NOT NULL,
            url TEXT NOT NULL,
            enabled INTEGER DEFAULT 1,
            local_path TEXT
        );)"
    };

    for (const auto& q : schemaQueries) {
        if (!query.exec(q)) {
            qCritical() << "Schema exec error:" << query.lastError().text() << "Query:" << q;
            return false;
        }
    }

    return true;
}

} // namespace ktbrowser
