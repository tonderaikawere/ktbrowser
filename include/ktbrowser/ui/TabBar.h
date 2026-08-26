#pragma once

#include <QWidget>
#include <QTabBar>
#include <QToolButton>
#include <QIcon>
#include <QString>

namespace ktbrowser {

class TabBar : public QWidget {
    Q_OBJECT
public:
    explicit TabBar(QWidget* parent = nullptr);

    int addTab(const QString& text);
    void insertTab(int index, const QString& text);
    void removeTab(int index);
    void setTabText(int index, const QString& text);
    void setTabIcon(int index, const QIcon& icon);
    void setCurrentIndex(int index);
    int currentIndex() const;
    int count() const;

signals:
    void newTabRequested();
    void tabCloseRequested(int index);
    void currentChanged(int index);
    void tabMoved(int from, int to);

private:
    void setupUi();

    QTabBar* m_tabBar{nullptr};
    QToolButton* m_newTabBtn{nullptr};
};

} // namespace ktbrowser
