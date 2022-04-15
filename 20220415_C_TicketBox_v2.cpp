// 2022.04.14 -> 2022.04.15 수정 
// Ticket Box program for a theme park.
// 특이사항 
// (1) 12개월 미만 : 무료
// (2) 12개월 이상~36개월 미만 : 입장료 무료. 유아용 놀이기구 탑승 원할 경우, 유아용 자유이용권 구매 가능.
// (3) 경로 우대 & 상시 우대 : 중복 적용 불가. 적용 원하는 우대 항목 선택 필요. 
// => 출력 개선 

#include <stdio.h>
#include <time.h> 

int main () {
	
	// 오늘 날짜 불러오기 
	time_t t = time(NULL);
	struct tm today = *localtime(&t);
	int todayYear = today.tm_year + 1900;
	int todayMonth = today.tm_mon + 1;
	int todayDay = today.tm_mday;
	
	// 출력 상수/변수 
	int orderList[10][8] = {0};
	const int SAVE_TICKET_TYPE = 0, SAVE_AGE_TYPE = 1, SAVE_TICKET_PRICE = 2, SAVE_TICKET_NUBMER = 3, SAVE_TOTAL_PRICE = 4, SAVE_BENEFIT_TYPE = 5, SAVE_BENEFIT_NUMBER = 6, SAVE_FINAL_PRICE = 7;
	const int TICKET_TYPE_NAME_ALL_1DAY = 1, TICKET_TYPE_NAME_ALL_AFTER4 = 2, TICKET_TYPE_NAME_PARK_1DAY = 3, TICKET_TYPE_NAME_PARK_AFTER4 = 4;
	int ticketTypeName;
	const int AGE_TYPE_NAME_ELDER = 1, AGE_TYPE_NAME_ADULT = 2, AGE_TYPE_NAME_JUVENILE = 3, AGE_TYPE_NAME_CHILD = 4, AGE_TYPE_NAME_BABY = 5, AGE_TYPE_NAME_NEWBORN = 6;
	int ageTypeName;
	const int BENEFIT_TYPE_NAME_NON = 1, BENEFIT_TYPE_NAME_DISABLED = 2, BENEFIT_TYPE_NAME_NATIONAL_MERIT = 3, BENEFIT_TYPE_NAME_PREGNANT = 4, BENEFIT_TYPE_NAME_ARMY = 5, BENEFIT_TYPE_NAME_MULTICHILD = 6;
	int benefitType;
	
	// 요금 상수 & 변수 선언
	const int PRICE_ALL_1DAY_ADULT = 62000, PRICE_ALL_1DAY_JUVENILE = 54000, PRICE_ALL_1DAY_CHILD = 47000, PRICE_ALL_1DAY_BABY=15000, PRICE_ALL_1DAY_NEWBORN = 0;
	const int PRICE_ALL_AFTER4_ADULT = 50000, PRICE_ALL_AFTER4_JUVENILE = 43000, PRICE_ALL_AFTER4_CHILD = 36000, PRICE_ALL_AFTER4_BABY = 15000, PRICE_ALL_AFTER4_NEWBORN = 0;  
	const int PRICE_PARK_1DAY_ADULT = 59000, PRICE_PARK_1DAY_JUVENILE = 52000, PRICE_PARK_1DAY_CHILD = 46000, PRICE_PARK_1DAY_BABY = 15000, PRICE_PARK_1DAY_NEWBORN = 0;
	const int PRICE_PARK_AFTER4_ADULT = 47000, PRICE_PARK_AFTER4_JUVENILE = 41000, PRICE_PARK_AFTER4_CHILD = 35000, PRICE_PARK_AFTER4_BABY = 15000, PRICE_PARK_AFTER4_NEWBORN = 0;
	int priceArray[9]; // 권종 선택에 따른 요금 입력할 배열 
	
	// 나이 상수 & 변수 선언 
	const int ELDER_AGE_MIN = 65;
	const int ADULT_AGE_MAX = 64, ADULT_AGE_MIN = 19;
	const int JUVENILE_AGE_MAX = 18, JUVERNILE_AGE_MIN = 13;
	const int CHILD_AGE_MAX = 12, CHILD_AGE_MIN = 3;
	const int BABY_AGE_MAX = 2, BABY_AGE_MIN = 1; 
	const int NEWBORN_AGE = 0;
	const int INDEX_MALE_OLD = 1, INDEX_FEMALE_OLD = 2, INDEX_MALE_NEW = 3, INDEX_FEMALE_NEW = 4; 
	const int BIRTH_YEAR_ADD_OLD = 1900, BIRTH_YEAR_ADD_NEW = 2000;
	
	// 우대사항  상수 선언
	const float BENEFIT_NON = 0, BENEFIT_DISABLED = 0.5, BENEFIT_NATIONAL_MERIT = 0.5, BENEFIT_PREGNANT = 0.5, BENEFIT_ARMY = 0.49, BENEFIT_MULTICHILD = 0.3;
	const int  BENEFIT_NON_MAX = 0, BENEFIT_DISABLED_MAX = 2, BENEFIT_NATIONAL_MERIT_MAX = 2, BENEFIT_PREGNANT_MAX = 1, BENEFIT_ARMY_MAX = 2, BENEFIT_MULTICHILD_MAX = 1;
	
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
		 
	
	do { // ~ while => Begin a new purchasing process after payment of a prior process. 
	
		// 누적 데이터 변수 선언
		int orderCount = 0;
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
					ticketTypeName = TICKET_TYPE_NAME_ALL_1DAY;
					break;
				case 2:
					priceArray[1] = PRICE_ALL_AFTER4_CHILD;
					priceArray[2] = PRICE_ALL_AFTER4_ADULT;
					priceArray[2] = PRICE_ALL_AFTER4_JUVENILE;
					priceArray[3] = PRICE_ALL_AFTER4_CHILD;
					priceArray[4] = PRICE_ALL_AFTER4_BABY;
					priceArray[5] = PRICE_ALL_AFTER4_NEWBORN;
					ticketTypeName = TICKET_TYPE_NAME_ALL_AFTER4;
					break;
				case 3:
					priceArray[0] = PRICE_PARK_1DAY_CHILD;
					priceArray[1] = PRICE_PARK_1DAY_ADULT;
					priceArray[2] = PRICE_PARK_1DAY_JUVENILE;
					priceArray[3] = PRICE_PARK_1DAY_CHILD;
					priceArray[4] = PRICE_PARK_1DAY_BABY;
					priceArray[5] = PRICE_PARK_1DAY_NEWBORN;
					ticketTypeName = TICKET_TYPE_NAME_PARK_1DAY;
					break;
				case 4:
					priceArray[0] = PRICE_PARK_AFTER4_CHILD;
					priceArray[1] = PRICE_PARK_AFTER4_ADULT;
					priceArray[2] = PRICE_PARK_AFTER4_JUVENILE;
					priceArray[3] = PRICE_PARK_AFTER4_CHILD;
					priceArray[4] = PRICE_PARK_AFTER4_BABY;
					priceArray[5] = PRICE_PARK_AFTER4_NEWBORN;
					ticketTypeName = TICKET_TYPE_NAME_PARK_AFTER4;
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
					ageTypeName = AGE_TYPE_NAME_ELDER;
				} else if (inputBenefit_Elder == 2) {
					ticketPrice = priceArray[1];
					ageTypeName = AGE_TYPE_NAME_ADULT;
				} 	
			} if (userAge >= ELDER_AGE_MIN && inputBenefit == 1) {
				ticketPrice = priceArray[0];
				ageTypeName = AGE_TYPE_NAME_ELDER;									// 성인 - 경로 (0) 
			} if (userAge >= ADULT_AGE_MIN  && userAge <= ADULT_AGE_MAX) { 			// 성인 (1)
				ticketPrice = priceArray[1];
				ageTypeName = AGE_TYPE_NAME_ADULT;	
			} if (userAge >= JUVERNILE_AGE_MIN && userAge <= JUVENILE_AGE_MAX) {	// 청소년 (2) 
				ticketPrice = priceArray[2];
				ageTypeName = AGE_TYPE_NAME_JUVENILE;	
			} if (userAge >= CHILD_AGE_MIN && userAge < CHILD_AGE_MAX) {			// 어린이 (3)
				ticketPrice = priceArray[3];
				ageTypeName = AGE_TYPE_NAME_CHILD;	
			} if ((userAge >= BABY_AGE_MIN && userAge <= BABY_AGE_MAX )) {			// 베이비 (4)
				do {
					printf("만 36개월 미만 유아의 경우 입장료는 무료입니다.\n유아용 놀이시설 자유이용권을 구매하시겠습니까?\n\t1. 유아용 자유이용권 구매\n\t2. 입장권만 구매");
					scanf("%d", &inputTicketSelect_Baby);
				} while (inputTicketSelect_Baby < 1 || inputTicketSelect_Baby > 2);
				if (inputTicketSelect_Baby == 1) {									// 베이비 자유이용권 -> 15,000원(4) 
					ticketPrice = priceArray[4];
					ageTypeName = AGE_TYPE_NAME_BABY;
				} else if (inputTicketSelect_Baby == 2)  {							// 베이비 입장권 -> 무료 (= newborn) (5) 
					ticketPrice = priceArray[5];
					ageTypeName = AGE_TYPE_NAME_NEWBORN;
				}	
			} if (userAge = NEWBORN_AGE) {											// 뉴본 = 12개월 미만 (무료) (5)
				ticketPrice = priceArray[5];
				ageTypeName = AGE_TYPE_NAME_NEWBORN;
			} 
			
			// Ticket price before applying discount benefit. 
			totalTicketPrice = ticketPrice * inputNumberOfTicket;
	
			// Check the benefit and discounted amount. 
			if (userAge >= ELDER_AGE_MIN && inputBenefit_Elder == 1) { 	// 경로 우대 적용 대상인 경우 -> 상시 우대 적용하지 않음. 
				appliedBenefit = BENEFIT_NON;
				discountedTicketNumber = BENEFIT_NON_MAX;
				benefitType = BENEFIT_TYPE_NAME_NON;
			} else {
				if (inputTicketSelect == 1 || inputTicketSelect == 2) { 	// 상시 우대 (1) 종합 이용권 선택한 경우 
						if (inputBenefit == 1) { 	// 우대사항 없음 (0)
						appliedBenefit = BENEFIT_NON;
						discountedTicketNumber = BENEFIT_NON_MAX;
						benefitType = BENEFIT_TYPE_NAME_NON;
					}
					if (inputBenefit == 2) { 		// 장애인 (1)
						appliedBenefit = BENEFIT_DISABLED;
						if (inputNumberOfTicket <= BENEFIT_DISABLED_MAX) {
							discountedTicketNumber = inputNumberOfTicket;
						} else {
							discountedTicketNumber = BENEFIT_DISABLED_MAX;
						}
						benefitType = BENEFIT_TYPE_NAME_DISABLED;
					}
					if (inputBenefit == 3) { 		// 국가유공자 (2) 
						appliedBenefit = BENEFIT_NATIONAL_MERIT;
						if (inputNumberOfTicket <= BENEFIT_NATIONAL_MERIT_MAX) {
							discountedTicketNumber = inputNumberOfTicket;
						} else {
							discountedTicketNumber = BENEFIT_NATIONAL_MERIT_MAX;
						}
						benefitType = BENEFIT_TYPE_NAME_NATIONAL_MERIT;
					} 
					if (inputBenefit == 4) { 		// 임산부 (3)
						appliedBenefit = BENEFIT_PREGNANT;
						if (inputNumberOfTicket <= BENEFIT_PREGNANT_MAX) {
							discountedTicketNumber = inputNumberOfTicket;
						} else {
							discountedTicketNumber = BENEFIT_PREGNANT_MAX;
						}
						benefitType = BENEFIT_TYPE_NAME_PREGNANT;
					}
					if (inputBenefit == 5) { 		// 휴가장병 (4)
						appliedBenefit = BENEFIT_ARMY;
						if (inputNumberOfTicket <= BENEFIT_ARMY_MAX) {
							discountedTicketNumber = inputNumberOfTicket;
						} else {
							discountedTicketNumber =  BENEFIT_ARMY_MAX;
						}
						benefitType = BENEFIT_TYPE_NAME_ARMY;
					}
					if (inputBenefit == 6) { 		//다자녀 (5)
						appliedBenefit = BENEFIT_MULTICHILD;
						if (inputNumberOfTicket <= BENEFIT_MULTICHILD_MAX) {
							discountedTicketNumber = inputNumberOfTicket;
						} else {
							discountedTicketNumber = BENEFIT_MULTICHILD_MAX;
						}
						benefitType = BENEFIT_TYPE_NAME_MULTICHILD;
					}	
				} else if (inputTicketSelect == 3 || inputTicketSelect == 4) { // 상시 우대 (2) 파크 이용권 선택한 경우 
					if (inputBenefit == 1 || inputBenefit == 4 || inputBenefit == 5 || inputBenefit == 6) { 
						appliedBenefit = BENEFIT_NON;
						discountedTicketNumber = BENEFIT_NON_MAX;
						benefitType = BENEFIT_TYPE_NAME_NON;
					}
					if (inputBenefit == 2) { 		// 장애인 (장애인 & 국가유공자 우대 두 가지만 파크이용권에 적용 가능)
						appliedBenefit = BENEFIT_DISABLED;
						if (inputNumberOfTicket <= BENEFIT_DISABLED_MAX) {
							discountedTicketNumber = inputNumberOfTicket;
						} else {
							discountedTicketNumber = BENEFIT_DISABLED_MAX;
						}
						benefitType = BENEFIT_TYPE_NAME_DISABLED;
					}
					if (inputBenefit == 3) { 		// 국가유공자 (국가유공자 우대 두 가지만 파크이용권에 적용 가능) 
						appliedBenefit = BENEFIT_NATIONAL_MERIT;
						if (inputNumberOfTicket <= BENEFIT_NATIONAL_MERIT_MAX) {
							discountedTicketNumber = inputNumberOfTicket;
						} else {
							discountedTicketNumber = BENEFIT_NATIONAL_MERIT_MAX;
						}
						benefitType = BENEFIT_TYPE_NAME_NATIONAL_MERIT;
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
			
			// 인쇄할 배열에 값 넣기 
			orderList[orderCount][SAVE_TICKET_TYPE] = ticketTypeName; 				// 0.이용권 종류 
			orderList[orderCount][SAVE_AGE_TYPE] = ageTypeName; 					// 1.나이에 대한 권종 
			orderList[orderCount][SAVE_TICKET_PRICE] = ticketPrice; 				// 2.티켓  금액 (1장당) 
			orderList[orderCount][SAVE_TICKET_NUBMER] = inputNumberOfTicket; 		// 3.티켓 수량 
			orderList[orderCount][SAVE_TOTAL_PRICE] = totalTicketPrice; 			// 4.토탈  금액 (금액 x 수량) 
			orderList[orderCount][SAVE_BENEFIT_TYPE] = benefitType; 				// 5.우대사항 
			orderList[orderCount][SAVE_BENEFIT_NUMBER] = discountedTicketNumber; 	// 6.우대 적용 수량 
			orderList[orderCount][SAVE_FINAL_PRICE] = finalTicketPrice; 			// 7.최종 금액
			
			orderCount++;
			
			
			printf("티켓을 추가 선택하시겠습니까?\n\t1. 추가 선택\n\t2. 종료 및 결제\n\t ==> ");
			scanf("%d", &continueTicketPurchase);
			
		} while (continueTicketPurchase == 1); 
		
		printf("****************************************\n");
		printf("%30s%10s%10s%10s%10s%20s%10s%10s\n","티켓 종류","나이","티켓 가격","티켓 수량","총 가격","우대 사항","우대 적용","최종 가격");
		// 이용권 종류 출력
		for (int index = 0; index < orderCount; index++) {
			
			if (orderList[index][SAVE_TICKET_TYPE] == 1) {
				printf("%30s","""종합이용권 - 주간권(1DAY)");
			} else if (orderList[index][SAVE_TICKET_TYPE] == 2) {
				printf("%30s","종합이용권 - 야간권(AFTER4)\t");
			} else if (orderList[index][SAVE_TICKET_TYPE] == 3) {
				printf("%30s","파크이용권 - 주간권(1DAY)\t");
			}
			else if (orderList[index][SAVE_TICKET_TYPE] == 4) {
				printf("%30s","파크이용권 - 야간권(AFTER4)\t");
			}

			if (orderList[index][SAVE_AGE_TYPE] == 1) {
				printf("%10s","성인(경로우대)\t");
			} else if (orderList[index][SAVE_AGE_TYPE] == 2) {
				printf("%10s","성인\t");
			} else if (orderList[index][SAVE_AGE_TYPE] == 3) {
				printf("%10s","청소년\t");
			} else if (orderList[index][SAVE_AGE_TYPE] == 4) {
				printf("%10s","어린이\t");
			} else if (orderList[index][SAVE_AGE_TYPE] == 5) {
				printf("%10s","베이비(자유이용권)\t");
			}
			else if (orderList[index][SAVE_AGE_TYPE] == 6) {
				printf("%10s","베이비(입장권)\t");
			}
			// 티켓 가격 출력 
			printf("%20d",orderList[index][SAVE_TICKET_PRICE]);
			// 티켓 수량 출력 
			printf("%20d",orderList[index][SAVE_TICKET_NUBMER]);
			// 티켓 토탈 가격 (가격 x 수량) 출력 
			printf("%20d",orderList[index][SAVE_TOTAL_PRICE]);
			//우대사항 출력 
			if (orderList[index][SAVE_BENEFIT_TYPE] == 1) {
				printf("%20s","*우대 적용 없음\t");
			} else if (orderList[index][SAVE_BENEFIT_TYPE] == 2) {
				printf("%20s","*장애인 우대 적용\t");
			} else if (orderList[index][SAVE_BENEFIT_TYPE] == 3) {
				printf("%20s","*국가유공자 우대 적용\t");
			} else if (orderList[index][SAVE_BENEFIT_TYPE] == 4) {
				printf("%20s","*임산부 우대 적용\t");
			} else if (orderList[index][SAVE_BENEFIT_TYPE] == 5) {
				printf("%20s","*휴가장병 우대 적용\t");
			}
			else if (orderList[index][SAVE_BENEFIT_TYPE] == 6) {
				printf("%20s","*다둥이 행복카드 우대 적용\t");
			}
			//우대 가격 적용 수량 출력 
			printf("%20d",orderList[index][SAVE_BENEFIT_NUMBER]);	
			//최종 가격 적용 수량 출력 
			printf("%20d\n",orderList[index][SAVE_FINAL_PRICE]);	
		}
		
		
		printf("****************************************\n");
		printf("****************************************\n");
			
			printf("계속 진행 여부를 선택하십시오.\n\t1. 신규 발권 시작\n\t2. 발권 종료\n\t ==> ");
			scanf("%d", &NewPurchase);
		
	} while (NewPurchase == 1);
	
		printf("티켓 발권을 종료합니다.");

	return 0;
}
