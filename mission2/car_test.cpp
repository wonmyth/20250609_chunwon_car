#include "gmock/gmock.h"
//#include "car_asm.cpp"
#include "car_asm_code.cpp"

using namespace testing;

class MockCarAssembly : public CarAssembly {
public:
	// MOCK_METHOD(int, getSum, (int a, int b), ());
};


TEST(Group, TC1) {
	CarAssembly& car = CarAssembly::getIncetance();
	//int ret = cal.getSum(10, 20);
	//EXPECT_EQ(30, ret);
}
TEST(Group, TC2) {
	CarAssembly& car = CarAssembly::getIncetance();

	car.delay(DELAY_MS_NORMAL);
}

TEST(Group, TC3) {
	CarAssembly& car = CarAssembly::getIncetance();
	std::string str = "CAR_TYPE_1";
	int ret = car.AddCarType(car.GetCarMaxNum(), str);
	EXPECT_EQ(car.GetCarMaxNum(), ret);
}

TEST(Group, TC4) {
	CarAssembly& car = CarAssembly::getIncetance();
	std::string str = "ENGINE_TYPE_1";
	int ret = car.AddEngineType(car.GetEngineMaxNum(), str);
	EXPECT_EQ(car.GetEngineMaxNum(), ret);
}

TEST(Group, TC5) {
	CarAssembly& car = CarAssembly::getIncetance();
	std::string str = "BRAKE_TYPE_1";
	int ret = car.AddBrakeType(car.GetBrakeMaxNum(), str);
	EXPECT_EQ(car.GetBrakeMaxNum(), ret);
}

TEST(Group, TC6) {
	CarAssembly& car = CarAssembly::getIncetance();
	std::string str = "STEERING_TYPE_1";
	int ret = car.AddSteeringType(car.GetSteeringMaxNum(), str);
	EXPECT_EQ(car.GetSteeringMaxNum(), ret);
}

TEST(Group, TC7) {
	CarAssembly& car = CarAssembly::getIncetance();
	int step, answer, ret;

	step = CAR_TYPE_Q;
	answer = car.GetCarMaxNum();
	ret = car.CheckType(step, answer);
	EXPECT_EQ(false, ret);

	step = ENGINE_Q;
	answer = car.GetEngineMaxNum();
	ret = car.CheckType(step, answer);
	EXPECT_EQ(false, ret);

	step = BRAKE_SYSTEM_Q;
	answer = car.GetBrakeMaxNum();
	ret = car.CheckType(step, answer);
	EXPECT_EQ(false, ret);

	step = STEERING_SYSTEM_Q;
	answer = car.GetSteeringMaxNum();
	ret = car.CheckType(step, answer);
	EXPECT_EQ(false, ret);

	step = RUN_TEST_Q;
	answer = MAX_RUN_TEST;
	ret = car.CheckType(step, answer);
	EXPECT_EQ(false, ret);

	step = RUN_TEST_Q;
	answer = NUM_BACK;
	ret = car.CheckType(step, answer);
	EXPECT_EQ(true, ret);
}

TEST(Group, TC8) {
	CarAssembly& car = CarAssembly::getIncetance();
	
	bool ret;

	char* checkNumber = nullptr;
	ret = car.IsAnswerNumber(checkNumber);
	EXPECT_EQ(false, ret);

	char checkNumber_a[] = "A\n";
	ret = car.IsAnswerNumber(checkNumber_a);
	EXPECT_EQ(false, ret);

	char checkNumber_1[] = "\0";
	ret = car.IsAnswerNumber(checkNumber_1);
	EXPECT_EQ(true, ret);
}

TEST(Group, TC_PrintSelectType) {
	CarAssembly& car = CarAssembly::getIncetance();
	int step;

	step = CAR_TYPE_Q;
	car.PrintSelectType(step);

	step = ENGINE_Q;
	car.PrintSelectType(step);

	step = BRAKE_SYSTEM_Q;
	car.PrintSelectType(step);

	step = STEERING_SYSTEM_Q;
	car.PrintSelectType(step);

	step = RUN_TEST_Q;
	car.PrintSelectType(step);
}

TEST(Group, TC_selectCarType) {
	CarAssembly& car = CarAssembly::getIncetance();
	int answer;

	answer = SEDAN;
	car.selectCarType(answer);
	car.printCarType(answer);

	answer = car.GetCarMaxNum();
	car.selectCarType(answer);
	car.printCarType(answer);
}

TEST(Group, TC_selectEngine) {
	CarAssembly& car = CarAssembly::getIncetance();
	int answer;

	answer = GM;
	car.selectEngine(answer);
	car.printEngine(answer);

	answer = car.GetEngineMaxNum();
	car.selectEngine(answer);
	car.printEngine(answer);
}

