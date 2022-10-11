#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <kernel/process.h>
#include <kernel/type.h>
#include <stdlib/unorderedmap.h>

namespace kernel
{

class ProcessManager{
public:
    std::UnorderedMap<uint64, Process*> *processes;
    
    ProcessManager();
    ~ProcessManager();
    
    void initialize();
};

}

#endif // PROCESSMANAGER_H
