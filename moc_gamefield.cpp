/****************************************************************************
** Meta object code from reading C++ file 'gamefield.h'
**
** Created: Thu Mar 8 20:03:26 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gamefield.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamefield.h' doesn't include <QObject>."
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GameField[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   11,   10,   10, 0x08,
      67,   10,   63,   10, 0x08,
      76,   10,   10,   10, 0x08,
     105,   96,   10,   10, 0x08,
     130,   10,   10,   10, 0x08,
     156,   10,   10,   10, 0x08,
     182,   10,   10,   10, 0x08,
     208,   10,   10,   10, 0x08,
     234,   10,   10,   10, 0x08,
     260,   10,   10,   10, 0x08,
     286,   10,   10,   10, 0x08,
     312,   10,   10,   10, 0x08,
     338,   10,   10,   10, 0x08,
     364,   10,   10,   10, 0x08,
     390,   10,   10,   10, 0x08,
     416,   10,   10,   10, 0x08,
     442,   10,   10,   10, 0x08,
     468,   10,   10,   10, 0x08,
     494,   10,   10,   10, 0x08,
     520,   10,   10,   10, 0x08,
     546,   10,   10,   10, 0x08,
     572,   10,   10,   10, 0x08,
     598,   10,   10,   10, 0x08,
     624,   10,   10,   10, 0x08,
     650,   10,   10,   10, 0x08,
     676,   10,   10,   10, 0x08,
     702,   10,   10,   10, 0x08,
     728,   10,   10,   10, 0x08,
     754,   10,   10,   10, 0x08,
     780,   10,   10,   10, 0x08,
     806,   10,   10,   10, 0x08,
     832,   10,   10,   10, 0x08,
     858,   10,   10,   10, 0x08,
     884,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GameField[] = {
    "GameField\0\0pos\0"
    "on_gameField_customContextMenuRequested(QPoint)\0"
    "int\0random()\0updateNamesLabels()\0"
    "playerId\0recreatePlayerLabel(int)\0"
    "on_button_1_100_clicked()\0"
    "on_button_2_100_clicked()\0"
    "on_button_3_100_clicked()\0"
    "on_button_4_100_clicked()\0"
    "on_button_5_100_clicked()\0"
    "on_button_6_100_clicked()\0"
    "on_button_1_200_clicked()\0"
    "on_button_2_200_clicked()\0"
    "on_button_3_200_clicked()\0"
    "on_button_4_200_clicked()\0"
    "on_button_5_200_clicked()\0"
    "on_button_6_200_clicked()\0"
    "on_button_1_300_clicked()\0"
    "on_button_2_300_clicked()\0"
    "on_button_3_300_clicked()\0"
    "on_button_4_300_clicked()\0"
    "on_button_5_300_clicked()\0"
    "on_button_6_300_clicked()\0"
    "on_button_1_400_clicked()\0"
    "on_button_2_400_clicked()\0"
    "on_button_3_400_clicked()\0"
    "on_button_4_400_clicked()\0"
    "on_button_5_400_clicked()\0"
    "on_button_6_400_clicked()\0"
    "on_button_1_500_clicked()\0"
    "on_button_2_500_clicked()\0"
    "on_button_3_500_clicked()\0"
    "on_button_4_500_clicked()\0"
    "on_button_5_500_clicked()\0"
    "on_button_6_500_clicked()\0"
};

const QMetaObject GameField::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GameField,
      qt_meta_data_GameField, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GameField::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GameField::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GameField::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GameField))
        return static_cast<void*>(const_cast< GameField*>(this));
    return QDialog::qt_metacast(_clname);
}

int GameField::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_gameField_customContextMenuRequested((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 1: { int _r = random();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 2: updateNamesLabels(); break;
        case 3: recreatePlayerLabel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: on_button_1_100_clicked(); break;
        case 5: on_button_2_100_clicked(); break;
        case 6: on_button_3_100_clicked(); break;
        case 7: on_button_4_100_clicked(); break;
        case 8: on_button_5_100_clicked(); break;
        case 9: on_button_6_100_clicked(); break;
        case 10: on_button_1_200_clicked(); break;
        case 11: on_button_2_200_clicked(); break;
        case 12: on_button_3_200_clicked(); break;
        case 13: on_button_4_200_clicked(); break;
        case 14: on_button_5_200_clicked(); break;
        case 15: on_button_6_200_clicked(); break;
        case 16: on_button_1_300_clicked(); break;
        case 17: on_button_2_300_clicked(); break;
        case 18: on_button_3_300_clicked(); break;
        case 19: on_button_4_300_clicked(); break;
        case 20: on_button_5_300_clicked(); break;
        case 21: on_button_6_300_clicked(); break;
        case 22: on_button_1_400_clicked(); break;
        case 23: on_button_2_400_clicked(); break;
        case 24: on_button_3_400_clicked(); break;
        case 25: on_button_4_400_clicked(); break;
        case 26: on_button_5_400_clicked(); break;
        case 27: on_button_6_400_clicked(); break;
        case 28: on_button_1_500_clicked(); break;
        case 29: on_button_2_500_clicked(); break;
        case 30: on_button_3_500_clicked(); break;
        case 31: on_button_4_500_clicked(); break;
        case 32: on_button_5_500_clicked(); break;
        case 33: on_button_6_500_clicked(); break;
        default: ;
        }
        _id -= 34;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
