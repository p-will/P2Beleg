/****************************************************************************
** Meta object code from reading C++ file 'tabelle.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Tabelle/tabelle.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tabelle.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_tabelleWindow_t {
    QByteArrayData data[9];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tabelleWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tabelleWindow_t qt_meta_stringdata_tabelleWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "tabelleWindow"
QT_MOC_LITERAL(1, 14, 8), // "neuladen"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 9), // "speichern"
QT_MOC_LITERAL(4, 34, 9), // "aenderung"
QT_MOC_LITERAL(5, 44, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(6, 62, 8), // "loeschen"
QT_MOC_LITERAL(7, 71, 6), // "insert"
QT_MOC_LITERAL(8, 78, 9) // "ausleihen"

    },
    "tabelleWindow\0neuladen\0\0speichern\0"
    "aenderung\0QTableWidgetItem*\0loeschen\0"
    "insert\0ausleihen"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tabelleWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    1,   46,    2, 0x08 /* Private */,
       6,    0,   49,    2, 0x08 /* Private */,
       7,    0,   50,    2, 0x08 /* Private */,
       8,    0,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void tabelleWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tabelleWindow *_t = static_cast<tabelleWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->neuladen(); break;
        case 1: _t->speichern(); break;
        case 2: _t->aenderung((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->loeschen(); break;
        case 4: _t->insert(); break;
        case 5: _t->ausleihen(); break;
        default: ;
        }
    }
}

const QMetaObject tabelleWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_tabelleWindow.data,
      qt_meta_data_tabelleWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *tabelleWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tabelleWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_tabelleWindow.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Ui::tabelleWindow"))
        return static_cast< Ui::tabelleWindow*>(this);
    return QDialog::qt_metacast(_clname);
}

int tabelleWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
