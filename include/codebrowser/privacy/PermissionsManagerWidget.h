#pragma once

#include "codebrowser/privacy/PrivacyManager.h"
#include <QDialog>
#include <QTableWidget>
#include <QPushButton>

namespace codebrowser {

class PermissionsManagerWidget : public QDialog {
    Q_OBJECT
public:
    explicit PermissionsManagerWidget(QWidget* parent = nullptr);

    void refreshPermissions();

private:
    void setupUi();

    QTableWidget* m_tableWidget{nullptr};
};

} // namespace codebrowser
