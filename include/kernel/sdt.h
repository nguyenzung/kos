#ifndef RSDP_H
#define RSDP_H

#include <kernel/utils.h>
#include <kernel/type.h>
#include <stdlib/list.h>

namespace kernel
{

typedef struct RSDPDescriptor {    
    char    signature[8];
    uint8   checksum;
    char    oemId[6];
    uint8   revision;
    uint32  rsdtAddress;
 
    uint32  length;
    uint64  xsdtAddress;
    uint8   extendedChecksum;
    uint8   reserved[3];
}  __attribute__ ((packed)) RSDPDescriptor;

typedef struct ACPISDTHeader
{
    char    signature[4];
    uint32  length;
    uint8   revision;
    uint8   checksum;
    char    oemId[6];
    char    oemTableId[8];
    uint32  oemRevision;
    uint32  creatorId;
    uint32  creatorRevision;
}  __attribute__ ((packed)) ACPISDTHeader;

typedef struct RSDT 
{
    ACPISDTHeader h;
    uint32 nextSDT[];
}  __attribute__ ((packed)) RSDT;

typedef struct XSDT 
{
    ACPISDTHeader h;
    uint64 nextSDT[];
}  __attribute__ ((packed)) XSDT;

typedef struct MADTHeader
{
    uint32 localAPICAddress;
    uint32 flags;
} __attribute__ ((packed)) MADTHeader;

typedef struct LAPICDescriptor
{
    uint8   type;               // type = 0
    uint8   length;
    uint8   apicProcessorId;
    uint8   apicId;
    uint32  flags;
} __attribute__ ((packed)) ProcessorDescriptor;

typedef struct IOAPICDescriptor
{
    uint8   type;               // type = 1
    uint8   length;
    uint8   ioApicId;
    uint8   reserved;
    uint32  ioApicAddress;
    uint32  globalSystemInterruptBase;
} __attribute__ ((packed)) IOAPICDescriptor;

typedef struct LAPICOverrideDescriptor
{
    uint8   type;               // type = 5
    uint8   length;
    uint16  reserved;
    uint64  physicalAddress;
} __attribute__((packed)) LAPICOverrideDescriptor;

class SDT
{
public:
    RSDPDescriptor *rsdpDescriptor;
    RSDT *rsdt;
    XSDT *xsdt;
    ACPISDTHeader *madt;
    MADTHeader *madtHeader;
    ProcessorDescriptor *processorDescriptor;
    
    std::List<LAPICDescriptor*> localApicDescriptors;
    std::List<IOAPICDescriptor*> ioApicDescriptors;
    
    SDT();
    DEF_MODULE_INSTANCE(SDT)
    
    void initialize();
    void scan();
    void parse();
    bool checksum();

    void parseRSDT();
    void parseXSDT();
    
    void parseMADT();
    
    void view();
};




}

#endif