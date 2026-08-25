#include "codebrowser/ui/HistoryManagerWidget.h"
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QDateTime>

namespace codebrowser {

HistoryManagerWidget::HistoryManagerWidget(QWidget* parent)
    : QDialog(parent) {
    setWindowTitle("Browsing History");
    setMinimumSize(700, 480);
    setupUi();
    refreshHistory();
}

void HistoryManagerWidget::setupUi() {
    auto* mainLayout = new QVBoxLayout(this);

    // Controls
    auto* topLayout = new QHBoxLayout();
    m_searchEdit = new QLineEdit(this);
    m_searchEdit->setPlaceholderText("Search history...");
    topLayout->addWidget(m_searchEdit);

    m_timeRangeCombo = new QComboBox(this);
    m_timeRangeCombo->addItems({"All Time", "Last Hour", "Last 24 Hours", "Last 7 Days"});
    topLayout->addWidget(m_timeRangeCombo);

    auto* clearTimeBtn = new QPushButton("Clear Time Range", this);
    auto* deleteItemBtn = new QPushButton("Delete Selected", this);
    auto* clearAllBtn = new QPushButton("Clear All History", this);

    topLayout->addWidget(clearTimeBtn);
    topLayout->addWidget(deleteItemBtn);
    topLayout->addWidget(clearAllBtn);

    mainLayout->addLayout(topLayout);

    // Table View
    m_tableWidget = new QTableWidget(this);
    m_tableWidget->setColumnCount(4);
    m_tableWidget->setHorizontalHeaderLabels({"Title", "URL", "Visit Time", "ID"});
    m_tableWidget->setColumnWidth(0, 220);
    m_tableWidget->setColumnWidth(1, 300);
    m_tableWidget->setColumnWidth(2, 140);
    m_tableWidget->hideColumn(3);
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableWidget->horizontalHeader()->setStretchLastSection(true);

    mainLayout->addWidget(m_tableWidget);

    connect(m_searchEdit, &QLineEdit::textChanged, this, [this](const QString& text) {
        if (text.isEmpty()) {
            refreshHistory();
        } else {
            m_tableWidget->setRowCount(0);
            auto items = m_repo.searchHistory(text);
            for (const auto& item : items) {
                int r = m_tableWidget->rowCount();
                m_tableWidget->insertRow(r);
                m_tableWidget->setItem(r, 0, new QTableWidgetItem(item.title));
                m_tableWidget->setItem(r, 1, new QTableWidgetItem(item.url));
                m_tableWidget->setItem(r, 2, new QTableWidgetItem(item.visitTime.toString("yyyy-MM-dd hh:mm")));
                m_tableWidget->setItem(r, 3, new QTableWidgetItem(QString::number(item.id)));
            }
        }
    });

    connect(deleteItemBtn, &QPushButton::clicked, this, &HistoryManagerWidget::deleteSelectedItem);
    connect(clearTimeBtn, &QPushButton::clicked, this, &HistoryManagerWidget::clearHistoryByTime);

    connect(clearAllBtn, &QPushButton::clicked, this, [this]() {
        if (QMessageBox::question(this, "Clear History", "Are you sure you want to clear all browsing history?") == QMessageBox::Yes) {
            m_repo.clearAllHistory();
            refreshHistory();
        }
    });

    connect(m_tableWidget, &QTableWidget::cellDoubleClicked, this, [this](int row, int col) {
        Q_UNUSED(col);
        auto* item = m_tableWidget->item(row, 1);
        if (item) {
            emit openUrlRequested(item->text());
            accept();
        }
    });
}

void HistoryManagerWidget::refreshHistory() {
    m_tableWidget->setRowCount(0);
    auto items = m_repo.getRecentHistory(200);

    for (const auto& item : items) {
        int r = m_tableWidget->rowCount();
        m_tableWidget->insertRow(r);
        m_tableWidget->setItem(r, 0, new QTableWidgetItem(item.title));
        m_tableWidget->setItem(r, 1, new QTableWidgetItem(item.url));
        m_tableWidget->setItem(r, 2, new QTableWidgetItem(item.visitTime.toString("yyyy-MM-dd hh:mm")));
        m_tableWidget->setItem(r, 3, new QTableWidgetItem(QString::number(item.id)));
    }
}

void HistoryManagerWidget::deleteSelectedItem() {
    int r = m_tableWidget->currentRow();
    if (r < 0) return;

    auto* idItem = m_tableWidget->item(r, 3);
    if (idItem) {
        int64_t id = idItem->text().toLongLong();
        m_repo.deleteItem(id);
        refreshHistory();
    }
}

void HistoryManagerWidget::clearHistoryByTime() {
    QString range = m_timeRangeCombo->currentText();
    QDateTime now = QDateTime::currentDateTime();
    QDateTime start;

    if (range == "Last Hour") {
        start = now.addSecs(-3600);
    } else if (range == "Last 24 Hours") {
        start = now.addDays(-1);
    } else if (range == "Last 7 Days") {
        start = now.addDays(-7);
    } else {
        m_repo.clearAllHistory();
        refreshHistory();
        return;
    }

    m_repo.clearHistoryTimeRange(start, now);
    refreshHistory();
}

} // namespace codebrowser
