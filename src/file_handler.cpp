/*
  Copyright Christian Mertens 2022
*/
#include "file_handler.h"
#include <Arduino.h>

PROGMEM const unsigned char kGammaTable[]  = {
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
  stripHandler_(strip),
  file_index_(0),
  nb_files_(0)
{
  
}

bool FileHandler::Setup()
{
  pinMode(kSdssPin, OUTPUT);

  while (!SD.begin(kSdssPin)) {
    // SD init failed    
    return false;
  }
  
  return  true;
}

void FileHandler::ScanForFiles()
{
  root_ = SD.open("/");
  GetFileNamesFromSD(root_);
  ISort(file_names_, nb_files_);
}

String FileHandler::GetFilename() const
{
  return file_names_[file_index_];
}

FileHandler::ErrorCode FileHandler::SendFile(const String& Filename, 
                                             const uint8_t brightness,
                                             const unsigned long frameDelay)
{
  ErrorCode error = kNoError;
  char temp[14];
  Filename.toCharArray(temp, 14);
  data_file_ = SD.open(temp);

  // if the file is available send it to the LED's
  if (data_file_) {
    error = ReadFile(brightness, frameDelay);
    data_file_.close();
  }
  else {
    error = kFileReadError;
    Setup();
  }

  return error;
}

void FileHandler::SelectNextFile()
{
  if (file_index_ < nb_files_ - 1) {
    file_index_++;
  }
  else {
    file_index_ = 0;                // On the last file so wrap round to the first file
  }
}

void FileHandler::SelectPreviousFile()
{
  if (file_index_ > 0) {
    file_index_--;
  }
  else {
    file_index_ = nb_files_ - 1;   // On the last file so wrap round to the first file
  }
}

FileHandler::ErrorCode FileHandler::ReadFile(const uint8_t brightness, 
                                             const unsigned long frameDelay)
{
  const uint16_t kMyBmpBfType = 0x4D42;
  const uint32_t kMyBmpBfOffBits = 54;
  const uint32_t kMyBmpBiSize = 40;
  const uint32_t kMyBmpBiRgb = 0L;

  ErrorCode error = kNoError;

  uint16_t bmp_type = ReadInt();
  uint32_t bmp_size = ReadLong();       // Don't remove. Data must be read to comply sequence
  uint16_t bmp_reserved_1 = ReadInt();  // Don't remove. Data must be read to comply sequence
  uint16_t bmp_reserved_2 = ReadInt();  // Don't remove. Data must be read to comply sequence
  uint32_t bmp_off_bits = ReadLong();
  bmp_off_bits = 54;

  // Suppress compiler warning for unused variables
  (void)bmp_size;
  (void)bmp_reserved_1;
  (void)bmp_reserved_2;

  /* Check file header */
  if (bmp_type != kMyBmpBfType || bmp_off_bits != kMyBmpBfOffBits) {
    error = kFileNotABitmap;
    return error;
  }

  /* Read info header */
  uint32_t img_size = ReadLong();
  uint32_t img_width = ReadLong();
  uint32_t img_height = ReadLong();
  uint16_t img_planes = ReadInt();
  uint16_t img_bit_count = ReadInt();
  uint32_t img_compression = ReadLong();
  uint32_t img_size_image = ReadLong();
  uint32_t img_x_pels_per_meter = ReadLong(); // Don't remove. Data must be read to comply sequence
  uint32_t img_y_pels_per_meter = ReadLong(); // Don't remove. Data must be read to comply sequence
  uint32_t img_clr_used = ReadLong();         // Don't remove. Data must be read to comply sequence
  uint32_t img_clr_important = ReadLong();    // Don't remove. Data must be read to comply sequence

  // Suppress compiler warning for unused variables
  (void)img_x_pels_per_meter;
  (void)img_y_pels_per_meter;
  (void)img_clr_used;
  (void)img_clr_important;

  /* Check info header */
  if ( img_size != kMyBmpBiSize || img_width <= 0 ||
       img_height <= 0 || img_planes != 1 ||
       img_bit_count != 24 || img_compression != kMyBmpBiRgb ||
       img_size_image == 0 )
  {
    error = kUnsupportedBitmap;
    return error;
  }

  int display_width = img_width;
  if (img_width > kStripLength) {
    display_width = kStripLength;           //only display the number of led's we have
  }

  /* compute the line length */
  uint32_t line_length = img_width * 3;
  if ((line_length % 4) != 0)
    line_length = (line_length / 4 + 1) * 4;

  for (int y = img_height; y > 0; y--) {
    for (int x = 0; x < display_width; x++) {
      uint32_t offset = (kMyBmpBfOffBits + (((y - 1) * line_length) + (x * 3))) ;
      data_file_.seek(offset);

      RgbValues rgbVal = GetRGBwithGamma(brightness);

    // TODO: Outsourde strip value call
      stripHandler_.SetPixelColor(x, rgbVal.r, rgbVal.g, rgbVal.b);
    }
    // TODO: outsource LatchAndDelay call
    stripHandler_.LatchAndDelay(frameDelay);
  }

  return error;
}

void FileHandler::GetFileNamesFromSD(File dir) {
  int file_count = 0;
  String current_filename = "";
  while (1) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      nb_files_ = file_count;
      entry.close();
      break;
    }
    else {
      if (entry.isDirectory()) {
      }
      else {
        current_filename = entry.name();
        if (current_filename.endsWith(".bmp") || current_filename.endsWith(".BMP") ) { //find files with our extension only
          file_names_[file_count] = entry.name();
          file_count++;
        }
      }
    }
    entry.close();
  }
}

uint32_t FileHandler::ReadLong() {
  uint32_t ret_value;
  byte incoming_byte;

  incoming_byte = ReadByte();
  ret_value = (uint32_t)((byte)incoming_byte);

  incoming_byte = ReadByte();
  ret_value += (uint32_t)((byte)incoming_byte) << 8;

  incoming_byte = ReadByte();
  ret_value += (uint32_t)((byte)incoming_byte) << 16;

  incoming_byte = ReadByte();
  ret_value += (uint32_t)((byte)incoming_byte) << 24;

  return ret_value;
}

uint16_t FileHandler::ReadInt() {
  byte incoming_byte = 0;
  uint16_t ret_value = 0;
  incoming_byte = ReadByte();
  ret_value += (uint16_t)((byte)incoming_byte);
  incoming_byte = ReadByte();
  ret_value += (uint16_t)((byte)incoming_byte) << 8;
  return ret_value;
}

int FileHandler::ReadByte() {
  int ret_byte = -1;
  while (ret_byte < 0) ret_byte = data_file_.read();
  return ret_byte;
}

// Sort the filenames in alphabetical order
void FileHandler::ISort(String * filenames, int n) {
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
FileHandler::RgbValues FileHandler::GetRGBwithGamma(const uint8_t brightness) {
  RgbValues values;
  values.g = Gamma(ReadByte()) / (101 - brightness);
  values.b = Gamma(ReadByte()) / (101 - brightness);
  values.r = Gamma(ReadByte()) / (101 - brightness);

  return values;
}

byte FileHandler::Gamma(byte x)
{
  return pgm_read_byte(&kGammaTable[x]);
}