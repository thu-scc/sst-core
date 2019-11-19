#include <sst_config.h>
#include "sst/core/impl/partitioners/manual.h"

#include <sst/core/warnmacros.h>

#include <string>

#include "sst/core/configGraph.h"

using namespace std;

namespace SST {
namespace IMPL {
namespace Partition {

SSTManualPartition::SSTManualPartition(RankInfo world_size, RankInfo my_rank, int UNUSED(verbosity)) :
    SSTPartitioner(),
    world_size(world_size) {
	FILE* f_manualrank = fopen("partition.in", "r");
	if (f_manualrank) {
		size_t id, rank;
		while (fscanf(f_manualrank, "%lu%lu", &id, &rank) != EOF) {
			this->predefined_map[id] = rank;
		}
		fclose(f_manualrank);
	}
}

void SSTManualPartition::performPartition(ConfigGraph* graph) {
    ConfigComponentMap_t& compMap = graph->getComponentMap();
    RankInfo rank(0, 0);

	fprintf(stderr, "Map size is %lu\n", compMap.size());
    for(ConfigComponentMap_t::iterator compItr = compMap.begin();
            compItr != compMap.end();
            compItr++) {

		if (this->predefined_map.find(compItr->id) != 
				this->predefined_map.end()) {
			auto rank = this->predefined_map[compItr->id];
			compItr->rank = RankInfo(rank >> 16, rank & 0xffffu);
			fprintf(stderr, "Rank for %lu is %u!\n", compItr->id, compItr->rank.rank);
		} else {
			fprintf(stderr, "Rank for %lu not found!\n", compItr->id);
			compItr->rank = rank;

			rank.rank++;
			if ( rank.rank == world_size.rank ) {
				rank.thread = (rank.thread+1)%world_size.thread;
				rank.rank = 0;
			}
		}
    }
}

} // namespace Partition
} // namespace IMPL
} // namespace SST
