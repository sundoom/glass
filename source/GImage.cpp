/*
*  GImage.cpp
*  glass
*
*  Created by sunjun on 11-6-14.
*  Copyright 2011 sunstdio. All rights reserved.
*
*/
//////////////////////////////////////////////////////////////////////////

#include <Glass.h>

//////////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////////

GImage::GImage()
{
  mWidth = mHeight = 0;
  mFormat = PF_R8G8B8;
}

GImage::~GImage()
{

}

//////////////////////////////////////////////////////////////////////////

/*
====================
Width
====================
*/
U32 GImage::Width() const
{
  return mWidth;
}

/*
====================
Height
====================
*/
U32 GImage::Height() const
{
  return mHeight;
}

/*
====================
Format
====================
*/
U32 GImage::Format() const
{
  return mFormat;
}

/*
====================
Pixels
====================
*/
const U8* GImage::Pixels() const
{
  return &mPixels[0];
}

//////////////////////////////////////////////////////////////////////////

/*
====================
Create
====================
*/
GImage* GImage::Create(U32 w, U32 h, U32 f)
{
  CHECK(w && h);
  GImage* image = GNEW(GImage); CHECK(image);
  image->mWidth = w;
  image->mHeight = h;
  image->mFormat = f;
  switch(f)
  {
  case PF_R8G8B8:
    image->mPixels.resize(w * h * 3);
    break;
  case PF_R8G8B8A8:
    image->mPixels.resize(w * h * 4);
    break;
  case PF_R5G6B5:
    image->mPixels.resize(w * h * 2);
    break;
  default:
    GAssert(VA("The image`s format(%d) is unknown.\n", f));
    break;
  }
  return image;
}

/*
====================
Create
====================
*/
#pragma pack(push,1)
struct TGA_Header
{
  U8	IdFieldLength;
  U8	ColorMapType;
  U8	ImageTypeCode;		// 2 for uncompressed RGB format
  U16	ColorMapOrigin;
  U16	ColorMapLength;
  U8	ColorMapEntrySize;
  U16	XOrigin;
  U16	YOrigin;
  U16	Width;
  U16	Height;
  U8	BitsPerPixel;
  U8	ImageDescriptor;
};
#pragma pack(pop)

