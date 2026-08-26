#pragma once

#include "ktbrowser/ui/AddressBar.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QToolButton>

namespace ktbrowser {

class BrowserToolbar : public QWidget {
    Q_OBJECT
public:
    explicit BrowserToolbar(QWidget* parent = nullptr);

    AddressBar* addressBar() const { return m_addressBar; }
    QToolButton* settingsButton() const { return m_settingsBtn; }
    
    void setCanGoBack(bool can);
    void setCanGoForward(bool can);
    void setIsLoading(bool loading);
    void setShieldsCount(int count);

signals:
    void backRequested();
    void forwardRequested();
    void reloadRequested();
    void stopRequested();
    void homeRequested();
    void bookmarkRequested();
    void historyRequested();
    void privacyDashboardRequested();
    void downloadsRequested();
    void settingsRequested();

private:
    void setupUi();

    QHBoxLayout* m_layout{nullptr};
    QToolButton* m_backBtn{nullptr};
    QToolButton* m_forwardBtn{nullptr};
    QToolButton* m_reloadBtn{nullptr};
    QToolButton* m_homeBtn{nullptr};
    AddressBar* m_addressBar{nullptr};
    QToolButton* m_shieldsBtn{nullptr};
    QToolButton* m_bookmarkBtn{nullptr};
    QToolButton* m_historyBtn{nullptr};
    QToolButton* m_downloadsBtn{nullptr};
    QToolButton* m_settingsBtn{nullptr};
    
    bool m_isLoading{false};
};

} // namespace ktbrowser
