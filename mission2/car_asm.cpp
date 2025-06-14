#if 0
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unordered_map>
#include <string>

#define CLEAR_SCREEN "\033[H\033[2J"

#define STR_ENUM(e) (#e)
#define STR_EXIT "exit"
#define NUM_BACK (0)
#define MAX_BUF_SIZE 100
#define DELAY_MS_NORMAL 800
#define DELAY_MS_WAIT 1500
#define DELAY_MS_RUN 2000

enum QuestionType
{
    CAR_TYPE_Q,
    ENGINE_Q,
    BRAKE_SYSTEM_Q,
    STEERING_SYSTEM_Q,
    RUN_TEST_Q,
    MAX_QUESTION_TYPE
};

enum CarType
{
    START_CAR_TYPE = 1,
    SEDAN = START_CAR_TYPE,
    SUV,
    TRUCK,
    MAX_CAR_TYPE
};

enum Engine
{
    START_ENGINE_TYPE = 1,
    GM = START_ENGINE_TYPE,
    TOYOTA,
    WIA,
    MAX_ENGINE_TYPE
};

enum BrakeSystem
{
    START_BRAKE_SYSTEM = 1,
    MANDO = START_BRAKE_SYSTEM,
    CONTINENTAL,
    BOSCH_B,
    MAX_BRAKE_SYSTEM
};

enum SteeringSystem
{
    START_STEERING_SYSTEM = 1,
    BOSCH_S = START_STEERING_SYSTEM,
    MOBIS,
    MAX_STEERING_SYSTEM
};

enum run_test_step
{
    START_RUN_TEST = 1,
    RUN = START_RUN_TEST,
    TEST,
    MAX_RUN_TEST
};

class CarAssembly {
public:
    CarAssembly();

    void delay(int ms);
    void PrintCarType();
    void PrintEngineType();

    void PrintBrakeSystem();
    void PrintSteeringSystem();
    void PrintRunTest();

    void PrintSelectType(int step);

    void InitCarType();
    void AddCarType(int num, std::string str);


    int GetCarMaxNum();
    void InitEngineType();
    void AddEngineType(int num, std::string str);
    int GetEngineMaxNum();
    void InitBrakeType();
    void AddBrakeType(int num, std::string str);
    int GetBrakeMaxNum();
    void InitSteeringType();
    void AddSteeringType(int num, std::string str);
    int GetSteeringMaxNum();

    bool CheckType(int step, int answer);
    bool IsAnswerNumber(char* checkNumber);

    void selectCarType(int answer);
    void printCarType(int type);
    void selectEngine(int answer);
    void printEngine(int type);

    void selectBrakeSystem(int answer);
    void printBrakeSystem(int type);
    void selectSteeringSystem(int answer);
    void printSteeringSystem(int type);
    int isValidCheckByCompany();
    void runProducedCar();
    void testProducedCar();
    
    static CarAssembly& getIncetance() { // Singleton pattern
        static CarAssembly s;
        return s;
    }
private:
    int stack[MAX_QUESTION_TYPE];
    std::unordered_map<int, std::string> umap_car_type;
    std::unordered_map<int, std::string> umap_engine_type;
    std::unordered_map<int, std::string> umap_brake_type;
    std::unordered_map<int, std::string> umap_steering_type;
};

CarAssembly::CarAssembly() {
    memset(stack, 0x0, sizeof(stack));
    InitCarType();
    InitEngineType();
    InitBrakeType();
    InitSteeringType();
}

void CarAssembly::delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

void CarAssembly::PrintCarType() {
    printf(CLEAR_SCREEN);

    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
    printf("어떤 차량 타입을 선택할까요?\n");
    for (const auto& pair : umap_car_type) {
        if (pair.first >= START_CAR_TYPE)
            printf("%d. %s\n", pair.first, pair.second.c_str());
    }
}
void CarAssembly::PrintEngineType() {
    int max_num = (int)umap_engine_type.size();
    printf(CLEAR_SCREEN);
    printf("어떤 엔진을 탑재할까요?\n");
    printf("0. back\n");
    for (const auto& pair : umap_engine_type) {
        if (pair.first >= START_ENGINE_TYPE)
            printf("%d. %s\n", pair.first, pair.second.c_str());
    }
    printf("%d. 고장난 엔진\n", max_num);
}

void CarAssembly::PrintBrakeSystem() {
    printf(CLEAR_SCREEN);
    printf("어떤 제동장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    for (const auto& pair : umap_brake_type) {
        if (pair.first >= START_BRAKE_SYSTEM)
            printf("%d. %s\n", pair.first, pair.second.c_str());
    }
}
void CarAssembly::PrintSteeringSystem() {
    printf(CLEAR_SCREEN);
    printf("어떤 조향장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    for (const auto& pair : umap_steering_type) {
        if (pair.first >= START_STEERING_SYSTEM)
            printf("%d. %s\n", pair.first, pair.second.c_str());
    }
}
void CarAssembly::PrintRunTest() {
    printf(CLEAR_SCREEN);
    printf("멋진 차량이 완성되었습니다.\n");
    printf("어떤 동작을 할까요?\n");
    printf("0. 처음 화면으로 돌아가기\n");
    printf("1. RUN\n");
    printf("2. Test\n");
}

