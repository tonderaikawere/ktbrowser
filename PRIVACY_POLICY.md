# Privacy Policy for KT Browser (Kawerify Tech)

**Effective Date:** August 25, 2026  
**Publisher:** Kawerify Tech ([https://kawerifytech.com](https://kawerifytech.com))  
**Socials:** @kawerifytech  

---

## 1. Executive Summary
KT Browser ("KT" standing for **Kawerify Tech**) is built with a zero-telemetry, privacy-first architecture. We do not collect, track, monetize, or transmit your personal browsing history, search queries, IP address, or behavioral data.

---

## 2. Data Storage & Isolation
- **Local SQLite Encrypted Storage:** All bookmarks, history, download logs, and settings are stored locally on your device in your isolated user profile directory (`%LOCALAPPDATA%\KTBrowser\data\`).
- **No Cloud Syncing without Consent:** KT Browser operates entirely offline for browser metadata.

---

## 3. Network Protection & Tracking Blockers
- **Ad & Tracker Interception:** Built-in `QWebEngineUrlRequestInterceptor` filters out third-party advertising scripts, telemetry endpoints, and fingerprinting trackers at the network protocol layer.
- **Do Not Track (DNT) & GPC Signals:** KT Browser automatically attaches `DNT: 1` and `Sec-GPC: 1` headers to outbound network requests.

---

## 4. Third-Party Web Content
When loading third-party web pages, connections are established directly between your device and the destination server. HTTPS encryption is enforced by default.

---

## 5. Contact & Support
For security inquiries or privacy disclosures, contact Kawerify Tech:
- **Website:** [https://kawerifytech.com](https://kawerifytech.com)
- **Social Media:** @kawerifytech
