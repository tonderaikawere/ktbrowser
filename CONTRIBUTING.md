# Contributing to KT Browser

Thank you for your interest in contributing to **KT Browser** by **Kawerify Tech**!

## 🚀 How to Contribute

1. **Fork the Repository**: Create your own branch from `main`.
2. **Setup Development Environment**:
   - Install Python 3.10+ and `pip install -r requirements.txt`.
   - Install C++ compiler (MSYS2 / GCC 16+ or Clang) and Qt 6.x.
3. **Make Changes**:
   - Follow standard C++20 / PyQt6 conventions.
   - Keep UI design consistent with standard KT Browser UI guidelines by Kawerify Tech.
4. **Run Tests**:
   - Ensure all unit tests pass before submitting a pull request:
     ```bash
     python ktbrowser_qt6.py
     ```
5. **Submit a Pull Request**: Provide a clear explanation of changes and linked issue numbers.

## 📜 Code Style & Principles

- **Security First**: All user data must be isolated locally in SQLite/JSON. No unwanted telemetry.
- **Aesthetics**: Premium, modern KT Browser UI theme (`#4a80cb` tab bar, `#dee1e6` toolbar, `#382d47` new tab dark cards).
- **Clean Contracts**: Ensure all header `.h` declarations match `.cpp` implementations.

Thank you for building with **Kawerify Tech** ([https://kawerifytech.com](https://kawerifytech.com))!
