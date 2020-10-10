/****************************************************************************
** Meta object code from reading C++ file 'qzeroconfservice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qtzeroconf/qzeroconfservice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qzeroconfservice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QZeroConfServiceData_t {
    QByteArrayData data[5];
    char stringdata0[43];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QZeroConfServiceData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QZeroConfServiceData_t qt_meta_stringdata_QZeroConfServiceData = {
    {
QT_MOC_LITERAL(0, 0, 20), // "QZeroConfServiceData"
QT_MOC_LITERAL(1, 21, 4), // "name"
QT_MOC_LITERAL(2, 26, 4), // "type"
QT_MOC_LITERAL(3, 31, 6), // "domain"
QT_MOC_LITERAL(4, 38, 4) // "host"

    },
    "QZeroConfServiceData\0name\0type\0domain\0"
    "host"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QZeroConfServiceData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       4,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QString, 0x00095001,
       2, QMetaType::QString, 0x00095001,
       3, QMetaType::QString, 0x00095001,
       4, QMetaType::QString, 0x00095001,

       0        // eod
};

void QZeroConfServiceData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        QZeroConfServiceData *_t = reinterpret_cast<QZeroConfServiceData *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->name(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->type(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->domain(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->host(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject QZeroConfServiceData::staticMetaObject = {
    { nullptr, qt_meta_stringdata_QZeroConfServiceData.data,
      qt_meta_data_QZeroConfServiceData,  qt_static_metacall, nullptr, nullptr}
};

QT_WARNING_POP
QT_END_MOC_NAMESPACE
