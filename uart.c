/*
Owner = Antonescu Radu-Ion
Year = 2016

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdarg.h>
#include "common.h"
#include "uart.h"
#include "st/stm32f10x.h"

void uart_handler(void)
{
    uart_printf("got uart int~!\r\n");
}

void uart_putc(const char c)
{
    while(!(USART1->SR & TXE));
    USART1->DR = c;
}

void uart_puts(const char *a)
{
    char *i;
    for (i = (char *)a; *i != '\0'; i++) {
        while(!(USART1->SR & TXE));
        USART1->DR = *i;
    }
}

/* clk PA8
 * tx  PA9
 * rx  PA10
 * cts PA11
 * rts PA12*/
void uart_init(void)
{
    /* Enable UART1*/
    USART1->CR1 |= (1<<13)|(1<<3)|(1<<2)|1;
    USART1->CR2 |= (1<<13); // (1<<11) - clk
    // pg 103 - apb1 - peripheral clock prescaler for uart
    USART1->BRR = ((PCLOCK) / (115200)); /* works at 115200*/
    USART1->CR1 |= 1<<13;
}

void uart_printf(const char *fmt, ...)
{
    char buf[11], pos, space;
    va_list args;

    va_start(args, fmt);
    for (; *fmt != '\0'; fmt++) {
        if (*fmt == '%') {
            fmt++;
            if (*fmt == '\0') break;
            if (*fmt == '0') {
                space = 0; /* use '0' instead */
                fmt++;
            } else {
                space = 1;
            }
            if (*fmt >= '0' && *fmt <= '9') {
                pos = *fmt - '0';
                fmt++;
            }
            switch (*fmt) {
                case 'd':
                    itoa(va_arg(args, int), buf, 10);
                    if (pos) {
                        int i;
                        for (i = 0; i < pos - strlen(buf); i++) {
                            if (space) {
                                uart_putc(' ');
                            } else {
                                uart_putc('0');
                            }
                        }
                    }
                    uart_puts(buf);
                break;
                case 'x':
                    itoa(va_arg(args, int), buf, 16);
                    if (pos) {
                        int i;
                        for (i = 0; i < pos - strlen(buf); i++) {
                            if (space) {
                                uart_putc(' ');
                            } else {
                                uart_putc('0');
                            }
                        }
                    }
                    uart_puts(buf);
                break;
                case 's':
                    uart_puts(va_arg(args, char*));
                break;
                case 'c':
                    uart_putc(va_arg(args, int));
                break;
                case '%':
                    uart_putc('%');
                break;
                default:
                    uart_putc(*fmt);
            }
            pos = 0;
        } else {
            uart_putc(*fmt);
        }
    }
    va_end(args);
}

