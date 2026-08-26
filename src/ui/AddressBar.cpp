#include "ktbrowser/ui/AddressBar.h"
#include <QHBoxLayout>
#include <QToolButton>

namespace ktbrowser {

AddressBar::AddressBar(QWidget* parent)
    : QWidget(parent) {
    setupUi();
}

void AddressBar::setupUi() {
    auto* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    m_searchIcon = new QLabel(this);
    m_searchIcon->setText(" G ");
    m_searchIcon->setStyleSheet(R"(
        QLabel {
            color: #fce8e4;
            font-size: 14px;
            font-weight: bold;
            background: transparent;
            padding-left: 10px;
        }
    )");

    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setPlaceholderText("Ask Google or type a URL");
    m_lineEdit->setStyleSheet(R"(
        QLineEdit {
            background-color: #402421;
            color: #ffffff;
            border: 1px solid #57332e;
            border-radius: 16px;
            padding: 6px 14px 6px 36px;
            font-size: 14px;
            selection-background-color: #5c342f;
        }
        QLineEdit:focus {
            background-color: #4c2b27;
            border: 1px solid #f5b6a7;
        }
    )");

    // Position search icon inside line edit
    auto* internalLayout = new QHBoxLayout(m_lineEdit);
    internalLayout->setContentsMargins(4, 0, 8, 0);
    internalLayout->addWidget(m_searchIcon);
    internalLayout->addStretch();

    auto* starBtn = new QToolButton(m_lineEdit);
    starBtn->setText("⭐");
    starBtn->setStyleSheet("background: transparent; border: none; font-size: 14px;");
    internalLayout->addWidget(starBtn);

    layout->addWidget(m_lineEdit);

    connect(m_lineEdit, &QLineEdit::returnPressed, this, [this]() {
        emit navigateRequested(m_lineEdit->text());
    });
}

void AddressBar::setUrl(const QUrl& url) {
    if (url.toString() == "ktbrowser://newtab" || url.toString() == "about:blank") {
        m_lineEdit->clear();
        m_searchIcon->setText(" G ");
    } else {
        m_lineEdit->setText(url.toString());
        m_searchIcon->setText(url.scheme() == "https" ? "🔒" : "🌐");
    }
}

QString AddressBar::text() const {
    return m_lineEdit->text();
}

} // namespace ktbrowser
