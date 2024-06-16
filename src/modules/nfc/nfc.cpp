#include "nfc.h"
#include "../preferences/preferences.h"

bool nfc::init()
{
    uint32_t versiondata = NFC_Reader.getFirmwareVersion();
    if (!versiondata)
        return false;

    NFC_Reader.setPassiveActivationRetries(0xFF);
    NFC_Reader.SAMConfig();

    return true;
}

void nfc::loadStudentID()
{
    String id = preferences::get("student_id");
    uint16_t length = id.length();
    if (id[length - 1] != ',')
    {
        id += ",";
    }
    uint16_t start = 0;
    uint16_t end = id.indexOf(',');
    uint16_t i = 0;
    while (end != -1)
    {
        student_id[i] = id.substring(start, end).toInt();
        start = end + 1;
        end = id.indexOf(',', start);
        i++;
    }
    nfc::student_id[i] = 0;
}

uint32_t nfc::getStudentID()
{
    char id[11] = "0000000000";
    uint8_t success;
    uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0};
    uint8_t uidLength;
    uint8_t keya[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    uint8_t block = 60;
    uint8_t data[16];

    success = NFC_Reader.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

    if (success)
    {
        success = NFC_Reader.mifareclassic_AuthenticateBlock(uid, uidLength, block, 0, keya);
        if (success)
        {
            success = NFC_Reader.mifareclassic_ReadDataBlock(block, data);
            if (success)
            {
                for (int i = 0; i < 10; i++)
                {
                    id[i] = data[i];
                }
#ifdef DEBUG
                Serial.println("NFC Read Student ID: " + String(id));
#endif
            }
        }
    }
    return atoi(id);
}

bool nfc::matchStudentID()
{
    uint32_t id = nfc::getStudentID();
    for (uint16_t i = 0; nfc::student_id[i] != 0; i++)
    {
        if (id == nfc::student_id[i])
        {
            return true;
        }
    }
    return false;
}

bool nfc::canRead()
{
    uint8_t success;
    uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0};
    uint8_t uidLength;

    success = NFC_Reader.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

    return success;
}