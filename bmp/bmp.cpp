#include <stdint.h>
#include "bmp.h"
#include <QString>
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <QDataStream>
#define BMP_FILE_HEADER_SIZE 14
#define BMP_BITMAP_INFO_HEADER_SIZE 40
#define BFTYPE_OFFSET 0x00
#define BFSIZE_OFFSET  0x02
#define BFOFFBITS_OFFSET  0x0a

#define BISIZE_OFFSET   0x0e
#define BIWIDTH_OFFSET  0x12
#define BIHEIGHT_OFFSET 0x16
#define BIPLANES_OFFSET 0x1a
#define BIBITCOUNT_OFFSET   0x1c
#define BICOMPRESSION_OFFSET    0x1e
#define BISIZEIMAGES_OFFSET 0x22
#define BIXPELSPERMETER_OFFSET  0x26
#define BIYPELSPERMETER_OFFSET  0x2a
#define BICLRUSED_OFFSER    0x2e
#define BICLRLMPORTANT_OFFSET   0x32
Bmp::Bmp()
{

}

void Bmp::GetImageHW(uint32_t &width, uint32_t &hight)
{
    width = biWidth;
    hight = biHeight;
}

void Bmp::GetImageBitCount(uint16_t &bitCount)
{
    bitCount = biBitCount;
}

uint8_t Bmp::GetImageData(uint8_t *pImageDate,uint32_t &imageSize)
{
    if(imageSize < biSizeImages)
    {
        return 1;
    }
    QDataStream in;
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        in.setDevice(&file);
        in.setByteOrder(QDataStream::LittleEndian);
        in.skipRawData(BMP_FILE_HEADER_SIZE+BMP_BITMAP_INFO_HEADER_SIZE+palette_size);
        in.readRawData(reinterpret_cast<char*>(pImageDate),imageSize);
        file.close();
    }
    return 0;
}

uint8_t Bmp::DecodeImageInformation(QString filePath)
{
    QDataStream in;
    QFile file(filePath);
    fileName = filePath;
    if(file.open(QIODevice::ReadOnly))
    {
        in.setDevice(&file);
        in.setByteOrder(QDataStream::LittleEndian);//bmp图片头是低尾端
        in >> bfType;          //文件头类型 4d4a 表示bmp
        in >> bfSize;       //文件头大小
        in.skipRawData(4); //跳过数据，单位字节
        in >> bfOffBit; //bmp文件头到bmp位图数据的偏移量
        in >> biSize;
        in >> biWidth;
        in >> biHeight;
        in >> biPlanes;
        in >> biBitCount;   //说明比特数/像素数，值有1、2、4、8、16、24、32；
        in >> biCompression;
        in >> biSizeImages;
        in >> biXPelsPerMeter;
        in >> biYPelsPerMeter;
        in >> biClrUsed;
        in >> biClrImportant;
    }
    else
    {
         return 0x01;
    }
    //判断是否有调色版
    if(biBitCount<=8 && bfOffBit >BMP_FILE_HEADER_SIZE+BMP_BITMAP_INFO_HEADER_SIZE)
    {
         palette_size = bfOffBit -(BMP_FILE_HEADER_SIZE+BMP_BITMAP_INFO_HEADER_SIZE);
       //  uint8_t *p = new uint8_t(palette_size);  //申请1 个字节buff,buff内写palette_size
      //   uint8_t *p = new uint8_t[palette_size];    //申请palette_size个字节
     //   in.readRawData(reinterpret_cast<char*>(p),palette_size);  //需要用户自己申请buff
        //in.readBytes(reinterpret_cast<char*&>(p),palette_size); //方法自动申请buff,传指针的引用用于接收取出buff地址，uint的引用
     //    palette = reinterpret_cast<uint8_t(*)[4]>(p);
    }
    else
    {
           palette_size = 0;
    }

    file.close();
    int skip = 4-((biWidth*biHeight*biBitCount/8)+BMP_FILE_HEADER_SIZE+BMP_BITMAP_INFO_HEADER_SIZE+palette_size)%4;
    biSizeImages -= skip;
    //读取bmp位图数据
 //    bImageData = new uint8_t(biSizeImages);
   //  in.readRawData(reinterpret_cast<char*>(bImageData),biSizeImages);
    // qDebug() << bImageData;
    return 0;
}

void Bmp::GetImageOffset(uint32_t &offsetByte)
{
    offsetByte = bfOffBit;
}

void Bmp::GetImageinformation(uint32_t &width, uint32_t &hight,uint32_t& Compression, uint16_t &bitCount, uint32_t &imageSize, uint32_t &palette_size)
{
    width = biWidth;
    hight = biHeight;
    Compression = biCompression;
    bitCount = biBitCount;
  //  int skip = 4-((biWidth*biHeight*biBitCount/8)+BMP_FILE_HEADER_SIZE+BMP_BITMAP_INFO_HEADER_SIZE+palette_size)%4;
    imageSize = biSizeImages;
    palette_size = this->palette_size;
}
