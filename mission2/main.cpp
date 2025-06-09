#include "gmock/gmock.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
	testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}

#else
#include <stdio.h>
#include "car_asm_code.cpp"

int main()
{
    char buf[MAX_BUF_SIZE];
    int step = CAR_TYPE_Q;
    InitCarType();
    InitEngineType();
    InitBrakeType();
    InitSteeringType();

    while (1)
    {

        PrintSelectType(step);

        printf("INPUT > ");
        fgets(buf, sizeof(buf), stdin);

        // ���� ���๮�� ����
        char* context = nullptr;
        strtok_s(buf, "\r", &context);
        strtok_s(buf, "\n", &context);

        if (!strcmp(buf, STR_EXIT))
        {
            printf("���̹���\n");
            break;
        }

        // ���ڷ� �� ������� Ȯ��
        char* checkNumber;
        int answer = strtol(buf, &checkNumber, 10); // ���ڿ��� 10������ ��ȯ

        // �Է¹��� ���ڰ� ���ڰ� �ƴ϶��
        if (IsAnswerNumber(checkNumber) == false) {
            delay(DELAY_MS_NORMAL);
            continue;
        }

        if (CheckType(step, answer) == false) {
            delay(DELAY_MS_NORMAL);
            continue;
        }

        // ó������ ���ư���
        if (answer == NUM_BACK && step == RUN_TEST_Q)
        {
            step = CAR_TYPE_Q;
            continue;
        }

        // �������� ���ư���
        if (answer == NUM_BACK && step >= ENGINE_Q)
        {
            step -= 1;
            continue;
        }

        if (step == CAR_TYPE_Q)
        {
            selectCarType(answer);
            delay(DELAY_MS_NORMAL);
            step = ENGINE_Q;
        }
        else if (step == ENGINE_Q)
        {
            selectEngine(answer);
            delay(DELAY_MS_NORMAL);
            step = BRAKE_SYSTEM_Q;
        }
        else if (step == BRAKE_SYSTEM_Q)
        {
            selectBrakeSystem(answer);
            delay(DELAY_MS_NORMAL);
            step = STEERING_SYSTEM_Q;
        }
        else if (step == STEERING_SYSTEM_Q)
        {
            selectSteeringSystem(answer);
            delay(DELAY_MS_NORMAL);
            step = RUN_TEST_Q;
        }
        else if (step == RUN_TEST_Q && answer == RUN)
        {
            runProducedCar();
            delay(DELAY_MS_RUN);
        }
        else if (step == RUN_TEST_Q && answer == TEST)
        {
            printf("Test...\n");
            delay(DELAY_MS_WAIT);
            testProducedCar();
            delay(DELAY_MS_RUN);
        }
    }
}
#endif