void CarAssembly::PrintSelectType(int step) {
    if (step == CAR_TYPE_Q)
    {
        PrintCarType();
    }
    else if (step == ENGINE_Q)
    {
        PrintEngineType();
    }
    else if (step == BRAKE_SYSTEM_Q)
    {
        PrintBrakeSystem();
    }
    else if (step == STEERING_SYSTEM_Q)
    {
        PrintSteeringSystem();
    }
    else if (step == RUN_TEST_Q)
    {
        PrintRunTest();
    }
    printf("===============================\n");
}

void CarAssembly::InitCarType() {
    umap_car_type.clear();
    umap_car_type[0] = "NO_TYPE";
    umap_car_type[SEDAN] = STR_ENUM(SEDAN);
    umap_car_type[SUV] = STR_ENUM(SUV);
    umap_car_type[TRUCK] = STR_ENUM(TRUCK);
}
void CarAssembly::AddCarType(int num, std::string str) {
    umap_car_type[num] = str;
}


int CarAssembly::GetCarMaxNum() {
    return (int)umap_car_type.size();
}
void CarAssembly::InitEngineType() {
    umap_engine_type.clear();
    umap_engine_type[0] = "NO_TYPE";
    umap_engine_type[GM] = STR_ENUM(GM);
    umap_engine_type[TOYOTA] = STR_ENUM(TOYOTA);
    umap_engine_type[WIA] = STR_ENUM(WIA);
}
void CarAssembly::AddEngineType(int num, std::string str) {
    umap_engine_type[num] = str;
}
int CarAssembly::GetEngineMaxNum() {
    return (int)umap_engine_type.size();
}
void CarAssembly::InitBrakeType() {
    umap_brake_type.clear();
    umap_brake_type[0] = "NO_TYPE";
    umap_brake_type[MANDO] = STR_ENUM(MANDO);
    umap_brake_type[CONTINENTAL] = STR_ENUM(CONTINENTAL);
    umap_brake_type[BOSCH_B] = STR_ENUM(BOSCH_B);
}
void CarAssembly::AddBrakeType(int num, std::string str) {
    umap_brake_type[num] = str;
}
int CarAssembly::GetBrakeMaxNum() {
    return (int)umap_brake_type.size();
}
void CarAssembly::InitSteeringType() {
    umap_steering_type.clear();
    umap_steering_type[0] = "NO_TYPE";
    umap_steering_type[BOSCH_S] = STR_ENUM(BOSCH_S);
    umap_steering_type[MOBIS] = STR_ENUM(MOBIS);
}
void CarAssembly::AddSteeringType(int num, std::string str) {
    umap_steering_type[num] = str;
}
int CarAssembly::GetSteeringMaxNum() {
    return (int)umap_steering_type.size();
}

bool CarAssembly::CheckType(int step, int answer) {
    bool ret = true;

    if (step == CAR_TYPE_Q && !(answer >= START_CAR_TYPE && answer < GetCarMaxNum()))
    {
        printf("ERROR :: 차량 타입은 %d ~ %d 범위만 선택 가능\n", START_CAR_TYPE, GetCarMaxNum() - 1);
        ret = false;
    }

    if (step == ENGINE_Q && !(answer >= NUM_BACK && answer < GetEngineMaxNum()))
    {
        printf("ERROR :: 엔진은 %d ~ %d 범위만 선택 가능\n", START_ENGINE_TYPE, GetEngineMaxNum() - 1);
        ret = false;
    }

    if (step == BRAKE_SYSTEM_Q && !(answer >= NUM_BACK && answer < GetBrakeMaxNum()))
    {
        printf("ERROR :: 제동장치는 %d ~ %d 범위만 선택 가능\n", START_BRAKE_SYSTEM, GetBrakeMaxNum() - 1);
        ret = false;
    }

    if (step == STEERING_SYSTEM_Q && !(answer >= NUM_BACK && answer < GetSteeringMaxNum()))
    {
        printf("ERROR :: 조향장치는 %d ~ %d 범위만 선택 가능\n", START_STEERING_SYSTEM, GetSteeringMaxNum() - 1);
        ret = false;
    }

    if (step == RUN_TEST_Q && !(answer >= NUM_BACK && answer < MAX_RUN_TEST))
    {
        printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
        ret = false;
    }
    return ret;
}
bool CarAssembly::IsAnswerNumber(char* checkNumber) {
    if (checkNumber == nullptr) {
        printf("ERROR :: checkNumber == nullptr\n");
        return false;
    }
    if (*checkNumber != '\0')
    {
        printf("ERROR :: 숫자만 입력 가능\n");
        return false;
    }
    return true;
}

