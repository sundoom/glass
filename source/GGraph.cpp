/*
 *  GGraph.cpp
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

GGraph::GGraph(const GImage* image)
{
  CHECK(image);
  mImagePtr = (GImage*)image;
}

GGraph::~GGraph()
{

}

//////////////////////////////////////////////////////////////////////////

/*
====================
Draw
====================
*/
VOID GGraph::Draw(I32 x, I32 y, const GImage* image)
{
  CHECK(image);

  I32 SrcWidth = image->Width();
  I32 SrcHeight = image->Height();
  U8* SrcPixels = (U8*)image->Pixels();
  I32 DstWidth = mImagePtr->Width();
  I32 DstHeight = mImagePtr->Height();
  U8* DstPixels = (U8*)mImagePtr->Pixels();
  
  I32 SrcLeft = x;
  I32 SrcRight = x + SrcWidth;
  I32 SrcTop = y;
  I32 SrcBottom = y + SrcHeight;
  I32 DstLeft = 0;
  I32 DstRight = DstWidth;
  I32 DstTop = 0;
  I32 DstBottom = DstHeight;
  I32 ClipLeft = (SrcLeft > DstLeft) ? SrcLeft : DstLeft;
  I32 ClipRight = (SrcRight < DstRight) ? SrcRight : DstRight;
  I32 ClipTop = (SrcTop > DstTop) ? SrcTop : DstTop;
  I32 ClipBottom = (SrcBottom < DstBottom) ? SrcBottom : DstBottom;
  I32 ClipWidth = ClipRight - ClipLeft;
  I32 ClipHeight = ClipBottom - ClipTop;
  if(ClipWidth <= 0 || ClipHeight <= 0 ) return;

  I32 SrcXStart = ClipLeft - SrcLeft;
  I32 SrcYStart = ClipTop - SrcTop;
  I32 DstXStart = ClipLeft - DstLeft;
  I32 DstYStart = ClipTop - DstTop;

  switch(mImagePtr->Format())
  {
  case PF_R8G8B8:
    {
      U8* Dst = (U8*)(DstPixels + (DstXStart + DstYStart * DstWidth) * 3);
      switch(image->Format())
      {
      case PF_R8G8B8:
        {
          U8* Src = (U8*)(SrcPixels + (SrcXStart + SrcYStart * SrcWidth) * 3);
          for(I32 j = 0; j < ClipHeight; j++)
          {
            for(I32 i = 0; i < ClipWidth; i++)
            {
              Dst[i * 3 + 0 + j * DstWidth * 3] = Src[i * 3 + 0 + j * SrcWidth * 3];
              Dst[i * 3 + 1 + j * DstWidth * 3] = Src[i * 3 + 1 + j * SrcWidth * 3];
              Dst[i * 3 + 2 + j * DstWidth * 3] = Src[i * 3 + 2 + j * SrcWidth * 3];
            }
          }
        }
        break;
      case PF_R8G8B8A8:
        {
          U8* Src = (U8*)(SrcPixels + (SrcXStart + SrcYStart * SrcWidth) * 4);
          for(I32 j = 0; j < ClipHeight; j++)
          {
            for(I32 i = 0; i < ClipWidth; i++)
            {
              U8 rs = Src[i * 4 + 0 + j * SrcWidth * 4];
              U8 gs = Src[i * 4 + 1 + j * SrcWidth * 4];
              U8 bs = Src[i * 4 + 2 + j * SrcWidth * 4];
              U8 as = Src[i * 4 + 3 + j * SrcWidth * 4];
              U8&rd = Dst[i * 3 + 0 + j * DstWidth * 3];
              U8&gd = Dst[i * 3 + 1 + j * DstWidth * 3];
              U8&bd = Dst[i * 3 + 2 + j * DstWidth * 3];
              rd = (rs - rd) * as / 255 + rd;
              gd = (gs - gd) * as / 255 + gd;
              bd = (bs - bd) * as / 255 + bd;
            }
          }
        }
        break;
      case PF_R5G6B5:
        {
          U16* Src = (U16*)(SrcPixels + (SrcXStart + SrcYStart * SrcWidth) * 2);
          for(I32 j = 0; j < ClipHeight; j++)
          {
            for(I32 i = 0; i < ClipWidth; i++)
            {
              U16 c = Src[i + j * SrcWidth];
              U8 r = ((c >> 11) & 0x1f) << 3;
              U8 g = ((c >> 5) & 0x3f) << 2;
              U8 b = (c & 0x1f) << 3;
              Dst[i * 3 + 0 + j * DstWidth * 3] = r;
              Dst[i * 3 + 1 + j * DstWidth * 3] = g;
              Dst[i * 3 + 2 + j * DstWidth * 3] = b;
            }
          }
        }
        break;
      default:
        GAssert(VA("The src image`s format(%d) is unknown.\n", image->Format()));
        break;
      }
    }
    break;
  case PF_R8G8B8A8:
    {
      U8* Dst = (U8*)(DstPixels + (DstXStart + DstYStart * DstWidth) * 4);
      switch(image->Format())
      {
      case PF_R8G8B8:
        {
          U8* Src = (U8*)(SrcPixels + (SrcXStart + SrcYStart * SrcWidth) * 3);
          for(I32 j = 0; j < ClipHeight; j++)
          {
            for(I32 i = 0; i < ClipWidth; i++)
            {
              Dst[i * 4 + 0 + j * DstWidth * 4] = Src[i * 3 + 0 + j * SrcWidth * 3];
              Dst[i * 4 + 1 + j * DstWidth * 4] = Src[i * 3 + 1 + j * SrcWidth * 3];
              Dst[i * 4 + 2 + j * DstWidth * 4] = Src[i * 3 + 2 + j * SrcWidth * 3];
            }
          }
        }
        break;
      case PF_R8G8B8A8:
        {
          U8* Src = (U8*)(SrcPixels + (SrcXStart + SrcYStart * SrcWidth) * 4);
          for(I32 j = 0; j < ClipHeight; j++)
          {
            for(I32 i = 0; i < ClipWidth; i++)
            {
              U8 rs = Src[i * 4 + 0 + j * SrcWidth * 4];
              U8 gs = Src[i * 4 + 1 + j * SrcWidth * 4];
              U8 bs = Src[i * 4 + 2 + j * SrcWidth * 4];
              U8 as = Src[i * 4 + 3 + j * SrcWidth * 4];
              U8&rd = Dst[i * 4 + 0 + j * DstWidth * 4];
              U8&gd = Dst[i * 4 + 1 + j * DstWidth * 4];
              U8&bd = Dst[i * 4 + 2 + j * DstWidth * 4];
              rd = (rs - rd) * as / 255 + rd;
              gd = (gs - gd) * as / 255 + gd;
              bd = (bs - bd) * as / 255 + bd;
            }
          }
        }
        break;
      case PF_R5G6B5:
        {
          U16* Src = (U16*)(SrcPixels + (SrcXStart + SrcYStart * SrcWidth) * 2);
          for(I32 j = 0; j < ClipHeight; j++)
          {
            for(I32 i = 0; i < ClipWidth; i++)
            {
              U16 c = Src[i + j * SrcWidth];
              U8 r = ((c >> 11) & 0x1f) << 3;
              U8 g = ((c >> 5) & 0x3f) << 2;
              U8 b = (c & 0x1f) << 3;
              Dst[i * 4 + 0 + j * DstWidth * 4] = r;
              Dst[i * 4 + 1 + j * DstWidth * 4] = g;
              Dst[i * 4 + 2 + j * DstWidth * 4] = b;
            }
          }
        }
        break;
      default:
        GAssert(VA("The src image`s format(%d) is unknown.\n", image->Format()));
        break;
      }
    }
    break;
  case PF_R5G6B5:
    {
      U16* Dst = (U16*)(DstPixels + (DstXStart + DstYStart * DstWidth) * 2);
      switch(image->Format())
      {
      case PF_R8G8B8:
        {
          U8* Src = (U8*)(SrcPixels + (SrcXStart + SrcYStart * SrcWidth) * 3);
           for(I32 j = 0; j < ClipHeight; j++)
          {
            for(I32 i = 0; i < ClipWidth; i++)
            {
              U16 r = Src[i * 3 + 0 + j * SrcWidth * 3];
              U16 g = Src[i * 3 + 1 + j * SrcWidth * 3];
              U16 b = Src[i * 3 + 2 + j * SrcWidth * 3];
              Dst[i + j * DstWidth] = ((r>>3)<<11) | ((g>>2)<<5) | b;
            }
          }
        }
        break;
      case PF_R8G8B8A8:
        {
          U8* Src = (U8*)(SrcPixels + (SrcXStart + SrcYStart * SrcWidth) * 4);
          for(I32 j = 0; j < ClipHeight; j++)
          {
            for(I32 i = 0; i < ClipWidth; i++)
            {
              U8 rs = Src[i * 4 + 0 + j * SrcWidth * 4];
              U8 gs = Src[i * 4 + 1 + j * SrcWidth * 4];
              U8 bs = Src[i * 4 + 2 + j * SrcWidth * 4];
              U8 as = Src[i * 4 + 3 + j * SrcWidth * 4];
              U16& c = Dst[i + j * SrcWidth];
              U8 rd = ((c >> 11) & 0x1f) << 3;
              U8 gd = ((c >> 5) & 0x3f) << 2;
              U8 bd = (c & 0x1f) << 3;              
              rd = (rs - rd) * as / 255 + rd;
              gd = (gs - gd) * as / 255 + gd;
              bd = (bs - bd) * as / 255 + bd;
              c = ((rd>>3)<<11) | ((gd>>2)<<5) | bd;
            }
          }
        }
        break;
      case PF_R5G6B5:
        {
          U16* Src = (U16*)(SrcPixels + (SrcXStart + SrcYStart * SrcWidth) * 2);
          for(I32 j = 0; j < ClipHeight; j++)
          {
            for(I32 i = 0; i < ClipWidth; i++)
            {
              Dst[i + j * DstWidth] = Src[i + j * SrcWidth];
            }
          }
        }
        break;
      default:
        GAssert(VA("The src image`s format(%d) is unknown.\n", image->Format()));
        break;
      }
    }
    break;
  default:
    GAssert(VA("The dst image`s format(%d) is unknown.\n", mImagePtr->Format()));
    break;
  }
}

//////////////////////////////////////////////////////////////////////////