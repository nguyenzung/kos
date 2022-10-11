#ifndef BSP_H
#define BSP_H

#include <kernel/processor.h>

namespace kernel
{

class BSP : public Processor
{
public:
   BSP();
   void intialize(uint8 localApicId = 0) override;
   
   void enablePIC();
   void disablePIC();
   void enableAPIC();
   void disableAPIC();
   
   void activeSMP();
};

}

#endif // BSP_H