void CarAssembly::selectCarType(int answer)
{
    stack[CAR_TYPE_Q] = answer;

    auto item = umap_car_type.find(answer);
    if (item == umap_car_type.end()) {
        return;
    }
    printf("차량 타입으로 %s을 선택하셨습니다.\n", item->second.c_str());
}

void CarAssembly::printCarType(int type)
{
    auto item = umap_car_type.find(type);
    if (item == umap_car_type.end()) {
        return;
    }
    printf("Car Type : %s\n", item->second.c_str());
}
void CarAssembly::selectEngine(int answer)
{
    stack[ENGINE_Q] = answer;

    auto item = umap_engine_type.find(answer);
    if (item == umap_engine_type.end()) {
        return;
    }

    printf("%s 엔진을 선택하셨습니다.\n", item->second.c_str());
}
void CarAssembly::printEngine(int type)
{
    auto item = umap_engine_type.find(type);
    if (item == umap_engine_type.end()) {
        return;
    }
    printf("Engine : %s\n", item->second.c_str());
}

void CarAssembly::selectBrakeSystem(int answer)
{
    stack[BRAKE_SYSTEM_Q] = answer;

    auto item = umap_brake_type.find(answer);
    if (item == umap_brake_type.end()) {
        return;
    }

    printf("%s 제동장치를 선택하셨습니다.\n", item->second.c_str());
}
void CarAssembly::printBrakeSystem(int type)
{
    auto item = umap_brake_type.find(type);
    if (item == umap_brake_type.end()) {
        return;
    }
    printf("Brake System : %s\n", item->second.c_str());
}
void CarAssembly::selectSteeringSystem(int answer)
{
    stack[STEERING_SYSTEM_Q] = answer;

    auto item = umap_steering_type.find(answer);
    if (item == umap_steering_type.end()) {
        return;
    }

    printf("%s 조향장치를 선택하셨습니다.\n", item->second.c_str());
}
void CarAssembly::printSteeringSystem(int type)
{
    auto item = umap_steering_type.find(type);
    if (item == umap_steering_type.end()) {
        return;
    }
    printf("SteeringSystem : %s\n", item->second.c_str());
}
int CarAssembly::isValidCheckByCompany()
{
    if (stack[CAR_TYPE_Q] == SEDAN && stack[BRAKE_SYSTEM_Q] == CONTINENTAL)
    {
        return false;
    }
    else if (stack[CAR_TYPE_Q] == SUV && stack[ENGINE_Q] == TOYOTA)
    {
        return false;
    }
    else if (stack[CAR_TYPE_Q] == TRUCK && stack[ENGINE_Q] == WIA)
    {
        return false;
    }
    else if (stack[CAR_TYPE_Q] == TRUCK && stack[BRAKE_SYSTEM_Q] == MANDO)
    {
        return false;
    }
    else if (stack[BRAKE_SYSTEM_Q] == BOSCH_B && stack[STEERING_SYSTEM_Q] != BOSCH_S)
    {
        return false;
    }
    else
    {
        return true;
    }
    return true;
}

void CarAssembly::runProducedCar()
{
    if (isValidCheckByCompany() == false)
    {
        printf("자동차가 동작되지 않습니다\n");
    }
    else
    {
        if (stack[ENGINE_Q] == GetEngineMaxNum())
        {
            printf("엔진이 고장나있습니다.\n");
            printf("자동차가 움직이지 않습니다.\n");
        }
        else
        {
            printCarType(stack[CAR_TYPE_Q]);
            printEngine(stack[ENGINE_Q]);
            printBrakeSystem(stack[BRAKE_SYSTEM_Q]);
            printSteeringSystem(stack[STEERING_SYSTEM_Q]);
            printf("자동차가 동작됩니다.\n");
        }
    }
}

void CarAssembly::testProducedCar()
{
    if (stack[CAR_TYPE_Q] == SEDAN && stack[BRAKE_SYSTEM_Q] == CONTINENTAL)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
    }
    else if (stack[CAR_TYPE_Q] == SUV && stack[ENGINE_Q] == TOYOTA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
    }
    else if (stack[CAR_TYPE_Q] == TRUCK && stack[ENGINE_Q] == WIA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
    }
    else if (stack[CAR_TYPE_Q] == TRUCK && stack[BRAKE_SYSTEM_Q] == MANDO)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
    }
    else if (stack[BRAKE_SYSTEM_Q] == BOSCH_B && stack[STEERING_SYSTEM_Q] != BOSCH_S)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch조형장치 이외 사용 불가\n");

    }
    else
    {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
    }
}
#endif


