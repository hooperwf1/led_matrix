#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#define ROWS 8
#define COLS 8
#define NUM_LEDS ROWS * COLS

#define SER PB0
#define RCLK PB1
#define SRCLK PB2

char stairs[COLS] = {1, 0b11, 0b111, 0b1111, 0b11111, 0b111111, 0b1111111, 0xff};
char smile[COLS] = {0b00111100, 0b01000010, 0b10101001, 0b10000101, 0b10000101, 0b10101001, 0b01000010, 0b00111100};
char skull[COLS] = {0b01111100, 0b11001111, 0b11001110, 0b11111011, 0b11111011, 0b11001110, 0b11001111, 0b01111100};
char creeper[COLS] = {0, 0b01100000, 0b01101110, 0b00011100, 0b00011100, 0b01101110, 0b01100000, 0};
char number[COLS] = {0, 0b01000000, 0b01111110, 0, 0b01111110, 0b01010010, 0b01111110, 0};

void init_shift(){
    DDRB = (1 << SER) | (1 << SRCLK) | (1 << RCLK);
}

void shift(char rows, char cols){
    //cols first
    char current = cols;
    for(int i = 0; i < 16; i++){
        if(i == 8){
            current = rows;
        }

        // Check if first bit set
        if(current & (1 << i%8)){
            PORTB |= (1 << SER); 
        } else {
            PORTB &= ~(1 << SER); 
        }

        PORTB |= (1 << SRCLK);
        _delay_us(1);
        PORTB &= ~(1 << SRCLK);
    }

    PORTB |= (1 << RCLK);
    _delay_us(1);
    PORTB &= ~(1 << RCLK);
}

void draw_board(char board[COLS]){
    for(int i = 0; i < COLS; i++){
        shift(board[i], 1 << i);
    }
}

int main(void){
    init_shift();
    PORTB = 0xff;

    while(1){
        draw_board(smile); 
    }
}