TEST(Group, TC_selectBrakeSystem) {
	CarAssembly& car = CarAssembly::getIncetance();
	int answer;

	answer = MANDO;
	car.selectBrakeSystem(answer);
	car.printBrakeSystem(answer);

	answer = car.GetBrakeMaxNum();
	car.selectBrakeSystem(answer);
	car.printBrakeSystem(answer);
}

TEST(Group, TC_selectSteeringSystem) {
	CarAssembly& car = CarAssembly::getIncetance();
	int answer;

	answer = BOSCH_S;
	car.selectSteeringSystem(answer);
	car.printSteeringSystem(answer);

	answer = car.GetSteeringMaxNum();
	car.selectSteeringSystem(answer);
	car.printSteeringSystem(answer);
}

TEST(Group, TC_isValidCheckByCompany) {
	CarAssembly& car = CarAssembly::getIncetance();
	int fail_type;
	bool ret;

	car.selectCarType(SEDAN);
	car.selectBrakeSystem(CONTINENTAL);
	ret = car.isValidCheckByCompany(&fail_type);
	EXPECT_EQ(false, ret);
	EXPECT_EQ(MATCH_SEDAN_CONTINENTAL, fail_type);

	car.testProducedCar();
}

TEST(Group, TC_isValidCheckByCompany2) {
	CarAssembly& car = CarAssembly::getIncetance();
	int fail_type;
	bool ret;
	car.selectCarType(SUV);
	car.selectEngine(TOYOTA);
	ret = car.isValidCheckByCompany(&fail_type);
	EXPECT_EQ(false, ret);
	EXPECT_EQ(MATCH_SUV_TOYOTA, fail_type);
	car.testProducedCar();
}

TEST(Group, TC_isValidCheckByCompany3) {
	CarAssembly& car = CarAssembly::getIncetance();
	int fail_type;
	bool ret;
	car.selectCarType(TRUCK);
	car.selectEngine(WIA);
	ret = car.isValidCheckByCompany(&fail_type);
	EXPECT_EQ(false, ret);
	EXPECT_EQ(MATCH_TRUCK_WIA, fail_type);
	car.testProducedCar();
}
TEST(Group, TC_isValidCheckByCompany4) {
	CarAssembly& car = CarAssembly::getIncetance();
	int fail_type;
	bool ret;
	car.selectCarType(TRUCK);
	car.selectBrakeSystem(MANDO);
	ret = car.isValidCheckByCompany(&fail_type);
	EXPECT_EQ(false, ret);
	EXPECT_EQ(MATCH_TRUCK_MANDO, fail_type);
	car.testProducedCar();
}

TEST(Group, TC_isValidCheckByCompany5) {
	CarAssembly& car = CarAssembly::getIncetance();
	int fail_type;
	bool ret;
	car.selectBrakeSystem(BOSCH_B);
	car.selectSteeringSystem(MOBIS);
	ret = car.isValidCheckByCompany(&fail_type);
	EXPECT_EQ(false, ret);
	EXPECT_EQ(MATCH_BOSCH_B_BOSCH_S, fail_type);
	car.testProducedCar();
}
TEST(Group, TC_isValidCheckByCompany6) {
	CarAssembly& car = CarAssembly::getIncetance();
	int *fail_type = nullptr;
	bool ret;
	
	ret = car.isValidCheckByCompany(fail_type);
	EXPECT_EQ(false, ret);
	car.testProducedCar();
}

TEST(Group, TC_isValidCheckByCompany7) {
	CarAssembly& car = CarAssembly::getIncetance();
	int fail_type;
	bool ret;
	car.selectCarType(SEDAN);
	car.selectEngine(WIA);
	ret = car.isValidCheckByCompany(&fail_type);
	EXPECT_EQ(true, ret);
	EXPECT_EQ(MATCH_SUCCESS, fail_type);
	car.testProducedCar();
}

TEST(Group, TC_runProducedCar) {
	CarAssembly& car = CarAssembly::getIncetance();
	int fail_type;
	bool ret;
	car.selectCarType(SEDAN);
	car.selectBrakeSystem(CONTINENTAL);
	ret = car.isValidCheckByCompany(&fail_type);
	EXPECT_EQ(false, ret);
	EXPECT_EQ(MATCH_SEDAN_CONTINENTAL, fail_type);
	car.runProducedCar();
}
TEST(Group, TC_runProducedCar2) {
	int fail_type;
	CarAssembly& car = CarAssembly::getIncetance();
	car.selectEngine(car.GetEngineMaxNum());
	car.runProducedCar();
}
TEST(Group, TC_runProducedCar3) {
	CarAssembly& car = CarAssembly::getIncetance();
	car.selectCarType(SEDAN);
	car.selectEngine(WIA);
	car.runProducedCar();
}




