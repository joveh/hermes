#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "hermes/chargedGasDensity/ChargedGasDensity.h"
#include "hermes/chargedGasDensity/HII_Cordes91.h"
#include "hermes/chargedGasDensity/YMW16.h"

#include "hermes/neutralGasDensity/RingModelDensity.h"

#include "hermes/cosmicRayDensity/CosmicRayDensity.h"
#include "hermes/cosmicRayDensity/SimpleCRDensity.h"
#include "hermes/cosmicRayDensity/Sun08CRDensity.h"
#include "hermes/cosmicRayDensity/WMAP07CRDensity.h"
#include "hermes/cosmicRayDensity/DragonCRDensity.h"

#include "hermes/photonField/PhotonField.h"
#include "hermes/photonField/CMB.h"
#include "hermes/photonField/ISRF.h"

namespace py = pybind11;

namespace hermes {

void init_charged_gas_density(py::module &m) {

    // charged gas density models
    py::class_<ChargedGasDensity, std::shared_ptr<ChargedGasDensity>>(m, "ChargedGasDensity")
	      .def("getDensity", &ChargedGasDensity::getDensity);
    py::class_<HII_Cordes91, std::shared_ptr<HII_Cordes91>, ChargedGasDensity>(m, "HII_Cordes91")
	      .def(py::init<>())
	      .def("getDensity", &ChargedGasDensity::getDensity);
    py::class_<YMW16, std::shared_ptr<YMW16>, ChargedGasDensity>(m, "YMW16")
	      .def(py::init<>())
	      .def("getDensity", &ChargedGasDensity::getDensity);
}

}