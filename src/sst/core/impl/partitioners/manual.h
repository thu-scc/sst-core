#ifndef SST_CORE_IMPL_PARTITONERS_MANUAL_H
#define SST_CORE_IMPL_PARTITONERS_MANUAL_H

#include <sst/core/sstpart.h>
#include <sst/core/eli/elementinfo.h>

namespace SST {
namespace IMPL {
namespace Partition {

class SSTManualPartition : public SST::Partition::SSTPartitioner {

public:
    SST_ELI_REGISTER_PARTITIONER(
        SSTManualPartition,
        "sst",
        "manual",
        SST_ELI_ELEMENT_VERSION(1,0,0),
        "Partitions components manually")

private:
    RankInfo world_size;
	std::map<size_t, size_t> predefined_map;

public:
    SSTManualPartition(RankInfo world_size, RankInfo my_rank, int verbosity);
    
    /**
       Performs a partition of an SST simulation configuration
       \param graph The simulation configuration to partition
    */
	  void performPartition(PartitionGraph* graph) override {
			SST::Partition::SSTPartitioner::performPartition(graph);
	  }

    void performPartition(ConfigGraph* graph) override;

    bool requiresConfigGraph() override { return true; }
    bool spawnOnAllRanks() override { return false; }
    
        
};

} // namespace Partition
} // namespace IMPL
} //namespace SST
#endif //SST_CORE_IMPL_PARTITONERS_MANUAL_H
