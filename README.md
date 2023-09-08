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
