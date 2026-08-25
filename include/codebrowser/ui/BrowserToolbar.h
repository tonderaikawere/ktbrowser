#pragma once

#include "codebrowser/ui/AddressBar.h"
#include <QToolBar>
#include <QToolButton>

namespace codebrowser {

class BrowserToolbar : public QToolBar {
    Q_OBJECT
public:
    explicit BrowserToolbar(QWidget* parent = nullptr);

    AddressBar* addressBar() const { return m_addressBar; }
    
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
    void setupActions();

    QToolButton* m_backBtn{nullptr};
    QToolButton* m_forwardBtn{nullptr};
    QToolButton* m_reloadStopBtn{nullptr};
    QToolButton* m_homeBtn{nullptr};
    AddressBar* m_addressBar{nullptr};
    QToolButton* m_shieldsBtn{nullptr};
    QToolButton* m_bookmarkBtn{nullptr};
    QToolButton* m_historyBtn{nullptr};
    QToolButton* m_downloadsBtn{nullptr};
    QToolButton* m_settingsBtn{nullptr};
    
    bool m_isLoading{false};
};

} // namespace codebrowser
