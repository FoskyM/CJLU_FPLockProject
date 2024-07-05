#ifndef _NFC_H_
#define _NFC_H_
#include "../../api/def.h"
#include <Wire.h>
#include <PN532.h>
#include <PN532_I2C.h>
#include <NfcAdapter.h>

extern PN532_I2C pn532_I2C;
extern PN532 NFC_Reader;

namespace nfc
{
    extern bool loaded;
    extern uint32_t student_id[50];
    bool init();
    bool canRead();
    void loadStudentID();
    uint32_t getStudentID();
    bool matchStudentID();
    // bool matchConfigMode();
}

#endif