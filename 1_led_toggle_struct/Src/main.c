#include <stdint.h>

// Define memory-mapped register addresses
#define PERIPH_BASE         (0x40000000UL)
#define AHB1PERIPH_OFFSET   (0x00020000UL)
#define AHB1PERIPH_BASE     (PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET        (0x0000UL)
#define GPIOA_BASE          (AHB1PERIPH_BASE + GPIOA_OFFSET)
#define RCC_OFFSET          (0x3800UL)
#define RCC_BASE            (AHB1PERIPH_BASE + RCC_OFFSET)

// Define register offsets for GPIOA
#define GPIOA_MODER_OFFSET  (0x00UL)
#define GPIOA_ODR_OFFSET    (0x14UL)
#define RCC_AHB1ENR_OFFSET  (0x30UL)

// Define register pointers
#define GPIOA_MODER         (*(volatile uint32_t *)(GPIOA_BASE + GPIOA_MODER_OFFSET))
#define GPIOA_ODR           (*(volatile uint32_t *)(GPIOA_BASE + GPIOA_ODR_OFFSET))
#define RCC_AHB1ENR         (*(volatile uint32_t *)(RCC_BASE + RCC_AHB1ENR_OFFSET))

// Define constants
#define GPIOAEN             (1U << 0) // Enable bit for GPIOA
#define PIN5                (1U << 5) // Bit 5 for Pin 5

// GPIOA structure
typedef struct {
    uint32_t MODER;   // GPIO port mode register
    uint32_t ODR;     // GPIO port output data register
} GPIO_TypeDef;

// RCC structure
typedef struct {
    uint32_t AHB1ENR;  // RCC AHB1 peripheral clock enable register
} RCC_TypeDef;

int main(void) {
    // Initialize structures
    GPIO_TypeDef *GPIOA = (GPIO_TypeDef *)GPIOA_BASE;
    RCC_TypeDef *RCC = (RCC_TypeDef *)RCC_BASE;

    // 1. Enable the clock access to GPIOA
    RCC->AHB1ENR |= GPIOAEN;

    // 2. Set PA5 as an output pin
    GPIOA->MODER |= (1U << 10); // Set bit 10 to 1 to configure as an output
    GPIOA->MODER &= ~(1U << 11); // Clear bit 11 to configure as a general-purpose output

    while (1) {
        // 3. Toggle PA5 to turn the LED on and off
        GPIOA->ODR ^= PIN5;

        // Delay to control LED blink rate
        for (volatile uint32_t i = 0; i < 100000; i++) {
            // This loop provides a delay; adjust the value for your desired blink rate
        }
    }
}
