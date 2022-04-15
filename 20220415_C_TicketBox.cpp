// 2022.04.14 -> 2022.04.15 수정 
// Ticket Box program for a theme park.
// 특이사항 : 12개월 미만은 무료 & 12개월 이상~36개월 미만은 입장료 무료이지만, 유아용 놀이기구 탑승 원할 경우 유아용 자유이용권 구매 가능.

#include <stdio.h>
#include <time.h> 

int main () {
	
	// 오늘 날짜 불러오기 
	time_t t = time(NULL);
	struct tm today = *localtime(&t);
	int todayYear = today.tm_year + 1900;
	int todayMonth = today.tm_mon + 1;
	int todayDay = today.tm_mday;
	
	// 요금 상수 & 변수 선언
	const int PRICE_ALL_1DAY_ADULT = 62000, PRICE_ALL_1DAY_JUVENILE = 54000, PRICE_ALL_1DAY_CHILD = 47000, PRICE_ALL_1DAY_BABY=15000, PRICE_ALL_1DAY_NEWBORN = 0;
	const int PRICE_ALL_AFTER4_ADULT = 50000, PRICE_ALL_AFTER4_JUVENILE = 43000, PRICE_ALL_AFTER4_CHILD = 36000, PRICE_ALL_AFTER4_BABY = 15000, PRICE_ALL_AFTER4_NEWBORN = 0;  
	const int PRICE_PARK_1DAY_ADULT = 59000, PRICE_PARK_1DAY_JUVENILE = 52000, PRICE_PARK_1DAY_CHILD = 46000, PRICE_PARK_1DAY_BABY = 15000, PRICE_PARK_1DAY_NEWBORN = 0;
	const int PRICE_PARK_AFTER4_ADULT = 47000, PRICE_PARK_AFTER4_JUVENILE = 41000, PRICE_PARK_AFTER4_CHILD = 35000, PRICE_PARK_AFTER4_BABY = 15000, PRICE_PARK_AFTER4_NEWBORN = 0; 
	int priceArray[4]; // 권종 선택에 따른 요금 입력할 배열 
	char* PRINT_TICKET;
	
	// 나이 상수 & 변수 선언 
	const int ELDER_AGE_MIN = 65;
	const int ADULT_AGE_MAX = 64, ADULT_AGE_MIN = 19;
	const int JUVENILE_AGE_MAX = 18, JUVERNILE_AGE_MIN = 13;
	const int CHILD_AGE_MAX = 12, CHILD_AGE_MIN = 3;
	const int BABY_AGE_MAX = 2, BABY_AGE_MIN = 1; 
	const int NEWBORN_AGE = 0;
	const int INDEX_MALE_OLD = 1, INDEX_FEMALE_OLD = 2, INDEX_MALE_NEW = 3, INDEX_FEMALE_NEW = 4; 
	const int BIRTH_YEAR_ADD_OLD = 1900, BIRTH_YEAR_ADD_NEW = 2000;
	char* PRINT_AGE;
	
	// 우대사항  상수 선언
	const float BENEFIT_NON = 0, BENEFIT_DISABLED = 0.5, BENEFIT_NATIONAL_MERIT = 0.5, BENEFIT_PREGNANT = 0.5, BENEFIT_ARMY = 0.49, BENEFIT_MULTICHILD = 0.3;
	const int  BENEFIT_NON_MAX = 0, BENEFIT_DISABLED_MAX = 2, BENEFIT_NATIONAL_MERIT_MAX = 2, BENEFIT_PREGNANT_MAX = 1, BENEFIT_ARMY_MAX = 2, BENEFIT_MULTICHILD_MAX = 1;
	char* PRINT_BENEFIT;
	
	// 입력 변수 선언
	int inputTicketSelect; 		// 권종 선택 
	int inputTicketSelect_Baby; // 유아용 권종 선택 
	char inputSocialID[7]; 		// 사용자 주민등록번호 
	int inputNumberOfTicket;	// 티켓 수량 
	int inputBenefit; 			// 우대사항 
	int inputBenefit_Elder;		// 경로 우대 대상자 추가 선택 (경로 우대 vs 상시 우대)
	
	// 계산 변수 선언 
	int birthYearIndex; 		// 1900년대 & 2000년대생 구분
	int userBirthYear;			// 사용자 생년 
	int userBirthMonth;			// 사용자 생월 
	int userBirthDay;			// 사용자 생일 
	int userAge;				// **사용자 나이 
	int ticketPrice;			// **권종 & 나이에 따른 티켓 가격 
	int totalTicketPrice;		// **티켓 가격 X 수량 
	float appliedBenefit;		// 적용된 베네핏 금액 (종류에 따른 금액 상수 변수로 받아올 예정) 
	int discountedTicketPrice;	// **우대사항 적용으로 인한 할인 금액
	int discountedTicketNumber; // **우대사항 적용된 티켓 수량 
	int finalTicketPrice;		// **totalTicketPrice - discountedTicketPrice
	int continueTicketPurchase; // 티켓 발권 프로세스 반복 여부 선택 
	int NewPurchase;			// 새로운 주문 시작 여부 선택 
	
	// 인쇄용 상수 선언 
	// 1. 권종 
	const char* PRINT_TICKET_ALL_1DAY = "종합이용권 - 주간권(1DAY)";
	const char* PRINT_TICKET_ALL_AFETR4 = "종합이용건 - 야간권(AFTER4)";
	const char* PRINT_TICKET_PARK_1DAY = "파크이용권 - 주간권(1DAY)";
	const char* PRINT_TICKET_PARK_AFETER4 = "파크이용권 - 야간권(AFTER4)";
	// 2. 나이
	const char* PRINT_AGE_ADULT = "성인";
	const char* PRINT_AGE_JUVENILE = "청소년";
	const char* PRINT_AGE_CHILD = "어린이";
	const char* PRINT_AGE_BABY = "베이비";
	const char* PRINT_AGE_NEWBORN = "무료";
	const char* PRINT_AGE_ELDER = "성인 - 어린이 요금 적용";
	// 3. 우대 적용 
	const char* PRINT_BENEFIT_NON = "*우대 적용 없음";
	const char* PRINT_BENEFIT_DISABLED = "*장애인 우대 적용";
	const char* PRINT_BENEFIT_NATIONAL_MERIT = "*국가유공자 우대 적용";
	const char* PRINT_BENEFIT_PREGNANT = "*임산부 우대 적용";
	const char* PRINT_BENEFIT_ARMY = "*휴가장병 우대 적용";
	const char* PRINT_BENEFIT_MULTICHILD = "*다둥이 행복카드 우대 적용";
	 
	
	do { // ~ while => Begin a new purchasing process after payment of a prior process. 
	 
	// 누적 데이터 변수 선언
	int accumulatedFinalPrice = 0; // 총 주문 금액 
	int accumulatedTicketNumber = 0; // 총 주문 티켓 수량 
	
		// 티켓 주문 시작 
		do { // ~ while => return to beginning of the process if the user select "continue purchasing ticket" at the end of the process. 
		
			do {
				printf("권종을 선택하세요.\n\t1. 종합이용권 - 주간권(1DAY)\n\t2. 종합이용권 - 야간권(AFTER4)\n\t3. 파크이용권 - 주간권(1DAY)\n\t4. 파크이용권 - 야간권(AFTER4)\n\t => ");
				scanf("%d", &inputTicketSelect);
			} while (inputTicketSelect < 1 || inputTicketSelect > 4); 
			// 1~4 외 선택 시 선택창 재출력. 
			
			do {
			printf("티켓 사용자의 주민등록번호 앞 7자리를 입력하세요.(앞 6자리 & 뒷자리 첫 번째 숫자))\n\t => ");
			scanf("%s", &inputSocialID);
			} while ( ((inputSocialID[2]-48)*10 + (inputSocialID[3]-48)) > 12 || ((inputSocialID[4]-48)*10 + (inputSocialID[5]-48)) > 31 || inputSocialID[6]-48 > 4 );
			
			do {
				printf("주문 수량을 입력하세요. (최대 10장)\n\t => ");
				scanf("%d", &inputNumberOfTicket);
			} while ( inputNumberOfTicket < 1 || inputNumberOfTicket > 10);
			
			do {
				printf("우대사항을 선택하세요.\n\t1. 없음 (나이 우대는 자동 처리)\n\t2. 장애인\n\t3. 국가유공자\n\t4. 임산부 (종합이용권만 해당)\n\t5. 휴가장병 (종합이용권만 해당)\n\t6. 다자녀 (종합이용권만 해당)\n\t => ");
				scanf("%d", &inputBenefit);
			} while (inputBenefit < 1 || inputBenefit > 6);
			// 1~6 외 선택 시 선택창 재출력. 
			
			// 권종 선택에 따른 Price List  
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
			
			if (userAge >= ELDER_AGE_MIN && inputBenefit != 1) {											// 성인 - 경로 (어린이 요금 적용) 
				do {
					printf("요금 우대는 한 가지만 적용 가능합니다.\n경로 우대와 상시 우대 중 적용을 원하시는 항목을 선택하세요.\n\t1. 경로 우대\n\t2. 상시 우대(장애인, 국가유공자, 임산부, 휴가장병, 다자녀가족)\n\t=> ");
					scanf("%d", &inputBenefit_Elder);
				} while (inputBenefit_Elder < 1 || inputBenefit_Elder > 2);
				
				if (inputBenefit_Elder == 1) {
					ticketPrice = priceArray[0];
				} else if (inputBenefit_Elder == 2) {
					ticketPrice = priceArray[1];
				} 	
			} if (userAge >= ELDER_AGE_MIN && inputBenefit == 1) {
				ticketPrice = priceArray[0];	 
			} if (userAge >= ADULT_AGE_MIN  && userAge <= ADULT_AGE_MAX) { 			// 성인 
				ticketPrice = priceArray[1];
			} if (userAge >= JUVERNILE_AGE_MIN && userAge <= JUVENILE_AGE_MAX) {	// 청소년 
				ticketPrice = priceArray[2];
			} if (userAge >= CHILD_AGE_MIN && userAge < CHILD_AGE_MAX) {			// 어린이 
				ticketPrice = priceArray[3];
			} if ((userAge >= BABY_AGE_MIN && userAge <= BABY_AGE_MAX )) {			// 베이비 
				do {
					printf("만 36개월 미만 유아의 경우 입장료는 무료입니다.\n유아용 놀이시설 자유이용권을 구매하시겠습니까?\n\t1. 유아용 자유이용권 구매\n\t2. 입장권만 구매");
					scanf("%d", &inputTicketSelect_Baby);
				} while (inputTicketSelect_Baby < 1 || inputTicketSelect_Baby > 2);
				if (inputTicketSelect_Baby == 1) {									// 베이비 자유이용권 -> 15,000원 
					ticketPrice = priceArray[4];
				} else if (inputTicketSelect_Baby == 2)  {							// 베이비 입장권 -> 무료 (= newborn) 
					ticketPrice = priceArray[5];
				}	
			} if (userAge = NEWBORN_AGE) {											// 뉴본 = 12개월 미만 (무료) 
				ticketPrice = priceArray[5];
			} 
			
			// Ticket price before applying discount benefit. 
			totalTicketPrice = ticketPrice * inputNumberOfTicket;
	
			// Check the benefit and discounted amount. (경로우대와 상시우대 중복 적용이 안 됨... 추후 추가하기) 
			
			if (userAge >= ELDER_AGE_MIN && inputBenefit_Elder == 1) {
				appliedBenefit = BENEFIT_NON;
				discountedTicketNumber = BENEFIT_NON_MAX;
			} else {
				if (inputTicketSelect == 1 || inputTicketSelect == 2) { 	// 상시 우대 (1) 종합 이용권 선택한 경우 
						if (inputBenefit == 1) { 	// 우대사항 없음 
						appliedBenefit = BENEFIT_NON;
						discountedTicketNumber = BENEFIT_NON_MAX;
					}
					if (inputBenefit == 2) { 		// 장애인 
						appliedBenefit = BENEFIT_DISABLED;
						if (inputNumberOfTicket <= BENEFIT_DISABLED_MAX) {
							discountedTicketNumber = inputNumberOfTicket;
						} else {
							discountedTicketNumber = BENEFIT_DISABLED_MAX;
						}
					}
					if (inputBenefit == 3) { 		// 국가유공자 
						appliedBenefit = BENEFIT_NATIONAL_MERIT;
						if (inputNumberOfTicket <= BENEFIT_NATIONAL_MERIT_MAX) {
							discountedTicketNumber = inputNumberOfTicket;
						} else {
							discountedTicketNumber = BENEFIT_NATIONAL_MERIT_MAX;
						}
					} 
					if (inputBenefit == 4) { 		// 임산부 
						appliedBenefit = BENEFIT_PREGNANT;
						if (inputNumberOfTicket <= BENEFIT_PREGNANT_MAX) {
							discountedTicketNumber = inputNumberOfTicket;
						} else {
							discountedTicketNumber = BENEFIT_PREGNANT_MAX;
						}
					}
					if (inputBenefit == 5) { 		// 휴가장병 
						appliedBenefit = BENEFIT_ARMY;
						if (inputNumberOfTicket <= BENEFIT_ARMY_MAX) {
							discountedTicketNumber = inputNumberOfTicket;
						} else {
							discountedTicketNumber =  BENEFIT_ARMY_MAX;
						}
					}
					if (inputBenefit == 6) { 		//다자녀 
						appliedBenefit = BENEFIT_MULTICHILD;
						if (inputNumberOfTicket <= BENEFIT_MULTICHILD_MAX) {
							discountedTicketNumber = inputNumberOfTicket;
						} else {
							discountedTicketNumber = BENEFIT_MULTICHILD_MAX;
						}
					}	
				} else if (inputTicketSelect == 3 || inputTicketSelect == 4) { // 상시 우대 (2) 파크 이용권 선택한 경우 
					if (inputBenefit == 1 || inputBenefit == 4 || inputBenefit == 5 || inputBenefit == 6) { 
						appliedBenefit = BENEFIT_NON;
						discountedTicketNumber = BENEFIT_NON_MAX;
					}
					if (inputBenefit == 2) { 		// 장애인 (장애인 & 국가유공자 우대 두 가지만 파크이용권에 적용 가능)
						appliedBenefit = BENEFIT_DISABLED;
						if (inputNumberOfTicket <= BENEFIT_DISABLED_MAX) {
							discountedTicketNumber = inputNumberOfTicket;
						} else {
							discountedTicketNumber = BENEFIT_DISABLED_MAX;
						}
					}
					if (inputBenefit == 3) { 		// 국가유공자 (국가유공자 우대 두 가지만 파크이용권에 적용 가능) 
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
			printf("선택 티켓 수량: %d 장\n", inputNumberOfTicket);
			printf("정상 가격: %d 원 (%d 원 x %d 장)\n", totalTicketPrice, ticketPrice, inputNumberOfTicket);
			printf("\t=> 선택 권종: \n");
			printf("우대 금액: %d 원 (%d 원 x %d 장)\n", discountedTicketPrice, (int)(ticketPrice * appliedBenefit), discountedTicketNumber);
			printf("\t=> 적용 우대: \n");
			printf("우대 적용 후 티켓 가격은 총 %d 원입니다.\n", finalTicketPrice); 
			printf("\n결제할 누적 금액:  총 %d 원\n", accumulatedFinalPrice);
			printf("****************************************\n\n");
			
			printf("티켓을 추가 선택하시겠습니까?\n\t1. 추가 선택\n\t2. 종료 및 결제\n\t ==> ");
			scanf("%d", &continueTicketPurchase);
			
		} while (continueTicketPurchase == 1); 
			
			printf("****************************************\n");
			printf("\n");
			printf("========================================\n");
			printf("%20s%15s%15s%15s%20s\n", "이용권 종류", "나이 그룹", "가격", "수량", "우대 적용");
			printf("========================================\n");
			printf("%20s%15s%15s%15s%20s\n", "이용권 종류", "나이 그룹", "가격", "수량", "우대 적용"); // 추후 값으로... 
			printf("========================================\n");
			printf("%20s%15s%15d%15d\n", "Total",  " ", accumulatedFinalPrice, accumulatedTicketNumber);
			printf("****************************************\n");
			
			printf("계속 진행 여부를 선택하십시오.\n\t1. 신규 발권 시작\n\t2. 발권 종료\n\t ==> ");
			scanf("%d", &NewPurchase);
		
	} while (NewPurchase == 1);
	
		printf("티켓 발권을 종료합니다.");

	return 0;
}
