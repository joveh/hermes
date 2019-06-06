#ifndef HERMES_SKYMAPTEMP_H
#define HERMES_SKYMAPTEMP_H

#include "hermes/Units.h"
#include "hermes/ProgressBar.h"
#include "hermes/integrators/Integrator.h"
#include "hermes/skymaps/Skymap.h"
#include "hermes/skymaps/SkymapMask.h"

#if _OPENMP
#include <omp.h>
#define OMP_SCHEDULE static,100
#endif

#include <memory>
#include <vector>
#include <iostream>

namespace hermes {

template <typename QPXL, typename QSTEP>
class SkymapTemplate: public Skymap {
protected:
	typedef QPXL tPixel;
	QDirection iterdir;
	
	typedef std::vector<tPixel> tFluxContainer;
	mutable tFluxContainer fluxContainer;
	mutable std::vector<bool> maskContainer;
	std::shared_ptr<SkymapMask> mask;
	std::shared_ptr<IntegratorTemplate<QPXL, QSTEP> > integrator;
	
	void initContainer();
	void initMask();
public:
	SkymapTemplate(
		std::size_t nside = 32,
		const std::shared_ptr<SkymapMask> mask_ =
	       		std::make_shared<SkymapMask>(SkymapMask()));
	~SkymapTemplate();
	
	std::size_t getSize() const;
	double operator[](std::size_t ipix) const;
	QPXL getPixel(std::size_t ipix) const;

	void setIntegrator(std::shared_ptr<IntegratorTemplate<QPXL, QSTEP> > integrator_);
	void setOutput();
	
	void printPixels();
	void setMask(std::shared_ptr<SkymapMask> mask_);
	std::vector<bool> getMask();
	virtual void computePixel(
			std::size_t ipix,
			std::shared_ptr<IntegratorTemplate<QPXL, QSTEP> > integrator_);
	void compute();
	
	/** output **/
	void save(std::shared_ptr<Output> output) const;

        /** iterator goodies */
        typedef typename tFluxContainer::iterator iterator;
        typedef typename tFluxContainer::const_iterator const_iterator;
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
};

/* Definitions */

template <typename QPXL, typename QSTEP>
void SkymapTemplate<QPXL, QSTEP>::initContainer() {
	fluxContainer.reserve(npix);
	fluxContainer.insert(fluxContainer.begin(), npix, UNSEEN);
}

template <typename QPXL, typename QSTEP>
void SkymapTemplate<QPXL, QSTEP>::initMask() {
	maskContainer = mask->getMask(nside);
}

template <typename QPXL, typename QSTEP>
SkymapTemplate<QPXL, QSTEP>::SkymapTemplate(
		std::size_t nside_,
		const std::shared_ptr<SkymapMask> mask_) : Skymap(nside_), mask(mask_) {
	initContainer();
	initMask();
}

template <typename QPXL, typename QSTEP>
SkymapTemplate<QPXL, QSTEP>::~SkymapTemplate() {
	fluxContainer.clear();
}

template <typename QPXL, typename QSTEP>
std::size_t SkymapTemplate<QPXL, QSTEP>::getSize() const {
	return fluxContainer.size();
}

template <typename QPXL, typename QSTEP>
QPXL SkymapTemplate<QPXL, QSTEP>::getPixel(std::size_t i) const {
        return fluxContainer[i];
}

template <typename QPXL, typename QSTEP>
double SkymapTemplate<QPXL, QSTEP>::operator[](std::size_t i) const {
        return fluxContainer[i].getValue();
}

template <typename QPXL, typename QSTEP>
void SkymapTemplate<QPXL, QSTEP>::printPixels() {
	for (auto i: fluxContainer)
		std::cout << i.getValue() << ' ';
}

template <typename QPXL, typename QSTEP>
void SkymapTemplate<QPXL, QSTEP>::setIntegrator(
		std::shared_ptr<IntegratorTemplate<QPXL, QSTEP> > integrator_) {
	integrator = integrator_;
}

template <typename QPXL, typename QSTEP>
void SkymapTemplate<QPXL, QSTEP>::computePixel(
		std::size_t ipix,
		std::shared_ptr<IntegratorTemplate<QPXL, QSTEP> > integrator_) {
		iterdir = pix2ang_ring(getNside(), ipix);
		fluxContainer[ipix] = integrator_->integrateOverLOS(iterdir);
}

template <typename QPXL, typename QSTEP>
void SkymapTemplate<QPXL, QSTEP>::compute() {
#if _OPENMP
       	std::cout << "hermes::Integrator: Number of Threads: " << omp_get_max_threads() << std::endl;
#endif
	if(integrator == nullptr)
		throw std::runtime_error("Provide an integrator with Skymap::setIntegrator()");
	
	ProgressBar progressbar(getSize());
	progressbar.start("Compute skymap");

#pragma omp parallel for schedule(OMP_SCHEDULE)
	for (std::size_t ipix = 0; ipix < getSize(); ++ipix) {
		if (maskContainer[ipix] == true)
			computePixel(ipix, integrator);
#pragma omp critical(progressbarUpdate)
		progressbar.update();
	}
}

template <typename QPXL, typename QSTEP>
void SkymapTemplate<QPXL, QSTEP>::save(std::shared_ptr<Output> output) const {
	
	output->initOutput();
	output->createTable(static_cast<int>(npix));
	output->writeMetadata(nside, res, description);

	float tempArray[npix];
	for (unsigned long i = 0; i < npix; ++i)
		tempArray[i] = static_cast<float>(fluxContainer[i].getValue());

	output->writeColumn(npix, tempArray);
}

template <typename QPXL, typename QSTEP>
void SkymapTemplate<QPXL, QSTEP>::setMask(std::shared_ptr<SkymapMask> mask_) {
	mask = mask_;
	initMask();
}

template <typename QPXL, typename QSTEP>
std::vector<bool> SkymapTemplate<QPXL, QSTEP>::getMask() {
	return maskContainer;
}

template <typename QPXL, typename QSTEP>
typename SkymapTemplate<QPXL, QSTEP>::iterator SkymapTemplate<QPXL, QSTEP>::begin() {
        return fluxContainer.begin();
}

template <typename QPXL, typename QSTEP>
typename SkymapTemplate<QPXL, QSTEP>::const_iterator SkymapTemplate<QPXL, QSTEP>::begin() const {
        return fluxContainer.begin();
}

template <typename QPXL, typename QSTEP>
typename SkymapTemplate<QPXL, QSTEP>::iterator SkymapTemplate<QPXL, QSTEP>::end() {
        return fluxContainer.end();
}

template <typename QPXL, typename QSTEP>
typename SkymapTemplate<QPXL, QSTEP>::const_iterator SkymapTemplate<QPXL, QSTEP>::end() const {
        return fluxContainer.end();
}

} // namespace hermes

#endif // HERMES_SKYMAPTEMP_H
