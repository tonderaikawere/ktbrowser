/****************************************************************************
** Meta object code from reading C++ file 'BrowserToolbar.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/ktbrowser/ui/BrowserToolbar.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BrowserToolbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN9ktbrowser14BrowserToolbarE_t {};
} // unnamed namespace

template <> constexpr inline auto ktbrowser::BrowserToolbar::qt_create_metaobjectdata<qt_meta_tag_ZN9ktbrowser14BrowserToolbarE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ktbrowser::BrowserToolbar",
        "backRequested",
        "",
        "forwardRequested",
        "reloadRequested",
        "stopRequested",
        "homeRequested",
        "bookmarkRequested",
        "historyRequested",
        "privacyDashboardRequested",
        "downloadsRequested",
        "settingsRequested"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'backRequested'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'forwardRequested'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'reloadRequested'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'stopRequested'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'homeRequested'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'bookmarkRequested'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'historyRequested'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'privacyDashboardRequested'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'downloadsRequested'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'settingsRequested'
        QtMocHelpers::SignalData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<BrowserToolbar, qt_meta_tag_ZN9ktbrowser14BrowserToolbarE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ktbrowser::BrowserToolbar::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9ktbrowser14BrowserToolbarE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9ktbrowser14BrowserToolbarE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN9ktbrowser14BrowserToolbarE_t>.metaTypes,
    nullptr
} };

void ktbrowser::BrowserToolbar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<BrowserToolbar *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->backRequested(); break;
        case 1: _t->forwardRequested(); break;
        case 2: _t->reloadRequested(); break;
        case 3: _t->stopRequested(); break;
        case 4: _t->homeRequested(); break;
        case 5: _t->bookmarkRequested(); break;
        case 6: _t->historyRequested(); break;
        case 7: _t->privacyDashboardRequested(); break;
        case 8: _t->downloadsRequested(); break;
        case 9: _t->settingsRequested(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (BrowserToolbar::*)()>(_a, &BrowserToolbar::backRequested, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (BrowserToolbar::*)()>(_a, &BrowserToolbar::forwardRequested, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (BrowserToolbar::*)()>(_a, &BrowserToolbar::reloadRequested, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (BrowserToolbar::*)()>(_a, &BrowserToolbar::stopRequested, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (BrowserToolbar::*)()>(_a, &BrowserToolbar::homeRequested, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (BrowserToolbar::*)()>(_a, &BrowserToolbar::bookmarkRequested, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (BrowserToolbar::*)()>(_a, &BrowserToolbar::historyRequested, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (BrowserToolbar::*)()>(_a, &BrowserToolbar::privacyDashboardRequested, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (BrowserToolbar::*)()>(_a, &BrowserToolbar::downloadsRequested, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (BrowserToolbar::*)()>(_a, &BrowserToolbar::settingsRequested, 9))
            return;
    }
}

const QMetaObject *ktbrowser::BrowserToolbar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ktbrowser::BrowserToolbar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9ktbrowser14BrowserToolbarE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ktbrowser::BrowserToolbar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void ktbrowser::BrowserToolbar::backRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ktbrowser::BrowserToolbar::forwardRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ktbrowser::BrowserToolbar::reloadRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ktbrowser::BrowserToolbar::stopRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ktbrowser::BrowserToolbar::homeRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ktbrowser::BrowserToolbar::bookmarkRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void ktbrowser::BrowserToolbar::historyRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void ktbrowser::BrowserToolbar::privacyDashboardRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void ktbrowser::BrowserToolbar::downloadsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void ktbrowser::BrowserToolbar::settingsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}
QT_WARNING_POP
