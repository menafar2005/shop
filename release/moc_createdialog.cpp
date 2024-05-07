/****************************************************************************
** Meta object code from reading C++ file 'createdialog.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../space-csv-database/src/createdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'createdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CreateDialog_t {
    const uint offsetsAndSize[28];
    char stringdata0[294];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_CreateDialog_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_CreateDialog_t qt_meta_stringdata_CreateDialog = {
    {
QT_MOC_LITERAL(0, 12), // "CreateDialog"
QT_MOC_LITERAL(13, 28), // "on_createNewDBButton_clicked"
QT_MOC_LITERAL(42, 0), // ""
QT_MOC_LITERAL(43, 23), // "on_saveDBButton_clicked"
QT_MOC_LITERAL(67, 26), // "on_addObjectButton_clicked"
QT_MOC_LITERAL(94, 28), // "on_clearFieldsButton_clicked"
QT_MOC_LITERAL(123, 22), // "on_applyButton_clicked"
QT_MOC_LITERAL(146, 22), // "on_closeButton_clicked"
QT_MOC_LITERAL(169, 31), // "on_typeList_currentIndexChanged"
QT_MOC_LITERAL(201, 5), // "index"
QT_MOC_LITERAL(207, 27), // "on_chooseFileButton_clicked"
QT_MOC_LITERAL(235, 26), // "on_tempSlider_valueChanged"
QT_MOC_LITERAL(262, 5), // "value"
QT_MOC_LITERAL(268, 25) // "on_popSlider_valueChanged"

    },
    "CreateDialog\0on_createNewDBButton_clicked\0"
    "\0on_saveDBButton_clicked\0"
    "on_addObjectButton_clicked\0"
    "on_clearFieldsButton_clicked\0"
    "on_applyButton_clicked\0on_closeButton_clicked\0"
    "on_typeList_currentIndexChanged\0index\0"
    "on_chooseFileButton_clicked\0"
    "on_tempSlider_valueChanged\0value\0"
    "on_popSlider_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreateDialog[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x08,    1 /* Private */,
       3,    0,   75,    2, 0x08,    2 /* Private */,
       4,    0,   76,    2, 0x08,    3 /* Private */,
       5,    0,   77,    2, 0x08,    4 /* Private */,
       6,    0,   78,    2, 0x08,    5 /* Private */,
       7,    0,   79,    2, 0x08,    6 /* Private */,
       8,    1,   80,    2, 0x08,    7 /* Private */,
      10,    0,   83,    2, 0x08,    9 /* Private */,
      11,    1,   84,    2, 0x08,   10 /* Private */,
      13,    1,   87,    2, 0x08,   12 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void CreateDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CreateDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_createNewDBButton_clicked(); break;
        case 1: _t->on_saveDBButton_clicked(); break;
        case 2: _t->on_addObjectButton_clicked(); break;
        case 3: _t->on_clearFieldsButton_clicked(); break;
        case 4: _t->on_applyButton_clicked(); break;
        case 5: _t->on_closeButton_clicked(); break;
        case 6: _t->on_typeList_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->on_chooseFileButton_clicked(); break;
        case 8: _t->on_tempSlider_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->on_popSlider_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CreateDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CreateDialog.offsetsAndSize,
    qt_meta_data_CreateDialog,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_CreateDialog_t
, QtPrivate::TypeAndForceComplete<CreateDialog, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>


>,
    nullptr
} };


const QMetaObject *CreateDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreateDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CreateDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int CreateDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
