#include "codebrowser/ui/NewTabPage.h"
#include "codebrowser/adblock/AdBlockEngine.h"
#include "codebrowser/database/SettingsRepository.h"
#include "codebrowser/browser/NavigationController.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>

namespace codebrowser {

NewTabPage::NewTabPage(QWidget* parent)
    : QWidget(parent) {
    setupUi();
    refreshStats();

    connect(&AdBlockEngine::instance().statistics(), &BlockStatistics::statisticsUpdated,
            this, &NewTabPage::refreshStats);
}

void NewTabPage::setupUi() {
    setStyleSheet("background-color: #2b2238;");

    auto* outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);

    // Top Navigation Header (Kawerify Tech Badge, Gmail, Images, Grid, Profile)
    auto* topHeaderLayout = new QHBoxLayout();
    topHeaderLayout->setContentsMargins(24, 16, 24, 8);

    auto* ktBrandBtn = new QPushButton("🚀 Kawerify Tech", this);
    ktBrandBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #4a3461;
            color: #d0bcff;
            font-size: 13px;
            font-weight: bold;
            border-radius: 14px;
            padding: 5px 14px;
            border: 1px solid #5c4278;
        }
        QPushButton:hover {
            background-color: #5c4278;
            color: #ffffff;
        }
    )");
    connect(ktBrandBtn, &QPushButton::clicked, this, [this]() {
        emit searchRequested("https://kawerifytech.com");
    });
    topHeaderLayout->addWidget(ktBrandBtn);

    topHeaderLayout->addStretch();

    auto* gmailBtn = new QPushButton("Gmail", this);
    auto* imagesBtn = new QPushButton("Images", this);
    auto* gridBtn = new QPushButton("::", this);
    auto* profileBtn = new QPushButton("👤", this);

    QString topBtnStyle = R"(
        QPushButton {
            background: transparent;
            color: #ffffff;
            font-size: 14px;
            border: none;
            padding: 4px 10px;
        }
        QPushButton:hover {
            color: #d0bcff;
            text-decoration: underline;
        }
    )";
    gmailBtn->setStyleSheet(topBtnStyle);
    imagesBtn->setStyleSheet(topBtnStyle);
    gridBtn->setStyleSheet("background: transparent; color: #ffffff; font-size: 18px; border: none; font-weight: bold;");
    profileBtn->setStyleSheet("background: #4a3461; color: #ffffff; border-radius: 16px; min-width: 32px; min-height: 32px; font-size: 16px;");

    connect(gmailBtn, &QPushButton::clicked, this, [this]() { emit searchRequested("https://mail.google.com"); });
    connect(imagesBtn, &QPushButton::clicked, this, [this]() { emit searchRequested("https://images.google.com"); });

    topHeaderLayout->addWidget(gmailBtn);
    topHeaderLayout->addWidget(imagesBtn);
    topHeaderLayout->addWidget(gridBtn);
    topHeaderLayout->addWidget(profileBtn);

    outerLayout->addLayout(topHeaderLayout);

    // Main Content Area
    auto* mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    mainLayout->setContentsMargins(40, 10, 40, 30);
    mainLayout->setSpacing(20);

    // Giant Google Center Logo
    auto* logoLabel = new QLabel(this);
    logoLabel->setText("<h1 style='font-size: 80px; font-family: Segoe UI, sans-serif; font-weight: 700; color: #ffffff; margin: 5px 0;'>Google</h1>");
    logoLabel->setTextFormat(Qt::RichText);
    logoLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(logoLabel);

    // Search Box Bar (+ Ask Google | Mic | Lens | AI Mode)
    auto* searchFrame = new QFrame(this);
    searchFrame->setFixedWidth(680);
    searchFrame->setFixedHeight(50);
    searchFrame->setStyleSheet(R"(
        QFrame {
            background-color: #ffffff;
            border-radius: 25px;
        }
    )");

    auto* searchLayout = new QHBoxLayout(searchFrame);
    searchLayout->setContentsMargins(18, 0, 10, 0);
    searchLayout->setSpacing(10);

    auto* plusLabel = new QLabel("+", searchFrame);
    plusLabel->setStyleSheet("color: #5f6368; font-size: 20px; font-weight: bold; background: transparent;");

    m_searchEdit = new QLineEdit(searchFrame);
    m_searchEdit->setPlaceholderText("Ask Google");
    m_searchEdit->setStyleSheet(R"(
        QLineEdit {
            background: transparent;
            color: #202124;
            border: none;
            font-size: 16px;
        }
    )");

    auto* micBtn = new QPushButton("🎤", searchFrame);
    auto* lensBtn = new QPushButton("📷", searchFrame);
    auto* aiModeBtn = new QPushButton("✨ AI Mode", searchFrame);

    micBtn->setStyleSheet("background: transparent; border: none; font-size: 16px;");
    lensBtn->setStyleSheet("background: transparent; border: none; font-size: 16px;");
    aiModeBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #f1f3f4;
            color: #3c4043;
            font-size: 13px;
            font-weight: bold;
            border-radius: 15px;
            padding: 6px 14px;
            border: 1px solid #dadce0;
        }
        QPushButton:hover {
            background-color: #e8eaed;
        }
    )");

    searchLayout->addWidget(plusLabel);
    searchLayout->addWidget(m_searchEdit, 1);
    searchLayout->addWidget(micBtn);
    searchLayout->addWidget(lensBtn);
    searchLayout->addWidget(aiModeBtn);

    connect(m_searchEdit, &QLineEdit::returnPressed, this, [this]() {
        QString input = m_searchEdit->text().trimmed();
        if (!input.isEmpty()) {
            SettingsRepository repo;
            QUrl url = NavigationController::parseInput(input, "Google", repo.customSearchEngineUrl());
            emit searchRequested(url.toString());
        }
    });

    mainLayout->addWidget(searchFrame, 0, Qt::AlignCenter);

    // Circular Shortcut Icons Row (ChatGPT, GitHub, hPanel, Google Gemini, DeepSeek, Kawerify Tech, Show more)
    auto* shortcutsLayout = new QHBoxLayout();
    shortcutsLayout->setSpacing(22);

    struct CircularShortcut { QString name; QString icon; QString url; };
    QList<CircularShortcut> shortcuts = {
        {"ChatGPT", "🤖", "https://chatgpt.com"},
        {"tonderaika...", "🐙", "https://github.com"},
        {"hPanel", "⚡", "https://hpanel.hostinger.com"},
        {"Google Gemini", "✨", "https://gemini.google.com"},
        {"DeepSeek", "🐳", "https://chat.deepseek.com"},
        {"Kawerify Tech", "🌐", "https://kawerifytech.com"},
        {"Show more", "+", "codebrowser://newtab"}
    };

    for (const auto& sc : shortcuts) {
        auto* container = new QVBoxLayout();
        container->setAlignment(Qt::AlignCenter);

        auto* btn = new QPushButton(sc.icon, this);
        btn->setFixedSize(54, 54);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setStyleSheet(R"(
            QPushButton {
                background-color: #382d47;
                color: #ffffff;
                border-radius: 27px;
                font-size: 20px;
                border: none;
            }
            QPushButton:hover {
                background-color: #4a3c5d;
            }
        )");

        auto* label = new QLabel(sc.name, this);
        label->setStyleSheet("color: #d0bcff; font-size: 12px; margin-top: 4px;");
        label->setAlignment(Qt::AlignCenter);

        connect(btn, &QPushButton::clicked, this, [this, url = sc.url]() {
            if (url != "codebrowser://newtab") emit searchRequested(url);
        });

        container->addWidget(btn, 0, Qt::AlignCenter);
        container->addWidget(label, 0, Qt::AlignCenter);

        shortcutsLayout->addLayout(container);
    }

    mainLayout->addLayout(shortcutsLayout);

    // "Continue with these tabs" bottom panel
    auto* continueCard = new QFrame(this);
    continueCard->setFixedWidth(680);
    continueCard->setStyleSheet(R"(
        QFrame {
            background-color: #362947;
            border-radius: 16px;
            padding: 14px;
        }
    )");

    auto* cardHeaderLayout = new QHBoxLayout(continueCard);
    auto* cardTitle = new QLabel("Continue with these tabs", continueCard);
    cardTitle->setStyleSheet("color: #ffffff; font-size: 15px; font-weight: bold;");

    auto* menuDot = new QLabel("⋮", continueCard);
    menuDot->setStyleSheet("color: #d0bcff; font-size: 18px; font-weight: bold;");

    cardHeaderLayout->addWidget(cardTitle);
    cardHeaderLayout->addStretch();
    cardHeaderLayout->addWidget(menuDot);

    mainLayout->addWidget(continueCard, 0, Qt::AlignCenter);

    outerLayout->addLayout(mainLayout);

    // Bottom Footer (Kawerify Tech Credits & Customize Button)
    auto* bottomLayout = new QHBoxLayout();
    bottomLayout->setContentsMargins(24, 8, 24, 16);

    auto* creditsLabel = new QLabel("Built by <b>Kawerify Tech</b> (<a href='https://kawerifytech.com' style='color:#d0bcff;'>kawerifytech.com</a> | <b>@kawerifytech</b> in all socials)", this);
    creditsLabel->setOpenExternalLinks(true);
    creditsLabel->setStyleSheet("color: #b3a0d9; font-size: 13px;");
    bottomLayout->addWidget(creditsLabel);

    bottomLayout->addStretch();

    m_adsBlockedLabel = new QLabel("Ads Blocked: 0", this);
    m_trackersBlockedLabel = new QLabel("Trackers: 0", this);
    m_adsBlockedLabel->setStyleSheet("color: #8ab4f8; font-size: 13px; font-weight: bold; margin-right: 10px;");
    m_trackersBlockedLabel->setStyleSheet("color: #81c995; font-size: 13px; font-weight: bold; margin-right: 15px;");

    bottomLayout->addWidget(m_adsBlockedLabel);
    bottomLayout->addWidget(m_trackersBlockedLabel);

    auto* customizeBtn = new QPushButton("✏️ Customize Chrome", this);
    customizeBtn->setCursor(Qt::PointingHandCursor);
    customizeBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #3b2c4e;
            color: #d0bcff;
            font-size: 13px;
            font-weight: bold;
            border-radius: 18px;
            padding: 8px 18px;
            border: 1px solid #4a3b60;
        }
        QPushButton:hover {
            background-color: #4a3763;
            color: #ffffff;
        }
    )");

    bottomLayout->addWidget(customizeBtn);
    outerLayout->addLayout(bottomLayout);
}

void NewTabPage::refreshStats() {
    auto& stats = AdBlockEngine::instance().statistics();
    m_adsBlockedLabel->setText(QString("Ads Blocked: %1").arg(stats.adsBlocked()));
    m_trackersBlockedLabel->setText(QString("Trackers Intercepted: %1").arg(stats.trackersBlocked()));
}

} // namespace codebrowser
