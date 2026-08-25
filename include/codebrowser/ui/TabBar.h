#pragma once

#include <QTabBar>
#include <QToolButton>

namespace codebrowser {

class TabBar : public QTabBar {
    Q_OBJECT
public:
    explicit TabBar(QWidget* parent = nullptr);

signals:
    void newTabRequested();
    void closeTabRequested(int index);

protected:
    void tabInserted(int index) override;
    void tabRemoved(int index) override;

private:
    QToolButton* m_newTabBtn{nullptr};
};

} // namespace codebrowser
