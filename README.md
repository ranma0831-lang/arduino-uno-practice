# 아두이노 우노 실습

Arduino UNO R3로 LED, 버튼, 가변저항, 소리 센서, 7세그먼트를 다뤄 본 실습 기록입니다.
모든 스케치는 [Arduino CLI](https://arduino.github.io/arduino-cli/)로 컴파일하고 COM5에 연결된 우노에 올렸습니다.

## 정리 웹페이지

**https://ranma0831-lang.github.io/arduino-uno-practice/**

오늘 배운 내용을 그림과 함께 볼 수 있습니다. 원본은 [`docs/index.html`](docs/index.html)입니다.

- MCU · OS · GPIO 개념
- 보드 핀 배치 (핀을 누르면 설명이 나오는 보드 그림)
- 전원 넣는 방법과 전류 한계
- GPIO 네 가지 동작 (디지털 입출력, 아날로그 입력, PWM)
- 가변저항 · LED · 버튼(풀업, 풀다운, 내부 풀업) 결선
- 디바운싱, 상태 변화 감지, 인터럽트
- 네오픽셀, 7세그먼트
- 예제 7가지의 배선과 코드, 자주 하는 실수 10가지

## 폴더 구성

```
examples/   실습 예제 스케치
tests/      배선 문제를 찾을 때 쓴 진단용 스케치
wokwi/      Wokwi 시뮬레이터 프로젝트 (sketch.ino + diagram.json)
docs/       정리 웹페이지
```

## 예제

"확인"은 어디까지 동작을 확인했는지를 뜻합니다.

| 스케치 | 하는 일 | 배선 | 확인 |
|---|---|---|---|
| [`Blink`](examples/Blink) | 내장 LED를 1초 간격으로 깜빡임 | 없음 (D13 내장 LED) | 우노 |
| [`LedBlink`](examples/LedBlink) | LED를 0.5초 간격으로 깜빡임 | D13 → 220Ω → LED → GND | 우노 |
| [`TrafficLight`](examples/TrafficLight) | 초록 5초 → 노랑 2초 → 빨강 5초 반복 | D10 빨강, D9 노랑, D8 초록 (각각 220Ω) | 컴파일 |
| [`Potentiometer`](examples/Potentiometer) | 가변저항으로 LED 밝기 조절, 값을 시리얼로 출력 | 가변저항 5V · A0 · GND, D9 → 220Ω → LED | 우노 |
| [`ButtonCount`](examples/ButtonCount) | 버튼 누른 횟수를 시리얼로 출력 (상태 변화 감지) | D2 ↔ 버튼 ↔ GND (내부 풀업) | 컴파일 |
| [`SoundLed`](examples/SoundLed) | 소리가 나면 LED를 켜고, 조용해지고 1초 뒤 끔 | 센서 + → 5V, G → GND, AO → A0 / D8 → 220Ω → LED | 우노 |
| [`SoundTwoLed`](examples/SoundTwoLed) | 조용하면 빨간 LED, 소리가 들리면 초록 LED | 위와 같음 + D7 → 220Ω → 빨간 LED | 컴파일 |
| [`SegmentCounter`](examples/SegmentCounter) | 버튼을 누를 때마다 7세그먼트 숫자 0→9→0, LED 깜빡임 | D2~D8 → 220Ω → 세그먼트 a~g, COM → GND, D10 버튼, D11 LED | 우노 |
| [`NeoPixelChase`](examples/NeoPixelChase) | 네오픽셀 8개에 파란 점이 한 칸씩 이동 | 5V, GND, D6 → 330Ω → DIN | 컴파일 |
| [`RfidAccess`](examples/RfidAccess) | RC522로 카드를 읽어 등록된 카드면 초록, 아니면 빨강 | SDA D10, SCK D13, MOSI D11, MISO D12, RST D9, 3.3V, GND / D7 초록, D6 빨강 | 컴파일 |

`RfidAccess`의 허용 카드 UID(`DE AD BE EF`)는 예시 값입니다. 카드를 찍어 시리얼 모니터에 나온 UID로 바꿔야 합니다.

### Wokwi 시뮬레이터

| 프로젝트 | 하는 일 | 확인 |
|---|---|---|
| [`WokwiToggle`](wokwi/WokwiToggle) | 버튼을 누를 때마다 LED 토글 (`millis()` 디바운싱) | Wokwi에서 4번 눌러 켜짐 · 꺼짐 반복 확인 |
| [`WokwiBlink`](wokwi/WokwiBlink) | LED 0.5초 깜빡임 | 시뮬레이션 결과 확인 못 함 |

[wokwi.com](https://wokwi.com/projects/new/arduino-uno)에서 새 Uno 프로젝트를 열고 `sketch.ino`와 `diagram.json` 내용을 붙여 넣으면 됩니다.

## 진단용 스케치

| 스케치 | 용도 |
|---|---|
| [`FloatTest`](tests/FloatTest) | D2와 A0가 연결되어 있는지 확인. 내부 풀업을 켰다 껐다 하면서 값을 비교합니다 |
| [`SoundTest`](tests/SoundTest) | 소리 센서 AO의 50ms 구간 최소·최대값과 DO 상태 기록 |
| [`SegmentTest`](tests/SegmentTest) | 7세그먼트 막대를 D2부터 D8까지 하나씩 켜서 배선 확인 |
| [`GTest`](tests/GTest) | g 막대가 D8과 D9 중 어디에 연결됐는지 확인 |
| [`Empty`](tests/Empty) | 보드 멈추기 (모든 출력 끄기) |

## 업로드 방법

```bash
# 연결된 보드 찾기
arduino-cli board list

# 처음 한 번: 우노용 보드 패키지와 라이브러리 설치
arduino-cli core install arduino:avr
arduino-cli lib install MFRC522 "Adafruit NeoPixel"

# 컴파일 + 업로드 (폴더 이름과 .ino 파일 이름이 같아야 함)
arduino-cli compile --fqbn arduino:avr:uno -u -p COM5 examples/SoundLed

# 시리얼 모니터 (종료: Ctrl+C)
arduino-cli monitor -p COM5 -c baudrate=9600
```

## 실습하면서 겪은 문제

| 증상 | 원인 | 해결 |
|---|---|---|
| Wokwi에서 버튼을 눌러도 LED가 안 바뀜 | 손을 뗄 때 채터링으로 토글이 두 번 일어남 | `delay(50)` 대신 `millis()`로 50ms 동안 신호가 그대로일 때만 인정 |
| 소리 센서가 소리 없이 계속 반응 | 센서 선이 D2 대신 D1, A0 대신 A2에 꽂힘. 연결 안 된 핀이 60Hz 전기 잡음을 읽음 | 핀 위치를 고침. `FloatTest`로 0.2초에 24번(60Hz) 바뀌는 것을 확인 |
| 소리 센서 DO가 반대로 동작 | 이 모듈은 조용할 때 HIGH, 소리가 나면 LOW | DO 대신 AO 값(조용할 때 약 30, 박수 400 이상)으로 판단 |
| 바람을 불면 LED가 켜진 채로 남음 | 토글 방식은 긴 소리에 0.3초마다 켜짐과 꺼짐이 반복됨 | 소리 나는 동안만 켜고 1초 뒤 끄는 방식으로 변경 |
| 7세그먼트 숫자 몇 개가 이상함 | g 막대 선이 연결되지 않음. g를 쓰는 2, 3, 4, 5, 6, 8, 9만 이상하게 보임 | `SegmentTest`, `GTest`로 g 배선을 찾아 수정 |
| 업로드 중 COM5가 사라짐 | USB 연결이 끊김 (케이블이나 쇼트) | 케이블 확인 후 다시 연결 |
| 센서 전원이 안 들어감 | 긴 브레드보드의 전원 줄이 가운데에서 끊겨 있을 수 있음. USB 전원만 쓸 때 Vin은 전압이 거의 없음 | 위아래 전원 줄을 점퍼선으로 연결, 센서 전원은 5V에 연결 |

## 환경

- 보드: Arduino UNO R3 (ATmega328P, 5V, 16MHz)
- Arduino CLI, 보드 패키지 `arduino:avr` 1.8.8
- 라이브러리: MFRC522 1.4.12, Adafruit NeoPixel 1.15.5
