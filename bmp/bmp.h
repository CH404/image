
/*******************************
 * BMP格式的文件从头到尾以此是
 * bmp文件头     14Byte
 * {saveFigureImage
 * bfType       2byte       文件类型
 * bfSize       4byte       文件大小
 * bfReserved1  2byte       保留，必须设置为0
 * bfReserved2  2byte       保留，必须设置为0
 * bfOffBits    5byte       从头到位图数据的偏移(位图数据，正真的图片数据)
 * }
 * bmp位图信息    40byte
 * {
 * biSize       4byte       信息头大小 即40
 * biWidth     4byte       图像的width 单位像素PPI
 * biHeight     4byte       以像素为单位说明图像的高度，同时如果为正，说明位图倒立
 *                          （即数据表示从图像的左下角到右上角），如果为负说明正向
 * biPlanes     2byte       为目标设备说明颜色平面数，总被设置为1
 * biBitCount   2byte       说明比特数/像素数，值有1、2、4、8、16、24、32
 * biCompression    4byte   说明图像的压缩类型，最常用的就是0（BI_RGB），表示不压缩
 * biSizeImages     4byte   说明位图数据的大小，当用BI_RGB格式时，可以设置为0；
 * biXPelsPerMeter  4byte   表示水平分辨率，单位是像素/米，有符号整数；
 * biYPelsPerMeter  4byte   表示垂直分辨率，单位是像素/米，有符号整数；
 * biClrUsed        4byte   说明位图使用的调色板中的颜色索引数，为0说明使用所有；
 * biClrImportant   4byte   说明对图像显示有重要影响的颜色索引数，为0说明都重要；
 * }
 * 调色板
 * {
 * 调色板是可选的，24位图就无调色板，例如8位色图，位图数据中1个byte
 * 表示1个像素点颜色，1个byte =0 ~ 255,表示8位色图一个像素点的颜色
 * 可以有256种颜色，但是颜色是由RGB表示的(有的是RGBA,R red,G green,B bule,A alpha透明度)
 * 所以调色板就是包含了所有颜色的数组，位图数据就是引索号。
 * 调色板数组palette[N][4] N=256 256*4 = 1024byte
 * }
 *位图数据
 * {
 *  注意，这里的biHeight为正数，说明图像倒立，从左下角开始到右上角，以行为主序排列。
 *如果是24位色图，按照BGR的顺序排列，32位色图按照BGRAlpha排列。
 *位图数据排列还有一个规则，就是对齐。
 *Windows默认的扫描的最小单位是4字节，如果数据对齐满足这个值的话对于数据的获取速度等都是有很大的增益的。
 *因此，BMP图像顺应了这个要求，要求每行的数据的长度必须是4的倍数，如果不够需要进行比特填充（以0填充），
 *这样可以达到按行的快速存取。这样的话，位图数据的大小就不一定是宽x高x每像素字节数了，因为每行还可能有0填充。
 * RowSize=4*(BPP*width/32) BPP每个像素的比特数，即biBitCount，Width是宽度
 * //填充后的行大小
 * //如果需要填充的话 RowSize=4*(BPP*width/32)
 *
 * //程序中使用 int bytesPerLine=((bfWidth*biBitCount+31)>>5)<<2;代替，除法更耗时
 * //位图大小
 * int imageSize=bytesPerLine*bfHeight;
 * //一行如果有填充需跳过
 * int skip=4-((bfWidth*biBitCount)>>3)&3;
 * }
 * ******************************/
#ifndef BMP_H
#define BMP_H
#include <stdint.h>
#include "bmp_global.h"
#include <QString>
class BMP_EXPORT Bmp
{
public:
    Bmp();
private:
        uint16_t bfType;
        uint32_t bfSize;
        uint32_t bfOffBit;

        uint32_t biSize;
        uint32_t biWidth;
        uint32_t biHeight;
        uint16_t biPlanes;
        uint16_t biBitCount;
        uint32_t biCompression;
        uint32_t biSizeImages;
        int32_t biXPelsPerMeter;
        int32_t biYPelsPerMeter;
        uint32_t biClrUsed;
        uint32_t biClrImportant;

        //uint8_t (*palette)[4];
        uint32_t palette_size;  //调色板大小

        QString fileName;

     //   uint8_t *bImageData;
    public:
        void GetImageHW(uint32_t &width,uint32_t &hight);
        void GetImageBitCount(uint16_t &bitCount);
        uint8_t GetImageData(uint8_t *pImageDate,uint32_t &imageSize);
        uint8_t DecodeImageInformation(QString filePath);
        void GetImageOffset(uint32_t &offsetByte);
        void GetImageinformation(uint32_t &width,uint32_t &hight,uint32_t& Compression,uint16_t &bitCount,uint32_t &imageSize,uint32_t &palette_size);
};

#endif // BMP_H
