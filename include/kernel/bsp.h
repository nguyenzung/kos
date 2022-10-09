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
   
   void disablePIC();
   void enableAPIC();
   
   void activeSMP();
};

}

#endif // BSP_H
