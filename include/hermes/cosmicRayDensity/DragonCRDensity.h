#ifdef HERMES_HAVE_CFITSIO

#ifndef HERMES_DRAGONCRDENSITY_H
#define HERMES_DRAGONCRDENSITY_H

#include "hermes/cosmicRayDensity/CosmicRayDensity.h"
#include "hermes/FITSWrapper.h"
#include <cassert>
#include <memory>
#include <map>

namespace hermes {

class PID {
protected:
	int Z;
	int A;
	int id;
public:
	PID(int Z_, int A_) : Z(Z_), A(A_) {
		assert(A_ >= 0);
		id = Z * 100 + A;
	}

	virtual ~PID() {
	}

	bool isNucleus() {
		return (A > 0);
	}

	int atomicNr() const {
		return Z;
	}

	int massNr() const {
		return A;
	}
};

static const PID Electron(-1, 0);
static const PID Positron(1, 0);
static const PID Proton(1, 1);
static const PID Helium(2, 4);

class DragonCRDensity: public CosmicRayDensity {
private:
  	std::string filename;
	std::unique_ptr<FITSFile> ffile;
	PID pid;

	void readHeaderFromFITS();
	void readDensityFromFITS();
	void readEnergyAxis();
	void readSpatialGrid();
  
	int dimE, dimx, dimy, dimz;
	std::vector<std::unique_ptr<ScalarGridQPDensityPerEnergy> > grid;
	
	//TODO: implement as std::unordered_map
	std::map<QEnergy, std::size_t> energyIndex;
public:
	DragonCRDensity();
	DragonCRDensity(const std::string& filename_, const PID& pid_);
	QPDensityPerEnergy getDensityPerEnergy(const QEnergy& E_, const Vector3QLength& pos_) const;
	QPDensityPerEnergy getDensityPerEnergy(int iE_, const Vector3QLength& pos_) const;
};

} // namespace hermes

#endif // HERMES_DRAGONCRDENSITY_H

#endif // HERMES_HAVE_CFITSIO