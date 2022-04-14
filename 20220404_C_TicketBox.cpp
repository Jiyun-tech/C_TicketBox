// 2022.04.14
// Ticket Box program for a theme park.

#include <stdio.h>
#include <time.h> 

int main () {
	
	// 오늘 날짜 불러오기 
	time_t t = time(NULL);
	struct tm today = *localtime(&t);
	int todayYear = today.tm_year + 1900;
	int todayMonth = today.tm_mon + 1;
	int todayDay = today.tm_mday;
	
	// 요금 상수 변수 선언
	const int PRICE_ALL_1DAY_ADULT = 62000, PRICE_ALL_1DAY_JUVENILE = 54000, PRICE_ALL_1DAY_CHILD = 47000, PRICE_ALL_1DAY_BABY=15000, PRICE_ALL_1DAY_NEWBORN = 0;
	const int PRICE_ALL_AFTER4_ADULT = 50000, PRICE_ALL_AFTER4_JUVENILE = 43000, PRICE_ALL_AFTER4_CHILD = 36000, PRICE_ALL_AFTER4_BABY = 15000, PRICE_ALL_AFTER4_NEWBORN = 0;  
	const int PRICE_PARK_1DAY_ADULT = 59000, PRICE_PARK_1DAY_JUVENILE = 52000, PRICE_PARK_1DAY_CHILD = 46000, PRICE_PARK_1DAY_BABY = 15000, PRICE_PARK_1DAY_NEWBORN = 0;
	const int PRICE_PARK_AFTER4_ADULT = 47000, PRICE_PARK_AFTER4_JUVENILE = 41000, PRICE_PARK_AFTER4_CHILD = 35000, PRICE_PARK_AFTER4_BABY = 15000, PRICE_PARK_AFTER4_NEWBORN = 0; 
	int priceArray[4]; // 권종 선택에 따른 요금 입력할 배열 
	
	// 나이 상수 변수 선언 
	const int ELDER_AGE_MIN = 65;
	const int ADULT_AGE_MAX = 64, ADULT_AGE_MIN = 19;
	const int JUVENILE_AGE_MAX = 18, JUVERNILE_AGE_MIN = 13;
	const int CHILD_AGE_MAX = 12, CHILD_AGE_MIN = 3;
	const int BABY_AGE_MAX = 2, BABY_AGE_MIN = 1; 
	const int NEWBORN_AGE = 0;
	const int INDEX_MALE_OLD = 1, INDEX_FEMALE_OLD = 2, INDEX_MALE_NEW = 3, INDEX_FEMALE_NEW = 4; 
	const int BIRTH_YEAR_ADD_OLD = 1900, BIRTH_YEAR_ADD_NEW = 2000;
	
	// 우대사항 
	const float BENEFIT_NON = 0, BENEFIT_DISABLED = 0.5, BENEFIT_NATIONAL_MERIT = 0.5, BENEFIT_PREGNANT = 0.5, BENEFIT_ARMY = 0.49, BENEFIT_MULTICHILD = 0.3;
	const int  BENEFIT_NON_MAX = 0, BENEFIT_DISABLED_MAX = 2, BENEFIT_NATIONAL_MERIT_MAX = 2, BENEFIT_PREGNANT_MAX = 1, BENEFIT_ARMY_MAX = 2, BENEFIT_MULTICHILD_MAX = 1;

	// 입력 변수 선언
	int inputTicketSelect; 		// 권종 선택 
	char inputSocialID[7]; 		// 사용자 주민등록번호 
	int inputNumberOfTicket;	// 티켓 수량 
	int inputBenefit; 		// 우대사항 
	
	// 계산 변수 선언 
	int birthYearIndex; 		// 1900년대 & 2000년대생 구분
	int userBirthYear;		// 사용자 생년 
	int userBirthMonth;		// 사용자 생월 
	int userBirthDay;		// 사용자 생일 
	int userAge;			// **사용자 나이 
	int ticketPrice;		// **권종 & 나이에 따른 티켓 가격 
	int totalTicketPrice;		// **티켓 가격 X 수량 
	float appliedBenefit;		// 적용된 베네핏 금액 (종류에 따른 금액 상수 변수로 받아올 예정) 
	int discountedTicketPrice;	// **우대사항 적용으로 인한 할인 금액
	int discountedTicketNumber; 	// **우대사항 적용된 티켓 수량 
	int finalTicketPrice;		// **totalTicketPrice - discountedTicketPrice
	int continueTicketPurchase; 	// 티켓 발권 프로세스 반복 여부 선택 
	
	// 누적 데이터 변수 선언
	int accumulatedFinalPrice = 0; 	// 총 주문 금액 
	int accumulatedTicketNumber = 0; // 총 주문 티켓 수량 
	
	
	// 티켓 주문 시작 
	do { // ~ while => return to beginning of the process if the user select "continue purchasing ticket" at the end of the process. 
	
		do {
			printf("권종을 선택하세요.\n\t1. 종합이용권 - 주간권(1DAY)\n\t2. 종합이용권 - 야간권(AFTER4)\n\t3. 파크이용권 - 주간권(1DAY)\n\t4. 파크이용권 - 야간권(AFTER4)\n\t => ");
			scanf("%d", &inputTicketSelect);
		} while (inputTicketSelect < 1 || inputTicketSelect > 4); 
		// 1~4 외 선택 시 선택창 재출력. 
		
		do {
		printf("티켓 사용자의 주민등록번호 앞 7자리를 입력하세요.(앞 6자리 & 뒷자리 첫 번째 숫자까지)\n\t => ");
		scanf("%s", &inputSocialID);
		} while ( ((inputSocialID[2]-48)*10 + (inputSocialID[3]-48)) > 12 || ((inputSocialID[4]-48)*10 + (inputSocialID[5]-48)) > 31 || inputSocialID[6]-48 > 4 );
		
		printf("주문 수량을 입력하세요.\n\t => ");
		scanf("%d", &inputNumberOfTicket);
		
		do {
			printf("우대사항을 선택하세요.\n\t1. 없음 (나이 우대는 자동 처리)\n\t2. 장애인\n\t3. 국가유공자\n\t4. 임산부 (종합이용권만 해당)\n\t5. 휴가장병 (종합이용권만 해당)\n\t6. 다자녀 (종합이용권만 해당)\n\t => ");
			scanf("%d", &inputBenefit);
		} while (inputBenefit < 1 || inputBenefit > 6);
		// 1~6 외 선택 시 선택창 재출력. 
		
		// 권종 선택에 따른 Price List  
		switch (inputTicketSelect) {
			case 1:
				priceArray[0] = PRICE_ALL_1DAY_ADULT;
				priceArray[1] = PRICE_ALL_1DAY_JUVENILE;
				priceArray[2] = PRICE_ALL_1DAY_CHILD;
				priceArray[3] = PRICE_ALL_1DAY_BABY;
				priceArray[4] = PRICE_ALL_1DAY_NEWBORN;
				break;
			case 2:
				priceArray[0] = PRICE_ALL_AFTER4_ADULT;
				priceArray[1] = PRICE_ALL_AFTER4_JUVENILE;
				priceArray[2] = PRICE_ALL_AFTER4_CHILD;
				priceArray[3] = PRICE_ALL_AFTER4_BABY;
				priceArray[4] = PRICE_ALL_AFTER4_NEWBORN;
				break;
			case 3:
				priceArray[0] = PRICE_PARK_1DAY_ADULT;
				priceArray[1] = PRICE_PARK_1DAY_JUVENILE;
				priceArray[2] = PRICE_PARK_1DAY_CHILD;
				priceArray[3] = PRICE_PARK_1DAY_BABY;
				priceArray[4] = PRICE_PARK_1DAY_NEWBORN;
				break;
			case 4:
				priceArray[0] = PRICE_PARK_AFTER4_ADULT;
				priceArray[1] = PRICE_PARK_AFTER4_JUVENILE;
				priceArray[2] = PRICE_PARK_AFTER4_CHILD;
				priceArray[4] = PRICE_PARK_AFTER4_NEWBORN;
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
		if (userAge >= ADULT_AGE_MIN  && userAge <= ADULT_AGE_MAX) {
			ticketPrice = priceArray[0];
		} if (userAge >= JUVERNILE_AGE_MIN && userAge <= JUVENILE_AGE_MAX) {
			ticketPrice = priceArray[1];
		} if ((userAge >= CHILD_AGE_MIN && userAge < CHILD_AGE_MAX) || userAge >= ELDER_AGE_MIN) {
			ticketPrice = priceArray[2];
		} if ((userAge >= BABY_AGE_MIN && userAge <= BABY_AGE_MAX )) {
			ticketPrice = priceArray[3];
		} if (userAge <= NEWBORN_AGE) {
			ticketPrice = priceArray[4];
		}
		
		// Ticket price before applying discount benefit. 
		totalTicketPrice = ticketPrice * inputNumberOfTicket;
		
		// Check the benefit and discounted amount.
		if (userAge >= ELDER_AGE_MIN || userAge <= NEWBORN_AGE) {		// in case the user is older than 64. (above adult age range) => no other benebits can be applied.
			appliedBenefit = BENEFIT_NON;
			discountedTicketNumber = BENEFIT_NON_MAX;
		} else {
			if (inputTicketSelect == 1 || inputTicketSelect == 2) { // 종합 이용권 선택한 경우 
					if (inputBenefit == 1) { // 우대사항 없음 
					appliedBenefit = BENEFIT_NON;
					discountedTicketNumber = BENEFIT_NON_MAX;
				}
				if (inputBenefit == 2) { // 장애인 
					appliedBenefit = BENEFIT_DISABLED;
					if (inputNumberOfTicket <= BENEFIT_DISABLED_MAX) {
						discountedTicketNumber = inputNumberOfTicket;
					} else {
						discountedTicketNumber = BENEFIT_DISABLED_MAX;
					}
				}
				if (inputBenefit == 3) { // 국가유공자 
					appliedBenefit = BENEFIT_NATIONAL_MERIT;
					if (inputNumberOfTicket <= BENEFIT_NATIONAL_MERIT_MAX) {
						discountedTicketNumber = inputNumberOfTicket;
					} else {
						discountedTicketNumber = BENEFIT_NATIONAL_MERIT_MAX;
					}
				} 
				if (inputBenefit == 4) { // 임산부 
					appliedBenefit = BENEFIT_PREGNANT;
					if (inputNumberOfTicket <= BENEFIT_PREGNANT_MAX) {
						discountedTicketNumber = inputNumberOfTicket;
					} else {
						discountedTicketNumber = BENEFIT_PREGNANT_MAX;
					}
				}
				if (inputBenefit == 5) { // 휴가장병 
					appliedBenefit = BENEFIT_ARMY;
					if (inputNumberOfTicket <= BENEFIT_ARMY_MAX) {
						discountedTicketNumber = inputNumberOfTicket;
					} else {
						discountedTicketNumber =  BENEFIT_ARMY_MAX;
					}
				}
				if (inputBenefit == 6) { //다자녀 
					appliedBenefit = BENEFIT_MULTICHILD;
					if (inputNumberOfTicket <= BENEFIT_MULTICHILD_MAX) {
						discountedTicketNumber = inputNumberOfTicket;
					} else {
						discountedTicketNumber = BENEFIT_MULTICHILD_MAX;
					}
				}	
			} else if (inputTicketSelect == 3 || inputTicketSelect == 4) { // 파크 이용권 선택한 경우 
				if (inputBenefit == 1 || inputBenefit == 4 || inputBenefit == 5 || inputBenefit == 6) { 
					appliedBenefit = BENEFIT_NON;
					discountedTicketNumber = BENEFIT_NON_MAX;
				}
				if (inputBenefit == 2) { // 장애인 & 국가유공자 우대 두 가지만 파크이용권에 적용 가능. 
					appliedBenefit = BENEFIT_DISABLED;
					if (inputNumberOfTicket <= BENEFIT_DISABLED_MAX) {
						discountedTicketNumber = inputNumberOfTicket;
					} else {
						discountedTicketNumber = BENEFIT_DISABLED_MAX;
					}
				}
				if (inputBenefit == 3) { // 장애인 & 국가유공자 우대 두 가지만 파크이용권에 적용 가능. 
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
		printf("사용자 나이 : %d 세\n", userAge);
		printf("총 티켓 수량 : %d 장\n", inputNumberOfTicket);
		printf("정상 가격 : %d 원 (%d 원 x %d 장)\n", totalTicketPrice, ticketPrice, inputNumberOfTicket);
		printf("우대 금액 : %d 원 (%d 원 x %d 장)\n", discountedTicketPrice, (int)(ticketPrice * appliedBenefit), discountedTicketNumber);
		printf("선택하신 티켓 가격은 총 %d 원입니다.\n", finalTicketPrice); 
		printf("계산하실 누적 금액은 총 %d 원입니다.\n", accumulatedFinalPrice);
		printf("****************************************\n\n");
		printf("계속 발권하시겠습니까?\n\t1.티켓 발권\n\t2.종료\n\t ==> ");
		scanf("%d", &continueTicketPurchase);
		
	} while (continueTicketPurchase == 1);
		
		printf("****************************************\n");
		printf("선택하신 티켓 수량은 총 %d 개입니다.\n", accumulatedTicketNumber);
		printf("계산하실 금액은 총 %d 원입니다.\n", accumulatedFinalPrice);
		printf("****************************************\n");
		

	return 0;
}
