#include "hermes/integrators/RMIntegrator.h"
#include "hermes/integrators/LOSIntegrationMethods.h"

namespace hermes {

RMIntegrator::RMIntegrator(const std::shared_ptr<MagneticField> mfield,
			   const std::shared_ptr<ChargedGasDensity> gdensity) : mfield(mfield), gdensity(gdensity) {	
}

RMIntegrator::~RMIntegrator() { }

QRotationMeasure RMIntegrator::integrateOverLOS(QDirection direction) const {
	return sumIntegration<QRotationMeasure, QRMIntegral>(
			direction, [this](Vector3QLength pos) {return this->integralFunction(pos);});
}

QRMIntegral RMIntegrator::integralFunction(Vector3QLength pos) const {
	constexpr auto const_a0 = pow<3>(e_plus)/(8*pi*pi*epsilon0*squared(m_electron)*pow<3>(c_light));
	
	Vector3QMField B = mfield->getField(pos);
	if (B.getR() == 0_muG) return 0;
	// TODO: optimise
	QMField B_parallel = B.getR() * cos((B.getValue()).getAngleTo(pos.getValue()));

	return const_a0 * B_parallel * gdensity->getDensity(pos) * radian;
}

} // namespace hermes 
