/*
Owner = Antonescu Radu-Ion
Year = 2016

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "timer.h"
#include "st/stm32f10x.h"
#include "arm/irq.h"

void timer_resume(void);

void sys_tick_handler(void)	__attribute__((interrupt("IRQ")));

void sys_tick_handler(void) /* Timer 2 */
{
    uart_printf("timer fired!\r\n");
    timer_pause();
}


#ifndef PCLOCK
#define PCLOCK CPU_FREQ
#endif

volatile uint16_t *tim2_cr = &TIM2->CR1;

void timer_init(void)
{
    int i;
    
    /* pg. 362 */
    /*
    TIM2->PSC = 0xFFFF;
    TIM2->ARR = (30*PCLOCK/0xFFFF);
    TIM2->DIER |= 1<<6|1;
    asm volatile ("cpsie i");
    NVIC_enableIRQ(TIM2_IRQn);
    TIM2->CR1 = 1|1<<7|1<<3;*/

    STRELOAD = CPU_FREQ; /* once per second */
    STCURRENT = 0;
    STCTL |= (STEN | STINTEN);
}

void timer_pause(void)
{
    //TIM2->CR1 &= ~1;
    STCTL &= ~STINTEN;
}

void timer_resume(void)
{

    STCTL |= STINTEN;
}

