// Define memory-mapped register addresses
#define PERIPH_BASE         (0x40000000UL)
#define AHB1PERIPH_OFFSET   (0x00020000UL)
#define AHB1PERIPH_BASE     (PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET        (0x0000UL)
#define GPIOA_BASE          (AHB1PERIPH_BASE + GPIOA_OFFSET)
#define RCC_OFFSET          (0x3800UL)
#define RCC_BASE            (AHB1PERIPH_BASE + RCC_OFFSET)

// Define register offsets for GPIOA
#define GPIOA_MODE_R_OFFSET (0x00UL)
#define GPIOA_OD_R_OFFSET   (0x14UL)
#define RCC_AHB1EN_R_OFFSET (0x30UL)

// Define register pointers
#define GPIOA_MODE_R        (*(volatile unsigned int *)(GPIOA_BASE + GPIOA_MODE_R_OFFSET))
#define GPIOA_OD_R          (*(volatile unsigned int *)(GPIOA_BASE + GPIOA_OD_R_OFFSET))
#define RCC_AHB1EN_R        (*(volatile unsigned int *)(RCC_BASE + RCC_AHB1EN_R_OFFSET))

// Define constants
#define GPIOAEN             (1U << 0) // Enable bit for GPIOA
#define PIN5                (1U << 5) // Bit 5 for Pin 5
#define LED_PIN             PIN5      // LED is connected to Pin 5

int main(void) {
    // 1. Enable the clock access to GPIO A
    RCC_AHB1EN_R |= GPIOAEN;

    // 2. Set PA5 as an output pin
    GPIOA_MODE_R |= (1U << 10); // Set bit 10 to 1 to configure as an output
    GPIOA_MODE_R &= ~(1U << 11); // Clear bit 11 to configure as a general-purpose output

    while (1) {
        // 3. Set PA5 high to turn on the LED
        //GPIOA_OD_R |= LED_PIN;

        // Experiment 2 to toggle LED
    	GPIOA_OD_R ^= LED_PIN;
    	for(int i=0;i<100000;i++){}


    }
}
