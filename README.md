# light-stick-repeater
light stick repeater


# EDP 조사 자료.
## EPD(Electronic Paper Display) 개요
https://docs.pervasivedisplays.com/epd-usage/epd-driving-sequence/small-epds

## 제품 데이터시트
https://www.pervasivedisplays.com/wp-content/uploads/2019/06/1P159-00_01_E2213HS091_20171031.pdf

## 핀 Out 확인 
    - [ ] 회로도와 코드 비교하여 핀번호 맞게 되어있는지 확인
    : PC6   ->  LCD_SI      Display SPI Data Pin
    : PC7   ->  LCD_REST_N  Display Reset Pin
    : PC8   ->  LCD_SCLK    Display SPI Clock Pin
    : PD14  ->  LCD_SCS     Display SPI Chip select Pin
    : PF0   ->  LCD_BS      ??
    : PF1   ->  LCD_DC      Display Data/Command Control Pin
    : PF2   <-  LCD_BUSY_N  Display Busy Pin

    - [ ] 질문사항    
    : 1. BS 핀은 용도가 뭘까?
    : 2. 회로도의 RST_N 회로는 무엇인가?
    : 3. SPI 통신 구현팁?
