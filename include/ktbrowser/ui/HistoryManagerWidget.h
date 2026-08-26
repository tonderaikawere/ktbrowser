#pragma once

#include "ktbrowser/database/HistoryRepository.h"
#include <QDialog>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>

namespace ktbrowser {

class HistoryManagerWidget : public QDialog {
    Q_OBJECT
public:
    explicit HistoryManagerWidget(QWidget* parent = nullptr);

    void refreshHistory();

signals:
    void openUrlRequested(const QString& url);

private:
    void setupUi();
    void deleteSelectedItem();
    void clearHistoryByTime();

    QTableWidget* m_tableWidget{nullptr};
    QLineEdit* m_searchEdit{nullptr};
    QComboBox* m_timeRangeCombo{nullptr};
    HistoryRepository m_repo;
};

} // namespace ktbrowser
