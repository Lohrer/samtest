#include <same70.h>

void delay(int n)
{
    int i;

    for (; n > 0; n--)
    {
        for (i = 0; i < 450; i++)
            __asm("nop");
    }
}

int main()
{
    // Enable PIOC's clock
    REG_PMC_PCR = ID_PIOC;
    REG_PMC_PCR |= PMC_PCR_EN | PMC_PCR_CMD;

    // Set PIOC8 as output (0 = intput, 1 = output)
    REG_PIOC_OER = PIO_PC8;
    REG_PIOC_OWER = PIO_PC8;

    while(1)
    {
        // Toggle PIOC8
        REG_PIOC_CODR = PIO_PC8; // Clear output
        delay(500);
        REG_PIOC_SODR = PIO_PC8; // Set output
        delay(500);
    }
}
