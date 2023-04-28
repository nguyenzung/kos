#include <kernel/sdt.h>
#include <kernel/utils.h>
#include <stdlib/string.h>
#include <kernel/printer.h>

using namespace kernel;

SDT::SDT()
    :rsdpDescriptor(nullptr)
    ,rsdt(nullptr)
    ,xsdt(nullptr)
    ,madt(nullptr)
{
    SDT::instance = this;
}

IMPL_MODULE_INSTANCE(SDT)

void SDT::initialize()
{
    scan();
    parse();
//    view();
}

 /*   The RSDP is either located within the first 1 KB of the EBDA (Extended BIOS Data Area) 
 *   (a 2 byte real mode segment pointer to it is located at 0x40E),
 *   or in the memory region from 0x000E0000 to 0x000FFFFF (the main BIOS area below 1 MB). 
 */
void SDT::scan()
{
    uint64 *startAddress = (uint64*)(0x000E0000);
    uint64 *endAddress = (uint64*)(0x000FFFFF);

    char signature_[9] = "RSD PTR ";
    uint64 *signature = (uint64*)signature_;
    while (startAddress < endAddress)
    {
        if (*startAddress == *signature)
        {
            rsdpDescriptor = (RSDPDescriptor*)startAddress;
            if (checksum())
                break;
        }
        startAddress += 2;
    }
}

void SDT::parse()
{
    switch (rsdpDescriptor->revision) {
    case 0:
        parseRSDT();
        break;
    case 2:
        parseXSDT();
    default:
        break;
    }
}

bool SDT::checksum()
{
    char sum = 0;
    for (uint16 i = 0; i < rsdpDescriptor->length; i++)
    {
        sum += ((char*)rsdpDescriptor)[i];
    }
    return !sum;
}

void SDT::parseRSDT()
{
    rsdt = (RSDT *) rsdpDescriptor->rsdtAddress;
    uint8 numTable = (rsdt->h.length - sizeof(rsdt->h)) / 4;

    for (int i = 0; i < numTable; i++)
    {
        ACPISDTHeader *h = (ACPISDTHeader *)rsdt->nextSDT[i];
        if (!std::memcmp(h->signature, "ACPI", 4))
        {
            madt = h;
            parseMADT();
        }
    }
}

void SDT::parseXSDT()
{
    xsdt = (XSDT *) rsdpDescriptor->xsdtAddress;
    uint8 numTable = (xsdt->h.length - sizeof(xsdt->h)) / 8;
    printf("\n Address: %d, Entries %d, %s, %d, %d", xsdt, numTable, xsdt->h.signature, xsdt->h.length, sizeof(xsdt->h));

    for (int i = 0; i < numTable; i++)
    {
        ACPISDTHeader *h = (ACPISDTHeader *)xsdt->nextSDT[i];
        if (!std::memcmp(h->signature, "ACPI", 4))
        {
            madt = h;
            parseMADT();
        }
    }
}

void SDT::parseMADT()
{
    madtHeader = (MADTHeader*)((void*)madt + sizeof(ACPISDTHeader));
//    printf("\n MADT Header: LAPIC Address %p %b ", madtHeader->localAPICAddress, madtHeader->flags);
    void *descriptorEntries = (void*)madt + sizeof(ACPISDTHeader) + sizeof(MADTHeader);
    
    while (descriptorEntries < (void*)madt + madt->length) {
//        printf("\n Entry type: %d %d", *((uint8*)descriptorEntries), descriptorEntries);
        switch(*((uint8*)descriptorEntries)) {
        case 0: 
            localApicDescriptors.push_back((LAPICDescriptor*)descriptorEntries);
            break;
        case 1: 
            ioApicDescriptors.push_back((IOAPICDescriptor*)descriptorEntries);
            break;
        case 5:
            break;
        }
        descriptorEntries += *((uint8*) (descriptorEntries + 1));      
    }
}

MADTHeader* SDT::getMADTHeader()
{
    return madtHeader;
}

std::Vector<LAPICDescriptor*> SDT::getLAPICDescriptors()
{
    return localApicDescriptors;
}

std::Vector<IOAPICDescriptor*> SDT::getIOAPICDescriptors()
{
    return ioApicDescriptors;
}

void SDT::view()
{
    printf("\n Total LAPIC item: %d ", localApicDescriptors.size());
    printf("\n Total IOAPIC item: %d ", ioApicDescriptors.size());
    
    for(std::Vector<LAPICDescriptor*>::Iterator it = localApicDescriptors.begin(); it != localApicDescriptors.end(); ++it)
    {
        LAPICDescriptor* item = *it;
        printf("\n LAPIC: %d %d %d ", item->apicId, item->apicProcessorId, item->flags);
    }
}