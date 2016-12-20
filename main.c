/*
Owner = Antonescu Radu-Ion
Year = 2016

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "common.h"
#include "uart.h"
#include "timer.h"

#include "st/stm32f10x.h"

uint32_t first_run = 1;

volatile uint32_t *NVIC_setEnableRegister = (void*)0xE000E100;

#define crit_err_msg uart_printf

void default_handler(void)
{
    while (1);
}

void _hard_fault()
{
    crit_err_msg(__func__);
    default_handler();
}

void _mem_manage()
{
    crit_err_msg(__func__);
    default_handler();
}

void _buf_fault()
{
    crit_err_msg(__func__);
    default_handler();
}

void _usage_fault()
{
    crit_err_msg(__func__);
    default_handler();
}


main()
{
    int i;

    /* init clock systems pclock, sysclock, ... 
     * APB Low set /2 MCO PLL clock out*/
    RCC->CR |= 1 << 16; // HSE on
    // Wait for external oscilator to become ready
    while ((RCC->CR & (1 << 17)) == 0);
    RCC->CR |= (1 << 19); /* clock security; if fail then go back to HSI */
    /* Main PLL x6 no div src ext osc
     * not exceed 50MHz! CD00171190.pdf pg 101
     * bit16 = use external oscilator as pll source*/
#ifdef USE_PLL
    RCC->CFGR |= (1 << 10)|(1 << 16)|(1 << 20)|(1 << 22)|(1 << 26); //MCO sysclk
#else
    RCC->CFGR |= (1 << 26); //MCO sysclk
#endif

#ifdef USE_PLL
    /* Start PLL */
    RCC->CR |= (1 << 24);
    while((RCC->CR & (1 << 25)) == 0);
    /* Connect PLL */
    RCC->CFGR |= 2;
#else
    /* Connect External Clock */
    RCC->CFGR |= 1;
#endif

    /* reset peripherals */
    //RCC->APB2RSTR |= (1<<14)|(1<<3)|(1<<2)|1;

    /* pg 115 start peripheral clock for UART1 GPIOA GPIOB AFIO */
    RCC->APB2ENR |= (1<<14)|(1<<2)|(1<<3)|1;
    // Unlock Port A!
    GPIOA->BSRR = 0xffff;
    /* enable MCO/UART CLK on PA8 - alternate function */
    /* enable UART PINs 8 = clk 9 = tx 10 = rx*/
    GPIOA->CRH &= ~((1 << 2)|(1 << 6));
    /* for MCO */
    GPIOA->CRH |= 1|(1<<1)|(1<<3);
    GPIOA->CRH |= (1<<1)|(1<<3)|(1<<5)|(1<<7);

    /* GPIO example
    GPIOB->BSRR = 0xffff;
    GPIOB->CRH &= ~(1 << 10);
    GPIOB->CRH |= 1 << 9;
    */

    uart_init();

    uart_printf("Init demo platform %s software ver. %d\r\n", "Radu", 1);

    RCC->APB1ENR |= 1;
    timer_init();

    while (1);
}

