#ifndef HERMES_UNITSBASIC_H
#define HERMES_UNITSBASIC_H

#define HERMES_UNITSDISABLE

#include <array>
#include <cmath>

namespace hermes {

typedef double QNumber;
typedef double QAngle;
typedef double QLength;
typedef double QTime;
typedef double QEnergy;
typedef double QMField;
typedef double QMass;
typedef double QTemperature;
typedef double QIntensity;
typedef double QFrequency;
typedef double QECurrent;
typedef double QSubstance;
typedef double QLIntensity;
typedef double QArea;
typedef double QVolume;
typedef double QForce;
typedef double QPressure;
typedef double QECharge;
typedef double QPower;
typedef double QEResistance;
typedef double QECapacitance;
typedef double QEPotential;
typedef double QPDensityPerEnergy;
typedef double QAcceleration;
typedef double QSpeed;
typedef double QDifferentialFlux;
typedef double QEmissivity;
typedef double QPDensity;
typedef double QInverseLength;
typedef double QColumnDensity;
typedef double QRotationMeasure;
typedef double QDiffCrossSection;
typedef double QEnergyDensity;

typedef double QRMIntegral;
typedef double QSynchroConstant;
typedef double QPiZeroIntegral;
typedef double QRingCOIntensity;
typedef double QRingX0Unit;
typedef double QICInnerIntegral;
typedef double QICOuterIntegral;

typedef std::array<QAngle, 2> QDirection;

constexpr QLength	metre(1.0);
constexpr QTime		second(1.0);
constexpr QMass		kilogram(1.0);
constexpr QECurrent	ampere(1.0);
constexpr QTemperature	kelvin(1.0);
constexpr QSubstance	mole(1.0);
constexpr QLIntensity	candela(1.0);
constexpr QAngle	radian(1.0);

// Predefined derived units:
// doc: https://en.wikipedia.org/wiki/SI_derived_unit
constexpr QArea		square_metre(1.0);
constexpr QForce	newton(1.0);
constexpr QPressure	pascal(1.0);
constexpr QEnergy	joule(1.0);
constexpr QECharge	coulomb(1.0);
constexpr QMField	tesla(1.0);
constexpr QEPotential	volt(1.0);
constexpr QFrequency	hertz(1.0);
constexpr QPower	watt(1.0);
constexpr QEResistance	ohm(1.0);
constexpr QECapacitance farad(1.0);

constexpr double pi = 3.1415926535897932384626433832795;
constexpr double eulerGamma = 0.5772156649015328606065120900824;

constexpr QAngle degree = static_cast<double>(2*pi / 360.0) * radian;
/*
constexpr QLength operator"" _kpc(long double);
constexpr QLength operator"" _kpc(unsigned long long int x) { return QLength(static_cast<double>(x)); };
constexpr QLength operator"" _m(unsigned long long int x) { return QLength(static_cast<double>(x)); };
constexpr QAngle operator"" _deg(long double);
*/
// Physical constants
/* Definition of SI base units and constants used elsewhere in the code.
 Partly inherited from CRPropa3.
 Based on:
 - CODATA recommended values of the fundamental physical constants: 2006
        doi:10.1103/RevModPhys.80.633
 - IAU 2012 Resolution B2, IAU 2015 Resolution B2
        https://www.iau.org/administration/resolutions/
*/

constexpr auto e_plus		= 1.602176487e-19 * coulomb;
constexpr auto c_light		= 2.99792458e8 * metre / second;
constexpr auto c_squared 	= c_light * c_light;
constexpr auto amu 		= 1.660538921e-27 * kilogram;
constexpr auto m_proton 	= 1.67262158e-27 * kilogram;
constexpr auto m_neutron 	= 1.67492735e-27 * kilogram;
constexpr auto m_electron 	= 9.10938291e-31 * kilogram;
constexpr auto h_planck 	= 6.62606957e-34 * joule * second;
constexpr auto h_planck_bar 	= 6.62606957e-34 * joule * second / (2*pi);
constexpr auto k_boltzmann 	= 1.3806488e-23 * joule / kelvin;
constexpr auto mu0 		= (4*pi) * 1e-7 * newton / (ampere * ampere);
constexpr auto epsilon0 	= 1.0 / mu0 / c_squared;

// Predefined time-derived units:
constexpr QTime minute = 60. * second;
constexpr QTime hour = 60. * minute;
constexpr QTime day = 24. * hour;
constexpr QTime week = 7. * day;
constexpr QTime year = 365.25 * day;

// Predefined mass units:
constexpr QMass gramme = 0.001 * kilogram;
constexpr QMass tonne = 1000 * kilogram;
constexpr QMass ounce = 0.028349523125 * kilogram;
constexpr QMass pound = 16 * ounce;
constexpr QMass stone = 14 * pound;

// Predefined energy units:
constexpr QEnergy erg = 1e-7 * joule;

// Predefined length units:
constexpr QLength inch = 2.54 * 0.01 * metre;
constexpr QLength foot = 12 * inch;
constexpr QLength yard = 3 * foot;
constexpr QLength mile = 5280 * foot;

// Astronomical distances
constexpr QLength astronomical_unit = 149597870700.0 * metre;
constexpr QLength lightyear = year * c_light;
constexpr QLength parsec = 648000.0 / (1*pi) * astronomical_unit;

// Predefined area units:
constexpr QArea hectare = 1e4 * square_metre;
constexpr QArea barn = 1e-28 * square_metre;

// Predefined mixed units:
constexpr QAcceleration G = 9.80665 *  metre / (second*second);
constexpr QForce poundforce = pound*G;
constexpr QForce kilopond = kilogram*G;
constexpr auto gauss = 1e-4 * tesla;
constexpr auto electronvolt = e_plus * volt;
constexpr QPressure bar = 100000 * pascal;
constexpr QPressure psi = pound*G / (inch*inch);

// SI prefixes
constexpr double yocto = 1e-24;
constexpr double zepto = 1e-21;
constexpr double atto  = 1e-18;
constexpr double femto = 1e-15;
constexpr double pico  = 1e-12;
constexpr double nano  = 1e-9;
constexpr double micro = 1e-6;
constexpr double milli  = 1e-3;
constexpr double centi = 1e-2;
constexpr double deci  = 1e-1;
constexpr double deca  = 1e1;
constexpr double hecto = 1e2;
constexpr double kilo  = 1e3;
constexpr double mega  = 1e6;
constexpr double giga  = 1e9;
constexpr double tera  = 1e12;
constexpr double peta  = 1e15;
constexpr double exa   = 1e18;
constexpr double zetta = 1e21;
constexpr double yotta = 1e24;  

//inline fmod(double a, double b) { return std::fmod(a, b); }
inline double fabs(double a) { return std::fabs(a); }

template<int power>
constexpr double pow(const QNumber& num) { return std::pow(static_cast<double>(num), power); }
constexpr double squared(const QNumber& num) { return num*num; }

} // hermes namespace

#endif // HERMES_UNITS_H
