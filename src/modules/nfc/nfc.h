#ifndef _NFC_H_
#define _NFC_H_
#include "../../api/def.h"
#include <Wire.h>
#include <PN532.h>
#include <PN532_I2C.h>
#include <NfcAdapter.h>

PN532_I2C pn532_I2C(Wire);
PN532 NFC_Reader(pn532_I2C);

namespace nfc
{
    extern uint32_t student_id[];
    bool init();
    bool canRead();
    void loadStudentID();
    uint32_t getStudentID();
    bool matchStudentID();
}

#endif