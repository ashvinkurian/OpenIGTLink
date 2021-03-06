/*=========================================================================

  Program:   OpenIGTLink Library
  Module:    $HeadURL: http://svn.na-mic.org/NAMICSandBox/trunk/OpenIGTLink2_beta/Source/igtlutil/igtl_image.c $
  Language:  C
  Date:      $Date: 2010-04-15 15:51:48 -0400 (Thu, 15 Apr 2010) $
  Version:   $Revision: 6269 $

  Copyright (c) Insight Software Consortium. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include <string.h>
#include <math.h>

#include "igtl_point.h"
#include "igtl_util.h"

void igtl_export igtl_point_convert_byte_order(igtl_point_element* pointlist, int nitem)
{
  igtl_point_element* elem;
  int i;
  int j;
  igtl_int32* tmp;
      
  for (i = 0; i < nitem; i ++)
    {
    elem = &(pointlist[i]);
    if (igtl_is_little_endian()) 
      {
      for (j = 0; j < 3; j ++)
        {
        tmp = (igtl_int32*)&(elem->position[j]);
        *tmp = BYTE_SWAP_INT32(*tmp);
        }
      tmp = (igtl_int32*)&(elem->radius);
      *tmp = BYTE_SWAP_INT32(*tmp);
      }
    }
}


igtl_uint64 igtl_export igtl_point_get_crc(igtl_point_element* pointlist, int nitem)
{
  igtl_point_element* elem;
  int i;
  igtl_uint64  crc;

  crc = crc64(0, 0, 0);
  for (i = 0; i < nitem; i ++)
    {
    elem = &(pointlist[i]);
    crc = crc64((unsigned char*) elem, IGTL_POINT_ELEMENT_SIZE, crc);
    }

  return crc;
}
