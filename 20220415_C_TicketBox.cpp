// 2022.04.14 -> 2022.04.15 ���� 
// Ticket Box program for a theme park.
// Ư�̻��� 
// (1) 12���� �̸� : ����
// (2) 12���� �̻�~36���� �̸� : ����� ����. ���ƿ� ���̱ⱸ ž�� ���� ���, ���ƿ� �����̿�� ���� ����.
// (3) ��� ��� & ��� ��� : �ߺ� ���� �Ұ�. ���� ���ϴ� ��� �׸� ���� �ʿ�. 

#include <stdio.h>
#include <time.h> 

int main () {
	
	// ���� ��¥ �ҷ����� 
	time_t t = time(NULL);
	struct tm today = *localtime(&t);
	int todayYear = today.tm_year + 1900;
	int todayMonth = today.tm_mon + 1;
	int todayDay = today.tm_mday;
	
	// ��� ��� & ���� ����
	const int PRICE_ALL_1DAY_ADULT = 62000, PRICE_ALL_1DAY_JUVENILE = 54000, PRICE_ALL_1DAY_CHILD = 47000, PRICE_ALL_1DAY_BABY=15000, PRICE_ALL_1DAY_NEWBORN = 0;
	const int PRICE_ALL_AFTER4_ADULT = 50000, PRICE_ALL_AFTER4_JUVENILE = 43000, PRICE_ALL_AFTER4_CHILD = 36000, PRICE_ALL_AFTER4_BABY = 15000, PRICE_ALL_AFTER4_NEWBORN = 0;  
	const int PRICE_PARK_1DAY_ADULT = 59000, PRICE_PARK_1DAY_JUVENILE = 52000, PRICE_PARK_1DAY_CHILD = 46000, PRICE_PARK_1DAY_BABY = 15000, PRICE_PARK_1DAY_NEWBORN = 0;
	const int PRICE_PARK_AFTER4_ADULT = 47000, PRICE_PARK_AFTER4_JUVENILE = 41000, PRICE_PARK_AFTER4_CHILD = 35000, PRICE_PARK_AFTER4_BABY = 15000, PRICE_PARK_AFTER4_NEWBORN = 0; 
	int priceArray[6]; // ���� ���ÿ� ���� ��� �Է��� �迭 
	char* PRINT_TICKET;
	
	// ���� ��� & ���� ���� 
	const int ELDER_AGE_MIN = 65;
	const int ADULT_AGE_MAX = 64, ADULT_AGE_MIN = 19;
	const int JUVENILE_AGE_MAX = 18, JUVERNILE_AGE_MIN = 13;
	const int CHILD_AGE_MAX = 12, CHILD_AGE_MIN = 3;
	const int BABY_AGE_MAX = 2, BABY_AGE_MIN = 1; 
	const int NEWBORN_AGE = 0;
	const int INDEX_MALE_OLD = 1, INDEX_FEMALE_OLD = 2, INDEX_MALE_NEW = 3, INDEX_FEMALE_NEW = 4; 
	const int BIRTH_YEAR_ADD_OLD = 1900, BIRTH_YEAR_ADD_NEW = 2000;
	char* PRINT_AGE;
	
	// ������  ��� ����
	const float BENEFIT_NON = 0, BENEFIT_DISABLED = 0.5, BENEFIT_NATIONAL_MERIT = 0.5, BENEFIT_PREGNANT = 0.5, BENEFIT_ARMY = 0.49, BENEFIT_MULTICHILD = 0.3;
	const int  BENEFIT_NON_MAX = 0, BENEFIT_DISABLED_MAX = 2, BENEFIT_NATIONAL_MERIT_MAX = 2, BENEFIT_PREGNANT_MAX = 1, BENEFIT_ARMY_MAX = 2, BENEFIT_MULTICHILD_MAX = 1;
	char* PRINT_BENEFIT;
	
	// �Է� ���� ����
	int inputTicketSelect; 		// ���� ���� 
	int inputTicketSelect_Baby; // ���ƿ� ���� ���� 
	char inputSocialID[7]; 		// ����� �ֹε�Ϲ�ȣ 
	int inputNumberOfTicket;	// Ƽ�� ���� 
	int inputBenefit; 			// ������ 
	int inputBenefit_Elder;		// ��� ��� ����� �߰� ���� (��� ��� vs ��� ���)
	
	// ��� ���� ���� 
	int birthYearIndex; 		// 1900��� & 2000���� ����
	int userBirthYear;			// ����� ���� 
	int userBirthMonth;			// ����� ���� 
	int userBirthDay;			// ����� ���� 
	int userAge;				// **����� ���� 
	int ticketPrice;			// **���� & ���̿� ���� Ƽ�� ���� 
	int totalTicketPrice;		// **Ƽ�� ���� X ���� 
	float appliedBenefit;		// ����� ������ �ݾ� (������ ���� �ݾ� ��� ������ �޾ƿ� ����) 
	int discountedTicketPrice;	// **������ �������� ���� ���� �ݾ�
	int discountedTicketNumber; // **������ ����� Ƽ�� ���� 
	int finalTicketPrice;		// **totalTicketPrice - discountedTicketPrice
	int continueTicketPurchase; // Ƽ�� �߱� ���μ��� �ݺ� ���� ���� 
	int NewPurchase;			// ���ο� �ֹ� ���� ���� ���� 
	
	// �μ�� ��� ���� 
	// 1. ���� 
	const char* PRINT_TICKET_ALL_1DAY = "�����̿�� - �ְ���(1DAY)";
	const char* PRINT_TICKET_ALL_AFETR4 = "�����̿�� - �߰���(AFTER4)";
	const char* PRINT_TICKET_PARK_1DAY = "��ũ�̿�� - �ְ���(1DAY)";
	const char* PRINT_TICKET_PARK_AFETER4 = "��ũ�̿�� - �߰���(AFTER4)";
	// 2. ����
	const char* PRINT_AGE_ADULT = "����";
	const char* PRINT_AGE_JUVENILE = "û�ҳ�";
	const char* PRINT_AGE_CHILD = "���";
	const char* PRINT_AGE_BABY = "���̺�";
	const char* PRINT_AGE_NEWBORN = "����";
	const char* PRINT_AGE_ELDER = "���� - ��� ��� ����";
	// 3. ��� ���� 
	const char* PRINT_BENEFIT_NON = "*��� ���� ����";
	const char* PRINT_BENEFIT_DISABLED = "*����� ��� ����";
	const char* PRINT_BENEFIT_NATIONAL_MERIT = "*���������� ��� ����";
	const char* PRINT_BENEFIT_PREGNANT = "*�ӻ�� ��� ����";
	const char* PRINT_BENEFIT_ARMY = "*�ް��庴 ��� ����";
	const char* PRINT_BENEFIT_MULTICHILD = "*�ٵ��� �ູī�� ��� ����";
	 
	
	do { // ~ while => Begin a new purchasing process after payment of a prior process. 
	 
	// ���� ������ ���� ����
	int accumulatedFinalPrice = 0; // �� �ֹ� �ݾ� 
	int accumulatedTicketNumber = 0; // �� �ֹ� Ƽ�� ���� 
	
		// Ƽ�� �ֹ� ���� 
		do { // ~ while => return to beginning of the process if the user select "continue purchasing ticket" at the end of the process. 
		
			do {
				printf("������ �����ϼ���.\n\t1. �����̿�� - �ְ���(1DAY)\n\t2. �����̿�� - �߰���(AFTER4)\n\t3. ��ũ�̿�� - �ְ���(1DAY)\n\t4. ��ũ�̿�� - �߰���(AFTER4)\n\t => ");
				scanf("%d", &inputTicketSelect);
			} while (inputTicketSelect < 1 || inputTicketSelect > 4); 
			// 1~4 �� ���� �� ����â �����. 
			
			do {
			printf("Ƽ�� ������� �ֹε�Ϲ�ȣ �� 7�ڸ��� �Է��ϼ���.(�� 6�ڸ� & ���ڸ� ù ��° ����))\n\t => ");
			scanf("%s", &inputSocialID);
			} while ( ((inputSocialID[2]-48)*10 + (inputSocialID[3]-48)) > 12 || ((inputSocialID[4]-48)*10 + (inputSocialID[5]-48)) > 31 || inputSocialID[6]-48 > 4 );
			
			do {
				printf("�ֹ� ������ �Է��ϼ���. (�ִ� 10��)\n\t => ");
				scanf("%d", &inputNumberOfTicket);
			} while ( inputNumberOfTicket < 1 || inputNumberOfTicket > 10);
			
			do {
				printf("�������� �����ϼ���.\n\t1. ���� (���� ���� �ڵ� ó��)\n\t2. �����\n\t3. ����������\n\t4. �ӻ�� (�����̿�Ǹ� �ش�)\n\t5. �ް��庴 (�����̿�Ǹ� �ش�)\n\t6. ���ڳ� (�����̿�Ǹ� �ش�)\n\t => ");
				scanf("%d", &inputBenefit);
			} while (inputBenefit < 1 || inputBenefit > 6);
			// 1~6 �� ���� �� ����â �����. 
			
			// ���� ���ÿ� ���� Price List  
			switch (inputTicketSelect) {
				case 1:
					priceArray[0] = PRICE_ALL_1DAY_CHILD;
					priceArray[1] = PRICE_ALL_1DAY_ADULT;
					priceArray[2] = PRICE_ALL_1DAY_JUVENILE;
					priceArray[3] = PRICE_ALL_1DAY_CHILD;
					priceArray[4] = PRICE_ALL_1DAY_BABY;
					priceArray[5] = PRICE_ALL_1DAY_NEWBORN;
					break;
				case 2:
					priceArray[1] = PRICE_ALL_AFTER4_CHILD;
					priceArray[2] = PRICE_ALL_AFTER4_ADULT;
					priceArray[2] = PRICE_ALL_AFTER4_JUVENILE;
					priceArray[3] = PRICE_ALL_AFTER4_CHILD;
					priceArray[4] = PRICE_ALL_AFTER4_BABY;
					priceArray[5] = PRICE_ALL_AFTER4_NEWBORN;
					break;
				case 3:
					priceArray[0] = PRICE_PARK_1DAY_CHILD;
					priceArray[1] = PRICE_PARK_1DAY_ADULT;
					priceArray[2] = PRICE_PARK_1DAY_JUVENILE;
					priceArray[3] = PRICE_PARK_1DAY_CHILD;
					priceArray[4] = PRICE_PARK_1DAY_BABY;
					priceArray[5] = PRICE_PARK_1DAY_NEWBORN;
					break;
				case 4:
					priceArray[0] = PRICE_PARK_AFTER4_CHILD;
					priceArray[1] = PRICE_PARK_AFTER4_ADULT;
					priceArray[2] = PRICE_PARK_AFTER4_JUVENILE;
					priceArray[3] = PRICE_PARK_AFTER4_CHILD;
					priceArray[4] = PRICE_PARK_AFTER4_BABY;
					priceArray[5] = PRICE_PARK_AFTER4_NEWBORN;
					break;
				default :
					break;
			}
			
			// International Age of the user. (-48 ==> change ASCII code to Decimal number)
			birthYearIndex = inputSocialID[6]-48;
			if (birthYearIndex == INDEX_MALE_OLD || birthYearIndex == INDEX_FEMALE_OLD) {
				userBirthYear = (inputSocialID[0]-48)*10 + (inputSocialID[1]-48) + BIRTH_YEAR_ADD_OLD;
			} else if (birthYearIndex == INDEX_MALE_NEW || birthYearIndex == INDEX_FEMALE_NEW) {
				userBirthYear = (inputSocialID[0]-48)*10 + (inputSocialID[1]-48) + BIRTH_YEAR_ADD_NEW;
			} 
			userBirthMonth = (inputSocialID[2]-48)*10 + (inputSocialID[3]-48);
			userBirthDay = (inputSocialID[4]-48)*10 + (inputSocialID[5]-48);
			if (userBirthMonth < todayMonth || (userBirthMonth == todayMonth && userBirthDay <= todayDay)) {
				userAge = (todayYear) - userBirthYear;
			} else {
				userAge = (todayYear) - userBirthYear - 1;
			}
			
			// Confirm the price ticket considering age of the user.
			
			if (userAge >= ELDER_AGE_MIN && inputBenefit != 1) {											// ���� - ��� (��� ��� ����) 
				do {
					printf("��� ���� �� ������ ���� �����մϴ�.\n��� ���� ��� ��� �� ������ ���Ͻô� �׸��� �����ϼ���.\n\t1. ��� ���\n\t2. ��� ���(�����, ����������, �ӻ��, �ް��庴, ���ڳడ��)\n\t=> ");
					scanf("%d", &inputBenefit_Elder);
				} while (inputBenefit_Elder < 1 || inputBenefit_Elder > 2);
				
				if (inputBenefit_Elder == 1) {
					ticketPrice = priceArray[0];
				} else if (inputBenefit_Elder == 2) {
					ticketPrice = priceArray[1];
				} 	
			} if (userAge >= ELDER_AGE_MIN && inputBenefit == 1) {
				ticketPrice = priceArray[0];	 
			} if (userAge >= ADULT_AGE_MIN  && userAge <= ADULT_AGE_MAX) { 			// ���� 
				ticketPrice = priceArray[1];
			} if (userAge >= JUVERNILE_AGE_MIN && userAge <= JUVENILE_AGE_MAX) {	// û�ҳ� 
				ticketPrice = priceArray[2];
			} if (userAge >= CHILD_AGE_MIN && userAge < CHILD_AGE_MAX) {			// ��� 
				ticketPrice = priceArray[3];
			} if ((userAge >= BABY_AGE_MIN && userAge <= BABY_AGE_MAX )) {			// ���̺� 
				do {
					printf("�� 36���� �̸� ������ ��� ������ �����Դϴ�.\n���ƿ� ���̽ü� �����̿���� �����Ͻðڽ��ϱ�?\n\t1. ���ƿ� �����̿�� ����\n\t2. ����Ǹ� ����");
					scanf("%d", &inputTicketSelect_Baby);
				} while (inputTicketSelect_Baby < 1 || inputTicketSelect_Baby > 2);
				if (inputTicketSelect_Baby == 1) {									// ���̺� �����̿�� -> 15,000�� 
					ticketPrice = priceArray[4];
				} else if (inputTicketSelect_Baby == 2)  {							// ���̺� ����� -> ���� (= newborn) 
					ticketPrice = priceArray[5];
				}	
			} if (userAge = NEWBORN_AGE) {											// ���� = 12���� �̸� (����) 
				ticketPrice = priceArray[5];
			} 
			
			// Ticket price before applying discount benefit. 
			totalTicketPrice = ticketPrice * inputNumberOfTicket;
	
			// Check the benefit and discounted amount. (��ο��� ��ÿ�� �ߺ� ������ �� ��... ���� �߰��ϱ�) 
			
			if (userAge >= ELDER_AGE_MIN && inputBenefit_Elder == 1) {
				appliedBenefit = BENEFIT_NON;
				discountedTicketNumber = BENEFIT_NON_MAX;
			} else {
				if (inputTicketSelect == 1 || inputTicketSelect == 2) { 	// ��� ��� (1) ���� �̿�� ������ ��� 
						if (inputBenefit == 1) { 	// ������ ���� 
						appliedBenefit = BENEFIT_NON;
						discountedTicketNumber = BENEFIT_NON_MAX;
					}
					if (inputBenefit == 2) { 		// ����� 
						appliedBenefit = BENEFIT_DISABLED;
						if (inputNumberOfTicket <= BENEFIT_DISABLED_MAX) {
							discountedTicketNumber = inputNumberOfTicket;
						} else {
							discountedTicketNumber = BENEFIT_DISABLED_MAX;
						}
					}
					if (inputBenefit == 3) { 		// ���������� 
						appliedBenefit = BENEFIT_NATIONAL_MERIT;
						if (inputNumberOfTicket <= BENEFIT_NATIONAL_MERIT_MAX) {
							discountedTicketNumber = inputNumberOfTicket;
						} else {
							discountedTicketNumber = BENEFIT_NATIONAL_MERIT_MAX;
						}
					} 
					if (inputBenefit == 4) { 		// �ӻ�� 
						appliedBenefit = BENEFIT_PREGNANT;
						if (inputNumberOfTicket <= BENEFIT_PREGNANT_MAX) {
							discountedTicketNumber = inputNumberOfTicket;
						} else {
							discountedTicketNumber = BENEFIT_PREGNANT_MAX;
						}
					}
					if (inputBenefit == 5) { 		// �ް��庴 
						appliedBenefit = BENEFIT_ARMY;
						if (inputNumberOfTicket <= BENEFIT_ARMY_MAX) {
							discountedTicketNumber = inputNumberOfTicket;
						} else {
							discountedTicketNumber =  BENEFIT_ARMY_MAX;
						}
					}
					if (inputBenefit == 6) { 		//���ڳ� 
						appliedBenefit = BENEFIT_MULTICHILD;
						if (inputNumberOfTicket <= BENEFIT_MULTICHILD_MAX) {
							discountedTicketNumber = inputNumberOfTicket;
						} else {
							discountedTicketNumber = BENEFIT_MULTICHILD_MAX;
						}
					}	
				} else if (inputTicketSelect == 3 || inputTicketSelect == 4) { // ��� ��� (2) ��ũ �̿�� ������ ��� 
					if (inputBenefit == 1 || inputBenefit == 4 || inputBenefit == 5 || inputBenefit == 6) { 
						appliedBenefit = BENEFIT_NON;
						discountedTicketNumber = BENEFIT_NON_MAX;
					}
					if (inputBenefit == 2) { 		// ����� (����� & ���������� ��� �� ������ ��ũ�̿�ǿ� ���� ����)
						appliedBenefit = BENEFIT_DISABLED;
						if (inputNumberOfTicket <= BENEFIT_DISABLED_MAX) {
							discountedTicketNumber = inputNumberOfTicket;
						} else {
							discountedTicketNumber = BENEFIT_DISABLED_MAX;
						}
					}
					if (inputBenefit == 3) { 		// ���������� (���������� ��� �� ������ ��ũ�̿�ǿ� ���� ����) 
						appliedBenefit = BENEFIT_NATIONAL_MERIT;
						if (inputNumberOfTicket <= BENEFIT_NATIONAL_MERIT_MAX) {
							discountedTicketNumber = inputNumberOfTicket;
						} else {
							discountedTicketNumber = BENEFIT_NATIONAL_MERIT_MAX;
						}
					} 
				}	
			}
			discountedTicketPrice = (ticketPrice * appliedBenefit * discountedTicketNumber);
			
			// final ticket price after the benefit is applied.
			finalTicketPrice = totalTicketPrice - discountedTicketPrice;
			// total ticket price & number(accumulation)
			accumulatedFinalPrice = accumulatedFinalPrice + finalTicketPrice;
			accumulatedTicketNumber = accumulatedTicketNumber + inputNumberOfTicket;
			
			// print the final receipt.
			printf("\n****************************************\n");
			printf("���� Ƽ�� ����: %d ��\n", inputNumberOfTicket);
			printf("���� ����: %d �� (%d �� x %d ��)\n", totalTicketPrice, ticketPrice, inputNumberOfTicket);
			printf("\t=> ���� ����: \n");
			printf("��� �ݾ�: %d �� (%d �� x %d ��)\n", discountedTicketPrice, (int)(ticketPrice * appliedBenefit), discountedTicketNumber);
			printf("\t=> ���� ���: \n");
			printf("��� ���� �� Ƽ�� ������ �� %d ���Դϴ�.\n", finalTicketPrice); 
			printf("\n������ ���� �ݾ�:  �� %d ��\n", accumulatedFinalPrice);
			printf("****************************************\n\n");
			
			printf("Ƽ���� �߰� �����Ͻðڽ��ϱ�?\n\t1. �߰� ����\n\t2. ���� �� ����\n\t ==> ");
			scanf("%d", &continueTicketPurchase);
			
		} while (continueTicketPurchase == 1); 
			
			printf("****************************************\n");
			printf("\n");
			printf("========================================\n");
			printf("%20s%15s%15s%15s%20s\n", "�̿�� ����", "���� �׷�", "����", "����", "��� ����");
			printf("========================================\n");
			printf("%20s%15s%15s%15s%20s\n", "�̿�� ����", "���� �׷�", "����", "����", "��� ����"); // ���� ������... 
			printf("========================================\n");
			printf("%20s%15s%15d%15d\n", "Total",  " ", accumulatedFinalPrice, accumulatedTicketNumber);
			printf("****************************************\n");
			
			printf("��� ���� ���θ� �����Ͻʽÿ�.\n\t1. �ű� �߱� ����\n\t2. �߱� ����\n\t ==> ");
			scanf("%d", &NewPurchase);
		
	} while (NewPurchase == 1);
	
		printf("Ƽ�� �߱��� �����մϴ�.");

	return 0;
}
