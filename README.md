# Microprocessor
컴퓨터공학과 마이크로프로세서 실습 정리입니다.

![image](https://github.com/wonttan/Microprocessor/assets/58906858/9f83a623-0375-4f18-b6d3-845993470962)
```
#define PORTE
*(unsigned char)0x180
PORTE = 0x10100000

 16번지로 180번에 0xa0 < 이진수로 10100000

핀의 값을 PE7가 1부터 PE0까지 10100000

PD0 라이트 1꺼지고 0이되면 켜진다

PORTA~PORTB~~~PORTL <- #include <avr/io.h>에 PORT 입출력 장치와 대응시켜놨다.
PORTL 출력하기 위해서는 PORTL
읽을때는 x = PINL
DDRL <- 8비트 (Data Direction Register) < 0과1을 내보내는거 (라이트 출력) 입력용(0), 출력용(1) 입력용으로 쓸건지 출력용으로 쓸건지

3개의 레지스터가 정의되어있다. GPI 범용
```
## 23.09.15 Pjt_01
```
led.c 작성한 후에 led.h를 작성한다.
led.h에는 함수의 프로토타입을 작성하는 데 함수 반환 타입의 오류를 미연에 방지해준다.

main.c에 있는 것들을 led.c 파일로 쪼갠다.

진행 상태를 led로 확인할 수 있다. (led 몇 번을 상황에 따라 설정해서 오류 확인용도로 사용 가능)

unsigned char = uint8_t 
```
## 23.09.15 Pjt_02
![image](https://github.com/wonchihyeon/Microprocessor/assets/58906858/5eff7ee2-c3e4-4dca-99d8-dc1b1ca95e87)   
![image](https://github.com/wonchihyeon/Microprocessor/assets/58906858/200ceecd-7e40-46ed-9b00-9387d56324c4)    
![image](https://github.com/wonchihyeon/Microprocessor/assets/58906858/dc4ee003-5374-4cc1-b361-d7fd2c3c9514)    

```
USART(Universal Synchronous and Asynchronous serial Receiver and Transmitter) registers
serial : 직렬

UART (비동기 : 보내고싶을 때 보냄)

UART 총 4개가 있는데 0번 사용

8비트 레지스터에 쓰게 되면 보내겠다.
UDR0 = 'A'(쓰기)
A = UDR0 (읽기)
읽기/쓰기용도

전송된 것을 (A = UDR0)읽는 순간 소멸
쓰는 순간 전송 시작(UDR0 = A)

속도 조절 Speed
UBRRnL : 0L
UBRRnH : 0H

UCSRnA : Control Register 8비트

sbi(UCSR0A, U2X0) <- UCSR0A 레지스터의 U2XN(==1)번 비트를 1로 변경

cbi(UCSR0B, TXEN0) <- UCSR0B 레지스터의 TXEN0(==3)번 비트를 0으로 변경

끝의 숫자 N이 비트 번호임

개행문자 캐리지 리턴 하나 쓰고 새로운 줄에서
new line이 오면 뒤에 캐리지리턴도 따라서 보내도록 설정한다.

main함수에서 A부터 Z 까지 문자를 보내고 ABCDE~Z 까지 나오고 캐리지리턴을 반복

```
