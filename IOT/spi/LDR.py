#-*-coding: utf-8 -*-

# 필요한 라이브러리를 불러옵니다.
import spidev
import time

# 딜레이 시간 (센서 측정 간격)
delay = 0.5

# MCP3008 채널 중 센서에 연결한 채널 설정
ldr_channel = 0

# SPI 인스턴스 api 설정
spi = spidev.SpiDev()

# SPI 통신 시작하기
spi.open(0, 0)

# SPI 통신 속도 설정
spi.max_speed_hz = 100000

# 0 ~ 7 까지 8개의 채널에서 SPI 데이터를 읽어서 반환
def readadc(adcnum):
    if adcnum > 7 or adcnum < 0:
        return -1
    r = spi.xfer2([6 + ((adcnum&0x4)>>2),(adcnum&0x3)<<6,0])
    data = ((r[1] & 15) << 8) + r[2]
    return data

while True:
    ldr_value = readadc(ldr_channel)
    print("--------------------------")
    print("LDR Value: %d" % ldr_value)
    time.sleep(delay)
