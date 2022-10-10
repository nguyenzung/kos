#ifndef __TYPE_H__
#define __TYPE_H__

namespace kernel {

typedef      char   int8;
typedef      short  int16;
typedef      int    int32;
typedef      long   int64;

typedef      unsigned   char   uint8;
typedef      unsigned   short  uint16;
typedef      unsigned   int    uint32;
typedef      unsigned   long   uint64;

typedef long unsigned   int    size_t;



const  uint8  UINT8_MIN = 0;
const  uint8  UINT8_MAX = ~UINT8_MIN;

const  uint16  UINT16_MIN = 0;
const  uint16  UINT16_MAX = ~UINT16_MIN;

const  uint32  UINT32_MIN = 0;
const  uint32  UINT32_MAX = ~UINT32_MIN;

const  uint64  UINT64_MIN = 0;
const  uint64  UINT64_MAX = ~UINT64_MIN;


}
#endif