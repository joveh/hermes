#ifndef HERMES_PIZEROINTEGRATOR_H
#define HERMES_PIZEROINTEGRATOR_H

#include "hermes/Units.h"
#include "hermes/integrators/Integrator.h"
#include "hermes/neutralGasDensity/RingModelDensity.h"
#include "hermes/cosmicRayDensity/CosmicRayDensity.h"
#include "hermes/interactions/DifferentialCrossSection.h"

#include <memory>
#include <array>

namespace hermes {

class PiZeroIntegrator: public IntegratorTemplate<QDifferentialFlux> {
private:
	std::shared_ptr<CosmicRayDensity> crdensity;
	std::shared_ptr<RingModelDensity> ngdensity;
	std::shared_ptr<DifferentialCrossSection> crossSec; 

	QPiZeroIntegral integrateOverSumEnergy(
		Vector3QLength pos, QEnergy Egamma) const;
	QPiZeroIntegral integrateOverLogEnergy(
		Vector3QLength pos, QEnergy Egamma) const;

public:
	PiZeroIntegrator(
		const std::shared_ptr<CosmicRayDensity>,
		const std::shared_ptr<RingModelDensity>,
		const std::shared_ptr<DifferentialCrossSection>); 
	~PiZeroIntegrator();

	QPDensity densityProfile(const Vector3QLength &) const;

	QDifferentialFlux integrateOverLOS(QDirection iterdir) const;
	QDifferentialFlux integrateOverLOS(QDirection iterdir, QEnergy Egamma) const;
	QPiZeroIntegral integrateOverEnergy(
		Vector3QLength pos, QEnergy Egamma) const;
};

} // namespace hermes

#endif // HERMES_PIZEROINTEGRATOR_H