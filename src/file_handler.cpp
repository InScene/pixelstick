/*
  Copyright Christian Mertens 2022
*/
#include "file_handler.h"
#include <Arduino.h>

PROGMEM const unsigned char gammaTable[]  = {
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,
  2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,
  4,  4,  4,  4,  5,  5,  5,  5,  5,  6,  6,  6,  6,  6,  7,  7,
  7,  7,  7,  8,  8,  8,  8,  9,  9,  9,  9, 10, 10, 10, 10, 11,
  11, 11, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 15, 15, 16, 16,
  16, 17, 17, 17, 18, 18, 18, 19, 19, 20, 20, 21, 21, 21, 22, 22,
  23, 23, 24, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30,
  30, 31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 37, 37, 38, 38, 39,
  40, 40, 41, 41, 42, 43, 43, 44, 45, 45, 46, 47, 47, 48, 49, 50,
  50, 51, 52, 52, 53, 54, 55, 55, 56, 57, 58, 58, 59, 60, 61, 62,
  62, 63, 64, 65, 66, 67, 67, 68, 69, 70, 71, 72, 73, 74, 74, 75,
  76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
  92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 104, 105, 106, 107, 108,
  109, 110, 111, 113, 114, 115, 116, 117, 118, 120, 121, 122, 123, 125, 126, 127
};

FileHandler::FileHandler(StripHandler& strip) :
  stripHandler(strip),
  fileIndex(0),
  nbOfFiles(0)
{
  
}

bool FileHandler::setup()
{
  pinMode(SDssPin, OUTPUT);

  while (!SD.begin(SDssPin)) {
    // SD init failed    
    return false;
  }
  
  return  true;
}

void FileHandler::scanForFiles()
{
  root = SD.open("/");
  getFileNamesFromSD(root);
  isort(fileNames, nbOfFiles);
}

String FileHandler::getFilename() const
{
  return fileNames[fileIndex];
}

FileHandler::ErrorCode FileHandler::sendFile(const String& Filename, 
                                             const uint8_t brightness,
                                             const unsigned long frameDelay)
{
  ErrorCode error = NO_ERROR;
  char temp[14];
  Filename.toCharArray(temp, 14);
  dataFile = SD.open(temp);

  // if the file is available send it to the LED's
  if (dataFile) {
    error = read_the_file(brightness, frameDelay);
    dataFile.close();
  }
  else {
    error = FILE_READ_ERROR;
    setup();
  }

  return error;
}

void FileHandler::selectNextFile()
{
  if (fileIndex < nbOfFiles - 1) {
    fileIndex++;
  }
  else {
    fileIndex = 0;                // On the last file so wrap round to the first file
  }
}

void FileHandler::selectPreviousFile()
{
  if (fileIndex > 0) {
    fileIndex--;
  }
  else {
    fileIndex = nbOfFiles - 1;   // On the last file so wrap round to the first file
  }
}

