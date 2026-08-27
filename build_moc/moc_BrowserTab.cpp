/****************************************************************************
** Meta object code from reading C++ file 'BrowserTab.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/ktbrowser/browser/BrowserTab.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BrowserTab.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN9ktbrowser10BrowserTabE_t {};
} // unnamed namespace

template <> constexpr inline auto ktbrowser::BrowserTab::qt_create_metaobjectdata<qt_meta_tag_ZN9ktbrowser10BrowserTabE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ktbrowser::BrowserTab",
        "titleChanged",
        "",
        "title",
        "iconChanged",
        "QIcon",
        "icon",
        "urlChanged",
        "QUrl",
        "url",
        "loadStarted",
        "loadFinished",
        "success",
        "loadProgress",
        "progress"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'titleChanged'
        QtMocHelpers::SignalData<void(const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'iconChanged'
        QtMocHelpers::SignalData<void(const QIcon &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 },
        }}),
        // Signal 'urlChanged'
        QtMocHelpers::SignalData<void(const QUrl &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Signal 'loadStarted'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'loadFinished'
        QtMocHelpers::SignalData<void(bool)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 12 },
        }}),
        // Signal 'loadProgress'
        QtMocHelpers::SignalData<void(int)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 14 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<BrowserTab, qt_meta_tag_ZN9ktbrowser10BrowserTabE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ktbrowser::BrowserTab::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9ktbrowser10BrowserTabE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9ktbrowser10BrowserTabE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN9ktbrowser10BrowserTabE_t>.metaTypes,
    nullptr
} };

void ktbrowser::BrowserTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<BrowserTab *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->titleChanged((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->iconChanged((*reinterpret_cast<std::add_pointer_t<QIcon>>(_a[1]))); break;
        case 2: _t->urlChanged((*reinterpret_cast<std::add_pointer_t<QUrl>>(_a[1]))); break;
        case 3: _t->loadStarted(); break;
        case 4: _t->loadFinished((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->loadProgress((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (BrowserTab::*)(const QString & )>(_a, &BrowserTab::titleChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (BrowserTab::*)(const QIcon & )>(_a, &BrowserTab::iconChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (BrowserTab::*)(const QUrl & )>(_a, &BrowserTab::urlChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (BrowserTab::*)()>(_a, &BrowserTab::loadStarted, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (BrowserTab::*)(bool )>(_a, &BrowserTab::loadFinished, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (BrowserTab::*)(int )>(_a, &BrowserTab::loadProgress, 5))
            return;
    }
}

const QMetaObject *ktbrowser::BrowserTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ktbrowser::BrowserTab::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9ktbrowser10BrowserTabE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ktbrowser::BrowserTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ktbrowser::BrowserTab::titleChanged(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void ktbrowser::BrowserTab::iconChanged(const QIcon & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void ktbrowser::BrowserTab::urlChanged(const QUrl & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void ktbrowser::BrowserTab::loadStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ktbrowser::BrowserTab::loadFinished(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void ktbrowser::BrowserTab::loadProgress(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}
QT_WARNING_POP
