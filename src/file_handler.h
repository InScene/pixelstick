/*
  Copyright Christian Mertens 2022
*/
#ifndef __FILE_HANDLER_H__
#define __FILE_HANDLER_H__

#include <Arduino.h>
#include <SD.h>                          // Library for the SD Card

#define SDssPin 53                        // SD card CS pin
#define STRIP_LENGTH 144                  // Set the number of LEDs the LED Strip
#define MAX_FILES 200

class FileHandler
{
  public:
    FileHandler();

    bool setup();
    String getFilename() const;
    bool sendFile(String Filename);
    void selectNextFile();
    void selectPreviousFile();

  private:
    struct rgbValues{
      int r;
      int g;
      int b;
    };

    File root;
    File dataFile;
    String currentfilename;
    int fileIndex;
    int nbOfFiles;
    String fileNames[MAX_FILES];
    long buffer[STRIP_LENGTH];
    uint8_t brightness;

    void read_the_file();
    void getFileNamesFromSD(File dir);
    uint32_t readLong();
    uint16_t readInt();
    int readByte();
    void isort(String * filenames, int n);
    rgbValues getRGBwithGamma();

    byte gamma(byte x);
};

#endif // __FILE_HANDLER_H__