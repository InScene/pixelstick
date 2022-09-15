/*
  Copyright Christian Mertens 2022
*/
#ifndef __FILE_HANDLER_H__
#define __FILE_HANDLER_H__

#include <SD.h>
#include <strip_handler.h>

const uint8_t kSdssPin = 53;    // SD card CS pin
const uint8_t kMaxFiles = 200;
class FileHandler
{
  public:

    enum ErrorCode {
      kNoError = 0,
      kFileReadError,
      kFileNotABitmap,
      kUnsupportedBitmap
    };

    FileHandler(StripHandler& strip);

    bool Setup();
    void ScanForFiles();
    String GetFilename() const;
    ErrorCode SendFile(const String& kFilename, 
                       const uint8_t kBrightness, 
                       const unsigned long kFrameDelay);
    void SelectNextFile();
    void SelectPreviousFile();

  private:

    struct RgbValues{
      int r;
      int g;
      int b;
    };

    StripHandler& stripHandler_;
    File root_;
    File data_file_;
    int file_index_;
    int nb_files_;
    String file_names_[kMaxFiles];

    ErrorCode ReadFile(const uint8_t kBrightness, const unsigned long kFrameDelay);
    void GetFileNamesFromSD(File dir);
    uint32_t ReadLong();
    uint16_t ReadInt();
    int ReadByte();
    void ISort(String * filenames, int n);
    RgbValues GetRGBwithGamma(const uint8_t kBrightness);
    byte Gamma(byte x);
};

#endif // __FILE_HANDLER_H__