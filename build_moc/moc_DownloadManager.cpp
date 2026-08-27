/****************************************************************************
** Meta object code from reading C++ file 'DownloadManager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/ktbrowser/downloads/DownloadManager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DownloadManager.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN9ktbrowser15DownloadManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto ktbrowser::DownloadManager::qt_create_metaobjectdata<qt_meta_tag_ZN9ktbrowser15DownloadManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ktbrowser::DownloadManager",
        "downloadStarted",
        "",
        "DownloadItem",
        "item",
        "downloadUpdated",
        "downloadFinished"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'downloadStarted'
        QtMocHelpers::SignalData<void(const DownloadItem &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'downloadUpdated'
        QtMocHelpers::SignalData<void(const DownloadItem &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'downloadFinished'
        QtMocHelpers::SignalData<void(const DownloadItem &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DownloadManager, qt_meta_tag_ZN9ktbrowser15DownloadManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ktbrowser::DownloadManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9ktbrowser15DownloadManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9ktbrowser15DownloadManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN9ktbrowser15DownloadManagerE_t>.metaTypes,
    nullptr
} };

void ktbrowser::DownloadManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DownloadManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->downloadStarted((*reinterpret_cast<std::add_pointer_t<DownloadItem>>(_a[1]))); break;
        case 1: _t->downloadUpdated((*reinterpret_cast<std::add_pointer_t<DownloadItem>>(_a[1]))); break;
        case 2: _t->downloadFinished((*reinterpret_cast<std::add_pointer_t<DownloadItem>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (DownloadManager::*)(const DownloadItem & )>(_a, &DownloadManager::downloadStarted, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (DownloadManager::*)(const DownloadItem & )>(_a, &DownloadManager::downloadUpdated, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (DownloadManager::*)(const DownloadItem & )>(_a, &DownloadManager::downloadFinished, 2))
            return;
    }
}

const QMetaObject *ktbrowser::DownloadManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ktbrowser::DownloadManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9ktbrowser15DownloadManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ktbrowser::DownloadManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ktbrowser::DownloadManager::downloadStarted(const DownloadItem & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void ktbrowser::DownloadManager::downloadUpdated(const DownloadItem & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void ktbrowser::DownloadManager::downloadFinished(const DownloadItem & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}
QT_WARNING_POP