FileHandler::ErrorCode FileHandler::read_the_file(const uint8_t brightness, 
                                                  const unsigned long frameDelay)
{
  #define MYBMP_BF_TYPE           0x4D42
  #define MYBMP_BF_OFF_BITS       54
  #define MYBMP_BI_SIZE           40
  #define MYBMP_BI_RGB            0L
  #define MYBMP_BI_RLE8           1L
  #define MYBMP_BI_RLE4           2L
  #define MYBMP_BI_BITFIELDS      3L

  ErrorCode error = NO_ERROR;

  uint16_t bmpType = readInt();
  uint32_t bmpSize = readLong();       // Do not remove. The data must be read to comply with the sequence
  uint16_t bmpReserved1 = readInt();   // Do not remove. The data must be read to comply with the sequence
  uint16_t bmpReserved2 = readInt();   // Do not remove. The data must be read to comply with the sequence
  uint32_t bmpOffBits = readLong();
  bmpOffBits = 54;

  // Suppress compiler warning for unused variables
  (void)bmpSize;
  (void)bmpReserved1;
  (void)bmpReserved2;

  /* Check file header */
  if (bmpType != MYBMP_BF_TYPE || bmpOffBits != MYBMP_BF_OFF_BITS) {
    error = FILE_NOT_A_BITMAP;
    return error;
  }

  /* Read info header */
  uint32_t imgSize = readLong();
  uint32_t imgWidth = readLong();
  uint32_t imgHeight = readLong();
  uint16_t imgPlanes = readInt();
  uint16_t imgBitCount = readInt();
  uint32_t imgCompression = readLong();
  uint32_t imgSizeImage = readLong();
  uint32_t imgXPelsPerMeter = readLong();  // Do not remove. The data must be read to comply with the sequence
  uint32_t imgYPelsPerMeter = readLong();  // Do not remove. The data must be read to comply with the sequence
  uint32_t imgClrUsed = readLong();        // Do not remove. The data must be read to comply with the sequence
  uint32_t imgClrImportant = readLong();   // Do not remove. The data must be read to comply with the sequence

  // Suppress compiler warning for unused variables
  (void)imgXPelsPerMeter;
  (void)imgYPelsPerMeter;
  (void)imgClrUsed;
  (void)imgClrImportant;

  /* Check info header */
  if ( imgSize != MYBMP_BI_SIZE || imgWidth <= 0 ||
       imgHeight <= 0 || imgPlanes != 1 ||
       imgBitCount != 24 || imgCompression != MYBMP_BI_RGB ||
       imgSizeImage == 0 )
  {
    error = UNSUPPORTED_BITMAP;
    return error;
  }

  int displayWidth = imgWidth;
  if (imgWidth > STRIP_LENGTH) {
    displayWidth = STRIP_LENGTH;           //only display the number of led's we have
  }

  /* compute the line length */
  uint32_t lineLength = imgWidth * 3;
  if ((lineLength % 4) != 0)
    lineLength = (lineLength / 4 + 1) * 4;

  for (int y = imgHeight; y > 0; y--) {
    for (int x = 0; x < displayWidth; x++) {
      uint32_t offset = (MYBMP_BF_OFF_BITS + (((y - 1) * lineLength) + (x * 3))) ;
      dataFile.seek(offset);

      rgbValues rgbVal = getRGBwithGamma(brightness);

    // TODO: Outsourde strip value call
      stripHandler.setPixelColor(x, rgbVal.r, rgbVal.g, rgbVal.b);
    }
    // TODO: outsource latchanddelay call
    stripHandler.latchanddelay(frameDelay);
  }

  return error;
}

void FileHandler::getFileNamesFromSD(File dir) {
  int fileCount = 0;
  String CurrentFilename = "";
  while (1) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      nbOfFiles = fileCount;
      entry.close();
      break;
    }
    else {
      if (entry.isDirectory()) {
      }
      else {
        CurrentFilename = entry.name();
        if (CurrentFilename.endsWith(".bmp") || CurrentFilename.endsWith(".BMP") ) { //find files with our extension only
          fileNames[fileCount] = entry.name();
          fileCount++;
        }
      }
    }
    entry.close();
  }
}

uint32_t FileHandler::readLong() {
  uint32_t retValue;
  byte incomingbyte;

  incomingbyte = readByte();
  retValue = (uint32_t)((byte)incomingbyte);

  incomingbyte = readByte();
  retValue += (uint32_t)((byte)incomingbyte) << 8;

  incomingbyte = readByte();
  retValue += (uint32_t)((byte)incomingbyte) << 16;

  incomingbyte = readByte();
  retValue += (uint32_t)((byte)incomingbyte) << 24;

  return retValue;
}

uint16_t FileHandler::readInt() {
  byte incomingbyte = 0;
  uint16_t retValue = 0;
  incomingbyte = readByte();
  retValue += (uint16_t)((byte)incomingbyte);
  incomingbyte = readByte();
  retValue += (uint16_t)((byte)incomingbyte) << 8;
  return retValue;
}

int FileHandler::readByte() {
  int retbyte = -1;
  while (retbyte < 0) retbyte = dataFile.read();
  return retbyte;
}

// Sort the filenames in alphabetical order
void FileHandler::isort(String * filenames, int n) {
  for (int i = 1; i < n; ++i) {
    String j = filenames[i];
    int k;
    for (k = i - 1; (k >= 0) && (j < filenames[k]); k--) {
      filenames[k + 1] = filenames[k];
    }
    filenames[k + 1] = j;
  }
}

// TODO: Cancel dependence on brightness
FileHandler::rgbValues FileHandler::getRGBwithGamma(const uint8_t brightness) {
  rgbValues values;
  values.g = gamma(readByte()) / (101 - brightness);
  values.b = gamma(readByte()) / (101 - brightness);
  values.r = gamma(readByte()) / (101 - brightness);

  return values;
}

byte FileHandler::gamma(byte x)
{
  return pgm_read_byte(&gammaTable[x]);
}