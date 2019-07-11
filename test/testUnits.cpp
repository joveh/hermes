#include "gtest/gtest.h"

#include "hermes.h"

namespace hermes {

TEST(UnitsBasic, LengthOperations) {
	QLength x(2.3_km), y(3.2_m), z(0.0);
	z = x + y;
	EXPECT_EQ(z, 2303.2_m);
}

TEST(UnitsBasic, Angles) {
	QAngle omega(2_pi);

	EXPECT_EQ(omega, 360_deg);
	EXPECT_EQ(omega - 270_deg, pi/2.*radian);
}

TEST(UnitsBasic, Trigonometry) {
	QAngle alpha(1_pi/4);

	EXPECT_NEAR(sin(alpha), sqrt(2)/2, 0.0000001);
	EXPECT_NEAR(cos(alpha), sqrt(2)/2, 0.0000001);
	EXPECT_NEAR(tan(alpha), 1, 0.0000001);
}

TEST(UnitsBasic, MinMax) {
	QEnergy E1(1_J);
	QEnergy E2(2_eV);

	EXPECT_EQ(std::min(E1,E2), E2);
	EXPECT_EQ(std::max(E1,E2), E1);
}

TEST(UnitsBasic, OtherOperations) {
	QTime t1(1);
	QTime t2(3);

	EXPECT_EQ(squared(t2) + squared(t1), 10*pow<2>(1_s));
	EXPECT_LT(t1, 1_h);
	EXPECT_GT(t1, 1_ms);
}

TEST(UnitsDerived, Derived) {
	QEnergy E(10.0_J);
	QPressure P(5.0_Pa);
	EXPECT_EQ(static_cast<double>(E), 10.0);
	EXPECT_EQ(P, 5 * newton / (metre*metre));
}

TEST(UnitsDerived, FineStructureConst) {
	QNumber alpha = mu0 / 4_pi * e_plus * e_plus * c_light / h_planck_bar;
	EXPECT_NEAR(static_cast<double>(alpha), 1/137.035999, 0.0001);
}



int main(int argc, char **argv) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}

} // namespace hermes
