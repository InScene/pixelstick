/*
  Copyright Christian Mertens 2022
*/
#ifndef __FILE_HANDLER_H__
#define __FILE_HANDLER_H__

#include <SD.h>                          // Library for the SD Card
#include <strip_handler.h>

#define SDssPin 53                        // SD card CS pin
#define STRIP_LENGTH 144                  // Set the number of LEDs the LED Strip
#define MAX_FILES 200

class FileHandler
{
  public:

    enum ErrorCode {
      NO_ERROR = 0,
      FILE_READ_ERROR,
      FILE_NOT_A_BITMAP,
      UNSUPPORTED_BITMAP
    };

    FileHandler(StripHandler& strip);

    bool setup();
    void scanForFiles();
    String getFilename() const;
    ErrorCode sendFile(const String& Filename, 
                       const uint8_t brightness, 
                       const unsigned long frameDelay);
    void selectNextFile();
    void selectPreviousFile();

  private:
    struct rgbValues{
      int r;
      int g;
      int b;
    };

    StripHandler& stripHandler;
    File root;
    File dataFile;
    int fileIndex;
    int nbOfFiles;
    String fileNames[MAX_FILES];
    long buffer[STRIP_LENGTH];

    ErrorCode read_the_file(const uint8_t brightness, const unsigned long frameDelay);
    void getFileNamesFromSD(File dir);
    uint32_t readLong();
    uint16_t readInt();
    int readByte();
    void isort(String * filenames, int n);
    rgbValues getRGBwithGamma(const uint8_t brightness);

    byte gamma(byte x);
};

#endif // __FILE_HANDLER_H__