/****************************************************************************
** Meta object code from reading C++ file 'teacher_portal.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../teacher_portal.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'teacher_portal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.0. It"
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

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSteacher_portalENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSteacher_portalENDCLASS = QtMocHelpers::stringData(
    "teacher_portal",
    "back",
    "",
    "send_time_changed",
    "time",
    "send_stu_status",
    "username",
    "s",
    "read",
    "show_graph",
    "shut",
    "initial",
    "mode",
    "add_course",
    "delete_course",
    "cancel",
    "back_to_login",
    "set_time",
    "list_student",
    "stu_forbid",
    "name"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSteacher_portalENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   98,    2, 0x06,    1 /* Public */,
       3,    1,   99,    2, 0x06,    2 /* Public */,
       5,    2,  102,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    0,  107,    2, 0x08,    7 /* Private */,
       9,    0,  108,    2, 0x08,    8 /* Private */,
      10,    0,  109,    2, 0x08,    9 /* Private */,
      11,    1,  110,    2, 0x08,   10 /* Private */,
      13,    0,  113,    2, 0x08,   12 /* Private */,
      14,    0,  114,    2, 0x08,   13 /* Private */,
      15,    0,  115,    2, 0x08,   14 /* Private */,
      16,    0,  116,    2, 0x08,   15 /* Private */,
      17,    0,  117,    2, 0x08,   16 /* Private */,
      18,    0,  118,    2, 0x08,   17 /* Private */,
      19,    1,  119,    2, 0x08,   18 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   20,

       0        // eod
};

Q_CONSTINIT const QMetaObject teacher_portal::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSteacher_portalENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSteacher_portalENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSteacher_portalENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<teacher_portal, std::true_type>,
        // method 'back'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'send_time_changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'send_stu_status'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'read'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'show_graph'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'shut'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'initial'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'add_course'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'delete_course'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cancel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'back_to_login'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'set_time'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'list_student'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stu_forbid'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>
    >,
    nullptr
} };

void teacher_portal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<teacher_portal *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->back(); break;
        case 1: _t->send_time_changed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->send_stu_status((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 3: _t->read(); break;
        case 4: _t->show_graph(); break;
        case 5: _t->shut(); break;
        case 6: _t->initial((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->add_course(); break;
        case 8: _t->delete_course(); break;
        case 9: _t->cancel(); break;
        case 10: _t->back_to_login(); break;
        case 11: _t->set_time(); break;
        case 12: _t->list_student(); break;
        case 13: _t->stu_forbid((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (teacher_portal::*)();
            if (_t _q_method = &teacher_portal::back; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (teacher_portal::*)(int );
            if (_t _q_method = &teacher_portal::send_time_changed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (teacher_portal::*)(QString , bool );
            if (_t _q_method = &teacher_portal::send_stu_status; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *teacher_portal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *teacher_portal::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSteacher_portalENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int teacher_portal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void teacher_portal::back()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void teacher_portal::send_time_changed(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void teacher_portal::send_stu_status(QString _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
