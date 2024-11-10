#include "SRLevels.h"

SRLevels::SRLevels(const double& d2pScale,
    const std::vector<std::vector<double>>& dat,
    const Position& origin, const double& minDat) {
    genLevels(dat);
    genLevelLines(d2pScale, origin, minDat);
}

SRLevels::~SRLevels() {}

void SRLevels::genLevels(const std::vector<std::vector<double>>& y) {}

void SRLevels::genLevelLines(const double& d2p, const Position& orig,
    const double& yMin) {

}