GImage* GImage::Load(const GData* data)
{
  CHECK(data);

  // the new image
  GImage* image = GNEW(GImage); CHECK(image);

  // get the header of the tga
  const TGA_Header* tga_header = (TGA_Header*)data->Get();
  if(tga_header->ImageTypeCode == 10) // 10 = RLE compressed 
  {
    if(tga_header->BitsPerPixel == 32)
    {
      // build the image
      image->mWidth = tga_header->Width;
      image->mHeight = tga_header->Height;
      image->mFormat = PF_R8G8B8A8;
      image->mPixels.resize(image->mWidth * image->mHeight * 4);

      // process image data
      U8*	idData = (U8*)tga_header + sizeof(TGA_Header); 
      U8*	colorMap = idData + tga_header->IdFieldLength;
      U8*	imageData = (U8*)(colorMap + (tga_header->ColorMapEntrySize + 4) / 8 * tga_header->ColorMapLength);
      U32* pixelData = (U32*)&image->mPixels[0];

      U8	pixel[4];
      I32 rleRun = 0;
      I32 rawRun = 0;

      for(I32 Y = tga_header->Height - 1; Y >= 0; Y--) // Y-flipped.
      {					
        for(I32 X = 0; X < tga_header->Width; X++)
        {						
          if(rleRun > 0)
          {
            rleRun--;  // reuse current Pixel data.
          }
          else if(rawRun == 0) // new raw pixel or RLE-run.
          {
            U8 rleChunk = *(imageData++);							
            if(rleChunk & 0x80)
            {
              rleRun = ( rleChunk & 0x7F ) + 1;
              rawRun = 1;
            }
            else
            {
              rawRun = ( rleChunk & 0x7F ) + 1;
            }
          }							
          // Retrieve new pixel data - raw run or single pixel for RLE stretch.
          if(rawRun > 0)
          {
            pixel[2] = imageData[0];
            pixel[1] = imageData[1];
            pixel[0] = imageData[2];
            pixel[3] = imageData[3];
            imageData += 4;
            rawRun--;
            rleRun--;
          }
          // Store.
          pixelData[Y*tga_header->Width + X] = *(U32*)&pixel;
        }
      }

      return image;
    }
    else if(tga_header->BitsPerPixel == 24)
    {
      // build the image
      image->mWidth = tga_header->Width;
      image->mHeight = tga_header->Height;
      image->mFormat = PF_R8G8B8;
      image->mPixels.resize(image->mWidth * image->mHeight * 3);

      // process image data
      U8*	idData = (U8*)tga_header + sizeof(TGA_Header); 
      U8*	colorMap = idData + tga_header->IdFieldLength;
      U8*	imageData = (U8*)(colorMap + (tga_header->ColorMapEntrySize + 4) / 8 * tga_header->ColorMapLength);
      U8* pixelData = (U8*)&image->mPixels[0];
      U8 pixel[3];
      I32 rleRun = 0;
      I32 rawRun = 0;

      for(I32 Y = tga_header->Height - 1; Y >= 0; Y--) // Y-flipped.
      {					
        for(I32 X = 0;X < tga_header->Width; X++)
        {						
          if(rleRun > 0)
          {
            rleRun--;  // reuse current Pixel data.
          }
          else if(rawRun == 0) // new raw pixel or RLE-run.
          {
            U8 rleChunk = *(imageData++);
            if(rleChunk & 0x80)
            {
              rleRun = (rleChunk & 0x7F) + 1;
              rawRun = 1;
            }
            else
            {
              rawRun = (rleChunk & 0x7F) + 1;
            }
          }							
          // Retrieve new pixel data - raw run or single pixel for RLE stretch.
          if(rawRun > 0)
          {
            pixel[0] = *(imageData++);
            pixel[1] = *(imageData++);
            pixel[2] = *(imageData++);
            rawRun--;
            rleRun--;
          }
          // Store.
          pixelData[(Y*tga_header->Width*3) + (X*3+0)] = pixel[2];
          pixelData[(Y*tga_header->Width*3) + (X*3+1)] = pixel[1];
          pixelData[(Y*tga_header->Width*3) + (X*3+2)] = pixel[0];
        }
      }

      return image;
    }
    else if(tga_header->BitsPerPixel == 16)
    {
      // build the image
      image->mWidth = tga_header->Width;
      image->mHeight = tga_header->Height;
      image->mFormat = PF_R5G6B5;
      image->mPixels.resize(image->mWidth * image->mHeight * 2);

      // process image data
      U8*	idData = (U8*)tga_header + sizeof(TGA_Header);
      U8*	colorMap = idData + tga_header->IdFieldLength;				
      U16*imageData = (U16*)(colorMap + (tga_header->ColorMapEntrySize + 4) / 8 * tga_header->ColorMapLength);
      U16*pixelData = (U16*)&image->mPixels[0];
      U16 pixel;
      I32 rleRun = 0;
      I32 rawRun = 0;

      for(I32 Y = tga_header->Height - 1; Y >= 0; Y--) // Y-flipped.
      {					
        for(I32 X = 0; X < tga_header->Width; X++)
        {						
          if(rleRun > 0)
          {
            rleRun--;  // reuse current Pixel data.
          }
          else if(rawRun == 0) // new raw pixel or RLE-run.
          {
            U8 rleChunk =  *((U8*)imageData);
            imageData = (U16*)(((U8*)imageData) + 1);
            if(rleChunk & 0x80)
            {
              rleRun = (rleChunk & 0x7F) + 1;
              rawRun = 1;
            }
            else
            {
              rawRun = (rleChunk & 0x7F) + 1;
            }
          }							
          // Retrieve new pixel data - raw run or single pixel for RLE stretch.
          if(rawRun > 0)
          { 
            U16 color = *(imageData++);
            pixel = (((color>>10)&0x1f)<<11) | (((color>>5)&0x1f)<<6) | (color&0x1f);
            rawRun--;
            rleRun--;
          }
          // Store.
          pixelData[Y*tga_header->Width + X] = pixel;
        }
      }

      return image;
    }
    else
    {
      GAssert( VA( "TGA header uses an unsupported rle-compressed bit-depth: %u", tga_header->BitsPerPixel ) );
      return NULL;
    }
  }
  else if(tga_header->ImageTypeCode == 2) // 2 = Uncompressed 
  {
    if(tga_header->BitsPerPixel == 32)
    {
      // build the image
      image->mWidth = tga_header->Width;
      image->mHeight = tga_header->Height;
      image->mFormat = PF_R8G8B8A8;
      image->mPixels.resize(image->mWidth * image->mHeight * 4);

      // process image data
      U8*	idData = (U8*)tga_header + sizeof(TGA_Header);
      U8*	colorMap = idData + tga_header->IdFieldLength;
      U8* imageData = (U8*)(colorMap + (tga_header->ColorMapEntrySize + 4)/8 * tga_header->ColorMapLength);
      U32* pixelData = (U32*)&image->mPixels[0];
      U8 pixel[4];

      for(I32 Y = 0; Y < tga_header->Height; Y++)
      {
        for(I32 X = 0; X < tga_header->Width; X++)
        {
          pixel[2] = imageData[((tga_header->Height-Y-1) * tga_header->Width*4) + (X*4+0)];
          pixel[1] = imageData[((tga_header->Height-Y-1) * tga_header->Width*4) + (X*4+1)];
          pixel[0] = imageData[((tga_header->Height-Y-1) * tga_header->Width*4) + (X*4+2)];
          pixel[3] = imageData[((tga_header->Height-Y-1) * tga_header->Width*4) + (X*4+3)];
          pixelData[Y*tga_header->Width + X] = *(U32*)&pixel;
        }
      }

      return image;
    }
    else if(tga_header->BitsPerPixel == 24)
    {
      // build the image
      image->mWidth = tga_header->Width;
      image->mHeight = tga_header->Height;
      image->mFormat = PF_R8G8B8;
      image->mPixels.resize(image->mWidth * image->mHeight * 3);

      // process image data
      U8*	idData = (U8*)tga_header + sizeof(TGA_Header);
      U8*	colorMap = idData + tga_header->IdFieldLength;
      U8*	imageData = (U8*)(colorMap + (tga_header->ColorMapEntrySize + 4) / 8 * tga_header->ColorMapLength);
      U8* pixelData = (U8*)&image->mPixels[0];
      U8 pixel[3];

      for(I32 Y = 0; Y < tga_header->Height; Y++)
      {
        for(I32 X = 0; X < tga_header->Width; X++)
        {
          pixel[0] = imageData[((tga_header->Height-Y-1)*tga_header->Width*3) + (X*3+0)];
          pixel[1] = imageData[((tga_header->Height-Y-1)*tga_header->Width*3) + (X*3+1)];
          pixel[2] = imageData[((tga_header->Height-Y-1)*tga_header->Width*3) + (X*3+2)];
          pixelData[(Y*tga_header->Width*3) + (X*3+0)] = pixel[2];
          pixelData[(Y*tga_header->Width*3) + (X*3+1)] = pixel[1];
          pixelData[(Y*tga_header->Width*3) + (X*3+2)] = pixel[0];
        }
      }

      return image;
    }
    else if(tga_header->BitsPerPixel == 16)
    {
      // build the image
      image->mWidth = tga_header->Width;
      image->mHeight = tga_header->Height;
      image->mFormat = PF_R5G6B5;
      image->mPixels.resize(image->mWidth * image->mHeight * 2);

      // process image data
      U8*	idData = (U8*)tga_header + sizeof(TGA_Header);
      U8*	colorMap = idData + tga_header->IdFieldLength;
      U16* imageData = (U16*)(colorMap + (tga_header->ColorMapEntrySize + 4) / 8 * tga_header->ColorMapLength);
      U16* pixelData = (U16*)&image->mPixels[0];

      for(I32 Y = 0; Y < tga_header->Height; Y++)
      {
        for(I32 X = 0; X < tga_header->Width; X++)
        {
          U16 color = imageData[(tga_header->Height-Y-1) * tga_header->Width + X];
          U16 pixel = (((color>>10)&0x1f)<<11) | (((color>>5)&0x1f)<<6) | (color&0x1f);
          pixelData[Y*tga_header->Width + X] = pixel;
        }
      }

      return image;
    }
    else
    {
      GAssert( VA("TGA uses an unsupported bit-depth: %u" ,tga_header->BitsPerPixel) );
      return NULL;
    }
  }
  else
  {
    GAssert( VA("TGA is an unsupported type: %u", tga_header->ImageTypeCode) );
    return NULL;
  }

  return image;
}

//////////////////////////////////////////////////////////////////////////