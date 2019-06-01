/**
 * ----------------------------------------------------------------------------
 * NOTE: The library file MFRC522.h has a lot of useful info. Please read it.
 *
 * Released into the public domain.
 * ----------------------------------------------------------------------------
 * This sample shows get data from flash and then write the data on a MIFARE Classic PICC
 * (= card/tag).
 *
 * BEWARE: Data will be written to the PICC, in sector #3 (blocks #A).
 *
 *
 * Typical pin layout used:
 * ---------------------------------------
 *             MFRC522      Arduino       
 *             Reader/PCD   Uno/101       
 * Signal      Pin          Pin           
 * ---------------------------------------
 * RST/Reset   RST          9             
 * SPI SS      SDA(SS)      10            
 * SPI MOSI    MOSI         11 / ICSP-4   
 * SPI MISO    MISO         12 / ICSP-1   
 * SPI SCK     SCK          13 / ICSP-3   
 *
 */

#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>

#define RST_PIN         4           // Configurable, see typical pin layout above
#define SS_PIN          3          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

MFRC522::MIFARE_Key key;

/**
 * key.
 */
  const byte MFRC_KEY_V0_0[][MFRC522::MF_KEY_SIZE] = {
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},   // S0
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},   // S1
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},   // S2
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},   // S3
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},   // S4
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},   // S5
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},   // S6
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},   // S7
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},   // S8
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},   // S9
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},   // SA
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},   // SB
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},   // SC
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},   // SD
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},   // SE
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}    // SF
};

/**  
 *   Firma
 */
const char sign_course[] PROGMEM = {"¡Sobresaliente!"};

byte dataBlock[]    = {
        0x44, 0x65, 0x66, 0x61, //  D,  e,   f,  a,
        0x75, 0x6C, 0x74, 0x20, //  u,  l,   t,   ,
        0x6D, 0x65, 0x73, 0x73, //  m, s, s, a,
        0x61, 0x67, 0x65, 0x20  // g, e,  ,  
};


// In this sample we use the second sector,
// that is: sector #3, covering block #8 up to and including block #11
byte sector         = 3;
byte blockAddr      = 8;
byte trailerBlock   = 11;

/**
 * Initialize.
 */
void setup() {
    
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card

    // Read the phrase from flash and compose the sign for sector A:
   for (byte k = 0; k < strlen_P(sign_course); k++) {
      dataBlock[k] = pgm_read_byte_near(sign_course + k);
   }
    // Prepare the key (used both as key A and as key B)
    // using FFFFFFFFFFFFh which is the default at chip delivery from the factory
    for (byte i = 0; i < MFRC522::MF_KEY_SIZE; i++) {
        key.keyByte[i] = 0xFF;
        //key.keyByte[i] = pgm_read_byte_near(MFRC_KEY_V0_0+ MFRC522::MF_KEY_SIZE*sector + i);
    }
}

/**
 * Main loop.
 */
void loop() {
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if ( ! mfrc522.PICC_IsNewCardPresent())
        return;

    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial())
        return;

    // Show some details of the PICC (that is: the tag/card)
    MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);

    // Check for compatibility
    if (    piccType != MFRC522::PICC_TYPE_MIFARE_MINI
        &&  piccType != MFRC522::PICC_TYPE_MIFARE_1K
        &&  piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
        return;
    }
    
    MFRC522::StatusCode status;
//    byte buffer[18];
//    byte size = sizeof(buffer);
    
    // Authenticate using key B
    status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        return;
    }

    // Write data to the block
    status = (MFRC522::StatusCode) mfrc522.MIFARE_Write(blockAddr, dataBlock, 16);
    if (status != MFRC522::STATUS_OK) {
    }
    
    // Halt PICC
    mfrc522.PICC_HaltA();
    // Stop encryption on PCD
    mfrc522.PCD_StopCrypto1();
}
