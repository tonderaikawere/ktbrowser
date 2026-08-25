#pragma once

#include "codebrowser/browser/TabManager.h"
#include "codebrowser/ui/BrowserToolbar.h"
#include "codebrowser/ui/TabBar.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QVBoxLayout>

namespace codebrowser {

class BrowserWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit BrowserWindow(QWidget* parent = nullptr);
    ~BrowserWindow() override = default;

    TabManager* tabManager() const { return m_tabManager; }

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
    void setupUi();
    void setupConnections();
    void applyTheme(const QString& themeName);

    TabBar* m_tabBar{nullptr};
    BrowserToolbar* m_toolbar{nullptr};
    QStackedWidget* m_stackedWidget{nullptr};
    TabManager* m_tabManager{nullptr};
};

} // namespace codebrowser
